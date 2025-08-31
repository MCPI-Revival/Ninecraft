#include <SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <ancmp/android_atomic.h>

#define AUDIO_ENGINE_MAX_STREAMS 64

#define PCM_S 1
#define PCM_U 2
#define PCM_F 3
#define PCM_BE 1
#define PCM_LE 2

typedef struct {
    bool active;
    uint8_t *buffer;
    uint32_t buffer_size;
    uint32_t num_channels;
    uint32_t bits_per_sample;
    uint32_t freq;
    uint32_t format;
    uint32_t endianess;
    float gain;
    float pitch;
    uint32_t frame_size;
    uint32_t frame_count;
    float sample_pos;
    float rate_ratio;
} audio_engine_stream_t;

static audio_engine_stream_t audio_engine_streams[AUDIO_ENGINE_MAX_STREAMS];
static SDL_AudioDeviceID audio_engine_device = 0;
static SDL_AudioSpec audio_engine_audio_spec;

static bool audio_engine_initialized = false;

uint8_t *audio_engine_buffer = NULL;
volatile int is_full = 0;

static float audio_engine_decode_sample(uint8_t *sample_data, uint32_t sample_size, uint32_t format) {
    float sample = 0;
    if (sample_size == 1 && format == PCM_S) {
        int8_t tmp;
        memcpy(&tmp, sample_data, sizeof(tmp));
        sample = (float)tmp;
        sample /= 128.0;
    } else if (sample_size == 2 && format == PCM_S) {
        int16_t tmp;
        memcpy(&tmp, sample_data, sizeof(tmp));
        sample = (float)tmp;
        sample /= 32768.0;
    } else if (sample_size == 4 && format == PCM_S) {
        int32_t tmp;
        memcpy(&tmp, sample_data, sizeof(tmp));
        sample = (float)tmp;
        sample /= 2147483648.0;
    } else if (sample_size == 1 && format == PCM_U) {
        uint8_t tmp;
        memcpy(&tmp, sample_data, sizeof(tmp));
        sample = (float)tmp;
        sample -= 128.0;
        sample /= 128.0;
    } else if (sample_size == 2 && format == PCM_U) {
        uint16_t tmp;
        memcpy(&tmp, sample_data, sizeof(tmp));
        sample = (float)tmp;
        sample -= 32768.0;
        sample /= 32768.0;
    } else if (sample_size == 4 && format == PCM_U) {
        uint32_t tmp;
        memcpy(&tmp, sample_data, sizeof(tmp));
        sample = (float)tmp;
        sample -= 2147483648.0;
        sample /= 2147483648.0;
    } else if (sample_size == 4 && format == PCM_F) {
        memcpy(&sample, sample_data, sizeof(sample));
    }
    return sample;
}

static void audio_engine_mix(audio_engine_stream_t *stream, Uint8 *out_stream, int len) {
    int sample_count = len / 4;
    int sample_size = stream->bits_per_sample / 8;
    float *out = (float *)out_stream;
    for (int i = 0; i < sample_count; i += audio_engine_audio_spec.channels) {
        size_t frame_pos = (size_t)stream->sample_pos;
        if (frame_pos >= stream->frame_count - 1) {
            stream->active = false;
            break;
        }
        float frac = stream->sample_pos - (float)frame_pos;
        uint8_t *frame1 = &stream->buffer[frame_pos * stream->frame_size];
        uint8_t *frame2 = &stream->buffer[(frame_pos + 1) * stream->frame_size];
        uint32_t num_channels = (stream->num_channels < audio_engine_audio_spec.channels) ? audio_engine_audio_spec.channels : stream->num_channels;

        for (int ch = 0; ch < num_channels; ++ch) {
            size_t idx1 = i + (ch % audio_engine_audio_spec.channels);
            size_t idx2 = (ch % stream->num_channels) * sample_size;
            float sample1 = audio_engine_decode_sample(&frame1[idx2], sample_size, stream->format);
            float sample2 = audio_engine_decode_sample(&frame2[idx2], sample_size, stream->format);
            float interpolated = sample1 + (sample2 - sample1) * frac;

            interpolated *= stream->gain;
            out[idx1] += interpolated;

            if (out[idx1] > 1.0f) {
                out[idx1] = 1.0f;
            }
            if (out[idx1] < -1.0f) {
                out[idx1] = -1.0f;
            }
        }
        stream->sample_pos += stream->rate_ratio;
    }
    if ((uint32_t)stream->sample_pos >= stream->frame_count) {
        stream->active = false;
    }
}

static void SDLCALL audio_engine_audio_callback(void *userdata, Uint8 *stream, int len) {
    memset(stream, 0, len);
    if (!android_atomic_cmpxchg(1, 1, &is_full)) {
        memcpy(stream, audio_engine_buffer, len);
        android_atomic_cmpxchg(1, 0, &is_full);
    }
    for (int i = 0; i < AUDIO_ENGINE_MAX_STREAMS; ++i) {
        audio_engine_stream_t *audio_engine_stream = &audio_engine_streams[i];
        if (audio_engine_stream->active) {
            audio_engine_mix(audio_engine_stream, stream, len);
        }
    }
}

void audio_engine_write(uint8_t *buffer, uint32_t buffer_size, uint32_t num_channels, uint32_t bits_per_sample, uint32_t freq, uint32_t format, uint32_t endianess, float gain, float pitch) {
    if (audio_engine_initialized && buffer && buffer_size) {
        int sample_size = bits_per_sample / 8;
        uint32_t frame_size = (bits_per_sample / 8) * num_channels;
        uint32_t frame_count = buffer_size / frame_size;
        float sample_pos = 0;
        float rate_ratio = ((float)freq * pitch) / (float)audio_engine_audio_spec.freq;

        size_t out_frame_count = (size_t)((float)frame_count / rate_ratio) + 1;
        size_t out_sample_count = out_frame_count * audio_engine_audio_spec.channels;
        size_t out_stream_size = out_sample_count * sizeof(float);
        float *out_stream = (float *)calloc(out_stream_size, 1);

        if (!out_stream) {
            return;
        }

        for (int i = 0; i < out_sample_count; i += audio_engine_audio_spec.channels) {
            size_t frame_pos = (size_t)sample_pos;
            if (frame_pos >= frame_count - 1) {
                break;
            }
            float frac = sample_pos - (float)frame_pos;
            uint8_t *frame1 = &buffer[frame_pos * frame_size];
            uint8_t *frame2 = &buffer[(frame_pos + 1) * frame_size];
            uint32_t max_channels = (num_channels < audio_engine_audio_spec.channels) ? audio_engine_audio_spec.channels : num_channels;

            for (int ch = 0; ch < max_channels; ++ch) {
                size_t idx1 = i + (ch % audio_engine_audio_spec.channels);
                size_t idx2 = (ch % num_channels) * sample_size;
                float sample1 = audio_engine_decode_sample(&frame1[idx2], sample_size, format);
                float sample2 = audio_engine_decode_sample(&frame2[idx2], sample_size, format);
                float interpolated = sample1 + (sample2 - sample1) * frac;

                interpolated *= gain;
                out_stream[idx1] = interpolated;
            }
            sample_pos += rate_ratio;
        }

        size_t c = out_stream_size / audio_engine_audio_spec.size;
        size_t len_nr = c * audio_engine_audio_spec.size;
        size_t remaining = out_stream_size - len_nr;

        for (int i = 0; i < c; ++i) {
            while (android_atomic_cmpxchg(0, 1, &is_full)) {
            }
            SDL_LockAudioDevice(audio_engine_device);
            memcpy(audio_engine_buffer, &out_stream[i * audio_engine_audio_spec.size], audio_engine_audio_spec.size);
            SDL_UnlockAudioDevice(audio_engine_device);
        }
        if (remaining) {
            while (android_atomic_cmpxchg(0, 1, &is_full)) {
            }
            SDL_LockAudioDevice(audio_engine_device);
            memcpy(audio_engine_buffer, &out_stream[len_nr], remaining);
            SDL_UnlockAudioDevice(audio_engine_device);
        }
        
        free(out_stream);
    }
}

void audio_engine_init() {
    if (!audio_engine_initialized) {
        SDL_AudioSpec desired_spec;

        if (SDL_Init(SDL_INIT_AUDIO) < 0) {
            printf("SDL_Init Audio failed: %s\n", SDL_GetError());
            return;
        }

        memset(&desired_spec, 0, sizeof(desired_spec));
        memset(&audio_engine_audio_spec, 0, sizeof(audio_engine_audio_spec));

        desired_spec.freq = 44100;
        desired_spec.format = AUDIO_F32LSB;
        desired_spec.channels = 2;
        desired_spec.samples = 1024;
        desired_spec.callback = audio_engine_audio_callback;

        audio_engine_device = SDL_OpenAudioDevice(NULL, 0, &desired_spec, &audio_engine_audio_spec, 0);

        if (!audio_engine_device) {
            printf("SDL_OpenAudioDevice failed: %s\n", SDL_GetError());
            return;
        }

        audio_engine_buffer = calloc(audio_engine_audio_spec.size, 1);
        if (!audio_engine_buffer) {
            puts("Failed to allocate memory");
            return;
        }

        SDL_PauseAudioDevice(audio_engine_device, 0);
        memset(audio_engine_streams, 0, sizeof(audio_engine_streams));
        audio_engine_initialized = true;
    }
}

void audio_engine_destroy() {
    if (audio_engine_initialized) {
        if (audio_engine_device) {
            SDL_CloseAudioDevice(audio_engine_device);
            audio_engine_device = 0;
        }
        SDL_QuitSubSystem(SDL_INIT_AUDIO);
        audio_engine_initialized = false;
    }
}

void audio_engine_tick() {} // this is a stub and should not be modified

void audio_engine_play(uint8_t *buffer, uint32_t buffer_size, uint32_t num_channels, uint32_t bits_per_sample, uint32_t freq, uint32_t format, uint32_t endianess, float gain, float pitch) {
    if (audio_engine_initialized && buffer && buffer_size) {
        SDL_LockAudioDevice(audio_engine_device);
        for (int i = 0; i < AUDIO_ENGINE_MAX_STREAMS; ++i) {
            audio_engine_stream_t *audio_engine_stream = &audio_engine_streams[i];
            if (!audio_engine_stream->active) {
                audio_engine_stream->active = true;
                audio_engine_stream->buffer = buffer;
                audio_engine_stream->buffer_size = buffer_size;
                audio_engine_stream->num_channels = num_channels;
                audio_engine_stream->bits_per_sample = bits_per_sample;
                audio_engine_stream->freq = freq;
                audio_engine_stream->format = format;
                audio_engine_stream->endianess = endianess;
                audio_engine_stream->gain = gain;
                audio_engine_stream->pitch = pitch;
                audio_engine_stream->frame_size = (bits_per_sample / 8) * num_channels;
                audio_engine_stream->frame_count = buffer_size / audio_engine_stream->frame_size;
                audio_engine_stream->sample_pos = 0;
                audio_engine_stream->rate_ratio = ((float)freq * pitch) / (float)audio_engine_audio_spec.freq;
                break;
            }
        }
        SDL_UnlockAudioDevice(audio_engine_device);
    }
}
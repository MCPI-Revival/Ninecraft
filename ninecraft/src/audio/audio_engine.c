#include <ninecraft/audio/audio_engine.h>
#include <stdio.h>

bool audio_engine_is_inited = false;
ALCdevice *audio_engine_device = NULL;
ALCcontext *audio_engine_context = NULL;
source_queue_t audio_engine_active_sources;
source_queue_t audio_engine_idle_sources;

void audio_engine_delete_sources_callback(ALuint source, ALuint buffer, bool *stop, bool *delete_entry) {
    if (source && alIsSource(source)) {
        alDeleteSources(1, &source);
    }
    if (buffer && alIsBuffer(buffer)) {
        alDeleteBuffers(1, &buffer);
    }
    *delete_entry = true;
}

void audio_engine_tick_sources_callback(ALuint source, ALuint buffer, bool *stop, bool *delete_entry) {
    if (source && alIsSource(source)) {
        ALint source_state;
        alGetSourcei(source, AL_SOURCE_STATE, &source_state);
        if (source_state != AL_PLAYING) {
            alSourcei(source, AL_BUFFER, 0);
            if (audio_engine_idle_sources.size < 50) {
                source_queue_push(&audio_engine_idle_sources, source, buffer);
            } else {
                alDeleteSources(1, &source);
                if (buffer && alIsBuffer(buffer)) {
                    alDeleteBuffers(1, &buffer);
                }
            }
            *delete_entry = true;
        }
    }
}

void audio_engine_init() {
    if (!audio_engine_is_inited) {
        ALCenum alc_err;

        if (!source_queue_init(&audio_engine_active_sources)) {
            puts("[AUDIO_ENGINE] Failed to initialize the active sources queue");
            return;
        }
        if (!source_queue_init(&audio_engine_idle_sources)) {
            puts("[AUDIO_ENGINE] Failed to initialize the idle sources queue");
            return;
        }
        audio_engine_device = alcOpenDevice(NULL);
        if (!audio_engine_device) {
            puts("[AUDIO_ENGINE] Failed to open device");
            return;
        }
        audio_engine_context = alcCreateContext(audio_engine_device, NULL);
        if (!audio_engine_context) {
            puts("[AUDIO_ENGINE] Failed to create context");
            return;
        }
        
        if (!alcMakeContextCurrent(audio_engine_context)) {
            puts("[AUDIO_ENGINE] Failed to set context");
            return;
        }
        audio_engine_is_inited = true;
    }
}

void audio_engine_destroy() {
    if (audio_engine_is_inited) {
        audio_engine_is_inited = false;
        source_queue_iterate(&audio_engine_active_sources, audio_engine_delete_sources_callback);
        source_queue_iterate(&audio_engine_idle_sources, audio_engine_delete_sources_callback);
        
        if (!alcMakeContextCurrent(NULL)) {
            puts("[AUDIO_ENGINE] Failed to set context");
            return;
        }
        alcDestroyContext(audio_engine_context);
        if (!alcCloseDevice(audio_engine_device)) {
            puts("[AUDIO_ENGINE] Failed to close device");
            return;
        }
    }
}

void audio_engine_tick() {
    if (audio_engine_is_inited) {
        source_queue_iterate(&audio_engine_active_sources, audio_engine_tick_sources_callback);
    }
}

void audio_engine_play(uint8_t *buffer, uint32_t buffer_size, uint32_t num_channels, uint32_t bits_per_sample, uint32_t freq, float gain, float pitch) {
    if (audio_engine_is_inited) {
        ALenum err;
        ALuint al_source, al_buffer;
        ALenum format = AL_NONE;
        
        if (!source_queue_pop(&audio_engine_idle_sources, &al_source, &al_buffer)) {
            alGenSources(1, &al_source);
            err = alGetError();
            if (err != AL_NO_ERROR) {
                puts("[AUDIO_ENGINE] Failed to generate source");
                if (al_source || alIsSource(al_source)) {
                    alDeleteSources(1, &al_source);
                }
                return;
            }
            alGenBuffers(1, &al_buffer);
            err = alGetError();
            if (err != AL_NO_ERROR) {
                puts("[AUDIO_ENGINE] Failed to generate buffer");
                if (al_buffer || alIsBuffer(al_buffer)) {
                    alDeleteBuffers(1, &al_buffer);
                }
                return;
            }
        }

        if (num_channels == 1) {
            format = bits_per_sample == 16 ? AL_FORMAT_MONO16 : AL_FORMAT_MONO8;
        }
        else if (num_channels == 2) {
            format = bits_per_sample == 16 ? AL_FORMAT_STEREO16 : AL_FORMAT_STEREO8;
        }

        alBufferData(al_buffer, format, buffer, buffer_size, freq);
        err = alGetError();
        if (err != AL_NO_ERROR) {
            puts("[AUDIO_ENGINE] Failed to load buffer");
            if (al_buffer || alIsBuffer(al_buffer)) {
                alDeleteBuffers(1, &al_buffer);
            }
            return;
        }

        alSourcei(al_source, AL_LOOPING, AL_FALSE);
        err = alGetError();
        if (err != AL_NO_ERROR) {
            puts("[AUDIO_ENGINE] Failed to disable looping on source");
            if (al_source || alIsSource(al_source)) {
                alDeleteSources(1, &al_source);
            }
            alDeleteBuffers(1, &al_buffer);
            return;
        }
        alSource3f(al_source, AL_POSITION, 0.0f, 0.0f, 0.0f);
        err = alGetError();
        if (err != AL_NO_ERROR) {
            puts("[AUDIO_ENGINE] Failed to set position on source");
            if (al_source || alIsSource(al_source)) {
                alDeleteSources(1, &al_source);
            }
            alDeleteBuffers(1, &al_buffer);
            return;
        }
        alSource3f(al_source, AL_VELOCITY, 0.0f, 0.0f, 0.0f);
        err = alGetError();
        if (err != AL_NO_ERROR) {
            puts("[AUDIO_ENGINE] Failed to set velocity on source");
            if (al_source || alIsSource(al_source)) {
                alDeleteSources(1, &al_source);
            }
            alDeleteBuffers(1, &al_buffer);
            return;
        }
        alSourcei(al_source, AL_SOURCE_RELATIVE, AL_TRUE);
        err = alGetError();
        if (err != AL_NO_ERROR) {
            puts("[AUDIO_ENGINE] Failed to set relativity on source");
            if (al_source || alIsSource(al_source)) {
                alDeleteSources(1, &al_source);
            }
            alDeleteBuffers(1, &al_buffer);
            return;
        }
        alSourcef(al_source, AL_GAIN, gain);
        err = alGetError();
        if (err != AL_NO_ERROR) {
            puts("[AUDIO_ENGINE] Failed to set gain on source");
            if (al_source || alIsSource(al_source)) {
                alDeleteSources(1, &al_source);
            }
            alDeleteBuffers(1, &al_buffer);
            return;
        }

        alSourcef(al_source, AL_PITCH, pitch);
        err = alGetError();
        if (err != AL_NO_ERROR) {
            puts("[AUDIO_ENGINE] Failed to set gain on source");
            if (al_source || alIsSource(al_source)) {
                alDeleteSources(1, &al_source);
            }
            alDeleteBuffers(1, &al_buffer);
            return;
        }

        alSourcei(al_source, AL_BUFFER, al_buffer);
        err = alGetError();
        if (err != AL_NO_ERROR) {
            puts("[AUDIO_ENGINE] Failed to set buffer on source");
            if (al_source || alIsSource(al_source)) {
                alDeleteSources(1, &al_source);
            }
            alDeleteBuffers(1, &al_buffer);
            return;
        }
        alSourcePlay(al_source);
        err = alGetError();
        if (err != AL_NO_ERROR) {
            puts("[AUDIO_ENGINE] Failed to play on source");
            if (al_source || alIsSource(al_source)) {
                alDeleteSources(1, &al_source);
            }
            alDeleteBuffers(1, &al_buffer);
            return;
        }
        source_queue_push(&audio_engine_active_sources, al_source, al_buffer);
    }
}
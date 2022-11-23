#pragma once

#include <AL/al.h>
#include <AL/alc.h>
#include <stdbool.h>

typedef struct {
    ALCdevice *device;
    ALCcontext *context;
} audio_engine_t;

struct pcm_metadata {
    int32_t channels;
    int32_t frame_size;
    int32_t sample_rate;
    int32_t frames;
};

bool audio_engine_create_audio_device(audio_engine_t *audio_engine);

bool audio_engine_destroy_audio_device(audio_engine_t *audio_engine);

ALuint audio_engine_create_sound_effect(void *symbol);

void audio_engine_play(ALuint buffer);
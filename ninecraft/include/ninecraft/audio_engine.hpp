#pragma once

#include <AL/al.h>
#include <AL/alc.h>

#ifdef __cplusplus
extern "C" {
#endif

int audio_engine_create_audio_device(ALCdevice **device, ALCcontext **context);

int audio_engine_destroy_audio_device(ALCdevice **device, ALCcontext **context);

ALuint audio_engine_create_sound_effect(void *symbol);

void audio_engine_play(ALuint buffer);

#ifdef __cplusplus
}
#endif
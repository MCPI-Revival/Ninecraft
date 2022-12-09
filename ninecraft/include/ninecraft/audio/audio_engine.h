#ifndef NINECRAFT_AUDIO_AUDIO_ENGINE_H
#define NINECRAFT_AUDIO_AUDIO_ENGINE_H

#include <AL/al.h>
#include <AL/alc.h>
#include <stdbool.h>

struct _audio_engine_source_map_entry;

typedef struct _audio_engine_source_map_entry {
    ALuint source;
    struct _audio_engine_source_map_entry *next;
} audio_engine_source_map_entry_t;

typedef struct {
    audio_engine_source_map_entry_t *entries;
} audio_engine_source_map_t;

typedef struct {
    ALCdevice *device;
    ALCcontext *context;
    char *buffer_names[100];
    ALuint buffers[100];
    size_t buffer_index;
    audio_engine_source_map_t sources;
    audio_engine_source_map_t idle_sources;
    bool is_initialized;
} audio_engine_t;

typedef struct {
    int32_t channels;
    int32_t frame_size;
    int32_t sample_rate;
    int32_t frames;
} audio_engine_pcm_metadata_t;

void audio_engine_source_map_init(audio_engine_source_map_t *source_map);

void audio_engine_source_map_push(audio_engine_source_map_t *source_map, ALuint source);

ALuint audio_engine_source_map_pop(audio_engine_source_map_t *source_map);

void audio_engine_source_map_destroy(audio_engine_source_map_t *source_map);

size_t audio_engine_source_map_size(audio_engine_source_map_t *source_map);

bool audio_engine_create_audio_device(audio_engine_t *audio_engine);

void audio_engine_delete_buffers(audio_engine_t *audio_engine);

bool audio_engine_destroy_audio_device(audio_engine_t *audio_engine);

ALuint audio_engine_load_sound(char *name, void *handle);

ALuint audio_engine_get_buffer(audio_engine_t *audio_engine, char *name, void *handle);

void audio_engine_play(audio_engine_t *audio_engine, void *handle, char *name, float x, float y, float z, float volume, float pitch, bool is_ui);

void audio_engine_update(audio_engine_t *audio_engine, float volume, float x, float y, float z, float yaw);

#endif
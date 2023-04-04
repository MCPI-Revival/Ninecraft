#ifndef NINECRAFT_AUDIO_SOUND_REPOSITORY_H
#define NINECRAFT_AUDIO_SOUND_REPOSITORY_H

#include <stddef.h>
#include <stdint.h>

typedef struct {
    char *name;
    uint8_t *buffer;
    size_t buffer_size;
    int freq;
    int num_channels;
    int bits_per_sample;
} ninecraft_sound_resource_t;

typedef struct {
    ninecraft_sound_resource_t a;
    ninecraft_sound_resource_t b;
    ninecraft_sound_resource_t c;
    ninecraft_sound_resource_t d;
} ninecraft_sound_resources_t;

typedef struct {
    char *name;
    size_t resources_count;
    ninecraft_sound_resources_t resources;
} ninecraft_sound_t;

ninecraft_sound_resource_t *ninecraft_get_sound_buffer(char *name);

#endif
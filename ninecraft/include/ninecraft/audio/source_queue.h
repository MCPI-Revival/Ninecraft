#ifndef NINECRAFT_AUDIO_SOURCE_QUEUE_H
#define NINECRAFT_AUDIO_SOURCE_QUEUE_H

#include <AL/al.h>
#include <stddef.h>
#include <stdbool.h>

#define SOURCE_QUEUE_INIT {NULL, 0}

typedef struct source_queue_entry_ {
    struct source_queue_entry_ *next;
    ALuint source;
    ALuint buffer;
} source_queue_entry_t;

typedef struct {
    source_queue_entry_t *sources;
    size_t size;
} source_queue_t;

typedef void (*source_queue_callback_t)(source_queue_entry_t *current, source_queue_entry_t *previous, bool *stop, bool *delete_entry);

bool source_queue_push(source_queue_t *queue, ALuint source, ALuint buffer);

bool source_queue_pop(source_queue_t *queue, ALuint *source);

void source_queue_iterate(source_queue_t *queue, source_queue_callback_t callback);

#endif
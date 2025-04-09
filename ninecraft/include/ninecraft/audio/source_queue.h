#ifndef NINECRAFT_AUDIO_SOURCE_QUEUE_H
#define NINECRAFT_AUDIO_SOURCE_QUEUE_H

#include <AL/al.h>
#include <stddef.h>
#include <stdbool.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif

typedef struct source_queue_entry_ {
    struct source_queue_entry_ *next;
    struct source_queue_entry_ *prev;
    ALuint source;
    ALuint buffer;
} source_queue_entry_t;

typedef struct {
    source_queue_entry_t *sources;
    size_t size;
#ifdef _WIN32
    HANDLE lock;
#else
    pthread_mutex_t lock;
#endif
} source_queue_t;

typedef void (*source_queue_callback_t)(ALuint source, ALuint buffer, bool *stop, bool *delete_entry);

bool source_queue_init(source_queue_t *queue);

bool source_queue_push(source_queue_t *queue, ALuint source, ALuint buffer);

bool source_queue_pop(source_queue_t *queue, ALuint *source, ALuint *buffer);

void source_queue_iterate(source_queue_t *queue, source_queue_callback_t callback);

#endif
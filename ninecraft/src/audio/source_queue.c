#include <ninecraft/audio/source_queue.h>
#include <stdlib.h>

bool source_queue_init(source_queue_t *queue) {
    queue->sources = NULL;
    queue->size = 0;
#ifdef _WIN32
    queue->lock = CreateMutex(NULL, FALSE, NULL);
    if (queue->lock == NULL) {
        return false;
    }
#else
    if (pthread_mutex_init(&queue->lock, NULL) != 0) {
        return false;
    }
#endif
    return true;
}

bool source_queue_push(source_queue_t *queue, ALuint source, ALuint buffer) {
    source_queue_entry_t *entry;

    if (!queue) {
        return false;
    }
    entry = (source_queue_entry_t *)malloc(sizeof(source_queue_entry_t));
    if (!entry) {
        return false;
    }
    entry->source = source;
    entry->buffer = buffer;
    entry->prev = NULL;
#ifdef _WIN32
    WaitForSingleObject(queue->lock, INFINITE);
#else
    pthread_mutex_lock(&queue->lock);
#endif
    entry->next = queue->sources;
    if (queue->sources) {
        queue->sources->prev = entry;
    }
    queue->sources = entry;
    ++queue->size;
#ifdef _WIN32
    ReleaseMutex(queue->lock);
#else
    pthread_mutex_unlock(&queue->lock);
#endif
    return true;
}

bool source_queue_pop(source_queue_t *queue, ALuint *source, ALuint *buffer) {
    source_queue_entry_t *entry;

    if (!queue) {
        return false;
    }
#ifdef _WIN32
    WaitForSingleObject(queue->lock, INFINITE);
#else
    pthread_mutex_lock(&queue->lock);
#endif
    entry = queue->sources;
    if (!entry) {
#ifdef _WIN32
        ReleaseMutex(queue->lock);
#else
        pthread_mutex_unlock(&queue->lock);
#endif
        return false;
    }
    queue->sources = entry->next;
    --queue->size;
    *source = entry->source;
    *buffer = entry->buffer;
    if (queue->sources) {
        queue->sources->prev = NULL;
    }
    free(entry);
#ifdef _WIN32
    ReleaseMutex(queue->lock);
#else
    pthread_mutex_unlock(&queue->lock);
#endif
    return true;
}

void source_queue_iterate(source_queue_t *queue, source_queue_callback_t callback) {
    source_queue_entry_t *entry, *current;
    bool stop = false;

#ifdef _WIN32
    WaitForSingleObject(queue->lock, INFINITE);
#else
    pthread_mutex_lock(&queue->lock);
#endif
    entry = queue->sources;

    while (entry != NULL && !stop) {
        bool delete_entry = false;

        current = entry;
        entry = entry->next;
        callback(current->source, current->buffer, &stop, &delete_entry);
        if (delete_entry) {
            if (current->prev == NULL && current->next == NULL) {
                queue->sources = NULL;
            } else if (current->prev == NULL) {
                queue->sources = current->next;
                queue->sources->prev = NULL;
            } else if (current->next == NULL) {
                current->prev->next = NULL;
            } else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }
            free(current);
            --queue->size;
        }
    }
#ifdef _WIN32
    ReleaseMutex(queue->lock);
#else
    pthread_mutex_unlock(&queue->lock);
#endif
}
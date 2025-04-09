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
    source_queue_entry_t *entry = (source_queue_entry_t *)malloc(sizeof(source_queue_entry_t));
    if (!entry || !queue) {
        return false;
    }
    entry->source = source;
    entry->buffer = buffer;
    entry->prev = NULL;
    entry->next = queue->sources;
    queue->sources = entry;
    ++queue->size;
    return true;
}

bool source_queue_pop(source_queue_t *queue, ALuint *source, ALuint *buffer) {
    source_queue_entry_t *entry;

    if (!queue) {
        return false;
    }
    entry = queue->sources;
    if (!entry) {
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
    return true;
}

void source_queue_iterate(source_queue_t *queue, source_queue_callback_t callback) {
    source_queue_entry_t *entry = queue->sources;
    source_queue_entry_t *current;
    bool stop = false;

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
}
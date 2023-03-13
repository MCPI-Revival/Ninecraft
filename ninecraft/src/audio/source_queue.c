#include <ninecraft/audio/source_queue.h>
#include <stdlib.h>

bool source_queue_push(source_queue_t *queue, ALuint source, ALuint buffer) {
    source_queue_entry_t *entry = (source_queue_entry_t *)malloc(sizeof(source_queue_entry_t));
    if (entry != NULL) {
        entry->next = queue->sources;
        entry->source = source;
        entry->buffer = buffer;
        queue->sources = entry;
        ++queue->size;
        return true;
    }
    return false;
}

bool source_queue_pop(source_queue_t *queue, ALuint *source) {
    source_queue_entry_t *entry = queue->sources;
    if (entry != NULL) {
        *source = entry->source;
        queue->sources = entry->next;
        free(entry);
        --queue->size;
        return true;
    }
    return false;
}

void source_queue_iterate(source_queue_t *queue, source_queue_callback_t callback) {
    source_queue_entry_t *current_entry = queue->sources;
    source_queue_entry_t *previous_entry = NULL;
    bool stop = false;
    bool delete_entry = false;
    while (current_entry != NULL && !stop) {
        source_queue_entry_t *next_entry = current_entry->next;
        callback(current_entry, previous_entry, &stop, &delete_entry);

        if (delete_entry) {
            --queue->size;
            if (previous_entry == NULL) {
                queue->sources = next_entry;
            } else {
                previous_entry->next = next_entry;
            }
            free(current_entry);
        } else {
            previous_entry = current_entry;
        }
        current_entry = next_entry;
    }
}
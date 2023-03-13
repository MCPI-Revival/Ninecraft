#ifndef NINECRAFT_AUDIO_AUDIO_ENGINE_H
#define NINECRAFT_AUDIO_AUDIO_ENGINE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <ninecraft/audio/source_queue.h>
#include <AL/alc.h>

extern bool audio_engine_is_inited;
extern ALCdevice *audio_engine_device;
extern ALCcontext *audio_engine_context;
extern source_queue_t audio_engine_active_sources;
extern source_queue_t audio_engine_idle_sources;

void audio_engine_delete_sources_callback(source_queue_entry_t *current, source_queue_entry_t *previous, bool *stop, bool *delete_entry);

void audio_engine_tick_sources_callback(source_queue_entry_t *current, source_queue_entry_t *previous, bool *stop, bool *delete_entry);

void audio_engine_init();

void audio_engine_destroy();

void audio_engine_tick();

void audio_engine_play(uint8_t *buffer, uint32_t buffer_size, uint32_t num_channels, uint32_t bits_per_sample, uint32_t freq, float gain);

#endif
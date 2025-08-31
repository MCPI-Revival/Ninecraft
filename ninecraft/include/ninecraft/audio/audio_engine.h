#ifndef NINECRAFT_AUDIO_AUDIO_ENGINE_H
#define NINECRAFT_AUDIO_AUDIO_ENGINE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

void audio_engine_write(uint8_t *buffer, uint32_t buffer_size, uint32_t num_channels, uint32_t bits_per_sample, uint32_t freq, uint32_t format, uint32_t endianess, float gain, float pitch);

void audio_engine_init();

void audio_engine_destroy();

void audio_engine_tick();

void audio_engine_play(uint8_t *buffer, uint32_t buffer_size, uint32_t num_channels, uint32_t bits_per_sample, uint32_t freq, uint32_t format, uint32_t endianess, float gain, float pitch);

#endif
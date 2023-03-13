#ifndef NINECRAFT_AUDIO_SLES_H
#define NINECRAFT_AUDIO_SLES_H

#include <stdint.h>

struct sles_object {
    uint32_t (*realize)(struct sles_object **self, uint32_t async);
    void *field_1;
    void *field_2;
    uint32_t (*get_interface)(struct sles_object **self, uint32_t *iid, void ***itf);
    void *field_4;
    void *field_5;
    uint32_t (*destroy)(struct sles_object **self);
    void *field_7;
    void *field_8;
    void *field_9;
};

typedef struct {
    void *locator;
    void *format;
} sles_data_t;

typedef struct {
	uint32_t format_type;
	uint32_t num_channels;
	uint32_t samples_per_sec;
	uint32_t bits_per_sample;
	uint32_t container_size;
	uint32_t channel_mask;
	uint32_t endianness;
} sles_pcm_format_t;

struct sles_engine_interface {
    void *field_0;
    void *field_1;
    uint32_t (*create_audio_player)(
        struct sles_engine_interface **self,
        struct sles_object ***player,
        sles_data_t *data_source,
        sles_data_t *data_sink,
        uint32_t interface_count,
        uint32_t **interfaces,
        uint32_t *interfaces_required
    );
    void *field_3;
    void *field_4;
    void *field_5;
    void *field_6;
    uint32_t (*create_output_mix)(
        struct sles_engine_interface **self,
        struct sles_object ***mix,
        uint32_t interface_count,
        uint32_t **interfaces,
        uint32_t *interfaces_required
    );
    void *field_8;
    void *field_9;
    void *field_10;
    void *field_11;
    void *field_12;
    void *field_13;
    void *field_14;
};

struct sles_volume_interface {
    uint32_t (*set_volume_level)(struct sles_volume_interface **self, int16_t level);
    void *field_1;
    uint32_t (*get_max_volume_level)(struct sles_volume_interface **self, int16_t *level);
    void *field_3;
    void *field_4;
    void *field_5;
    void *field_6;
    void *field_7;
    void *field_8;
};

struct sles_play_interface {
    uint32_t (*set_play_state)(struct sles_play_interface **self, uint32_t state);
    void *field_1;
    void *field_2;
    void *field_3;
    void *field_4;
    void *field_5;
    void *field_6;
    void *field_7;
    void *field_8;
    void *field_9;
    void *field_10;
    void *field_11;
};

struct sles_bufferqueue_interface {
    uint32_t (*enquire)(struct sles_bufferqueue_interface **self, void *buffer, uint32_t size);
    void *field_1;
    void *field_2;
    uint32_t (*register_callback)(
        struct sles_bufferqueue_interface **self,
        void (*callback)(
            struct sles_bufferqueue_interface **self,
            void *context
        ),
        void *context
    );
};

extern uint32_t *sles_iid_engine;
extern uint32_t *sles_iid_bufferqueue;
extern uint32_t *sles_iid_volume;
extern uint32_t *sles_iid_play;

uint32_t sles_create_engine(struct sles_object ***engine, uint32_t options_count, void *options, uint32_t interface_count, uint32_t **interfaces, uint32_t *interfaces_required);

void sles_tick();

#endif
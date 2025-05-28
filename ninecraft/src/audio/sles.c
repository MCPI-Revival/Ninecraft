#include <ninecraft/audio/sles.h>
#include <ninecraft/audio/audio_engine.h>
#include <stdio.h>

#define SL_DATAFORMAT_PCM ((uint32_t) 0x00000002)
#define SL_DATAFORMAT_PCM_EX ((uint32_t) 0x00000004)

uint32_t sles_iid_engine_ = 0;
uint32_t sles_iid_bufferqueue_ = 1;
uint32_t sles_iid_volume_ = 2;
uint32_t sles_iid_play_ = 3;

uint32_t *sles_iid_engine = &sles_iid_engine_;
uint32_t *sles_iid_bufferqueue = &sles_iid_bufferqueue_;
uint32_t *sles_iid_volume = &sles_iid_volume_;
uint32_t *sles_iid_play = &sles_iid_play_;

int16_t sles_volume_level = 0;
sles_data_t *sles_data_source;

uint32_t sles_bufferqueue_interface_enquire(struct sles_bufferqueue_interface **self, void *buffer, uint32_t size) {
    int16_t max_vol = 0;
    float gain = (float)((sles_volume_level + 2000) - max_vol) / 2000.0f;
    sles_pcm_format_t *metadata = (sles_pcm_format_t *)sles_data_source->format;
    uint32_t format = 0;
    if (metadata->format_type == SL_DATAFORMAT_PCM_EX) {
        format = metadata->representation;
    } else if (metadata->format_type == SL_DATAFORMAT_PCM) {
        format = 1;
    }
    audio_engine_play(buffer, size, metadata->num_channels, metadata->bits_per_sample, metadata->samples_per_sec / 1000, format, metadata->endianness, gain, 1.0f);
    return 0;
}

uint32_t sles_bufferqueue_interface_register_callback(
    struct sles_bufferqueue_interface **self,
    void (*callback)(
        struct sles_bufferqueue_interface **self,
        void *context),
    void *context
) {
    callback(self, context);
    return 0;
}

struct sles_bufferqueue_interface sles_bufferqueue_interface = {
    .enquire = sles_bufferqueue_interface_enquire,
    .register_callback = sles_bufferqueue_interface_register_callback
};

struct sles_bufferqueue_interface *sles_bufferqueue_interface_p = &sles_bufferqueue_interface;

uint32_t sles_play_interface_set_play_state(struct sles_play_interface **self, uint32_t state) {
    return 0;
}

struct sles_play_interface sles_play_interface = {
    .set_play_state = sles_play_interface_set_play_state
};

struct sles_play_interface *sles_play_interface_p = &sles_play_interface;

uint32_t sles_volume_interface_set_volume_level(struct sles_volume_interface **self, int16_t level) {
    sles_volume_level = level;
    return 0;
}

uint32_t sles_volume_interface_get_max_volume_level(struct sles_volume_interface **self, int16_t *level) {
    *level = 0;
    return 0;
}

struct sles_volume_interface sles_volume_interface = {
    .set_volume_level = sles_volume_interface_set_volume_level,
    .get_max_volume_level = sles_volume_interface_get_max_volume_level
};

struct sles_volume_interface *sles_volume_interface_p = &sles_volume_interface;

uint32_t sles_audioplayer_realize(struct sles_object **self, uint32_t async) {
    return 0;
}

uint32_t sles_audioplayer_get_interface(struct sles_object **self, uint32_t *iid, void ***itf) {
    if (iid == sles_iid_play) {
        *itf = (void **)&sles_play_interface_p;
    } else if (iid == sles_iid_volume) {
        *itf = (void **)&sles_volume_interface_p;
    } else if (iid == sles_iid_bufferqueue) {
        *itf = (void **)&sles_bufferqueue_interface_p;
    }
    return 0;
}

uint32_t sles_audioplayer_destroy(struct sles_object **self) {
    return 0;
}

struct sles_object sles_audioplayer = {
    .realize = sles_audioplayer_realize,
    .get_interface = sles_audioplayer_get_interface,
    .destroy = sles_audioplayer_destroy
};

struct sles_object *sles_audioplayer_p = &sles_audioplayer;

uint32_t sles_outputmix_realize(struct sles_object **self, uint32_t async) {
    return 0;
}

struct sles_object sles_outputmix = {
    .realize = sles_outputmix_realize
};

struct sles_object *sles_outputmix_p = &sles_outputmix;

uint32_t sles_engine_interface_create_audio_player(
    struct sles_engine_interface **self,
    struct sles_object ***player,
    sles_data_t *data_source,
    sles_data_t *data_sink,
    uint32_t interface_count,
    uint32_t **interfaces,
    uint32_t *interfaces_required
) {
    sles_data_source = data_source;
    *player = &sles_audioplayer_p;
    return 0;
}

uint32_t sles_engine_interface_create_output_mix(
    struct sles_engine_interface **self,
    struct sles_object ***mix,
    uint32_t interface_count,
    uint32_t **interfaces,
    uint32_t *interfaces_required
) {
    *mix = &sles_outputmix_p;
    return 0;
}

struct sles_engine_interface sles_engine_interface = {
    .create_audio_player = sles_engine_interface_create_audio_player,
    .create_output_mix = sles_engine_interface_create_output_mix
};

struct sles_engine_interface *sles_engine_interface_p = &sles_engine_interface;

uint32_t sles_engine_realize(struct sles_object **self, uint32_t async) {
    return 0;
}

uint32_t sles_engine_get_interface(struct sles_object **self, uint32_t *iid, void ***itf) {
    *itf = (void **)&sles_engine_interface_p;
    return 0;
}

uint32_t sles_engine_destroy(struct sles_object **self) {
    return 0;
}

struct sles_object sles_engine = {
    .realize = sles_engine_realize,
    .get_interface = sles_engine_get_interface,
    .destroy = sles_engine_destroy
};

struct sles_object *sles_engine_p = &sles_engine;

uint32_t sles_create_engine(struct sles_object ***engine, uint32_t options_count, void *options, uint32_t interface_count, uint32_t **interfaces, uint32_t *interfaces_required) {
    *engine = &sles_engine_p;
    return 0;
}
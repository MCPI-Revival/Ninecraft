#include <stddef.h>
#include <AL/alext.h>
#include <ninecraft/audio_engine.h>
#include <ninecraft/sound_repo.h>
#include <stdio.h>
#include <hybris/dlfcn.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

void audio_engine_source_map_init(audio_engine_source_map_t *source_map) {
    source_map->entries = NULL;
};

void audio_engine_source_map_push(audio_engine_source_map_t *source_map, ALuint source) {
    audio_engine_source_map_entry_t *source_map_entry = (audio_engine_source_map_entry_t *)malloc(sizeof(audio_engine_source_map_entry_t));
    source_map_entry->next = source_map->entries;
    source_map_entry->source = source;
    source_map->entries = source_map_entry;
}

ALuint audio_engine_source_map_pop(audio_engine_source_map_t *source_map) {
    if (source_map->entries == NULL) {
        return 0;
    } else {
        ALuint out = source_map->entries->source;
        audio_engine_source_map_entry_t *source_map_entry = source_map->entries->next;
        free(source_map->entries);
        source_map->entries = source_map_entry;
        return out;
    }
}

void audio_engine_source_map_destroy(audio_engine_source_map_t *source_map) {
    audio_engine_source_map_entry_t *entry = source_map->entries;
    while (entry != NULL) {
        audio_engine_source_map_entry_t *tmp = entry->next;
        if (entry->source && alIsSource(entry->source)) {
            alDeleteSources(1, &entry->source);
            ALenum al_err = alGetError();
            if (al_err != AL_NO_ERROR) {
                puts("Failed to delete source");
            }
        }
        free(entry);
        entry = tmp;
    }
}

size_t audio_engine_source_map_size(audio_engine_source_map_t *source_map) {
    size_t size = 0;
    audio_engine_source_map_entry_t *entry = source_map->entries;
    while (entry != NULL) {
        entry = entry->next;
        ++size;
    }
    return size;
}

bool audio_engine_create_audio_device(audio_engine_t *audio_engine) {
    audio_engine->is_initialized = false;
    audio_engine_source_map_init(&audio_engine->sources);
    audio_engine_source_map_init(&audio_engine->idle_sources);
    audio_engine->buffer_index = 0;
    audio_engine->device = alcOpenDevice(NULL);
	if (!audio_engine->device) {
        puts("Failed to open audio device");
		return false;
    }

	audio_engine->context = alcCreateContext(audio_engine->device, NULL);
    ALCenum alc_err = alcGetError(audio_engine->device);
	if (alc_err != ALC_NO_ERROR) {
        puts("Failed to create audio context");
		return false;
    }

	alcMakeContextCurrent(audio_engine->context);
    alc_err = alcGetError(audio_engine->device);
	if (alc_err != ALC_NO_ERROR) {
        puts("Failed to set audio context");
		return false;
    }

    alEnable(AL_SOURCE_DISTANCE_MODEL);
    ALenum al_err = alGetError();
	if (al_err != AL_NO_ERROR) {
        puts("Failed to enable the source distance model");
		return false;
    }
    audio_engine->is_initialized = true;
    return true;
}

void audio_engine_delete_buffers(audio_engine_t *audio_engine) {
    for (int i = 0; i < audio_engine->buffer_index; ++i) {
        ALuint buffer = audio_engine->buffers[i];
        if (alIsBuffer(buffer)) {
            alDeleteBuffers(1, &buffer);
        }
    }
}

bool audio_engine_destroy_audio_device(audio_engine_t *audio_engine) {
    if (audio_engine->is_initialized) {
        audio_engine->is_initialized = false;
        audio_engine_source_map_destroy(&audio_engine->sources);
        audio_engine_source_map_destroy(&audio_engine->idle_sources);
        audio_engine_delete_buffers(audio_engine);

        alcMakeContextCurrent(NULL);
        ALCenum alc_err = alcGetError(audio_engine->device);
	    if (alc_err != ALC_NO_ERROR) {
            puts("Failed to set audio context");
		    return false;
        }
	    alcDestroyContext(audio_engine->context);
	    alc_err = alcGetError(audio_engine->device);
	    if (alc_err != ALC_NO_ERROR) {
            puts("Failed to destroy audio context");
		    return false;
        }
	    alcCloseDevice(audio_engine->device);
        alc_err = alcGetError(audio_engine->device);
	    if (alc_err != ALC_NO_ERROR) {
            puts("Failed to close audio device");
		    return false;
        }
    } else {
        return false;
    }
    return true;
}

ALuint audio_engine_load_sound(char *name, void *handle) {
    audio_engine_pcm_metadata_t *meta = (audio_engine_pcm_metadata_t *) hybris_dlsym(handle, name);

    ALenum format = AL_NONE;
    if (meta->channels == 1) {
        format = meta->frame_size == 2 ? AL_FORMAT_MONO16 : AL_FORMAT_MONO8;
    } else if (meta->channels == 2) {
        format = meta->frame_size == 2 ? AL_FORMAT_STEREO16 : AL_FORMAT_STEREO8;
    } else {
        puts("Invalid Format");
        return 0;
    }

	ALsizei data_size = meta->channels * meta->frames * meta->frame_size;
    void *data = (void *)((size_t)meta + sizeof(audio_engine_pcm_metadata_t));

	ALuint buffer = 0;
	alGenBuffers(1, &buffer);
	alBufferData(buffer, format, data, data_size, meta->sample_rate);

	ALenum err = alGetError();
	if (err != AL_NO_ERROR) {
        puts("Buffer error");
		if (buffer && alIsBuffer(buffer)) {
			alDeleteBuffers(1, &buffer);
        }
		return 0;
	}
	return buffer;
}

ALuint audio_engine_get_buffer(audio_engine_t *audio_engine, char *name, void *handle) {
    char *sample_names[5];
    get_sound(sample_names, name);
    if ((int)sample_names[0] != 0) {
        srand(time(NULL));
        int sample_index = rand() % (((int)sample_names[0] + 1) - 1) + 1;
        printf("%d\n", sample_index);
        char *sample_name = sample_names[sample_index];
        printf("%s\n", sample_name);
        for (int i = 0; i < audio_engine->buffer_index; ++i) {
            if (strcmp(sample_name, audio_engine->buffer_names[i]) == 0) {
                return audio_engine->buffers[i];
            }
        }
        ALuint buffer = audio_engine_load_sound(sample_name, handle);
        if (buffer != 0 && audio_engine->buffer_index < 100) {
            audio_engine->buffer_names[audio_engine->buffer_index] = sample_name;
            audio_engine->buffers[audio_engine->buffer_index++] = buffer;
        }
        return buffer;
    }
    return 0;
}

void audio_engine_play(audio_engine_t *audio_engine, void *handle, char *name, float x, float y, float z, float volume, float pitch, bool is_ui) {
    if (!audio_engine->is_initialized) {
        return;
    }
    if (pitch < 0.5f) {
        pitch = 0.5f;
    } else if (pitch > 2.0f) {
        pitch = 2.0f;
    }
    ALuint buffer = audio_engine_get_buffer(audio_engine, name, handle);
    if (volume > 0.0f && buffer) {
        ALuint al_source;
        if (audio_engine->idle_sources.entries != NULL) {
            al_source = audio_engine_source_map_pop(&audio_engine->idle_sources);
        } else {
            alGenSources(1, &al_source);
            ALenum err = alGetError();
            if (err != AL_NO_ERROR) {
                puts("OpenAL error");
                if (al_source && alIsSource(al_source)) {
                    alDeleteSources(1, &al_source);
                }
                return;
            }
        }
        alSourcef(al_source, AL_PITCH, pitch);
        ALenum err = alGetError();
        if (err != AL_NO_ERROR) {
            puts("OpenAL error");
            if (al_source && alIsSource(al_source)) {
                alDeleteSources(1, &al_source);
            }
            return;
        }
        alSourcef(al_source, AL_GAIN, volume);
        err = alGetError();
        if (err != AL_NO_ERROR) {
            puts("OpenAL error");
            if (al_source && alIsSource(al_source)) {
                alDeleteSources(1, &al_source);
            }
            return;
        }
        alSource3f(al_source, AL_POSITION, x, y, z);
        err = alGetError();
        if (err != AL_NO_ERROR) {
            puts("OpenAL error");
            if (al_source && alIsSource(al_source)) {
                alDeleteSources(1, &al_source);
            }
            return;
        }
        alSource3f(al_source, AL_VELOCITY, 0, 0, 0);
        err = alGetError();
        if (err != AL_NO_ERROR) {
            puts("OpenAL error");
            if (al_source && alIsSource(al_source)) {
                alDeleteSources(1, &al_source);
            }
            return;
        }
        alSourcei(al_source, AL_LOOPING, AL_FALSE);
        err = alGetError();
        if (err != AL_NO_ERROR) {
            puts("OpenAL error");
            if (al_source && alIsSource(al_source)) {
                alDeleteSources(1, &al_source);
            }
            return;
        }
        alSourcei(al_source, AL_SOURCE_RELATIVE, is_ui ? AL_TRUE : AL_FALSE);
        err = alGetError();
        if (err != AL_NO_ERROR) {
            puts("OpenAL error");
            if (al_source && alIsSource(al_source)) {
                alDeleteSources(1, &al_source);
            }
            return;
        }
        alSourcei(al_source, AL_DISTANCE_MODEL, AL_LINEAR_DISTANCE_CLAMPED);
        err = alGetError();
        if (err != AL_NO_ERROR) {
            puts("OpenAL error");
            if (al_source && alIsSource(al_source)) {
                alDeleteSources(1, &al_source);
            }
            return;
        }
        alSourcef(al_source, AL_MAX_DISTANCE, 22.0f);
        err = alGetError();
        if (err != AL_NO_ERROR) {
            puts("OpenAL error");
            if (al_source && alIsSource(al_source)) {
                alDeleteSources(1, &al_source);
            }
            return;
        }
        alSourcef(al_source, AL_ROLLOFF_FACTOR, 1.0f);
        err = alGetError();
        if (err != AL_NO_ERROR) {
            puts("OpenAL error");
            if (al_source && alIsSource(al_source)) {
                alDeleteSources(1, &al_source);
            }
            return;
        }
        alSourcef(al_source, AL_REFERENCE_DISTANCE, 2.0f);
        err = alGetError();
        if (err != AL_NO_ERROR) {
            puts("OpenAL error");
            if (al_source && alIsSource(al_source)) {
                alDeleteSources(1, &al_source);
            }
            return;
        }
        alSourcei(al_source, AL_BUFFER, buffer);
        err = alGetError();
        if (err != AL_NO_ERROR) {
            puts("OpenAL error");
            if (al_source && alIsSource(al_source)) {
                alDeleteSources(1, &al_source);
            }
            return;
        }
        alSourcePlay(al_source);
        err = alGetError();
        if (err != AL_NO_ERROR) {
            puts("OpenAL error");
            if (al_source && alIsSource(al_source)) {
                alDeleteSources(1, &al_source);
            }
            return;
        }
        audio_engine_source_map_push(&audio_engine->sources, al_source);
    }
}

void audio_engine_update(audio_engine_t *audio_engine, float volume, float x, float y, float z, float yaw) {
    if (!audio_engine->is_initialized) {
        return;
    }
    alListenerf(AL_GAIN, volume);
    ALenum err = alGetError();
    if (err != AL_NO_ERROR) {
        puts("Failed to set listener volume");
    }

    alListener3f(AL_POSITION, x, y, z);
    err = alGetError();
    if (err != AL_NO_ERROR) {
        puts("Failed to set listener pos");
    }
    
    float radian_yaw = yaw * (M_PI / 180);
    ALfloat orientation[] = {
        -sinf(radian_yaw), 0.0f, cosf(radian_yaw),
        0.0f, 1.0f, 0.0f
    };

    alListenerfv(AL_ORIENTATION, orientation);
    err = alGetError();
    if (err != AL_NO_ERROR) {
        puts("Failed to set listener orientation");
    }

    audio_engine_source_map_entry_t *entry = audio_engine->sources.entries;
    audio_engine_source_map_entry_t *old_entry = NULL;
    while (entry != NULL) {
        audio_engine_source_map_entry_t *tmp = entry->next;
        bool remove = false;
        if (entry->source && alIsSource(entry->source)) {
            ALint source_state;
            alGetSourcei(entry->source, AL_SOURCE_STATE, &source_state);
            ALenum al_err = alGetError();
            if (al_err != AL_NO_ERROR) {
                puts("Failed to get source");
            }
            if (source_state != AL_PLAYING) {
                remove = true;
                if (audio_engine_source_map_size(&audio_engine->idle_sources) < 50) {
                    audio_engine_source_map_push(&audio_engine->idle_sources, entry->source);
                } else {
                    alDeleteSources(1, &entry->source);
                    al_err = alGetError();
                    if (al_err != AL_NO_ERROR) {
                        puts("Failed to delete source");
                    }
                }
            }
        } else {
            remove = true;
        }

        if (remove) {
            if (old_entry == NULL) {
                audio_engine->sources.entries = tmp;
            } else {
                old_entry->next = tmp;
            }
            free(entry);
        } else {
            old_entry = entry;
        }
        entry = tmp;
    }
}
#include <stddef.h>
#include <AL/alext.h>
#include <ninecraft/audio_engine.h>
#include <stdio.h>

struct pcm_metadata {
    int32_t channels;
    int32_t frame_size;
    int32_t sample_rate;
    int32_t frames;
};

int audio_engine_create_audio_device(ALCdevice **device, ALCcontext **context) {
    *device = alcOpenDevice(NULL);
	if (!*device) {
        printf("errorr!!! 1\n");
		return 0;
    }

	*context = alcCreateContext(*device, NULL);
	if (!*context) {
        printf("errorr!!! 2\n");
		return 0;
    }

	alcMakeContextCurrent(*context);
    ALenum err = alGetError();
	if (err != AL_NO_ERROR) {
        printf("errorr!!! 3\n");
		return 0;
    }
    alEnable(AL_SOURCE_DISTANCE_MODEL);
    err = alGetError();
	if (err != AL_NO_ERROR) {
        printf("errorr!!! 4\n");
		return 0;
    }

    const ALCchar* name = NULL;
	if (alcIsExtensionPresent(*device, "ALC_ENUMERATE_ALL_EXT"))
		name = alcGetString(*device, ALC_ALL_DEVICES_SPECIFIER);
	if (!name || alcGetError(*device) != AL_NO_ERROR)
		name = alcGetString(*device, ALC_DEVICE_SPECIFIER);
	printf("Opened \"%s\"\n", name);

    puts("alls good");
    return 1;
}

int audio_engine_destroy_audio_device(ALCdevice **device, ALCcontext **context) {
    alcMakeContextCurrent(NULL);
    ALenum err = alGetError();
	if (err != AL_NO_ERROR) {
		return 0;
    }
	alcDestroyContext(*context);
	err = alGetError();
	if (err != AL_NO_ERROR) {
		return 0;
    }
	alcCloseDevice(*device);
    err = alGetError();
	if (err != AL_NO_ERROR) {
		return 0;
    }
    return 1;
}

ALuint audio_engine_create_sound_effect(void *symbol) {
    struct pcm_metadata *meta = (struct pcm_metadata *) symbol;

    ALenum format = AL_NONE;
    if (meta->channels == 1) {
        format = meta->frame_size == 2 ? AL_FORMAT_MONO16 : AL_FORMAT_MONO8;
    } else if (meta->channels == 2) {
        format = meta->frame_size == 2 ? AL_FORMAT_STEREO16 : AL_FORMAT_STEREO8;
    } else {
        puts("errrrr form!!!");
        return 0;
    }

	ALsizei data_size = meta->channels * meta->frames * meta->frame_size;
    void *data = (void *) (((int)symbol)+sizeof(struct pcm_metadata));

	ALuint buffer = 0;
	alGenBuffers(1, &buffer);
	alBufferData(buffer, format, data, data_size, meta->sample_rate);

	ALenum err = alGetError();
	if (err != AL_NO_ERROR) {
        puts("errrrr buff!!!");
		if (buffer && alIsBuffer(buffer)) {
			alDeleteBuffers(1, &buffer);
        }
		return 0;
	}

    puts("alls good buf");

	return buffer;
}

void audio_engine_play(ALuint buffer) {
    ALuint p_Source;
    alGenSources(1, &p_Source);
	alSourcef(p_Source, AL_PITCH, 1.f);
	alSourcef(p_Source, AL_GAIN, 1.f);
	alSource3f(p_Source, AL_POSITION, 0.f, 0.f, 0.f);
	alSource3f(p_Source, AL_VELOCITY, 0.f, 0.f, 0.f);
	alSourcei(p_Source, AL_LOOPING, AL_FALSE);
    alSourcei(p_Source, AL_SOURCE_RELATIVE, AL_TRUE);
	alSourcei(p_Source, AL_BUFFER, buffer);
    alSourcePlay(p_Source);
    //alDeleteSources(1, &p_Source);
}
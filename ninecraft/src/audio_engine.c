#include <stddef.h>
#include <AL/alext.h>
#include <ninecraft/audio_engine.h>
#include <stdio.h>

bool audio_engine_create_audio_device(audio_engine_t *audio_engine) {
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
    return true;
}

bool audio_engine_destroy_audio_device(audio_engine_t *audio_engine) {
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
    return true;
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
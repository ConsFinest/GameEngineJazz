#include "audioSource.h"
#include <stb_vorbis/stb_vorbis.h>

AudioSource::~AudioSource()
{
	alDeleteSources(1, &sourceId);
	alDeleteBuffers(1, &bufferId);
}

void AudioSource::load_ogg(const std::string& _fileName)
{
	int channels = 0;
	int sampleRate = 0;
	short* output = NULL;

	size_t samples = stb_vorbis_decode_filename(
		_fileName.c_str(), &channels, &sampleRate, &output);

	if (samples == -1)
	{
		throw std::exception();
	}

	// Record the sample rate required by OpenAL
	freq = sampleRate;

	// Record the format required by OpenAL
	if (channels == 1)
	{
		format = AL_FORMAT_MONO16;
	}
	else
	{
		format = AL_FORMAT_STEREO16;

		// Force format to be mono (Useful for positional audio)
		// format = AL_FORMAT_MONO16;
		// freq *= 2;
	}

	// Allocate enough space based on short (two chars) multipled by the number of
	// channels and length of clip
	bufferData.resize(sizeof(*output) * channels * samples);
	memcpy(&bufferData.at(0), output, bufferData.size());

	// Clean up the read data
	free(output);
}

void AudioSource::audioSourceInit(const std::string& _fileName)
{
	bufferId = 0;

	format = 0;
	freq = 0;

	alGenBuffers(1, &bufferId);

	load_ogg(_fileName);

	alBufferData(bufferId, format, &bufferData.at(0),
		static_cast<ALsizei>(bufferData.size()), freq);
}

void AudioSource::playAudio()
{
	sourceId = 0;

	alGenSources(1, &sourceId);

	alSource3f(sourceId, AL_POSITION, 0.0f, 0.0f, 0.0f);
	alSourcei(sourceId, AL_BUFFER, bufferId);
	alSourcePlay(sourceId);
}

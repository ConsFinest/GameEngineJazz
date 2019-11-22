#ifndef  _AUDIO_SOURCE_H_
#define _AUDIO_SOURCE_H_

#include <AL/al.h>
#include <AL/alc.h>
#include "component.h"
#include <vector>
#include <string>

class AudioSource : public Component
{
	ALuint bufferId;
	ALuint sourceId;
	ALint state;

	ALenum format;
	ALsizei freq;

	std::vector<char> bufferData;

 public:

	 ~AudioSource();
	 void load_ogg(const std::string& _fileName);
	 void audioSourceInit(const std::string& _fileName);
	 void playAudio();
};





#endif // ! _AUDIO_SOURCE_H_

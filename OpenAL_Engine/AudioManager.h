#pragma once

#include"OpenAL/OpenAlCore/OpenALDevice.h"
#include"OpenAL/AudioSpeaker/AudioSpeaker.h"

#include<map>
#include <utility>
#include <functional>

namespace htAudio {

	class AudioManager
	{
	public:
		AudioManager();
		~AudioManager();

		int AddSpeaker(std::string filepath, std::string SoundName, std::string material);
		int AddSpeaker(std::string filepath, uint16_t id);
		int AddSpeaker(std::string filepath, std::string soundname);

		void RemoveSpeaker( int numb );

	private:
		OpenALDevice* AlDevice;						// デバイスポインタ
		std::map<ALuint, AudioSpeaker*> SpeakerMap;	// speakerのmap 管理するやつ

	};

}
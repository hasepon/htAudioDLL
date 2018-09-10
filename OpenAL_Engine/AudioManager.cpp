#include "AudioManager.h"


namespace htAudio {

	AudioManager::AudioManager()
	{
		AlDevice = new OpenALDevice();
	}

	AudioManager::~AudioManager()
	{
		for(auto var : SpeakerMap)
		{
			delete var.second;
		}

		SpeakerMap.clear();

		if (AlDevice == nullptr)
		{
			return;
		}
		delete AlDevice;
	}

	int AudioManager::AddSpeaker(std::string filepath, std::string SoundName, std::string material)
	{
		ALuint numb;
		AudioSpeaker* speaker;

		speaker = new AudioSpeaker(filepath, SoundName, material);
		numb = speaker->GetSpeakerNumb();

		SpeakerMap.insert( std::make_pair(numb,speaker) );

		return numb;

	}

	int AudioManager::AddSpeaker(std::string filepath, uint16_t id)
	{
		ALuint numb;
		AudioSpeaker* speaker;

		speaker = new AudioSpeaker(filepath, id);
		numb = speaker->GetSpeakerNumb();

		SpeakerMap.insert(std::make_pair(numb, speaker));

		return numb;
	}

	int AudioManager::AddSpeaker(std::string filepath, std::string soundname)
	{
		ALuint numb;
		AudioSpeaker* speaker;

		speaker = new AudioSpeaker(filepath, soundname);
		numb = speaker->GetSpeakerNumb();

		SpeakerMap.insert(std::make_pair(numb, speaker));

		return numb;
	}

	void AudioManager::RemoveSpeaker(int numb)
	{
		auto itr = SpeakerMap.find(numb);

		if (SpeakerMap.end() != itr)
		{
			delete SpeakerMap[numb];
			SpeakerMap.erase(itr);
		}

	}

}
#pragma once

#include"OpenAL/OpenAlCore/OpenALDevice.h"
#include"OpenAL/AudioSpeaker/AudioSpeaker.h"

#include<map>
#include <utility>
#include <functional>

namespace htAudio {

	/// <summary>
	/// Deviceの管理とスピーカーの管理をするクラス
	/// </summary>
	class AudioManager
	{
	public:
		AudioManager();
		~AudioManager();

		int AddSpeaker(std::string filepath, std::string SoundName, std::string material);
		int AddSpeaker(std::string filepath, uint16_t id);
		int AddSpeaker(std::string filepath, std::string soundname);

		void ThreadUpdate();

		bool SpeakerFormat( int numb );
		void RemoveSpeaker( int numb );

		void AllDelete();

	private:
		OpenALDevice* AlDevice;						// デバイスポインタ
		std::map<ALuint, AudioSpeaker*> SpeakerMap;	// speakerのmap 管理するやつ
		std::thread UpdateThread;	// 自動アップデート用のスレッド

	};

}
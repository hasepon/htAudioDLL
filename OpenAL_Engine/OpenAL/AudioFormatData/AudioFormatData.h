#pragma once

#include<iostream>
#include<string>
#include<tchar.h>

#include"../FileLoad/LoadSoundFile.h"
#include"../AudioListener/AudioListener.h"
#include<pugixml.hpp>

#pragma comment(lib, "pugixml.lib")

namespace htAudio
{
	/// <summary>
	/// xmlÇÃì«Ç›çûÇ›
	/// </summary>
	/// 
	class AudioFormatData
	{
	public:
		AudioFormatData();
		~AudioFormatData();

		SoundType GetAudioFormatData(std::string filepath, std::string Soundname);
		SoundType GetAudioFormatData(std::string filepath, int id);
		void WriteAudioFormatData(std::string filepath, SoundType registinfo);

		bool ReadListenerState(ListenerStates* state, std::string filepath);
		bool WriteListenerState(ListenerStates state, std::string filepath);

		//bool ReadSpeakerState(ListenerStates* state, std::string filepath);
		//bool WriteSpeakerState(ListenerStates state, std::string filepath);

	private:


	};

}
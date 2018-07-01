#pragma once


#include"../FileLoad/LoadSoundFile.h"
#include<pugixml.hpp>

#ifdef _DEBUG
#pragma comment(lib, "pugixml_d.lib")
#else
#pragma comment(lib, "pugixml.lib")
#endif // _DEBUG

#include<iostream>
#include<string>
#include<tchar.h>

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

	private:


	};

}
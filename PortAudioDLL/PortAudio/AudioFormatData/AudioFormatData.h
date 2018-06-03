#pragma once

#include"../FileLoad/LoadSoundFile.h"
#include<pugixml.hpp>

#pragma comment(lib, "pugixml.lib")

#ifdef _DLL
#define PUGIXML_API __declspec(dllexport)
#else
#define PUGIXML_API __declspec(dllimport)
#endif


#include<iostream>
#include<string>
#include<tchar.h>

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


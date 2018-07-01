#pragma once

#include"htAudioSpeaker.h"

#include<uchar.h>

AudioSpeaker* htaSpeakerCreate(char* filepath, char* soundname, char* material)
{
	
	std::string path, name, mat;

	path = filepath;
	name = soundname;
	mat = material;

	return new AudioSpeaker(path,name,mat);
}

AudioSpeaker* htaSpeakerCreateID(char* filepath, uint16_t id)
{
	std::string path = filepath;
	return new AudioSpeaker(path, id);
}

AudioSpeaker* htaSpeakerCreateName(char* filepath, char* soundname)
{
	std::string path = filepath;
	std::string name = soundname;
	return new AudioSpeaker(path, name);
}

void  htaSpeakerDelete(AudioSpeaker* instance)
{
	if (instance == nullptr)
	{
		return;
	}

	delete instance;
}

void  htaSpeakerPosition(AudioSpeaker* instance,float x, float y, float z)
{
	instance->SetPosition(x,y,z);
}

void  htaSpeakerPositionArray(AudioSpeaker* instance, float Pos[3])
{
	instance->SetPosition(Pos);
}

bool  Play(AudioSpeaker* instance)
{
	return instance->Play();
}

bool  Update(AudioSpeaker* instance)
{
	return instance->Update();
}

bool  Stop(AudioSpeaker* instance)
{
	return instance->Stop();
}

bool  Pause(AudioSpeaker* instance)
{
	return instance->Pause();
}
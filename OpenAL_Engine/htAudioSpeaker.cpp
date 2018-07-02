#pragma once

#include"htAudioSpeaker.h"

#include<uchar.h>

AudioSpeaker* htaSpeakerCreate(char* filepath, char* soundname, char* material)
{
	return new AudioSpeaker(filepath, soundname, material);
}

AudioSpeaker* htaSpeakerCreateID(char* filepath, uint16_t id)
{
	return new AudioSpeaker(filepath, id);
}

AudioSpeaker* htaSpeakerCreateName(char* filepath, char* soundname)
{
	return new AudioSpeaker(filepath, soundname);
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

bool Formatflag(AudioSpeaker* instance)
{
	return instance->GetResourceflag();
}
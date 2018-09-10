#pragma once

#include"htAudioSpeaker.h"

#include<uchar.h>
#include<codecvt>
#include<string>

std::string wide_to_multi_capi(std::wstring const& src)
{
	std::size_t converted{};
	std::vector<char> dest(src.size() * sizeof(wchar_t) + 1, '\0');
	if (::_wcstombs_s_l(&converted, dest.data(), dest.size(), src.data(), _TRUNCATE, ::_create_locale(LC_ALL, "jpn")) != 0) {
		throw std::system_error{ errno, std::system_category() };
	}
	dest.resize(std::char_traits<char>::length(dest.data()));
	dest.shrink_to_fit();
	return std::string(dest.begin(), dest.end());
}


int htaSpeakerCreate(wchar_t* filepath, wchar_t* soundname, wchar_t* material)
{
	std::string path, name, mat;
	
	path = wide_to_multi_capi(filepath);
	name = wide_to_multi_capi(soundname);
	mat  = wide_to_multi_capi(material);

	return new AudioSpeaker(path, name, mat);
}

int htaSpeakerCreateID(wchar_t* filepath, uint16_t id)
{
	std::string path;

	path = wide_to_multi_capi(filepath);

	return new AudioSpeaker(path, id);
}

int htaSpeakerCreateName(wchar_t* filepath, wchar_t* soundname)
{
	std::string path, name;

	path = wide_to_multi_capi(filepath);
	name = wide_to_multi_capi(soundname);

	return new AudioSpeaker(path, name);
}

void  htaSpeakerDelete(AudioSpeaker* instance)
{
	if (instance == nullptr)
	{
		return;
	}

	delete instance;
	instance = nullptr;
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

void htaSpeakerVelocity(AudioSpeaker* instance, float x, float y, float z)
{
	instance->SetVelocity(x, y, z);
}

void htaSpeakerVelocityArray(AudioSpeaker* instance, float Pos[3])
{
	instance->SetVelocity(Pos);
}

void htaSpeakerDirection(AudioSpeaker* instance, float x, float y, float z)
{
	instance->SetDirection(x, y, z);
}

void htaSpeakerDirectionArray(AudioSpeaker* instance, float dir[3])
{
	instance->SetDirection(dir);
}

void htaSpeakerSetConeOuterGain(AudioSpeaker* Instance, float val)
{
	Instance->SetConeOuterGain(val);
}

float htaSpeakerGetConeOuterGain(AudioSpeaker* Instance)
{
	return (float)Instance->GetConeOuterGain();
}

void htaSpeakerSetConeInnerAngle(AudioSpeaker* Instance, float val)
{
	Instance->SetConeInnerAngle(val);
}

float htaSpeakerGetConeInnerAngle(AudioSpeaker* Instance)
{
	return (float)Instance->GetConeInnerAngle();
}

void htaSpeakerSetConeOuterAngle(AudioSpeaker* Instance, float val)
{
	Instance->SetConeOuterAngle(val);
}

float htaSpeakerGetConeOuterAngle(AudioSpeaker* Instance)
{
	return (float)Instance->GetConeOuterAngle();
}
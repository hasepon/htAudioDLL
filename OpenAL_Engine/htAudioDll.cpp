#include"htAudioDll.h"

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

int htaSpeakerCreate(AudioManager* mgtPtr, wchar_t* filepath, wchar_t* soundname, wchar_t* material)
{
	std::string path, name, mat;

	path = wide_to_multi_capi(filepath);
	name = wide_to_multi_capi(soundname);
	mat = wide_to_multi_capi(material);

	int SpeakerNumb = mgtPtr->AddSpeaker(path, name, mat);

	return SpeakerNumb;
}

int htaSpeakerCreateID(AudioManager* mgtPtr, wchar_t* filepath, uint16_t id)
{
	std::string path;

	path = wide_to_multi_capi(filepath);

	int SpeakerNumb = mgtPtr->AddSpeaker(path, id);

	return SpeakerNumb;
}

int htaSpeakerCreateName(AudioManager* mgtPtr, wchar_t* filepath, wchar_t* soundname)
{
	std::string path, name;

	path = wide_to_multi_capi(filepath);
	name = wide_to_multi_capi(soundname);

	int SpeakerNumb = mgtPtr->AddSpeaker(path, name);

	return SpeakerNumb;
}

void  htaSpeakerDelete(AudioManager* mgtPtr, int Numb)
{
	mgtPtr->RemoveSpeaker(Numb);
}

bool  Play(int speakerId)
{
	return Play(speakerId);
}

bool  Stop(int speakerId)
{
	return Stop(speakerId);
}

bool  Pause(int speakerId)
{
	return Pause(speakerId);
}

bool Formatflag(AudioManager* mgtPtr, int speakerId)
{
	return mgtPtr->SpeakerFormat(speakerId);
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


AudioListener* htaListenerCreate()
{
	return new AudioListener();
}

void htaListenerDelete(AudioListener* Instance)
{
	if (Instance == nullptr)
	{
		return;
	}

	delete Instance;

}

void htaListenerPosition(AudioListener* Instance, float x, float y, float z)
{
	Instance->Setposition(x, y, z);
}

void htaListenerPositionArray(AudioListener* Instance, float Pos[3])
{
	Instance->Setposition(Pos);
}

void htaListenerVelocity(AudioListener* Instance, float x, float y, float z)
{
	Instance->SetVelocity(x, y, z);
}

void htaListenerVelocityArray(AudioListener* Instance, float vec[3])
{
	Instance->SetVelocity(vec);
}

void htaListenerOrientation(AudioListener* Instance, float AtVec[3], float UpVec[3])
{
	Instance->SetOrientation(AtVec, UpVec);
}

void htaListenerOrientationArray(AudioListener* Instance, float AtOrient[6])
{
	Instance->SetOrientation(AtOrient);
}

bool htaCreate(OpenALDevice* instance)
{
	instance = new OpenALDevice();

	return instance->GetCreateDeviceFlag();
}

void htaDelete(OpenALDevice* Instance)
{
	if (Instance == nullptr)
	{
		return;
	}

	delete Instance;
}

/// <summary>
/// C#側から3DAudioに必要なポインターを受け取って使用する
/// </summary>
/// <param name="speakerId"></param>
/// <param name="position"></param>
/// <param name="velocity"></param>
/// <param name="Dir"></param>
void htaAddI3DAudio(AudioManager* mgtPtr, int speakerId, float* position[3], float* velocity[3], float* Dir[3])
{
	I3DAudio* i3deffect = new I3DAudio(speakerId);
	
	i3deffect->SetPosition(position);
	i3deffect->SetDirection(Dir);
	i3deffect->SetVelocity(velocity);

	mgtPtr->AddEffect(i3deffect,speakerId);
}

void htaI3DAudioGain(int speakerId, float* gain)
{
	alSourcefv(speakerId, AL_GAIN, gain);
}


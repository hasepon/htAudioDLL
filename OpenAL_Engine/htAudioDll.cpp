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
/// 3DAudioの機能をOnにする
/// 位置情報、向き情報、速度情報をポインタで渡して自動更新
/// </summary>
void htaAddI3DAudio(AudioManager* mgtPtr, int speakerId, I3DAudioInfo* info)
{
	I3DAudio* i3deffect = new I3DAudio(speakerId,info);
	mgtPtr->AddEffect(i3deffect,speakerId);
}

/// <summary>
/// 3DAudioのコーンを機能をOnにする
/// インナーアングル、アウターアングル、アウターゲインを設定する
/// </summary>
void htaAddCone(AudioManager* mgtPtr, int speakerId, float innerangle, float outerangle, float outergain)
{
	ConeState* conestate = new ConeState(speakerId);
	conestate->SetConeInnerAngle(innerangle);
	conestate->SetConeOuterAngle(outerangle);
	conestate->SetConeOuterGain(outergain);
	mgtPtr->AddEffect(conestate,speakerId);

}

void htaSpeakerSetConeOuterGain(int speakerId, float val)
{
	alSourcef(speakerId, AL_CONE_OUTER_GAIN, val);
}

float htaSpeakerGetConeOuterGain(int speakerId)
{
	float val;
	alGetSourcef(speakerId, AL_CONE_OUTER_GAIN, &val);
	return val;
}

void htaSpeakerSetConeInnerAngle(int speakerId, float val)
{
	alSourcef(speakerId, AL_CONE_INNER_ANGLE, val);
}

float htaSpeakerGetConeInnerAngle(int speakerId)
{
	float val;
	alGetSourcef(speakerId, AL_CONE_INNER_ANGLE, &val);
	return val;
}

void htaSpeakerSetConeOuterAngle(int speakerId, float val)
{
	alSourcef(speakerId, AL_CONE_OUTER_ANGLE, val);
}

float htaSpeakerGetConeOuterAngle(int speakerId)
{
	float val;
	alGetSourcef(speakerId, AL_CONE_OUTER_ANGLE, &val);
	return val;
}

/// <summary>
/// リバーヴの機能をOnにする
/// 
/// </summary>
void htaAddReverb(AudioManager* mgtPtr, int speakerId, REVERB_INFO* info)
{
	ReverbEffects* effect = new ReverbEffects(speakerId);
	effect->SetInfo(info);
	mgtPtr->AddEffect(effect,speakerId);
}
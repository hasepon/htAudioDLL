#pragma once

#include"Definclude.h"
#include"OpenAL/AudioSpeaker/AudioSpeaker.h"

using namespace htAudio;

/// <summary>
/// オーディオデバイスを作成するための宣言
/// </summary>
extern "C"
{
	UNITY_INTERFACE_EXPORT AudioSpeaker* UNITY_INTERFACE_API htaSpeakerCreate(wchar_t* filepath, wchar_t* soundname, wchar_t* material);
	UNITY_INTERFACE_EXPORT AudioSpeaker* UNITY_INTERFACE_API htaSpeakerCreateID(wchar_t* filepath, uint16_t id);
	UNITY_INTERFACE_EXPORT AudioSpeaker* UNITY_INTERFACE_API htaSpeakerCreateName(wchar_t* filepath, wchar_t* soundname);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaSpeakerDelete(AudioSpeaker*);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaSpeakerPosition(AudioSpeaker*,float x, float y, float z);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaSpeakerPositionArray(AudioSpeaker*, float Pos[3]);
	UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API Play(AudioSpeaker* instance);
	UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API Update(AudioSpeaker* instance);
	UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API Stop(AudioSpeaker* instance);
	UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API Pause(AudioSpeaker* instance);
	UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API Formatflag(AudioSpeaker* instance);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaSpeakerVelocity(AudioSpeaker* instance,float x, float y, float z);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaSpeakerVelocityArray(AudioSpeaker* instance, float Vec[3]);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaSpeakerDirection(AudioSpeaker* instance, float x, float y, float z);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaSpeakerDirectionArray(AudioSpeaker* instance, float dir[3]);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API  htaSpeakerSetConeOuterGain(AudioSpeaker* Instance, float val);
	UNITY_INTERFACE_EXPORT float UNITY_INTERFACE_API htaSpeakerGetConeOuterGain(AudioSpeaker* Instance);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API  htaSpeakerSetConeInnerAngle(AudioSpeaker* Instance, float val);
	UNITY_INTERFACE_EXPORT float UNITY_INTERFACE_API htaSpeakerGetConeInnerAngle(AudioSpeaker* Instance);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API  htaSpeakerSetConeOuterAngle(AudioSpeaker* Instance, float val);
	UNITY_INTERFACE_EXPORT float UNITY_INTERFACE_API htaSpeakerGetConeOuterAngle(AudioSpeaker* Instance);
}
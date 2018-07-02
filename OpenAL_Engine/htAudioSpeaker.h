#pragma once

#include"Definclude.h"
#include"OpenAL/AudioSpeaker/AudioSpeaker.h"

using namespace htAudio;

/// <summary>
/// オーディオデバイスを作成するための宣言
/// </summary>
extern "C"
{
	UNITY_INTERFACE_EXPORT AudioSpeaker* UNITY_INTERFACE_API htaSpeakerCreate(char* filepath, char* soundname, char* material);
	UNITY_INTERFACE_EXPORT AudioSpeaker* UNITY_INTERFACE_API htaSpeakerCreateID(char* filepath, uint16_t id);
	UNITY_INTERFACE_EXPORT AudioSpeaker* UNITY_INTERFACE_API htaSpeakerCreateName(char* filepath, char* soundname);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaSpeakerDelete(AudioSpeaker*);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaSpeakerPosition(AudioSpeaker*,float x, float y, float z);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaSpeakerPositionArray(AudioSpeaker*, float Pos[3]);
	UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API Play(AudioSpeaker* );
	UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API Update(AudioSpeaker* );
	UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API Stop(AudioSpeaker* );
	UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API Pause(AudioSpeaker* );
	UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API Formatflag(AudioSpeaker* instance);
	//UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaSpeakerVelocity(float x, float y, float z);
	//UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaSpeakerVelocity(float Pos[3]);
	//UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaSpeakerOrientation(float AtVec[3], float UpVec[3]);
	//UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaSpeakerOrientation(float AtOrient[6]);
}
#pragma once

#include"Definclude.h"
#include"OpenAL/AudioListener/AudioListener.h"

using namespace htAudio;

/// <summary>
/// オーディオデバイスを作成するための宣言
/// </summary>
extern "C"
{
	UNITY_INTERFACE_EXPORT AudioListener* UNITY_INTERFACE_API htaListenerCreate();
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaListenerDelete(AudioListener*);
	
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaListenerPosition(float x, float y, float z);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaListenerPositionArray(float Pos[3]);
	
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaListenerVelocity(float x, float y, float z);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaListenerVelocityArray(float Pos[3]);
	
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaListenerOrientation(float AtVec[3],float UpVec[3]);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaListenerOrientationArray(float AtOrient[6]);
}
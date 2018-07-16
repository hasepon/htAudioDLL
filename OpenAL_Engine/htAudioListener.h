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
	
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaListenerPosition(AudioListener* Instance,float x, float y, float z);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaListenerPositionArray(AudioListener* Instance, float Pos[3]);
	
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaListenerVelocity(AudioListener* Instance, float x, float y, float z);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaListenerVelocityArray(AudioListener* Instance, float Pos[3]);
	
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaListenerOrientation(AudioListener* Instance, float AtVec[3],float UpVec[3]);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaListenerOrientationArray(AudioListener* Instance, float AtOrient[6]);

	/*UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaListenerSetConeOuterGain(AudioListener* Instance,float val);
	UNITY_INTERFACE_EXPORT float UNITY_INTERFACE_API htaListenerGetConeOuterGain(AudioListener* Instance);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaListenerSetConeInnerAngle(AudioListener* Instance, float val);
	UNITY_INTERFACE_EXPORT float UNITY_INTERFACE_API htaListenerGetConeInnerAngle(AudioListener* Instance);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaListenerSetConeOuterAngle(AudioListener* Instance, float val);
	UNITY_INTERFACE_EXPORT float UNITY_INTERFACE_API htaListenerGetConeOuterAngle(AudioListener* Instance);*/

}
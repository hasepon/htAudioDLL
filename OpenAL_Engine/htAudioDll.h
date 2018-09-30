#pragma once

#include"Definclude.h"

#include"OpenAL/AudioSpeaker/AudioSpeaker.h"
#include"OpenAL/AudioListener/AudioListener.h"
#include"OpenAL/OpenAlCore/OpenALDevice.h"

#include"I3DAudio.h"
#include"ConeState.h"
#include"ReverbEffects.h"
#include"AudioManager.h"

using namespace htAudio;


/// <summary>
/// これは設定用のdll
/// </summary>
extern "C" {

	// デバイス、Manager
	UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API htaCreate(OpenALDevice* instance);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaDelete(OpenALDevice* Instance);

	// Listenerの機能
	UNITY_INTERFACE_EXPORT AudioListener* UNITY_INTERFACE_API htaListenerCreate();
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaListenerDelete(AudioListener*);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaListenerPosition(AudioListener* Instance, float x, float y, float z);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaListenerPositionArray(AudioListener* Instance, float Pos[3]);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaListenerVelocity(AudioListener* Instance, float x, float y, float z);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaListenerVelocityArray(AudioListener* Instance, float Pos[3]);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaListenerOrientation(AudioListener* Instance, float AtVec[3], float UpVec[3]);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaListenerOrientationArray(AudioListener* Instance, float AtOrient[6]);

	// Speaker関係
	UNITY_INTERFACE_EXPORT int UNITY_INTERFACE_API htaSpeakerCreate(AudioManager* mgtPtr, wchar_t* filepath, wchar_t* soundname, wchar_t* material);
	UNITY_INTERFACE_EXPORT int UNITY_INTERFACE_API htaSpeakerCreateID(AudioManager* mgtPtr, wchar_t* filepath, uint16_t id);
	UNITY_INTERFACE_EXPORT int UNITY_INTERFACE_API htaSpeakerCreateName(AudioManager* mgtPtr, wchar_t* filepath, wchar_t* soundname);	
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaSpeakerDelete(AudioManager* mgtPtr, int Numb);
	UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API Play(int speakerId);
	UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API Stop(int speakerId);
	UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API Pause(int speakerId);
	UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API Formatflag(AudioManager* mgtPtr, int speakerId);

	// Effectの機能
	
	/* 3DAudio関係 */
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaAddI3DAudio(AudioManager* mgtPtr,int speakerId, I3DAudioInfo* info);
	
	/* Corn関係 */
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaAddCone(AudioManager* mgtPtr, int speakerId, float innerangle, float outerangle, float outergain);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API  htaSpeakerSetConeOuterGain( int speakerId, float val);
	UNITY_INTERFACE_EXPORT float UNITY_INTERFACE_API htaSpeakerGetConeOuterGain( int speakerId );
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API  htaSpeakerSetConeInnerAngle(int speakerId, float val);
	UNITY_INTERFACE_EXPORT float UNITY_INTERFACE_API htaSpeakerGetConeInnerAngle(int speakerId );
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API  htaSpeakerSetConeOuterAngle(int speakerId, float val);
	UNITY_INTERFACE_EXPORT float UNITY_INTERFACE_API htaSpeakerGetConeOuterAngle(int speakerId );

	/* Reverb関係 */
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaAddReverb(AudioManager* mgtPtr, int speakerId, REVERB_INFO* info);


}
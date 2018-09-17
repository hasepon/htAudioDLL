#pragma once

#include"Definclude.h"

#include"OpenAL/AudioSpeaker/AudioSpeaker.h"
#include"OpenAL/AudioListener/AudioListener.h"
#include"OpenAL/OpenAlCore/OpenALDevice.h"

#include"AudioManager.h"

using namespace htAudio;

extern "C" {
	// Speaker作成
	UNITY_INTERFACE_EXPORT int UNITY_INTERFACE_API htaSpeakerCreate(AudioManager* mgtPtr, wchar_t* filepath, wchar_t* soundname, wchar_t* material);
	UNITY_INTERFACE_EXPORT int UNITY_INTERFACE_API htaSpeakerCreateID(AudioManager* mgtPtr, wchar_t* filepath, uint16_t id);
	UNITY_INTERFACE_EXPORT int UNITY_INTERFACE_API htaSpeakerCreateName(AudioManager* mgtPtr, wchar_t* filepath, wchar_t* soundname);
	
	// Speakerの機能
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaSpeakerDelete(AudioManager* mgtPtr, int Numb);
	UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API Play(int speakerId);
	UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API Stop(int speakerId);
	UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API Pause(int speakerId);
	UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API Formatflag(AudioManager* mgtPtr, int speakerId);

	// Effectの機能
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaSpeakerPosition(AudioSpeaker*, float x, float y, float z);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaSpeakerPositionArray(AudioSpeaker*, float Pos[3]);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaSpeakerVelocity(AudioSpeaker* instance, float x, float y, float z);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaSpeakerVelocityArray(AudioSpeaker* instance, float Vec[3]);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaSpeakerDirection(AudioSpeaker* instance, float x, float y, float z);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaSpeakerDirectionArray(AudioSpeaker* instance, float dir[3]);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API  htaSpeakerSetConeOuterGain(AudioSpeaker* Instance, float val);
	UNITY_INTERFACE_EXPORT float UNITY_INTERFACE_API htaSpeakerGetConeOuterGain(AudioSpeaker* Instance);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API  htaSpeakerSetConeInnerAngle(AudioSpeaker* Instance, float val);
	UNITY_INTERFACE_EXPORT float UNITY_INTERFACE_API htaSpeakerGetConeInnerAngle(AudioSpeaker* Instance);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API  htaSpeakerSetConeOuterAngle(AudioSpeaker* Instance, float val);
	UNITY_INTERFACE_EXPORT float UNITY_INTERFACE_API htaSpeakerGetConeOuterAngle(AudioSpeaker* Instance);

	// Listenerの機能
	UNITY_INTERFACE_EXPORT AudioListener* UNITY_INTERFACE_API htaListenerCreate();
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaListenerDelete(AudioListener*);

	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaListenerPosition(AudioListener* Instance, float x, float y, float z);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaListenerPositionArray(AudioListener* Instance, float Pos[3]);

	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaListenerVelocity(AudioListener* Instance, float x, float y, float z);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaListenerVelocityArray(AudioListener* Instance, float Pos[3]);

	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaListenerOrientation(AudioListener* Instance, float AtVec[3], float UpVec[3]);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaListenerOrientationArray(AudioListener* Instance, float AtOrient[6]);

	// デバイス、Manager
	UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API htaCreate(OpenALDevice* instance);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaDelete(OpenALDevice* Instance);


}
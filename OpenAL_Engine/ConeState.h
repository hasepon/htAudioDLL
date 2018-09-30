#pragma once

#include "AudioEffects.h"
#include"OpenAL/OpenAlCore/OpenALDevice.h"

namespace htAudio {

	class ConeState : public AudioEffects
	{
	public:
		ConeState(ALuint source);
		~ConeState();

		void SetConeOuterGain(float val);
		float GetConeOuterGain();

		void SetConeInnerAngle(float val);
		float GetConeInnerAngle();

		void SetConeOuterAngle(float val);
		float GetConeOuterAngle();

	private:
		ALuint Source;

		ALfloat ConeOuterGain;	// コーンの外部ゲイン数値
		ALfloat InnerAngle;		// 内部の角度
		ALfloat OuterAngle;		// 外部の角度

	};

}
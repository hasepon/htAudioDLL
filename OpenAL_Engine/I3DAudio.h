#pragma once

#include "AudioEffects.h"
#include"OpenAL/OpenAlCore/OpenALDevice.h"
#include"ConeState.h"

namespace htAudio {

	struct I3DAudioInfo
	{
		ALfloat* Position[3];	// Position
		ALfloat* Velocity[3];	// 移動速度
		ALfloat* Direction[3];	// 向き
	};

	class I3DAudio : public AudioEffects
	{
	public:
		I3DAudio(ALuint source, I3DAudioInfo* info);
		~I3DAudio();

		void SetPosition(float* x, float* y, float* z);
		void SetPosition(float* pos[3]);

		void SetVelocity(float* x, float* y, float* z);
		void SetVelocity(float* vec[3]);

		void SetDirection(float* x, float* y, float* z);
		void SetDirection(float* dir[3]);

		void Update();

	private:

		ALuint Source;

		// 受け渡しで大丈夫な情報
		float Gain;
		
		// ポインタで欲しい情報
		I3DAudioInfo* Info;

	};

}
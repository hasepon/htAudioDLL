#pragma once

#include "AudioEffects.h"
#include"OpenAL/OpenAlCore/OpenALDevice.h"
#include"ConeState.h"

namespace htAudio {

	class I3DAudio : public AudioEffects
	{
	public:
		I3DAudio(ALuint source);
		~I3DAudio();

		void SetPosition(float* x, float* y, float* z);
		void SetPosition(float* pos[3]);

		void SetVelocity(float* x, float* y, float* z);
		void SetVelocity(float* vec[3]);

		void SetDirection(float* x, float* y, float* z);
		void SetDirection(float* dir[3]);

	private:
		ALuint Source;

		ALfloat* Position[3];	// Position
		ALfloat* Velocity[3];	// ˆÚ“®‘¬“x
		ALfloat* Direction[3];	// Œü‚«

	};

}
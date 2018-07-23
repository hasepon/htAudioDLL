#pragma once
#include "AudioEffects.h"
#include"OpenAL/OpenAlCore/OpenALDevice.h"

namespace htAudio
{
	struct PITCH_INFO
	{
		uint16_t COARSE_TUNE;
		uint16_t FINE_TUNE;
	};

	class PitchEffect : public AudioEffects
	{
	public:
		PitchEffect(ALuint source);
		~PitchEffect();

		void SetCoarse(int coarse);
		void SetFine(int fine);

	private:

		PITCH_INFO Info;

	};

}
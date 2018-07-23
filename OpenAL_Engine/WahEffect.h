#pragma once
#include "AudioEffects.h"
#include"OpenAL/OpenAlCore/OpenALDevice.h"

namespace htAudio {

	struct WAH_INFO
	{
		double ATTACK_TIME;
		double RELEASE_TIME;
		double RESONANCE;
		double PEAK_GAIN;
	};

	class WahEffect :public AudioEffects
	{
	public:
		WahEffect(ALuint source);
		~WahEffect();

		void SetAttackTime(float time);
		void SetReleaseTime(float time);
		void SetResonance(float val);
		void SetPeakGain(float gain);

	private:
		WAH_INFO Info;

	};

}
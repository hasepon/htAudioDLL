#pragma once
#include "AudioEffects.h"
#include"OpenAL/OpenAlCore/OpenALDevice.h"

namespace htAudio
{

	struct CHORUS_INFO
	{
		uint16_t WAVEROTM;
		uint16_t PHASE;
		double RATE;
		double DEPTH;
		double FEEDBACK;
		double DELAY;
	};

	class ChorusEffect :
		public AudioEffects
	{
	public:
		ChorusEffect(ALuint source);
		~ChorusEffect();
	
		void SetWaveForm(int form);
		void SetPhase(int value);
		void SetRate(float rate);
		void SetDepth(float value);
		void SetFeedBack(float value);
		void SetDelay(float value);

	private:
		CHORUS_INFO Info;

	};
}
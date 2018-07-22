#pragma once
#include "AudioEffects.h"
#include"OpenAL/OpenAlCore/OpenALDevice.h"

namespace htAudio {

	struct ECHO_INFO
	{
		double DELAY;
		double LRDELAY;
		double DAMPING;
		double FEEDBACK;
		double SPREAD;
	};

	class EchoEffect : public AudioEffects
	{
	public:
		EchoEffect(ALuint source);
		~EchoEffect();

		void SetDelay(float delay);
		void SetLRDelay(float lrdelay);
		void SetDamping(float damping);
		void SetFeedBack(float feedback);
		void SetSpRead(float spread);

	private:
		ECHO_INFO Info;

	};

}
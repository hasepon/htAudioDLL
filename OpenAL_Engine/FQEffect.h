#pragma once
#include "AudioEffects.h"
#include"OpenAL/OpenAlCore/OpenALDevice.h"

namespace htAudio {

	struct FQ_INFO
	{
		double FREQUENCY;
		uint16_t LEFT_DIRECTION;
		uint16_t RIGHT_DIRECTION;
	};

	class FQEffect : public AudioEffects
	{
	public:
		FQEffect(ALuint source);
		~FQEffect();

		void SetFrequency(float fq);
		void SetLRDirection(int left , int right);

	private:
		FQ_INFO Info;

	};

}
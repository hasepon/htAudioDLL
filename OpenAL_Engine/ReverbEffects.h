#pragma once

#include "AudioEffects.h"
#include"OpenAL/OpenAlCore/OpenALDevice.h"

namespace htAudio
{
	struct REVERB_INFO
	{
		double DENSITY;
		double DIFFUSION;
		double GAIN;
		double GAINHF;
		double DECAY_TIME;
		double DECAY_HFRATIO;
		double REFLECTIONS_GAIN;
		double REFLECTIONS_DELAY;
		double LATE_GAIN;
		double LATE_DELAY;
		double ROOM_ROLL_OFF;
		double AIR_GAINHF;
		int16_t AIR_HFLIMIT;
	};

	class ReverbEffects : public AudioEffects
	{
	public:
		ReverbEffects(ALuint source);
		~ReverbEffects();

		void SetInfo(REVERB_INFO* Info);

		void SetDensity(float density);
		void SetDiffusion(float diffusion);
		void SetGain(float gain,float gainhf);
		void SetDecay(float time , float hfratio);
		void SetReflection(float gain ,float delay);
		void SetLate(float gain, float reflection);
		void SetRoomRollOff(float val);
		void SetAir(float gainhf, int hflimit);

	private:
		REVERB_INFO* Info;		// ÉäÉoÅ[ÉuèÓïÒ
	};

}
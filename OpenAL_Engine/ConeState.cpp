#include "ConeState.h"

namespace htAudio
{

	ConeState::ConeState(ALuint source)
	{
		Source = source;
	}


	ConeState::~ConeState()
	{
	}


	void ConeState::SetConeOuterGain(float val)
	{
		ConeOuterGain = val;
		alSourcef(Source, AL_CONE_OUTER_GAIN, ConeOuterGain);
	}

	float ConeState::GetConeOuterGain()
	{
		alGetSourcef(Source, AL_CONE_OUTER_GAIN, &ConeOuterGain);
		return ConeOuterGain;
	}

	void ConeState::SetConeInnerAngle(float val)
	{
		InnerAngle = val;
		alSourcef(Source, AL_CONE_INNER_ANGLE, InnerAngle);
	}

	float ConeState::GetConeInnerAngle()
	{
		alGetSourcef(Source, AL_CONE_INNER_ANGLE, &InnerAngle);
		return InnerAngle;
	}

	void ConeState::SetConeOuterAngle(float val)
	{
		OuterAngle = val;
		alSourcef(Source, AL_CONE_OUTER_ANGLE, OuterAngle);
	}

	float ConeState::GetConeOuterAngle()
	{
		alGetSourcef(Source, AL_CONE_OUTER_ANGLE, &OuterAngle);
		return OuterAngle;
	}


}
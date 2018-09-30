#include "I3DAudio.h"


namespace htAudio {

	I3DAudio::I3DAudio(ALuint source, I3DAudioInfo* info)
	{
		Source = source;
		Info = info;
	}


	I3DAudio::~I3DAudio()
	{
	}

	void I3DAudio::Update()
	{
		alSourcefv(Source, AL_POSITION,  *Info->Position);
		alSourcefv(Source, AL_DIRECTION, *Info->Direction);
		alSourcefv(Source, AL_VELOCITY,  *Info->Velocity);
	}

	void I3DAudio::SetPosition(float* x, float* y, float* z)
	{
		Info->Position[0] = x;
		Info->Position[1] = y;
		Info->Position[2] = z;

		alSourcefv(Source, AL_POSITION, *Info->Position);
	}

	void I3DAudio::SetPosition(float* pos[3])
	{
		Info->Position[0] = pos[0];
		Info->Position[1] = pos[1];
		Info->Position[2] = pos[2];

		alSourcefv(Source, AL_POSITION, *Info->Position);
	}

	void I3DAudio::SetVelocity(float* x, float* y, float* z)
	{
		Info->Velocity[0] = x;
		Info->Velocity[1] = y;
		Info->Velocity[2] = z;

		alSourcefv(Source, AL_VELOCITY, *Info->Velocity);
	}

	void I3DAudio::SetVelocity(float* vec[3])
	{
		Info->Velocity[0] = vec[0];
		Info->Velocity[1] = vec[1];
		Info->Velocity[2] = vec[2];

		alSourcefv(Source, AL_VELOCITY, *Info->Velocity);
	}

	void I3DAudio::SetDirection(float* x, float* y, float* z)
	{
		Info->Direction[0] = x;
		Info->Direction[1] = y;
		Info->Direction[2] = z;
		alSourcefv(Source, AL_DIRECTION, *Info->Direction);
	}

	void I3DAudio::SetDirection(float* dir[3])
	{
		Info->Direction[0] = dir[0];
		Info->Direction[1] = dir[1];
		Info->Direction[2] = dir[2];
		alSourcefv(Source, AL_DIRECTION, *Info->Direction);
	}

}
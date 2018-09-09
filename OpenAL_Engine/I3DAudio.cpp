#include "I3DAudio.h"


namespace htAudio {

	I3DAudio::I3DAudio(ALuint source)
	{
		Source = source;
		Cone = new ConeState(Source);
	}


	I3DAudio::~I3DAudio()
	{
	}


	void I3DAudio::SetPosition(float x, float y, float z)
	{
		Position[0] = x;
		Position[1] = y;
		Position[2] = z;

		alSourcefv(Source, AL_POSITION, Position);
	}

	void I3DAudio::SetPosition(float pos[3])
	{
		Position[0] = pos[0];
		Position[1] = pos[1];
		Position[2] = pos[2];

		alSourcefv(Source, AL_POSITION, pos);
	}

	void I3DAudio::SetVelocity(float x, float y, float z)
	{
		Velocity[0] = x;
		Velocity[1] = y;
		Velocity[2] = z;

		alSourcefv(Source, AL_VELOCITY, Velocity);
	}

	void I3DAudio::SetVelocity(float vec[3])
	{
		Velocity[0] = vec[0];
		Velocity[1] = vec[1];
		Velocity[2] = vec[2];

		alSourcefv(Source, AL_VELOCITY, Velocity);
	}

	void I3DAudio::SetDirection(float x, float y, float z)
	{
		Direction[0] = x;
		Direction[1] = y;
		Direction[2] = z;
		alSourcefv(Source, AL_DIRECTION, Direction);
	}

	void I3DAudio::SetDirection(float dir[3])
	{
		Direction[0] = dir[0];
		Direction[1] = dir[1];
		Direction[2] = dir[2];
		alSourcefv(Source, AL_DIRECTION, Direction);
	}




}
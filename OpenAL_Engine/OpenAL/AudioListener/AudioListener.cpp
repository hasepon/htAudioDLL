#include "AudioListener.h"
#include"../AudioFormatData/AudioFormatData.h"

namespace htAudio {

	AudioListener::AudioListener()
	{
	}

	AudioListener::~AudioListener()
	{
	}

	void AudioListener::Setposition(float Pos[3])
	{
		Position[0] = Pos[0];
		Position[1] = Pos[1];
		Position[2] = Pos[2];

		alListenerfv(AL_POSITION, Position);
	}

	void AudioListener::Setposition(float x, float y, float z)
	{

		Position[0] = x;
		Position[1] = y;
		Position[2] = z;

		alListenerfv(AL_POSITION, Position);

	}

	void AudioListener::SetVelocity(float x, float y, float z)
	{

		Velocity[0] = x;
		Velocity[1] = y;
		Velocity[2] = z;

		alListenerfv(AL_VELOCITY, Velocity);
	}

	void AudioListener::SetVelocity(float vec[3])
	{

		Velocity[0] = vec[0];
		Velocity[1] = vec[1];
		Velocity[2] = vec[2];

		alListenerfv(AL_VELOCITY, Velocity);
	}

	void AudioListener::SetOrientation(float AtVec[3], float UpVec[3])
	{

		Pose[0] = AtVec[0];
		Pose[1] = AtVec[1];
		Pose[2] = AtVec[2];

		Pose[3] = UpVec[0];
		Pose[4] = UpVec[1];
		Pose[5] = UpVec[2];

		alListenerfv(AL_ORIENTATION, Pose);
	}

	void AudioListener::SetOrientation(float Orient[6])
	{
		Pose[0] = Orient[0];
		Pose[1] = Orient[1];
		Pose[2] = Orient[2];

		Pose[3] = Orient[3];
		Pose[4] = Orient[4];
		Pose[5] = Orient[5];

		alListenerfv(AL_ORIENTATION, Pose);
	}
	
}
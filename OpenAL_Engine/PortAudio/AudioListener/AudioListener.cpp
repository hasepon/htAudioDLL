#include "AudioListener.h"

namespace htAudio {

	AudioListener::AudioListener(float Pos[3], float Vel[3], float view[3], float pose[3])
	{
		Position[0] = Pos[0];
		Position[1] = Pos[1];
		Position[2] = Pos[2];

		Velocity[0] = Vel[0];
		Velocity[1] = Vel[1];
		Velocity[2] = Vel[2];

		Pose[0] = view[0];
		Pose[1] = view[1];
		Pose[2] = view[2];
		Pose[3] = pose[0];
		Pose[4] = pose[1];
		Pose[5] = pose[2];

		//alListenerfv(AL_POSITION, Position);
		alListener3f(AL_POSITION, Position[0], Position[1], Position[2]);
		alListenerfv(AL_VELOCITY, Velocity);
		alListenerfv(AL_ORIENTATION, Pose);

	}


	AudioListener::~AudioListener()
	{
	}


	void AudioListener::Setposition(float Pos[3])
	{
		alListenerfv(AL_POSITION, Pos);
	}

}
#include "AudioListener.h"

namespace htAudio {

	AudioListener::AudioListener(float* Pos[3], float* Vel[3], float* view[3], float* pose[3])
	{
		*Position = *Pos;
		*Velocity = *Vel;
		Pose[0] = view[0];
		Pose[1] = view[1];
		Pose[2] = view[2];
		Pose[3] = pose[0];
		Pose[4] = pose[1];
		Pose[5] = pose[2];

		alListenerfv(AL_POSITION, *Position);
		alListenerfv(AL_VELOCITY, *Velocity);
		alListenerfv(AL_ORIENTATION, *Pose);

	}


	AudioListener::~AudioListener()
	{
	}
}
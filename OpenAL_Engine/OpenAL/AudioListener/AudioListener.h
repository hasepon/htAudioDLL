#pragma once

#include"../OpenAlCore/OpenALDevice.h"
#include<array>

namespace htAudio {
	class AudioListener
	{
	public:
		AudioListener(float Pos[3], float Vel[3], float view[3], float Pose[3]);
		~AudioListener();

		void Setposition(float Pos[3]);

	private:
		ALfloat Position[3];
		ALfloat Velocity[3];
		ALfloat Pose[6];
	};
}
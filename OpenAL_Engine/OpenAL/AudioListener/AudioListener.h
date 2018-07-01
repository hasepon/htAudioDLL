#pragma once

#include"../OpenAlCore/OpenALDevice.h"
#include<array>

namespace htAudio {
	class AudioListener
	{
	public:
		AudioListener();
		~AudioListener();

		void Setposition(float x,float y,float z);
		void Setposition(float Pos[3]);

		void SetVelocity(float x, float y, float z);
		void SetVelocity(float vec[3]);;

		void SetOrientation(float AtVec[3],float UpVec[3]);
		void SetOrientation(float Orient[6]);

	private:
		ALfloat Position[3];
		ALfloat Velocity[3];
		ALfloat Pose[6];
	};
}
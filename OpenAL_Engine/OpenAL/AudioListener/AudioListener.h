#pragma once

#include"../OpenAlCore/OpenALDevice.h"
#include<array>

namespace htAudio {

	/// <summary>
	/// リスナーに使用するステート群
	/// 外部ファイルへ読み込み/掻き込みするstateを持つ
	/// </summary>
	struct ListenerStates
	{
		float OuterGain;
		float InnerAngle;
		float OuterAngle;
	};

	/// <summary>
	/// リスナーの設定等をするクラス
	/// </summary>
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

		/*void SetConeOuterGain(float angle);
		void SetConeInnerAngle(float angle);
		void SetConeOuterAngle(float angle);
		float GetConeOuterGain();
		float GetConeInnerAngle();
		float GetConeOuterAngle();*/

	private:
		ListenerStates States;
		ALfloat Position[3];
		ALfloat Velocity[3];
		ALfloat Pose[6];

		std::string Path;

	};

}
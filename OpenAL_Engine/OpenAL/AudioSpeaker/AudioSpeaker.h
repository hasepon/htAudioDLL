#pragma once


#include"../OpenAlCore/OpenALDevice.h"
#include"../FileLoad/LoadSoundFile.h"
#include<string>
#include<memory>
#include<array>
#include<complex.h>
#include<AL/efx-creative.h>

using namespace std;

namespace htAudio
{
	/// <summary>
	/// サウンドの再生用クラス
	/// サウンド再生の窓口クラス
	/// </summary>
	class AudioSpeaker
	{
	public:
		// 情報指定
		AudioSpeaker(std::string filepath, std::string SoundName, std::string material);
		// ID指定
		AudioSpeaker(std::string filepath, int id);
		//指定なし
		AudioSpeaker(std::string filepath, std::string SoundName);
		
		~AudioSpeaker();// デスト

		bool Play();	// 再生
		bool Update();	// 更新
		bool Stop();	// 停止
		bool Pause();	// 一時停止
		bool GetResourceflag() { return AudioResource.Soundtype.CreateFlag; }

		void SetPosition(float x, float y, float z);
		void SetPosition(float pos[3]);

		void SetVelocity(float x, float y, float z);
		void SetVelocity(float vec[3]);

		//void SetOrientation(float AtVec[3], float UpVec[3]);
		//void SetOrientation(float AtOrient[6]);

		void SetDirection(float x, float y, float z);
		void SetDirection(float dir[3]);

		void SetConeOuterGain(float val);
		float GetConeOuterGain();

		void SetConeInnerAngle(float val);
		float GetConeInnerAngle();

		void SetConeOuterAngle(float val);
		float GetConeOuterAngle();

		//float GetMaxVolume();
		//float GetLowVolume();
		//float GetDefaultVolume();

	private:
		bool SetBuffer(ALuint Buf);	// バッファの設定
		void Init();

		bool Successinit = false;	// 初期化成功

		std::shared_ptr<CLoadSoundFile> AudioSource;	// バッファー情報
		SoundResources AudioResource;	// オーディオ情報

		std::u16string UseMaterialAtt;		// マテリアルの設定
		std::string Filepath;

		//OpenAL用
		std::array<ALuint,2> Buffers;// バッファの設定
		ALuint Source;	// Sourceの設定

		// speaker情報
		ALfloat Position[3];	// Position
		ALfloat Volume;			// ボリューム
		ALfloat Velocity[3];	// 移動速度
		//ALfloat Orientation[6];	// 姿勢
		ALfloat Direction[3];	// 向き
		ALfloat ConeOuterGain;	
		ALfloat InnerAngle;
		ALfloat OuterAngle;

	};

}
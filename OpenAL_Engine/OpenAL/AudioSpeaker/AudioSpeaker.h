#pragma once


#include"../OpenAlCore/OpenALDevice.h"
#include"../FileLoad/LoadSoundFile.h"
#include<string>
#include<memory>
#include<array>
#include<complex.h>

#include<AL/efx.h>
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

		void SetDirection(float x, float y, float z);
		void SetDirection(float dir[3]);

		void SetConeOuterGain(float val);
		float GetConeOuterGain();

		void SetConeInnerAngle(float val);
		float GetConeInnerAngle();

		void SetConeOuterAngle(float val);
		float GetConeOuterAngle();

		bool AddEffects(EFFECTSNUM num);
		
		void SetReverb(float density, float diffusion, float gain, float decayTime);
		
	private:
		bool SetBuffer(ALuint Buf);						// バッファの設定
		void Init();									// 共通初期化処理
		bool SettingEffect(EFFECTSNUM,int EffectDef);	// エフェクト実装部

		bool Successinit = false;						// 初期化成功フラグ

		std::shared_ptr<CLoadSoundFile> AudioSource;	// バッファー情報
		SoundResources AudioResource;					// オーディオ情報

		std::string UseMaterialAtt;						// マテリアルの設定
		std::string Filepath;							// ファイルパス

		std::array<ALuint,2> Buffers;					// バッファの設定
		ALuint Source;									// Sourceの設定
		
		std::array<ALuint, MAX_EFFECTS> EffectSlot;		// エフェクトスロット
		std::array<ALuint, MAX_EFFECTS> Effect;			// エフェクト

		// speaker情報
		ALfloat Position[3];	// Position
		ALfloat Volume;			// ボリューム
		ALfloat Velocity[3];	// 移動速度
		ALfloat Direction[3];	// 向き
		ALfloat ConeOuterGain;	// コーンの外部ゲイン数値
		ALfloat InnerAngle;		// 内部の角度
		ALfloat OuterAngle;		// 外部の角度

	};

}
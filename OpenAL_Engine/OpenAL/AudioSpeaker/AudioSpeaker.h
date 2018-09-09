#pragma once

#include"../OpenAlCore/OpenALDevice.h"
#include"../FileLoad/LoadSoundFile.h"
#include"../../I3DAudio.h"
#include<string>
#include<memory>
#include<array>
#include<complex.h>
#include<future>

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
		void StopUpdate();

		bool AddEffects(EFFECTSNUM num);
		
	private:
		bool SetBuffer(ALuint Buf);						// バッファの設定
		void Init();									// 共通初期化処理
		bool SettingEffect(EFFECTSNUM,int EffectDef);	// エフェクト実装部

		bool Successinit = false;						// 初期化成功フラグ
		bool LoopFlag = true;							// updateloopフラグ

		std::shared_ptr<CLoadSoundFile> AudioSource;	// バッファー情報
		SoundResources AudioResource;					// オーディオ情報

		std::string UseMaterialAtt;						// マテリアルの設定
		std::string Filepath;							// ファイルパス

		std::array<ALuint,2> Buffers;					// バッファの設定
		ALuint Source;									// Sourceの設定
		
		std::array<ALuint, MAX_EFFECTS> EffectSlot;		// エフェクトスロット
		std::array<ALuint, MAX_EFFECTS> Effect;			// エフェクト

		ALfloat Volume;			// ボリューム
		I3DAudio* I3D;

		std::thread UpdateThread;	// 自動アップデート用のスレッド

	};

}
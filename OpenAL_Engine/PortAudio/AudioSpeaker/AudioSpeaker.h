#pragma once


#include"../OpenAlCore/OpenALDevice.h"
#include"../FileLoad/LoadSoundFile.h"
#include<string>
#include<memory>

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
		
	private:
		bool SetBuffer(ALuint Buf);	// バッファの設定
		void Init();

		CLoadSoundFile * AudioSource;	// バッファー情報
		SoundResources AudioResource;	// オーディオ情報

		std::string UseMaterialAtt;		// マテリアルの設定

		//OpenAL用
		ALuint Buffers[2];// バッファの設定
		ALuint Source;	// Sourceの設定

	};

}
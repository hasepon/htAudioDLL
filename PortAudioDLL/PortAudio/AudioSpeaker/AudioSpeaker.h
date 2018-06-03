#pragma once

#include"../OpenAlCore/OpenAlCore.h"
#include"../FileLoad/LoadSoundFile.h"
#include<string>
#include<memory>

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
	CLoadSoundFile* AudioSource;	// バッファー情報
	SoundResources AudioResource;	// オーディオ情報

	std::string UseMaterialAtt;

	//OpenAL用
	ALint Buf;
	ALuint Source;


};


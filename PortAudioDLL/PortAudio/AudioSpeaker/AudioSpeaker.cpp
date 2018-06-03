#include "AudioSpeaker.h"
#include"../FileLoad/Ogg/LoadOgg.h"
#include"../FileLoad/Wave/LoadWave.h"
#include"../AudioFormatData/AudioFormatData.h"
#include"../../Singleton.h"

/// <summary>
/// 再生情報の初期化
/// </summary>
/// <param name="filepath"></param>
/// <param name="SoundName"></param>
/// <param name="material"></param>
AudioSpeaker::AudioSpeaker(std::string filepath, std::string SoundName, std::string material)
{

	// オーディオ情報をxmlから取得
	AudioFormatData afd;
	AudioResource.Soundtype = afd.GetAudioFormatData(filepath, SoundName);

	// 属性を拾っているので処理
	// 取得情報から実データを取得
	for (auto var : AudioResource.Soundtype.Soundinfo)
	{
		// マテリアルの同一オブジェクトの検索
		if (material == var.MaterialObj)
		{
			if (var.Extension == "wav")
			{
				AudioSource = new CLoadWave(var.SoundName, AudioResource.Soundtype.Loopflag);
			}
			else if (var.Extension == "ogg")
			{
				AudioSource = new CLoadOgg(var.SoundName, AudioResource.Soundtype.Loopflag);
			}
			else {
				printf("ファイル形式が対応していない形式です");
			}
		}
	}

}

AudioSpeaker::AudioSpeaker(std::string filepath,int id)
{

	// オーディオ情報をxmlから取得
	AudioFormatData afd;
	AudioResource.Soundtype = afd.GetAudioFormatData(filepath, id);

	// マテリアルの設定がない場合id[0]の音を鳴らす
	if (AudioResource.Soundtype.Soundinfo[id].Extension == "wav")
	{
		AudioSource = new CLoadWave(AudioResource.Soundtype.Soundinfo[id].SoundName, AudioResource.Soundtype.Loopflag);
	}
	else if (AudioResource.Soundtype.Soundinfo[id].Extension == "ogg")
	{
		AudioSource = new CLoadOgg(AudioResource.Soundtype.Soundinfo[id].SoundName, AudioResource.Soundtype.Loopflag);
	}
	else {
		printf("ファイル形式が対応していない形式です");
	}
}

AudioSpeaker::AudioSpeaker(std::string filepath, std::string SoundName)
{
	// オーディオ情報をxmlから取得
	AudioFormatData afd;
	AudioResource.Soundtype = afd.GetAudioFormatData(filepath, SoundName);

	// マテリアルの設定がない場合id[0]の音を鳴らす
	if (AudioResource.Soundtype.Soundinfo[0].Extension == "wav")
	{
		AudioSource = new CLoadWave(AudioResource.Soundtype.Soundinfo[0].SoundName, AudioResource.Soundtype.Loopflag);
	}
	else if (AudioResource.Soundtype.Soundinfo[0].Extension == "ogg")
	{
		AudioSource = new CLoadOgg(AudioResource.Soundtype.Soundinfo[0].SoundName, AudioResource.Soundtype.Loopflag);
	}
	else {
		printf("ファイル形式が対応していない形式です");
	}

	AudioSource->Update();
	Buf = (ALint)AudioSource->GetPrimaryOggbuffer();
	OpenAlCore& OAC = Singleton<OpenAlCore>::get_instance();
	Source = OAC.SetBuffer(Buf);
}

AudioSpeaker::~AudioSpeaker()
{
	OpenAlCore& OAC = Singleton<OpenAlCore>::get_instance();
	OAC.Clear(Source, Buf);
	delete AudioSource;
}

bool AudioSpeaker::Play()
{
	printf("再生します\n");
	OpenAlCore& OAC = Singleton<OpenAlCore>::get_instance();
	OAC.Play(Source);
	return true;
}

bool AudioSpeaker::Update()
{
	printf("更新します\n"); 
	AudioSource->Update();
	Buf = (ALint)AudioSource->GetPrimaryOggbuffer();
	OpenAlCore& OAC = Singleton<OpenAlCore>::get_instance();
	OAC.SetBuffer(Buf);
	return true;
}

bool AudioSpeaker::Stop()
{
	printf("停止します\n");
	OpenAlCore& OAC = Singleton<OpenAlCore>::get_instance();
	OAC.Stop(Source);
	
	return true;
}

bool AudioSpeaker::Pause() 
{
	printf("中断します\n");
	OpenAlCore& OAC = Singleton<OpenAlCore>::get_instance();
	OAC.Pause(Source);
	return true;
}


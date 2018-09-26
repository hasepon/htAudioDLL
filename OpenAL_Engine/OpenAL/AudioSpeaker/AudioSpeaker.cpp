#include "AudioSpeaker.h"
#include"../FileLoad/Ogg/LoadOgg.h"
#include"../FileLoad/Wave/LoadWave.h"
#include"../AudioFormatData/AudioFormatData.h"

namespace htAudio {

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
		
		int id;

		Filepath = filepath;
		if (AudioResource.Soundtype.CreateFlag == true)
		{
			// 属性を拾っているので処理
			// 取得情報から実データを取得
			for (auto var : AudioResource.Soundtype.Soundinfo)
			{
				// マテリアルの同一オブジェクトの検索
				if (material == var.MaterialObj)
				{
					if (var.Extension == "wav")
					{
						id = var.Id;
						std::shared_ptr<CLoadSoundFile> shard(new CLoadWave(var.SoundName, AudioResource.Soundtype, filepath));
						AudioSource = shard;
					}
					else if (var.Extension == "ogg")
					{
						id = var.Id;
						std::shared_ptr<CLoadSoundFile> shard(new CLoadOgg(var.SoundName, AudioResource.Soundtype, filepath));
						AudioSource = shard;
					}
					else {
						printf("ファイル形式が対応していない形式です");
					}
				}
			}
			Init();
		}
	}

	AudioSpeaker::AudioSpeaker(std::string filepath, int id)
	{
		// オーディオ情報をxmlから取得
		AudioFormatData afd;
		AudioResource.Soundtype = afd.GetAudioFormatData(filepath, id);

		Filepath = filepath;
		if (AudioResource.Soundtype.CreateFlag == true)
		{
			// マテリアルの設定がない場合id[0]の音を鳴らす
			if (AudioResource.Soundtype.Soundinfo[id].Extension == "wav")
			{
				std::shared_ptr<CLoadSoundFile> shard(new CLoadWave(AudioResource.Soundtype.Soundinfo[id].SoundName, AudioResource.Soundtype, filepath));
				AudioSource = shard;
			}
			else if (AudioResource.Soundtype.Soundinfo[id].Extension == "ogg")
			{
				std::shared_ptr<CLoadSoundFile> shard(new CLoadOgg(AudioResource.Soundtype.Soundinfo[id].SoundName, AudioResource.Soundtype, filepath));
				AudioSource = shard;
			}
			else {
				printf("ファイル形式が対応していない形式です");
			}
			Init();
		}
	}

	AudioSpeaker::AudioSpeaker(std::string filepath, std::string SoundName)
	{
		// オーディオ情報をxmlから取得
		AudioFormatData afd;
		AudioResource.Soundtype = afd.GetAudioFormatData(filepath, SoundName);

		Filepath = filepath;

		if (AudioResource.Soundtype.CreateFlag == true)
		{
			// マテリアルの設定がない場合id[0]の音を鳴らす
			if (AudioResource.Soundtype.Soundinfo[0].Extension == "wav")
			{
				std::shared_ptr<CLoadSoundFile> shard(new CLoadWave(AudioResource.Soundtype.Soundinfo[0].SoundName, AudioResource.Soundtype, filepath));
				AudioSource = shard;

				alSourcef(Source, AL_MAX_GAIN, (ALfloat)AudioResource.Soundtype.Soundinfo[0].MaxVolume);     // 音量
			}
			else if (AudioResource.Soundtype.Soundinfo[0].Extension == "ogg")
			{
				std::shared_ptr<CLoadSoundFile> shard(new CLoadOgg(AudioResource.Soundtype.Soundinfo[0].SoundName, AudioResource.Soundtype, filepath));
				AudioSource = shard;
			}
			else {
				printf("ファイル形式が対応していない形式です");
			}
			Init();
		}
	}

	AudioSpeaker::~AudioSpeaker()
	{
		StopUpdate();

		delete I3D;

		if (AudioResource.Soundtype.StreamType == false)
		{

			alDeleteBuffers(1, &Buffers[0]);
			alDeleteSources(1, &Source);
		}
		else {
			alDeleteBuffers(2, &Buffers.front());
			alDeleteSources(1, &Source);
		}

		AudioFormatData afd;
		afd.WriteAudioFormatData(Filepath,AudioResource.Soundtype);

		// 初期化終了
		Successinit = true;
		
	}

	void AudioSpeaker::StopUpdate()
	{
		LoopFlag = false;
	}

	/// <summary>
	/// 初期バッファの作成とxmlから読み込んだ情報の設定
	/// </summary>
	void AudioSpeaker::Init()
	{
		if (AudioResource.Soundtype.StreamType == false)
		{
			alGenBuffers(1, &Buffers[0]);
			alGenSources(1, &Source);
			SetBuffer(Buffers[0]);
			alSourcei(Source, AL_BUFFER, Buffers[0]);
		}else{
			alGenBuffers(2, &Buffers[0]);
			alGenSources(1, &Source);
			SetBuffer(Buffers[0]);
			SetBuffer(Buffers[1]);
			alSourceQueueBuffers(Source, 2, &Buffers[0]);
		}


		// ソースの初期設定
		alSourcei(Source,AL_SOURCE_RELATIVE,AL_TRUE);

		LoopFlag = true;

	}

	//
	bool AudioSpeaker::SetBuffer(ALuint Buf)
	{
		if (!Buf) {
			alGenBuffers(1, &Buf);
		}

		// バッファの更新
		ALenum format = AudioSource->GetAudioChannel() == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
		int fq = AudioSource->GetAudioSpS();
		ALsizei size = (ALsizei)AudioSource->GetAudioBufferSize();

		alBufferData(Buf, format, AudioSource->GetBuffer(), size, fq);
		return true;
	}

	bool AudioSpeaker::Play()
	{
		alSourcePlay(Source);
		return true;
	}

	bool AudioSpeaker::Update()
	{
		if (AudioResource.Soundtype.StreamType == false)
		{
			int State = 0;
			alGetSourcei(Source, AL_SOURCE_STATE, &State);
			if (State != AL_PLAYING && AudioResource.LoopSound == 1)
			{
				Play();
			}
		}
		else 
		{
			int State = 0;
			alGetSourcei(Source, AL_BUFFERS_PROCESSED, &State);

			if (State > 0)
			{
				printf("バッファ更新中\n");
				AudioSource->Update();
				ALuint Buf = 0;
				alSourceUnqueueBuffers(Source, 1, &Buf);
				SetBuffer(Buf);
				alSourceQueueBuffers(Source, 1, &Buf);
			}

		}

		return true;
	}

	bool AudioSpeaker::Stop()
	{
		StopUpdate();

		alSourceStop(Source);
		return true;
	}

	bool AudioSpeaker::Pause()
	{
		alSourcePause(Source);
		return true;
	}

	/// <summary>
	/// 概要		:: 外部からのエフェクト呼び出し用の関数
	/// アクセス制限	:: public
	/// </summary>
	/// <param name="num">エフェクトの種類</param>
	/// <returns>エフェクト生成に成功しているかどうか</returns>
	bool AudioSpeaker::AddEffects(AudioEffects* effect)
	{
		EffectSlot.push_back(effect);

		return true;

	}

}
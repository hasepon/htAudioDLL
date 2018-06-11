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

		// 属性を拾っているので処理
		// 取得情報から実データを取得
		for (auto var : AudioResource.Soundtype.Soundinfo)
		{
			// マテリアルの同一オブジェクトの検索
			if (material == var.MaterialObj)
			{
				if (var.Extension == "wav")
				{
					AudioSource = new CLoadWave(var.SoundName, AudioResource.Soundtype);
				}
				else if (var.Extension == "ogg")
				{
					AudioSource = new CLoadOgg(var.SoundName, AudioResource.Soundtype);
				}
				else {
					printf("ファイル形式が対応していない形式です");
				}
			}
		}
		Init();
	}

	AudioSpeaker::AudioSpeaker(std::string filepath, int id)
	{
		// オーディオ情報をxmlから取得
		AudioFormatData afd;
		AudioResource.Soundtype = afd.GetAudioFormatData(filepath, id);

		// マテリアルの設定がない場合id[0]の音を鳴らす
		if (AudioResource.Soundtype.Soundinfo[id].Extension == "wav")
		{
			AudioSource = new CLoadWave(AudioResource.Soundtype.Soundinfo[id].SoundName, AudioResource.Soundtype);
		}
		else if (AudioResource.Soundtype.Soundinfo[id].Extension == "ogg")
		{
			AudioSource = new CLoadOgg(AudioResource.Soundtype.Soundinfo[id].SoundName, AudioResource.Soundtype);
		}
		else {
			printf("ファイル形式が対応していない形式です");
		}
		Init();
	}

	AudioSpeaker::AudioSpeaker(std::string filepath, std::string SoundName)
	{
		// オーディオ情報をxmlから取得
		AudioFormatData afd;
		AudioResource.Soundtype = afd.GetAudioFormatData(filepath, SoundName);

		// マテリアルの設定がない場合id[0]の音を鳴らす
		if (AudioResource.Soundtype.Soundinfo[0].Extension == "wav")
		{
			AudioSource = new CLoadWave(AudioResource.Soundtype.Soundinfo[0].SoundName, AudioResource.Soundtype);
		}
		else if (AudioResource.Soundtype.Soundinfo[0].Extension == "ogg")
		{
			AudioSource = new CLoadOgg(AudioResource.Soundtype.Soundinfo[0].SoundName, AudioResource.Soundtype);
		}
		else {
			printf("ファイル形式が対応していない形式です");
		}

		Init();
	}

	AudioSpeaker::~AudioSpeaker()
	{
		if (AudioResource.Soundtype.StreamType == false)
		{

			alDeleteBuffers(1, &Buffers[0]);
			alDeleteSources(1, &Source);
			delete AudioSource;
		}
		else {
			alDeleteBuffers(2, Buffers);
			alDeleteSources(1, &Source);
			delete AudioSource;
		}

		
	}

	void AudioSpeaker::Init()
	{
		if (AudioResource.Soundtype.StreamType == false)
		{
			alGenBuffers(1, &Buffers[0]);
			alGenSources(1, &Source);
			SetBuffer(Buffers[0]);
			alSourcei(Source, AL_BUFFER, Buffers[0]);
		}else{
			alGenBuffers(2, Buffers);
			alGenSources(1, &Source);
			SetBuffer(Buffers[0]);
			SetBuffer(Buffers[1]);
			alSourceQueueBuffers(Source, 2, Buffers);
		}
	}

	//
	bool AudioSpeaker::SetBuffer(ALuint Buf)
	{
		if (!Buf) {
			alGenBuffers(1, &Buf);
		}

		AudioSource->Update();
		// バッファの更新
		ALenum format = AudioSource->GetAudioChannel() == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
		int fq = AudioSource->GetAudioSpS();
		ALsizei size = AudioSource->GetAudioBufferSize();

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
		else {
			int State = 0;
			alGetSourcei(Source, AL_BUFFERS_PROCESSED, &State);
			if (State > 0)
			{
				ALuint Buf;
				alSourceUnqueueBuffers(Source, 1, &Buf);
				SetBuffer(Buf);
				alSourceQueueBuffers(Source, 1, &Buf);
			}
		}
		return true;
	}

	bool AudioSpeaker::Stop()
	{
		alSourceStop(Source);
		return true;
	}

	bool AudioSpeaker::Pause()
	{
		alSourcePause(Source);
		return true;
	}

	void AudioSpeaker::SetPosition(float* x, float* y, float* z)
	{
		Position[0] = x;
		Position[1] = y;
		Position[2] = z;

		alSource3f(Source,AL_POSITION, *Position[0], *Position[1], *Position[2]);
	}

	void AudioSpeaker::SetPosition(float* pos[3])
	{
		*Position = *pos;

		alSource3f(Source, AL_POSITION, *Position[0], *Position[1], *Position[2]);
	}

}
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
		alSourcef(Source, AL_MAX_GAIN, (ALfloat)AudioResource.Soundtype.Soundinfo[0].MaxVolume);     // 音量
		SetConeInnerAngle(AudioResource.Soundtype.Sorrundinfo.innerAngle);
		SetConeOuterAngle(AudioResource.Soundtype.Sorrundinfo.OuterAngle);
		SetConeOuterGain(AudioResource.Soundtype.Sorrundinfo.OuterGain);

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
		alSourceStop(Source);
		return true;
	}

	bool AudioSpeaker::Pause()
	{
		alSourcePause(Source);
		return true;
	}

	void AudioSpeaker::SetPosition(float x, float y, float z)
	{
		Position[0] = x;
		Position[1] = y;
		Position[2] = z;

		alSourcefv(Source,AL_POSITION, Position);
	}

	void AudioSpeaker::SetPosition(float pos[3])
	{
		Position[0] = pos[0];
		Position[1] = pos[1];
		Position[2] = pos[2];

		alSourcefv(Source, AL_POSITION, pos);
	}

	void AudioSpeaker::SetVelocity(float x, float y, float z)
	{
		Velocity[0] = x;
		Velocity[1] = y;
		Velocity[2] = z;

		alSourcefv(Source,AL_VELOCITY,Velocity);
	}

	void AudioSpeaker::SetVelocity(float vec[3])
	{
		Velocity[0] = vec[0];
		Velocity[1] = vec[1];
		Velocity[2] = vec[2];

		alSourcefv(Source, AL_VELOCITY, Velocity);
	}

	/*void AudioSpeaker::SetOrientation(float AtVec[3], float UpVec[3])
	{
		Orientation[0] = AtVec[0];
		Orientation[1] = AtVec[1];
		Orientation[2] = AtVec[2];
		Orientation[3] = UpVec[0];
		Orientation[4] = UpVec[1];
		Orientation[5] = UpVec[2];

		alSourcefv(Source, AL_ORIENTATION, Orientation);
	}

	void AudioSpeaker::SetOrientation(float AtOrient[6])
	{
		Orientation[0] = AtOrient[0];
		Orientation[1] = AtOrient[1];
		Orientation[2] = AtOrient[2];
		Orientation[3] = AtOrient[3];
		Orientation[4] = AtOrient[4];
		Orientation[5] = AtOrient[5];

		alSourcefv(Source, AL_ORIENTATION, Orientation);
	}*/

	void AudioSpeaker::SetDirection(float x, float y, float z)
	{
		Direction[0] = x;
		Direction[1] = y;
		Direction[2] = z;
		alSourcefv(Source, AL_DIRECTION, Direction);
	}

	void AudioSpeaker::SetDirection(float dir[3])
	{
		Direction[0] = dir[0];
		Direction[1] = dir[1];
		Direction[2] = dir[2];
		alSourcefv(Source, AL_DIRECTION, Direction);
	}

	void AudioSpeaker::SetConeOuterGain(float val)
	{
		ConeOuterGain = val;
		alSourcef(Source,AL_CONE_OUTER_GAIN, ConeOuterGain);
	}

	float AudioSpeaker::GetConeOuterGain()
	{
		alGetSourcef(Source,AL_CONE_OUTER_GAIN,&ConeOuterGain);
		return ConeOuterGain;
	}

	void AudioSpeaker::SetConeInnerAngle(float val)
	{
		InnerAngle = val;
		alSourcef(Source, AL_CONE_INNER_ANGLE, InnerAngle);
	}
	
	float AudioSpeaker::GetConeInnerAngle()
	{
		alGetSourcef(Source, AL_CONE_INNER_ANGLE, &InnerAngle);
		return InnerAngle;
	}

	void AudioSpeaker::SetConeOuterAngle(float val)
	{
		OuterAngle = val;
		alSourcef(Source, AL_CONE_OUTER_ANGLE, OuterAngle);
	}

	float AudioSpeaker::GetConeOuterAngle()
	{
		alGetSourcef(Source, AL_CONE_OUTER_ANGLE, &OuterAngle);
		return OuterAngle;
	}


}
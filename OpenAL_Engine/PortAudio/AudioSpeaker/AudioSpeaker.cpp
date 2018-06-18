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
					std::shared_ptr<CLoadSoundFile> shard(new CLoadWave(var.SoundName, AudioResource.Soundtype));
					AudioSource = shard;
				}
				else if (var.Extension == "ogg")
				{
					id = var.Id;
					std::shared_ptr<CLoadSoundFile> shard(new CLoadOgg(var.SoundName, AudioResource.Soundtype));
					AudioSource = shard;
				}
				else {
					printf("ファイル形式が対応していない形式です");
				}
			}
		}
		Init();

		alSourcei(Source, AL_GAIN, AudioResource.Soundtype.Soundinfo[id].MaxVolume);     // 音量

	}

	AudioSpeaker::AudioSpeaker(std::string filepath, int id)
	{
		// オーディオ情報をxmlから取得
		AudioFormatData afd;
		AudioResource.Soundtype = afd.GetAudioFormatData(filepath, id);

		// マテリアルの設定がない場合id[0]の音を鳴らす
		if (AudioResource.Soundtype.Soundinfo[id].Extension == "wav")
		{
			std::shared_ptr<CLoadSoundFile> shard(new CLoadWave(AudioResource.Soundtype.Soundinfo[id].SoundName, AudioResource.Soundtype));
			AudioSource = shard;
		}
		else if (AudioResource.Soundtype.Soundinfo[id].Extension == "ogg")
		{
			std::shared_ptr<CLoadSoundFile> shard(new CLoadOgg(AudioResource.Soundtype.Soundinfo[id].SoundName, AudioResource.Soundtype));
			AudioSource = shard;
		}
		else {
			printf("ファイル形式が対応していない形式です");
		}
		Init();

		alSourcei(Source, AL_GAIN, AudioResource.Soundtype.Soundinfo[id].MaxVolume);     // 音量

	}

	AudioSpeaker::AudioSpeaker(std::string filepath, std::string SoundName)
	{
		// オーディオ情報をxmlから取得
		AudioFormatData afd;
		AudioResource.Soundtype = afd.GetAudioFormatData(filepath, SoundName);

		// マテリアルの設定がない場合id[0]の音を鳴らす
		if (AudioResource.Soundtype.Soundinfo[0].Extension == "wav")
		{
			std::shared_ptr<CLoadSoundFile> shard(new CLoadWave(AudioResource.Soundtype.Soundinfo[0].SoundName, AudioResource.Soundtype));
			AudioSource = shard;
		}
		else if (AudioResource.Soundtype.Soundinfo[0].Extension == "ogg")
		{
			std::shared_ptr<CLoadSoundFile> shard(new CLoadOgg(AudioResource.Soundtype.Soundinfo[0].SoundName, AudioResource.Soundtype));
			AudioSource = shard;  
		}
		else {
			printf("ファイル形式が対応していない形式です");
		}

		Init();

		alSourcei(Source, AL_GAIN, AudioResource.Soundtype.Soundinfo[0].MaxVolume);     // 音量

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
			alGenBuffers(2, &Buffers.front());
			alGenSources(1, &Source);
			SetBuffer(Buffers[0]);
			SetBuffer(Buffers[1]);
			alSourceQueueBuffers(Source, 2, &Buffers.front());
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
				FFT();
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

	void AudioSpeaker::FFT()
	{
		fftw_complex *in, *out;
		fftw_plan plan;
		int size;
		size_t* sample;

		size = AudioSource->GetAudioBufferSize() / AudioResource.Format.nBlockAlign;
		sample = (size_t*)AudioSource->GetBuffer();

		in = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*size);
		out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*size);

		for (int i = 0; i = size; i++)
		{
			in[i][0] = sample[i];
			in[i][1] = 0.0;
		}

		plan = fftw_plan_dft_1d(size,in,out,FFTW_FORWARD,FFTW_ESTIMATE);
		fftw_execute(plan);

		float* dest;
		dest = new float(sizeof(float)*size);
		for (int i = 0; i < size; i++) {
			dest[i] = std::sqrt(out[i][0] * out[i][0] + out[i][1] * out[i][1]);
		}

		double max = 0;
		int index = 0;
		for (int i = 0; i < size; i++) {
			if (dest[i] > max) {
				max = dest[i];
				index = i;
			}
		}
		cout << endl << index << endl << max << endl;
		delete[] dest;

		fftw_destroy_plan(plan);
		fftw_free(in);
		fftw_free(out);

	}
}
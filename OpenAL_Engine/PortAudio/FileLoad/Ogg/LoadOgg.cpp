

#include "LoadOgg.h"

namespace htAudio {

	CLoadOgg::CLoadOgg(std::string soundlistnumb, SoundType xmlinfo)
	{
		m_SoundResouce.Soundtype = xmlinfo;
		m_SoundResouce.DataChunkSample = NULL;
		m_SoundResouce.DataChunkSize = NULL;
		m_SoundResouce.firstSampleOffSet = NULL;
		m_SoundResouce.HasGotWaveFormat = false;
		m_SoundResouce.Format = {};
		m_SoundResouce.LoopSound = m_SoundResouce.Soundtype.Loopflag;
		m_SoundResouce.PresetSoundName = FilePath + soundlistnumb + ".ogg";
		m_TotalReadSize = 0;

		m_Playbuf = new char[htAudio::BUFFER_SIZE];
		m_Secondbuf = new char[htAudio::BUFFER_SIZE];

		LoadFormat();
	}


	CLoadOgg::~CLoadOgg()
	{
		ov_clear(&m_Ovf);
		delete[] m_Playbuf;
		delete[] m_Secondbuf;
		m_SoundResouce.PresetSoundName.clear();
	}

	void CLoadOgg::LoadFormat()
	{
		// oggfileを開く
		if (ov_fopen(m_SoundResouce.PresetSoundName.c_str(), &m_Ovf))
		{
			// オープン失敗
			printf("oggファイルのオープン失敗");
			return;
		}

		// oggvorbisfile情報を取得
		vorbis_info* vi = ov_info(&m_Ovf, -1);

		m_SoundResouce.Format.wFormatTag = WAVE_FORMAT_PCM;
		m_SoundResouce.Format.nChannels = vi->channels;
		m_SoundResouce.Format.nSamplesPerSec = vi->rate;
		m_SoundResouce.Format.nBlockAlign = vi->channels * 2;
		m_SoundResouce.Format.wBitsPerSample = 16;
		m_SoundResouce.Format.nAvgBytesPerSec = (vi->rate) * (vi->channels * 2);
		m_SoundResouce.Format.cbSize = 0;
		m_SoundResouce.BufferSample = htAudio::BUFFER_SIZE;

		m_SoundResouce.HasGotWaveFormat = true;

	}

	void CLoadOgg::Update()
	{
		// oggvorbisfile情報を取得
		vorbis_info* vi = ov_info(&m_Ovf, -1);
		std::size_t readsample;

		// TODO :: ひとまず一つのバッファを使用して読み込み
		if (m_SoundResouce.SubmitTimes == 0)
		{
 			readsample = ReadDataRaw(0, 0, m_Playbuf);
			if (readsample > 0)
			{
				m_SoundResouce.SubmitTimes = 1;
			}
		}
		else if (m_SoundResouce.SubmitTimes == 1)
		{
			readsample = ReadDataRaw(0, 0, m_Secondbuf);
			if (readsample > 0)
			{
				m_SoundResouce.SubmitTimes = 0;
			}
		}
		m_TotalReadSize += readsample;
	}

	/// <summary>
	/// 指定サイズでのバッファの取得
	/// </summary>
	/// <param name="start"></param>
	/// <param name="sample"></param>
	/// <param name="buffer"></param>
	/// <returns></returns>
	std::size_t CLoadOgg::ReadDataRaw(const std::size_t start, const std::size_t sample, char* buffer)
	{
		if (buffer == 0)
		{
			return 0;
		}


		int requestsize = htAudio::BUFFER_SIZE;
		int bitstream = 0;
		int readsize = 0;
		unsigned int comsize = 0;
		bool isadjust = false;

		if (htAudio::BUFFER_SIZE < requestsize)
		{
			requestsize = htAudio::BUFFER_SIZE;
			isadjust = true;
		}

		int cnt = 0;

		//読み込み開始
		while (1)
		{
			// oggファイルの読み込み
			readsize = ov_read(&m_Ovf, (char*)(buffer + comsize), requestsize, 0, 2, 1, &bitstream);

			comsize += readsize;

			if (readsize == 0)
			{
				// ファイルエンド
				if (m_SoundResouce.LoopSound == true)
				{
					// 頭に戻す
					ov_time_seek(&m_Ovf, 0.0f);
					m_TotalReadSize = 0;
					m_SoundResouce.PlayTime = 0;
				}
				else
				{
					// 読み込み終了
					return comsize;
				}
			}

			if (comsize >= htAudio::BUFFER_SIZE)
			{
				return comsize;
			}

			if (htAudio::BUFFER_SIZE - comsize < htAudio::BUFFER_SIZE)
			{
				isadjust = true;
				requestsize = htAudio::BUFFER_SIZE - comsize;
			}

		}
		// エラー
		return 0;
	}


}
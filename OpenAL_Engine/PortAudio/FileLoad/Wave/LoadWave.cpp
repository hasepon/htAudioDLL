#include "LoadWave.h"
#include"../../OpenAlCore/OpenALDevice.h"

namespace htAudio
{
	//==============================================================
	//	Waveファイル情報の初期化
	//==============================================================
	CLoadWave::CLoadWave(std::string Soundlistnumb, SoundType xmlinfo)
	{
		// SoundResouceの初期化
		m_SoundResouce.Soundtype = xmlinfo;
		m_SoundResouce.DataChunkSample = NULL;
		m_SoundResouce.DataChunkSize = NULL;
		m_SoundResouce.firstSampleOffSet = NULL;
		m_SoundResouce.HasGotWaveFormat = false;
		m_SoundResouce.Format = {};
		m_SoundResouce.LoopSound = m_SoundResouce.Soundtype.Loopflag;
		m_SoundResouce.PresetSoundName = FilePath + Soundlistnumb + ".wav";


		// BGM保存用バッファの初期化
		//PrimaryMixed = new std::size_t[htAudio::BUFFER_SIZE];
		//SecondMixed = new std::size_t[htAudio::BUFFER_SIZE];

		// chunkデータの読み込み
		LoadFormat();

		// ストリーミング再生の場合初期化処理
		if (m_SoundResouce.Soundtype.StreamType == true)
		{
			PrepareStreamBuffer();
		}else {
			// プリロードバッファ
			PreloadBuffer();
		}

	}

	//==============================================================
	//	Waveファイル情報の解放
	//==============================================================
	CLoadWave::~CLoadWave()
	{
		m_SoundResouce.PresetSoundName.clear();
		//delete[] PrimaryMixed;
		PrimaryMixed.clear();
		//delete[] SecondMixed;
		SecondMixed.clear();
	}

	//====================================
	//	WAVEFORMATEXへのchunk情報の格納
	//====================================
	void CLoadWave::LoadFormat()
	{

		FILE* fp;

		fopen_s(&fp, m_SoundResouce.PresetSoundName.c_str(), "rb");

		if (fp == NULL)
			return;

		m_SoundResouce.Format.wFormatTag = WAVE_FORMAT_PCM;
		long offset = 12;

		while (true)
		{

			if (fseek(fp, offset, SEEK_SET) != 0)
				break;

			char chunksignature[4] = { 0 };
			std::size_t readChar = 0;

			while (readChar < 4)
			{
				std::size_t ret = fread(chunksignature + readChar, sizeof(char), 4 - readChar, fp);
				if (ret == 0)
					break;
				readChar += ret;
			}

			uint32_t chunksize = 0;
			if (fread(&chunksize, sizeof(uint32_t), 1, fp) == 0)
				break;

			// fmtチャンクを読み込み
			if (strncmp(chunksignature, "fmt ", 4) == 0)
			{
				std::size_t readSize = chunksize < sizeof(WAVEFORMATEX) ? chunksize : sizeof(WAVEFORMATEX);
				if (fread(&m_SoundResouce.Format, readSize, 1, fp) == 0)
					break;

				if (m_SoundResouce.Format.wFormatTag == WAVE_FORMAT_PCM)
					m_SoundResouce.Format.cbSize = 0;

				m_SoundResouce.HasGotWaveFormat = true;

			}

			// dataチャンク
			if (strncmp(chunksignature, "data", 4) == 0)
			{
				m_SoundResouce.firstSampleOffSet = offset + 8;
				m_SoundResouce.DataChunkSize = chunksize;
			}

			offset += (static_cast<long>(chunksize) + 8);

		}

		if (!m_SoundResouce.HasGotWaveFormat)
			return;

		// フォーマット取得が終了
		m_SoundResouce.DataChunkSample = m_SoundResouce.DataChunkSize / m_SoundResouce.Format.nBlockAlign;

		fclose(fp);
	}

	//====================================
	//	Update関数
	//		更新するよー
	//====================================
	void CLoadWave::Update()
	{
		if (m_SoundResouce.Soundtype.StreamType == true)
		{
			// ストリームバッファの更新
			UpdateStreamBuffer();
		}
	}

	//====================================
	//	Preload関数
	//		return : 読み込んだバッファ情報
	//====================================
	std::size_t CLoadWave::PreloadBuffer()
	{
		long first = 0;
		long last = m_SoundResouce.DataChunkSize;
		PrimaryMixed = std::vector<std::size_t>(last);
		//PrimaryMixed = new std::size_t[last];
		std::size_t readSample = ReadDataRaw(first, last, &(PrimaryMixed[0]));
		m_SoundResouce.BufferSample = m_SoundResouce.DataChunkSize;
		return readSample;
	}

	//====================================
	//	Stream用の初期化バッファ
	//		return : 読み込んだバッファ情報
	//====================================
	std::size_t CLoadWave::PrepareStreamBuffer()
	{
		std::size_t readSample = 0;
		m_SoundResouce.NextFirstSample = 0;
		PrimaryMixed = std::vector<std::size_t>(BUFFER_SIZE);
		SecondMixed = std::vector<std::size_t>(BUFFER_SIZE);

		// 最初のバッファ読み込み
		readSample = ReadDataRaw(m_SoundResouce.NextFirstSample, htAudio::BUFFER_SIZE, &(PrimaryMixed[0]));
		m_SoundResouce.NextFirstSample = readSample;
		m_SoundResouce.SubmitTimes = 1;

		// 次のバッファの読み込み4
		//readSample += ReadDataRaw(m_SoundResouce.NextFirstSample, htAudio::BUFFER_SIZE, &(SecondMixed[0]));
		//m_SoundResouce.NextFirstSample += readSample;
		//m_SoundResouce.SubmitTimes = 0;

		// 読み込み完了
		if (readSample > 0)
		{
			m_BufferLoadflag = true;
		}

		return readSample;
	}

	//====================================
	//	WAVEFORMATEXへのbuffer情報の更新
	//====================================
	std::size_t CLoadWave::UpdateStreamBuffer()
	{
		std::size_t readSamples = 0;
		// 前回の読み込みバッファを超えた場合新しく読み込みなおす
		if (m_SoundResouce.NextFirstSample < m_SoundResouce.DataChunkSample)
		{

			if (m_SoundResouce.SubmitTimes == 0)
			{
				readSamples = ReadDataRaw(m_SoundResouce.NextFirstSample, htAudio::BUFFER_SIZE, &(PrimaryMixed[0]));
				
				if (readSamples > 0)
				{
					m_SoundResouce.SubmitTimes = 1;
					m_SoundResouce.NextFirstSample += readSamples;
					m_BufferLoadflag = true;
				}
			}else if (m_SoundResouce.SubmitTimes == 1) {
				readSamples = ReadDataRaw(m_SoundResouce.NextFirstSample, htAudio::BUFFER_SIZE, &(SecondMixed[0]));

				if (readSamples > 0)
				{
					m_SoundResouce.SubmitTimes = 0;
					m_SoundResouce.NextFirstSample += readSamples;
					m_BufferLoadflag = true;
				}
			}

			// Loop処理
			if (m_SoundResouce.NextFirstSample >= m_SoundResouce.DataChunkSample&& m_SoundResouce.LoopSound == true)
			{
				m_SoundResouce.NextFirstSample = 0;
				PrepareStreamBuffer();
			}
			else
			{
				// 終了検知
				return readSamples;
			}

		}
		else {
			//更新無し
			readSamples = -1;
		}



		return readSamples;
	}

	//====================================
	//	Data部分の取得
	//	対応形式が16bit pcm
	//====================================
	std::size_t CLoadWave::ReadDataRaw(long first, long end, void* buffer)
	{

		FILE* fp;

		fopen_s(&fp, m_SoundResouce.PresetSoundName.c_str(), "rb");

		if (!buffer)
			return 0;

		if (!fp)
			return 0;

		if (!m_SoundResouce.HasGotWaveFormat)
			return 0;

		if (first >= m_SoundResouce.DataChunkSample)
			return 0;

		std::size_t actualSamples = first + end > m_SoundResouce.DataChunkSample ? m_SoundResouce.DataChunkSample - first : end;

		if (fseek(fp, m_SoundResouce.firstSampleOffSet + first * m_SoundResouce.Format.nBlockAlign, SEEK_SET) != 0)
			return 0;

		std::size_t readSample = 0;
		std::size_t ret;
		while (readSample < actualSamples)
		{
			ret = fread(reinterpret_cast<uint16_t*>(buffer) + readSample * m_SoundResouce.Format.nBlockAlign,
				m_SoundResouce.Format.nBlockAlign, actualSamples - readSample, fp);

			if (ret == 0)
				break;

			readSample += ret;
		}

		fclose(fp);

		m_SoundResouce.BufferSample = ret * m_SoundResouce.Format.nBlockAlign;

		return readSample;
	}

	//====================================
	//	Data部分の取得
	//	対応形式が32bit pcm
	//	用途はわかるような気がするが判別等々がよくわからない
	//====================================
	std::size_t CLoadWave::ReadNormalize(long first, long end, float* left, float* right)
	{
		FILE* fp;

		fopen_s(&fp, m_SoundResouce.PresetSoundName.c_str(), "rb");

		if (!fp)
			return 0;

		if (!m_SoundResouce.HasGotWaveFormat)
			return 0;

		if (first >= m_SoundResouce.DataChunkSample)
			return 0;

		std::size_t actualSamples = first + end > m_SoundResouce.DataChunkSample ? m_SoundResouce.DataChunkSample - first : end;

		if (fseek(fp, m_SoundResouce.firstSampleOffSet + first * m_SoundResouce.Format.nBlockAlign, SEEK_SET) != 0)
			return 0;

		std::size_t readSamples = 0;

		for (; readSamples < actualSamples; ++readSamples)
		{
			// 1 サンプル読み込み
			uint32_t data[2];
			std::size_t ret = fread(data, m_SoundResouce.Format.nBlockAlign, 1, fp);	// Warning: 3 チャンネル以上が来るとバッファオーバーラン
			if (ret == 0) break;

			// 量子化ビット数によって個別に処理
			switch (m_SoundResouce.Format.wBitsPerSample)
			{
			case 8:
				// 8bit signed: -128...0...127
			{
				int8_t * data_s8 = reinterpret_cast<int8_t *>(data);
				if (m_SoundResouce.Format.nChannels == 1)
				{
					float l = (data_s8[0] < 0) ? static_cast<float>(data_s8[0]) / 128.0f :
						static_cast<float>(data_s8[0]) / 127.0f;
					left[readSamples] = l;
					if (right) right[readSamples] = l;
				}
				else
				{
					float l = (data_s8[0] < 0) ? static_cast<float>(data_s8[0]) / 128.0f :
						static_cast<float>(data_s8[0]) / 127.0f;
					float r = (data_s8[1] < 0) ? static_cast<float>(data_s8[1]) / 128.0f :
						static_cast<float>(data_s8[1]) / 127.0f;
					if (right)
					{
						left[readSamples] = l;
						right[readSamples] = r;
					}
					else
					{
						left[readSamples] = (l + r) * 0.5f;
					}
				}
			}
			break;
			case 16:
				// 16bit signed: -32768...0...32767
			{
				int16_t * data_s16 = reinterpret_cast<int16_t *>(data);
				if (m_SoundResouce.Format.nChannels == 1)
				{
					float l = (data_s16[0] < 0) ? static_cast<float>(data_s16[0]) / 32768.0f :
						static_cast<float>(data_s16[0]) / 32767.0f;
					left[readSamples] = l;
					if (right) right[readSamples] = l;
				}
				else
				{
					float l = (data_s16[0] < 0) ? static_cast<float>(data_s16[0]) / 32768.0f :
						static_cast<float>(data_s16[0]) / 32767.0f;
					float r = (data_s16[1] < 0) ? static_cast<float>(data_s16[1]) / 32768.0f :
						static_cast<float>(data_s16[1]) / 32767.0f;
					if (right)
					{
						left[readSamples] = l;
						right[readSamples] = r;
					}
					else
					{
						left[readSamples] = (l + r) * 0.5f;
					}
				}
			}
			break;
			}
		}
		return readSamples;
	}

}
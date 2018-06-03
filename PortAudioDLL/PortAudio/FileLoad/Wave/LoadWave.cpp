#include "LoadWave.h"

//==============================================================
//	Waveファイル情報の初期化
//==============================================================
CLoadWave::CLoadWave(std::string Soundlistnumb, bool Loopflag)
{
	// SoundResouceの初期化
	m_SoundResouce.DataChunkSample = NULL;
	m_SoundResouce.DataChunkSize = NULL;
	m_SoundResouce.firstSampleOffSet = NULL;
	m_SoundResouce.HasGotWaveFormat = false;
	m_SoundResouce.Format = {};
	m_SoundResouce.LoopSound = Loopflag;		
	m_SoundResouce.PresetSoundName = FilePath + Soundlistnumb;

	// chunkデータの読み込み
	LoadFormat();
}

//==============================================================
//	Waveファイル情報の解放
//==============================================================
CLoadWave::~CLoadWave()
{
	m_SoundResouce.PresetSoundName.clear();
	SecondaryMixed.clear();
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
//	Preload関数
//		return : 読み込んだバッファ情報
//====================================
std::size_t CLoadWave::PreloadBuffer()
{
	long first = 0;
	long last = m_SoundResouce.DataChunkSize;
	PrimaryMixed = std::vector<float>(last * 2);
	std::size_t readSample = ReadDataRaw(first, last, &(PrimaryMixed[0]));

	return readSample;
}

//====================================
//	Stream用の初期化バッファ
//		return : 読み込んだバッファ情報
//====================================
std::size_t CLoadWave::PrepareStreamBuffer()
{
	std::size_t readSample = 0;
	// BGM保存用バッファの初期化
	PrimaryMixed = std::vector<float>(FRAMES_PER_BUFFER * 2);
	SecondaryMixed = std::vector<float>(FRAMES_PER_BUFFER * 2);

	// データ読み込み部
	readSample = ReadDataRaw(0, FRAMES_PER_BUFFER, &(PrimaryMixed[0]));


	// 読み込み完了
	if (readSample > 0)
	{
		m_SoundResouce.NextFirstSample += readSample;
		++m_SoundResouce.SubmitTimes;

		m_BufferLoadflag = true;
	}
	return readSample;
}

//====================================
//	WAVEFORMATEXへのbuffer情報の更新
//====================================
std::size_t CLoadWave::UpdateStreamBuffer()
{
	std::size_t readSamples;
	// 前回の読み込みバッファを超えた場合新しく読み込みなおす
	if (m_SoundResouce.NextFirstSample < m_SoundResouce.DataChunkSample)
	{
		readSamples = ReadDataRaw(
			m_SoundResouce.NextFirstSample
			,FRAMES_PER_BUFFER
			,&(PrimaryMixed[0]));

		if (readSamples > 0)
		{
			m_SoundResouce.NextFirstSample += readSamples;
			++m_SoundResouce.SubmitTimes;
			m_BufferLoadflag = true;
		}

		// Loop処理
		if (m_SoundResouce.NextFirstSample >= m_SoundResouce.DataChunkSample&& m_SoundResouce.LoopSound == true)
		{
			m_SoundResouce.NextFirstSample = 0;
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

	while (readSample < actualSamples)
	{
		std::size_t ret = fread(reinterpret_cast<uint8_t*>(buffer) + readSample * m_SoundResouce.Format.nBlockAlign,
			m_SoundResouce.Format.nBlockAlign, actualSamples - readSample, fp);

		if (ret == 0)
			break;

		readSample += ret;
	}

	fclose(fp);

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
			int8_t * data_s8 = reinterpret_cast< int8_t * >(data);
			if (m_SoundResouce.Format.nChannels == 1)
			{
				float l = (data_s8[0] < 0) ? static_cast< float >(data_s8[0]) / 128.0f :
					static_cast< float >(data_s8[0]) / 127.0f;
				left[readSamples] = l;
				if (right) right[readSamples] = l;
			}
			else
			{
				float l = (data_s8[0] < 0) ? static_cast< float >(data_s8[0]) / 128.0f :
					static_cast< float >(data_s8[0]) / 127.0f;
				float r = (data_s8[1] < 0) ? static_cast< float >(data_s8[1]) / 128.0f :
					static_cast< float >(data_s8[1]) / 127.0f;
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
			int16_t * data_s16 = reinterpret_cast< int16_t * >(data);
			if (m_SoundResouce.Format.nChannels == 1)
			{
				float l = (data_s16[0] < 0) ? static_cast< float >(data_s16[0]) / 32768.0f :
					static_cast< float >(data_s16[0]) / 32767.0f;
				left[readSamples] = l;
				if (right) right[readSamples] = l;
			}
			else
			{
				float l = (data_s16[0] < 0) ? static_cast< float >(data_s16[0]) / 32768.0f :
					static_cast< float >(data_s16[0]) / 32767.0f;
				float r = (data_s16[1] < 0) ? static_cast< float >(data_s16[1]) / 32768.0f :
					static_cast< float >(data_s16[1]) / 32767.0f;
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


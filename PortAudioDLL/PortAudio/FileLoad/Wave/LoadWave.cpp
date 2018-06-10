#include "LoadWave.h"

//==============================================================
//	Wave�t�@�C�����̏�����
//==============================================================
CLoadWave::CLoadWave(std::string Soundlistnumb, bool Loopflag)
{
	// SoundResouce�̏�����
	m_SoundResouce.DataChunkSample = NULL;
	m_SoundResouce.DataChunkSize = NULL;
	m_SoundResouce.firstSampleOffSet = NULL;
	m_SoundResouce.HasGotWaveFormat = false;
	m_SoundResouce.Format = {};
	m_SoundResouce.LoopSound = Loopflag;		
	m_SoundResouce.PresetSoundName = FilePath + Soundlistnumb;

	// chunk�f�[�^�̓ǂݍ���
	LoadFormat();
}

//==============================================================
//	Wave�t�@�C�����̉��
//==============================================================
CLoadWave::~CLoadWave()
{
	m_SoundResouce.PresetSoundName.clear();
	SecondaryMixed.clear();
}

//====================================
//	WAVEFORMATEX�ւ�chunk���̊i�[
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

		// fmt�`�����N��ǂݍ���
		if (strncmp(chunksignature, "fmt ", 4) == 0)
		{
			std::size_t readSize = chunksize < sizeof(WAVEFORMATEX) ? chunksize : sizeof(WAVEFORMATEX);
			if (fread(&m_SoundResouce.Format, readSize, 1, fp) == 0)
				break;

			if (m_SoundResouce.Format.wFormatTag == WAVE_FORMAT_PCM)
				m_SoundResouce.Format.cbSize = 0;

			m_SoundResouce.HasGotWaveFormat = true;

		}

		// data�`�����N
		if (strncmp(chunksignature, "data", 4) == 0)
		{
			m_SoundResouce.firstSampleOffSet = offset + 8;
			m_SoundResouce.DataChunkSize = chunksize;
		}

		offset += (static_cast<long>(chunksize) + 8);

	}

	if (!m_SoundResouce.HasGotWaveFormat)
		return;

	// �t�H�[�}�b�g�擾���I��
	m_SoundResouce.DataChunkSample = m_SoundResouce.DataChunkSize / m_SoundResouce.Format.nBlockAlign;

	fclose(fp);
}

//====================================
//	Preload�֐�
//		return : �ǂݍ��񂾃o�b�t�@���
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
//	Stream�p�̏������o�b�t�@
//		return : �ǂݍ��񂾃o�b�t�@���
//====================================
std::size_t CLoadWave::PrepareStreamBuffer()
{
	std::size_t readSample = 0;
	// BGM�ۑ��p�o�b�t�@�̏�����
	PrimaryMixed = std::vector<float>(FRAMES_PER_BUFFER * 2);
	SecondaryMixed = std::vector<float>(FRAMES_PER_BUFFER * 2);

	// �f�[�^�ǂݍ��ݕ�
	readSample = ReadDataRaw(0, FRAMES_PER_BUFFER, &(PrimaryMixed[0]));


	// �ǂݍ��݊���
	if (readSample > 0)
	{
		m_SoundResouce.NextFirstSample += readSample;
		++m_SoundResouce.SubmitTimes;

		m_BufferLoadflag = true;
	}
	return readSample;
}

//====================================
//	WAVEFORMATEX�ւ�buffer���̍X�V
//====================================
std::size_t CLoadWave::UpdateStreamBuffer()
{
	std::size_t readSamples;
	// �O��̓ǂݍ��݃o�b�t�@�𒴂����ꍇ�V�����ǂݍ��݂Ȃ���
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

		// Loop����
		if (m_SoundResouce.NextFirstSample >= m_SoundResouce.DataChunkSample&& m_SoundResouce.LoopSound == true)
		{
			m_SoundResouce.NextFirstSample = 0;
		}
		else
		{
			// �I�����m
			return readSamples;
		}

	}
	else {
		//�X�V����
		readSamples = -1;
	}

	return readSamples;
}

//====================================
//	Data�����̎擾
//	�Ή��`����16bit pcm
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
//	Data�����̎擾
//	�Ή��`����32bit pcm
//	�p�r�͂킩��悤�ȋC�����邪���ʓ��X���悭�킩��Ȃ�
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
		// 1 �T���v���ǂݍ���
		uint32_t data[2];
		std::size_t ret = fread(data, m_SoundResouce.Format.nBlockAlign, 1, fp);	// Warning: 3 �`�����l���ȏオ����ƃo�b�t�@�I�[�o�[����
		if (ret == 0) break;

		// �ʎq���r�b�g���ɂ���Čʂɏ���
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

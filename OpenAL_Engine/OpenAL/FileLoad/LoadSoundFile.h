#pragma once

#include<windows.h>
#include<vector>
#include<string>
#include<tchar.h>

#include<AL/al.h>
#include<AL/alc.h>

namespace htAudio
{
	// サウンド情報
	struct SoundInfo
	{
		int Id;
		std::string Extension;
		std::string SoundName;
		std::string MaterialObj;
		std::string Type;
		float MaxVolume;
	};

	// サウンドのタイプ
	struct SoundType {
		std::string Cue;
		std::string SubGroup;
		bool Loopflag;
		bool StreamType;
		std::vector<SoundInfo> Soundinfo;
	};


	// ヘッダー情報
	typedef struct {
		WORD  wFormatTag;
		WORD  nChannels;
		DWORD nSamplesPerSec;
		DWORD nAvgBytesPerSec;
		WORD  nBlockAlign;
		WORD  wBitsPerSample;
		WORD  cbSize;
	} AUDIOFORMAT;

	struct SoundResources
	{
		std::u16string PresetSoundName;// サウンド名
		AUDIOFORMAT Format;			// ヘッダー情報
		SoundType Soundtype;		// XMLから得た情報
		int PlayTime;				// 再生時間
		bool HasGotWaveFormat;		// フォーマット情報を取得済みか
		bool LoopSound;				// ループ情報

		std::size_t DataChunkSize;	// データバッファサイズ
		std::size_t DataChunkSample;
		long firstSampleOffSet;

		// Buffer情報
		std::size_t NextFirstSample = { 0 };
		std::size_t SubmitTimes = { 0 };
		std::size_t BufferSample = { 0 };
	};

	//==================================================
	//
	//	各種リソースのベースとなる部分
	//
	//==================================================
	class CLoadSoundFile
	{
	public:
		CLoadSoundFile() {}				// 初期化
		virtual ~CLoadSoundFile() {}	// 終了
		virtual void Update() {}

		virtual void* GetBuffer() = 0;	// 現在のバッファ情報の取得


		virtual std::size_t GetAudioBufferSize() { return m_SoundResouce.BufferSample; }
		virtual AUDIOFORMAT* GetWaveFormat() { return &m_SoundResouce.Format; };// サウンドファイルの情報を取得

		virtual int GetAudioChannel() { return m_SoundResouce.Format.nChannels; }
		virtual int GetAudioSpS() { return m_SoundResouce.Format.nSamplesPerSec; }

	protected:

		virtual void LoadFormat() = 0;	// サウンド情報(バッファ情報を除く)取得

		// バッファデータ読み込み
		virtual std::size_t ReadDataRaw() { return 0; }

		SoundResources m_SoundResouce;	// サウンド情報
		bool m_BufferLoadflag;			// 読み込みフラグ

		std::u16string FilePath = (u"../Data/Audio/");

	};
}
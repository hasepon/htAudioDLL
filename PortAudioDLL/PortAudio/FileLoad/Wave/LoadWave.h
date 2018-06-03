#pragma once

#include "../LoadSoundFile.h"

//-----------------------------------------------------------
//	WaveFileを扱うサウンドリソース読み込み
//	参考 https://gist.github.com/xrated/2700516
//------------------------------------------------------------
class CLoadWave : public CLoadSoundFile
{
public:
	CLoadWave(std::string soundlistnumb, bool Loopflag);
	~CLoadWave();
	std::size_t PreloadBuffer();
	std::size_t PrepareStreamBuffer();
	std::size_t UpdateStreamBuffer();

private:
	void LoadFormat();
	// 生データの読み込み
	std::size_t ReadDataRaw(long first, long end,void* buffer);
	// 正規化済みデータ読み込み
	std::size_t ReadNormalize(long first, long end, float* left, float* right);
};

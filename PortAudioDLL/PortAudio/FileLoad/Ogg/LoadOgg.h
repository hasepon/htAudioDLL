#pragma once

#include "../LoadSoundFile.h"

#include"vorbis/vorbisfile.h"
#ifdef _DEBUG
#pragma comment(lib,"libvorbisfile_static_d.lib")
#pragma comment(lib,"libogg_static_d.lib")
#pragma comment(lib,"libvorbis_static_d.lib")
#else
#pragma comment(lib,"libvorbisfile_static.lib")
#pragma comment(lib,"libogg_static.lib")
#pragma comment(lib,"libvorbis_static.lib")
#endif // DEBUG

//===========================================================
// TODO
//	Oggを読み込むクラス
//	Vorbislibを使用しています。
//===========================================================
class CLoadOgg : public CLoadSoundFile
{
public:
	CLoadOgg(std::string soundlistnumb, bool Loopflag);
	~CLoadOgg();
	void Update();

private:
	std::size_t ReadDataRaw(const std::size_t start, const std::size_t sample, char* buffer);
	void LoadFormat();

	int m_BuffCnt;

	OggVorbis_File m_Ovf;
	DWORD m_TotalReadSize;
};

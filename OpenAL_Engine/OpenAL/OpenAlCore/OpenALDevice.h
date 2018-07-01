#pragma once

#include"../../stdafx.h"
#include"../../Singleton.h"
#define AL_ALEXT_PROTOTYPES

#include<AL/al.h>
#include<AL/alc.h>

#include<AL/efx.h>
#include<AL/efx-creative.h>

#pragma comment(lib,"OpenAL32.lib")

namespace htAudio
{
	const int SAMPLE_PER_SEC = 44100;
	const int16_t BUFFER_SIZE = 6096;
	
	enum AlutError
	{
		ALUT_ERROR_NO_ERROR = 0,
		ALUT_ERROR_OUT_OF_MEMORY = 0x200,
		ALUT_ERROR_INVALID_ENUM,
		ALUT_ERROR_INVALID_VALUE,
		ALUT_ERROR_INVALID_OPERATION,
		ALUT_ERROR_NO_CURRENT_CONTEXT,
		ALUT_ERROR_AL_ERROR_ON_ENTRY,
		ALUT_ERROR_ALC_ERROR_ON_ENTRY,
		ALUT_ERROR_OPEN_DEVICE,
		ALUT_ERROR_CLOSE_DEVICE,
		ALUT_ERROR_CREATE_CONTEXT,
		ALUT_ERROR_MAKE_CONTEXT_CURRENT,
		ALUT_ERROR_DESTROY_CONTEXT,
		ALUT_ERROR_GEN_BUFFERS,
		ALUT_ERROR_BUFFER_DATA,
		ALUT_ERROR_IO_ERROR,
		ALUT_ERROR_UNSUPPORTED_FILE_TYPE,
		ALUT_ERROR_UNSUPPORTED_FILE_SUBTYPE,
		ALUT_ERROR_CORRUPT_OR_TRUNCATED_DATA
	};

	/// /// <summary>
	/// シングルトンを使用してオブジェクトを生成しています
	/// </summary>
	class OpenALDevice
	{
	public:
		void ErrorFunction();
		OpenALDevice();
		~OpenALDevice();
	private:
		ALCdevice * Device;
		ALCcontext* Context;
		ALCint Sends = 0;
	};
}
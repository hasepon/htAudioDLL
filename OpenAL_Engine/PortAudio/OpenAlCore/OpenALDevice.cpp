#include "OpenALDevice.h"

#include<stdio.h>
namespace htAudio {
	OpenALDevice::OpenALDevice()
	{
		// OpenALの初期化
		printf("初期化しました\n");
		Device = alcOpenDevice(nullptr);
		Context = alcCreateContext(Device,nullptr);

		ALCboolean success = alcMakeContextCurrent(Context);

		if (success == false)
		{
			printf("alcMakeContextCurrentに失敗しました");
		}
	}
	
	OpenALDevice::~OpenALDevice()
	{
		printf("OpenALを解放します\n");
		alcMakeContextCurrent(nullptr);
		alcDestroyContext(Context);
		alcCloseDevice(Device);
	}
	
	void OpenALDevice::ErrorFunction()
	{
		ALCenum err;
		err = alcGetError(Device);

		switch (err)
		{
		case AlutError::ALUT_ERROR_NO_ERROR:
			printf("エラーなし\n");
			break;

		case AlutError::ALUT_ERROR_OUT_OF_MEMORY:
			printf("メモリ不足です\n");
			break;

		case AlutError::ALUT_ERROR_INVALID_ENUM:
			printf("ALUTの関数に不正な定数が与えられました\n");
			break;

		case AlutError::ALUT_ERROR_INVALID_VALUE:
			printf("ALUTの関数に不正な値が与えられました\n");
			break;

		case AlutError::ALUT_ERROR_INVALID_OPERATION:
			printf("行った操作が不正です\n");
			break;

		case AlutError::ALUT_ERROR_NO_CURRENT_CONTEXT:
			printf("コンテキストがセットされてません\n");
			break;

		case AlutError::ALUT_ERROR_AL_ERROR_ON_ENTRY:
			printf("ALUTのエントリーエラー\n");
			break;

		case AlutError::ALUT_ERROR_ALC_ERROR_ON_ENTRY:
			printf("ALUTのエントリーエラー\n");
			break;

		case AlutError::ALUT_ERROR_OPEN_DEVICE:
			printf("デバイスオープンの際にエラーが発生しました\n");
			break;

		case AlutError::ALUT_ERROR_CLOSE_DEVICE:
			printf("デバイスクローズの際にエラーが発生しました\n");
			break;

		case AlutError::ALUT_ERROR_CREATE_CONTEXT:
			printf("コンテキスト生成でエラーが発生しました\n");
			break;

		case AlutError::ALUT_ERROR_MAKE_CONTEXT_CURRENT:
			printf("コンテキストの変更が出来ませんでした\n");
			break;

		case AlutError::ALUT_ERROR_DESTROY_CONTEXT:
			printf("コンテキストの破壊が出来ませんでした\n");
			break;

		case AlutError::ALUT_ERROR_GEN_BUFFERS:
			printf("ALBufferを生成する際にエラーが発生しました");
			break;

		case AlutError::ALUT_ERROR_BUFFER_DATA:
			printf("ALBufferを送信する際にエラーが発生しました");
			break;

		case AlutError::ALUT_ERROR_IO_ERROR:
			printf("I/Oエラー\n");
			break;

		case AlutError::ALUT_ERROR_UNSUPPORTED_FILE_TYPE:
			printf("サポートされていないファイルタイプです\n");
			break;

		case AlutError::ALUT_ERROR_UNSUPPORTED_FILE_SUBTYPE:
			printf("サポートされていないモードです\n");
			break;

		case AlutError::ALUT_ERROR_CORRUPT_OR_TRUNCATED_DATA:
			printf("サウンドデータに問題があります\n");
			break;

		}
	}
}
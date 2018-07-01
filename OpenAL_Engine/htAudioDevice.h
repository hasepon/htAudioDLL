#pragma once


#include"OpenAL/OpenAlCore/OpenALDevice.h"
#include"Definclude.h"

using namespace htAudio;

/// <summary>
/// オーディオデバイスを作成するための宣言
/// </summary>
extern "C"
{
	UNITY_INTERFACE_EXPORT OpenALDevice* UNITY_INTERFACE_API htaCreate();
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API htaDelete(OpenALDevice* Instance);
}
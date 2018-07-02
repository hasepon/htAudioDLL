#include"htAudioDevice.h"

bool htaCreate(OpenALDevice* instance)
{
	instance = new OpenALDevice();

	return instance->GetCreateDeviceFlag();
}

void htaDelete(OpenALDevice* Instance)
{
	if (Instance == nullptr)
	{
		return;
	}

	delete Instance;
}
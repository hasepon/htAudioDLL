#include"htAudioDevice.h"

OpenALDevice* htaCreate()
{
	return new OpenALDevice();
}

void htaDelete(OpenALDevice* Instance)
{
	if (Instance == nullptr)
	{
		return;
	}

	delete Instance;
}
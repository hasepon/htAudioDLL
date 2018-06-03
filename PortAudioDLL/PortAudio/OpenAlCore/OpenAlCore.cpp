#include "OpenAlCore.h"

OpenAlCore::OpenAlCore()
{
	const ALCchar* device_list = alcGetString(nullptr,ALC_DEVICE_SPECIFIER);

	ALDevice = alcOpenDevice(NULL);
	if (!ALDevice)
	{
		printf("OpenAl SoftÇÃèâä˙âªÇ…é∏îs");
		return;
	}

	ALContext = alcCreateContext(ALDevice, NULL);
	alcMakeContextCurrent(ALContext);

	if (!ALContext)
	{
		printf("contextÇÃçÏê¨Ç…é∏îs");
		return;
	}
}


OpenAlCore::~OpenAlCore()
{
	alcMakeContextCurrent(nullptr);
	alcDestroyContext(ALContext);
	alcCloseDevice(ALDevice);
}

ALuint OpenAlCore::SetBuffer(ALuint Buffer)
{
	ALuint ALbuffer = Buffer;
	alGenSources(1,&ALbuffer);

	ALuint Source;
	alGenSources(1, &Source);

	alSourcei(ALbuffer,AL_BUFFER, Source);

	return Source;
}

void OpenAlCore::Play(ALuint Source)
{
	alSourcePlay(Source);
}

void OpenAlCore::Pause(ALuint Source)
{
	alSourcePause(Source);
}
;
void OpenAlCore::Stop(ALuint Source)
{
	alSourceStop(Source);
}

void OpenAlCore::Clear(ALuint Source, ALuint Buffer)
{
	alDeleteSources(1,&Source);
	alDeleteBuffers(1,&Buffer);
}
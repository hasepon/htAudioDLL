#pragma once

#include<AL/al.h>
#include<AL/alc.h>
#include<stdio.h>

#pragma comment(lib,"OpenAL32.lib")

class OpenAlCore
{
public:
	OpenAlCore();
	~OpenAlCore();

	ALuint SetBuffer(ALuint Buffer);
	
	void Play(ALuint Source);
	void Pause(ALuint Source);
	void Stop(ALuint Source);

	void Clear(ALuint Source, ALuint Buffer);

private:
	ALCdevice * ALDevice;
	ALCcontext* ALContext;

};


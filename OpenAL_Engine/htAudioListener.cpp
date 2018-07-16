#include"htAudioListener.h"

AudioListener* htaListenerCreate()
{
	return new AudioListener();
}

void htaListenerDelete(AudioListener* Instance)
{
	if (Instance == nullptr)
	{
		return;
	}
	
	delete Instance;

}

void htaListenerPosition(AudioListener* Instance,float x, float y, float z)
{
	Instance->Setposition(x,y,z);
}

void htaListenerPositionArray(AudioListener* Instance,float Pos[3])
{
	Instance->Setposition(Pos);
}

void htaListenerVelocity(AudioListener* Instance, float x, float y, float z)
{
	Instance->SetVelocity(x,y,z);
}

void htaListenerVelocityArray(AudioListener* Instance, float vec[3])
{
	Instance->SetVelocity(vec);
}

void htaListenerOrientation(AudioListener* Instance, float AtVec[3], float UpVec[3])
{
	Instance->SetOrientation(AtVec,UpVec);
}

void htaListenerOrientationArray(AudioListener* Instance, float AtOrient[6])
{
	Instance->SetOrientation(AtOrient);
}

//void  htaListenerSetConeOuterGain(AudioListener* Instance, float val)
//{
//
//}
//
//float htaListenerGetConeOuterGain(AudioListener* Instance)
//{
//
//}
//
//void  htaListenerSetConeInnerAngle(AudioListener* Instance, float val)
//{
//
//}
//
//float htaListenerGetConeInnerAngle(AudioListener* Instance)
//{
//
//}
//
//void  htaListenerSetConeOuterAngle(AudioListener* Instance, float val)
//{
//
//}
//
//float htaListenerGetConeOuterAngle(AudioListener* Instance)
//{
//
//}
// OpenAL_Engine.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"

#include"OpenAL/OpenAlCore/OpenALDevice.h"
#include"OpenAL/AudioSpeaker/AudioSpeaker.h"
#include"OpenAL/AudioListener/AudioListener.h"
#include"Singleton.h"

using namespace htAudio;

int main()
{
	OpenALDevice& Oad = singleton<OpenALDevice>::get_instance();

	float SpeakerPos[3] = { 0.0, 0.0, 0.0 };

	float listenerPos[3] = { 0.0, 0.0, 0.0 };
	float listenerVel[3] = { 0.0, 0.0, 0.0 };
	float listenerview[3] = { 0.0, 0.0, 0.0 };
	float listenerpose[3] = { 0.0, 1.0, 0.0 };
	
	//AudioListener* testlitener = new AudioListener();
	AudioSpeaker* TestSpeaker = new AudioSpeaker("J:\\UnityProj\\PluginTest\\Data", "Test" );
	
	bool test = TestSpeaker->GetResourceflag();

	TestSpeaker->Play();

	while (false)
	{
		//TestSpeaker->Update();
		TestSpeaker->SetPosition(SpeakerPos);
	}

	//delete testlitener;
	delete TestSpeaker;
	SingletonFinalizer::finalize();

    return 0;
}


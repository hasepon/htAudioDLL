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
	
	AudioListener* testlitener = new AudioListener(listenerPos, listenerVel, listenerview, listenerpose);
	AudioSpeaker* TestSpeaker = new AudioSpeaker((u"../Data/Xml/SoundList.xml"), (u"Test") );
	
	TestSpeaker->Play();

	while (1)
	{
		TestSpeaker->Update();
		TestSpeaker->SetPosition(SpeakerPos);
		testlitener->Setposition(listenerPos);

	}

	delete TestSpeaker;
	delete testlitener;
	SingletonFinalizer::finalize();

    return 0;
}


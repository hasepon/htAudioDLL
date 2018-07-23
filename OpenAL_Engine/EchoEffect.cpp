#include "EchoEffect.h"

namespace htAudio {

	/// <summary>
	/// 概要 :: エコーの設定
	/// アクセス制限 :: public
	/// </summary>
	/// <param name="source">対象とするSource</param>
	EchoEffect::EchoEffect(ALuint source)
	{
		LPALGENEFFECTS algeneffect = (LPALGENEFFECTS)alGetProcAddress("alGenEffects");

		alGenAuxiliaryEffectSlots(1, &EffectSlot);

		if (alGetError() != AL_NO_ERROR)
			return;

		algeneffect(1, &Effect);

		if (alGetError() != AL_NO_ERROR)
			return;

		if (alIsEffect(Effect))
		{
			alEffecti(Effect, AL_EFFECT_TYPE, AL_EFFECT_ECHO);
			if (alGetError() != AL_NO_ERROR)
			{
				printf("リバーブの作成に失敗してます\n");
				return;
			}
		}

		alAuxiliaryEffectSloti(EffectSlot, AL_EFFECTSLOT_EFFECT, Effect);

		if (alGetError() == AL_NO_ERROR)
			printf("Successfully loaded effect into effect slot\n");

		alSource3i(source, AL_AUXILIARY_SEND_FILTER, EffectSlot, 0, NULL);
	}

	EchoEffect::~EchoEffect()
	{
	}

	/// <summary>
	/// 概要 :: ディレイの設定
	/// アクセス制限 :: public
	/// </summary>
	/// <param name="delay">delayの値の設定</param>
	/// MAX(0.207) :: MIN(0.0) :: Default(0.1)
	void EchoEffect::SetDelay(float delay)
	{
		Info.DELAY = delay;
		alEffectf(Effect, AL_ECHO_DELAY, Info.DELAY);
	}

	/// <summary>
	/// 概要 :: LRのディレイの設定
	/// アクセス制限 :: public
	/// </summary>
	/// <param name="lrdelay">二回目の遅延の制御</param>
	/// MAX(0.404) :: MIN(0.0) :: Default(0.1)
	void EchoEffect::SetLRDelay(float lrdelay)
	{
		Info.LRDELAY = lrdelay;
		alEffectf(Effect, AL_ECHO_LRDELAY, Info.LRDELAY);
	}

	/// <summary>
	/// 概要 :: エコーの強さ(意訳)
	/// アクセス制限 :: public
	/// </summary>
	/// <param name="damping">dampingの数値</param>
	/// MAX(0.99) :: MIN(0.0) :: Default(0.5)
	void EchoEffect::SetDamping(float damping)
	{
		Info.DAMPING = damping;
		alEffectf(Effect, AL_ECHO_DAMPING, Info.DAMPING);
	}

	/// <summary>
	/// 概要 :: sampleの長さ
	/// アクセス制限 :: public
	/// </summary>
	/// <param name="feedback">feedbackの強さ</param>
	/// MAX(1.0) :: MIN(0.0) :: Default(0.5)
	void EchoEffect::SetFeedBack(float feedback)
	{
		Info.FEEDBACK = feedback;
		alEffectf(Effect, AL_ECHO_FEEDBACK, Info.FEEDBACK);
	}

	/// <summary>
	/// 概要 :: パンニングの位置
	/// アクセス制限 :: public
	/// </summary>
	/// <param name="spread">パンニングの位置</param>
	/// MAX(1.0) :: MIN(-1.0) :: Default(-1.0)
	void EchoEffect::SetSpRead(float spread)
	{
		Info.SPREAD = spread;
		alEffectf(Effect, AL_ECHO_SPREAD, Info.SPREAD);
	}

}
#include "FlangerEffect.h"

namespace htAudio {

	/// <summary>
	/// 概要 :: フレンジャーの設定
	/// アクセス制限 :: public
	/// </summary>
	/// <param name="source">対象とするSource</param>
	FlangerEffect::FlangerEffect(ALuint source)
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
			alEffecti(Effect, AL_EFFECT_TYPE, AL_EFFECT_FLANGER);
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


	FlangerEffect::~FlangerEffect()
	{
	}

	/// <summary>
	/// 概要 :: どういった形で生成するか
	/// アクセス制限 :: public
	/// </summary>
	/// <param name="type">typeの値</param>
	/// MAX(1) :: LOW(0) :: Default(1)
	void FlangerEffect::SetWaveForm(int type)
	{
		Info.WAVEFORM = type;
		alEffectf(Effect, AL_FLANGER_WAVEFORM, Info.WAVEFORM);
	}

	/// <summary>
	/// 概要 :: どの位置に偏った状態で出すか
	/// アクセス制限 :: public
	/// </summary>
	/// <param name="ohase">pahseの値</param>
	/// MAX(180) :: LOW(-180) :: Default(0)
	void FlangerEffect::SetPhase(int phase)
	{
		Info.PHASE = phase;
		alEffectf(Effect, AL_FLANGER_PHASE, Info.PHASE);
	}

	/// <summary>
	/// 概要 :: ピッチ変調の量
	/// アクセス制限 :: public
	/// </summary>
	/// <param name="rate">rateの値</param>
	/// MAX(10.0) :: LOW(0.0) :: Default(0.27)
	void FlangerEffect::SetRate(float rate)
	{
		Info.RATE = rate;
		alEffectf(Effect, AL_FLANGER_RATE, Info.RATE);
	}

	/// <summary>
	/// 概要 :: ピッチの変化量
	/// アクセス制限 :: public
	/// </summary>
	/// <param name="depth">depthの値</param>
	/// MAX(1.0) :: LOW(0.0) :: Default(1.0)
	void FlangerEffect::SetDepth(float depth)
	{
		Info.DEPTH = depth;
		alEffectf(Effect, AL_FLANGER_DEPTH, Info.DEPTH);
	}

	/// <summary>
	/// 概要 :: リピート回数の設定
	/// アクセス制限 :: public
	/// </summary>
	/// <param name="feedback"></param>
	/// MAX(1.0) :: LOW(-1.0) :: Default(-0.5)
	void FlangerEffect::SetFeedback(float feedback)
	{
		Info.FEEDBACK = feedback;
		alEffectf(Effect, AL_FLANGER_FEEDBACK, Info.FEEDBACK);
	}

	/// <summary>
	/// 概要 :: 遅延時間の設定
	/// アクセス制限 :: public
	/// </summary>
	/// <param name="delay"></param>
	/// MAX(0.004) :: LOW(0.0) :: Default(0.002)
	void FlangerEffect::SetDelay(float delay)
	{
		Info.DELAY = delay;
		alEffectf(Effect, AL_FLANGER_DELAY, Info.DELAY);
	}

}
#include "ChorusEffect.h"


namespace htAudio
{
	/// <summary>
	/// 概要 :: コーラスの設定
	/// アクセス制限 :: public
	/// </summary>
	/// <param name="source">対象とするSource</param>
	ChorusEffect::ChorusEffect(ALuint source)
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
			alEffecti(Effect, AL_EFFECT_TYPE, AL_EFFECT_CHORUS);
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


	ChorusEffect::~ChorusEffect()
	{
	}

	/// <summary>
	/// 概要 :: どういった形で生成するか
	/// アクセス制限 :: public
	/// </summary>
	/// <param name="form">フォーマットの形式</param>
	/// 1(sin) 1(trinangle)
	void ChorusEffect::SetWaveForm(int form)
	{
		Info.WAVEROTM = form;
		alEffectf(Effect, AL_CHORUS_WAVEFORM, Info.WAVEROTM);
	}

	/// <summary>
	/// 概要 :: 位相差の制御
	/// アクセス制限 :: public
	/// </summary>
	/// <param name="value">位置の値</param>
	/// MAX(180) :: MIN(-180) :: Default :: 90
	void ChorusEffect::SetPhase(int value)
	{
		Info.PHASE = value;
		alEffectf(Effect, AL_CHORUS_PHASE, Info.PHASE);
	}

	/// <summary>
	/// 概要 :: 遅延時間の設定
	/// アクセス制限 :: public
	/// </summary>
	/// <param name="rate">遅延時間の値</param>
	/// MAX(10.0) :: MIN(0.0) :: Default(1.1)
	void ChorusEffect::SetRate(float rate)
	{
		Info.RATE = rate;
		alEffectf(Effect, AL_CHORUS_RATE, Info.RATE);
	}

	/// <summary>
	/// 概要 :: 深度の設定
	/// アクセス制限 :: public
	/// </summary>
	/// <param name="value">深度値</param>
	/// MAX(1.0) :: MIN(0.0) :: Default(0.1)
	void ChorusEffect::SetDepth(float value)
	{
		Info.DEPTH = value;
		alEffectf(Effect, AL_CHORUS_DEPTH, Info.DEPTH);
	}

	/// <summary>
	/// 概要 :: フィードバックされる数値の設定
	/// アクセス制限 :: public
	/// </summary>
	/// <param name="value">フィードバックの値</param>
	/// MAX(1.0) :: MIX(-1.0) :: Default(0.25)
	void ChorusEffect::SetFeedBack(float value)
	{
		Info.FEEDBACK = value;
		alEffectf(Effect, AL_CHORUS_FEEDBACK, Info.FEEDBACK);
	}

	/// <summary>
	/// 概要 :: ディレイ数値の設定
	/// アクセス制限 :: public
	/// </summary>
	/// <param name="value">ディレイ数値の設定</param>
	/// MAX(0.016) :: MIN(0.0) :: Default(0.016)
	void ChorusEffect::SetDelay(float value)
	{
		Info.DELAY = value;
		alEffectf(Effect, AL_CHORUS_DELAY, Info.DELAY);
	}

}
#include "EQEffect.h"

namespace htAudio {

	/// <summary>
	/// 概要 :: equalizerの設定
	/// アクセス制限 :: public
	/// </summary>
	/// <param name="source">対象とするSource</param>
	EQEffect::EQEffect(ALuint source)
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
			alEffecti(Effect, AL_EFFECT_TYPE, AL_EFFECT_EQUALIZER);
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


	EQEffect::~EQEffect()
	{

	}

	/// <summary>
	/// 概要 :: 最低値の設定
	/// </summary>
	/// <param name="gain">最大値</param>
	/// MAX(7.943) :: LOW(0.126) :: Default(1.0)
	/// <param name="cutoff">カットする最低音域</param>
	/// MAX(800.0) :: LOW(50.0) :: Default(200.0)
	void EQEffect::SetLow(float gain, float cutoff)
	{
		Info.LOW_GAIN = gain;
		alEffectf(Effect, AL_EQUALIZER_LOW_GAIN, Info.LOW_GAIN);
		Info.LOW_CUTOFF = cutoff;
		alEffectf(Effect, AL_EQUALIZER_LOW_CUTOFF, Info.LOW_CUTOFF);
	}

	void EQEffect::SetMid1(float gain, float center, float width)
	{
		Info.MID1_GAIN = gain;
		alEffectf(Effect, AL_EQUALIZER_MID1_GAIN, Info.MID1_GAIN);
		Info.MID1_CENTER = center;
		alEffectf(Effect, AL_EQUALIZER_MID1_CENTER, Info.MID1_CENTER);
		Info.MID1_WIDTH = width;
		alEffectf(Effect, AL_EQUALIZER_MID1_WIDTH, Info.MID1_WIDTH);
	}

	void EQEffect::SetMid2(float gain, float center, float width)
	{
		Info.MID2_GAIN = gain;
		alEffectf(Effect, AL_EQUALIZER_MID2_GAIN, Info.MID2_GAIN);
		Info.MID2_CENTER = center;
		alEffectf(Effect, AL_EQUALIZER_MID2_CENTER, Info.MID2_CENTER);
		Info.MID2_WIDTH = width;
		alEffectf(Effect, AL_EQUALIZER_MID2_WIDTH, Info.MID2_WIDTH);
	}

	void EQEffect::SetHigh(float gain, float cutoff)
	{
		Info.HIGH_GAIN = gain;
		alEffectf(Effect, AL_EQUALIZER_HIGH_GAIN, Info.HIGH_GAIN);
		Info.HIGH_CUTOFF = cutoff;
		alEffectf(Effect, AL_EQUALIZER_HIGH_CUTOFF, Info.HIGH_CUTOFF);
	}

}
#include "FQEffect.h"

namespace htAudio {

	/// <summary>
	/// 概要 :: リバーブの設定
	/// アクセス制限 :: public
	/// </summary>
	/// <param name="source">対象とするSource</param>
	FQEffect::FQEffect(ALuint source)
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
			alEffecti(Effect, AL_EFFECT_TYPE, AL_EFFECT_FREQUENCY_SHIFTER);
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


	FQEffect::~FQEffect()
	{

	}

	/// <summary>
	/// 概要 :: 変化量の設定
	/// アクセス制限 :: public
	/// </summary>
	/// <param name="fq">fqの変化の値</param>
	/// MAX(24000.0) :: LOW(0.0) :: Default(0.0)
	void FQEffect::SetFrequency(float fq)
	{
		Info.FREQUENCY = fq;
		alEffectf(Effect, AL_FREQUENCY_SHIFTER_FREQUENCY, (ALfloat)Info.FREQUENCY);
	}

	/// <summary>
	/// 概要 :: 内部信号の加算の設定
	/// </summary>
	/// <param name="left">leftの設定</param>
	/// <param name="right">rightの設定</param>
	/// down(0) :: Up(1) :: Off(2)
	void FQEffect::SetLRDirection(int left, int right)
	{
		Info.LEFT_DIRECTION = left;
		Info.RIGHT_DIRECTION = right;

		alEffectf(Effect, AL_FREQUENCY_SHIFTER_LEFT_DIRECTION , Info.LEFT_DIRECTION);
		alEffectf(Effect, AL_FREQUENCY_SHIFTER_RIGHT_DIRECTION , Info.RIGHT_DIRECTION);
	}


}
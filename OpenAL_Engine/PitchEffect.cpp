#include "PitchEffect.h"

namespace htAudio
{
	/// <summary>
	/// 概要 :: ピッチの設定
	/// アクセス制限 :: public
	/// </summary>
	/// <param name="source">対象とするSource</param>
	PitchEffect::PitchEffect(ALuint source)
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
			alEffecti(Effect, AL_EFFECT_TYPE, AL_EFFECT_PITCH_SHIFTER);
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


	PitchEffect::~PitchEffect()
	{
	}

	/// <summary>
	/// 概要 :: ピッチシフトの設定
	/// アクセス制限 :: public
	/// </summary>
	/// <param name="coarse">ずらす音階数</param>
	/// MAX(12.0) :: LOW(-12.0) :: Default(12.0)
	void PitchEffect::SetCoarse(int coarse)
	{
		Info.COARSE_TUNE = coarse;
		alEffectf(Effect, AL_PITCH_SHIFTER_COARSE_TUNE, Info.COARSE_TUNE);
	}

	/// <summary>
	/// 概要 :: ピッチシフト(半音)の設定
	/// アクセス制限 :: public
	/// </summary>
	/// <param name="fine"></param>
	/// MAX(50.0) :: LOW(-50.0) :: Default(0.0)
	void PitchEffect::SetFine(int fine)
	{
		Info.FINE_TUNE = fine;
		alEffectf(Effect, AL_PITCH_SHIFTER_FINE_TUNE, Info.FINE_TUNE);
	}
}
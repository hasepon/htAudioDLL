#include "WahEffect.h"

namespace htAudio {

	/// <summary>
	/// 概要 :: Wahの設定
	/// アクセス制限 :: public
	/// </summary>
	/// <param name="source">対象とするSource</param>
	WahEffect::WahEffect(ALuint source)
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
			alEffecti(Effect, AL_EFFECT_TYPE, AL_EFFECT_AUTOWAH);
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


	WahEffect::~WahEffect()
	{

	}

	/// <summary>
	/// 概要 :: 最小から最大へのスイープタイム
	/// アクセス制限 :: public
	/// </summary>
	/// <param name="time">スイープに使用する時間</param>
	/// MAX(1.0) :: LOW(0.0001) :: Default(0.06)
	void WahEffect::SetAttackTime(float time)
	{
		Info.ATTACK_TIME = time;
		alEffectf(Effect, AL_AUTOWAH_ATTACK_TIME, (ALfloat)Info.ATTACK_TIME);
	}

	/// <summary>
	/// 概要 :: 最大からベースへのスイープタイム
	/// アクセス制限 :: public
	/// </summary>
	/// <param name="time">スイープに使用する時間</param>
	/// MAX(1.0) :: LOW(0.0001) :: Default(0.06)
	void WahEffect::SetReleaseTime(float time)
	{
		Info.RELEASE_TIME = time;
		alEffectf(Effect, AL_AUTOWAH_RELEASE_TIME, (ALfloat)Info.RELEASE_TIME);
	}

	/// <summary>
	/// 概要 :: どの周波数帯をピークに設定するか
	/// アクセス制限 :: public
	/// </summary>
	/// <param name="time">ピークの数値</param>
	/// MAX(1000.0) :: LOW(2.0) :: Default(1000.0)
	void WahEffect::SetResonance(float val)
	{
		Info.RELEASE_TIME = val;
		alEffectf(Effect, AL_AUTOWAH_RELEASE_TIME, (ALfloat)Info.RELEASE_TIME);
	}

	/// <summary>
	/// 概要 :: band-pass filterをの使用レベル
	/// アクセス制限 :: public
	/// </summary>
	/// <param name="gain">gainの設定</param>
	/// MAX(31621.0) :: LOW(0.00003) :: Default(11.22)
	void WahEffect::SetPeakGain(float gain)
	{
		Info.PEAK_GAIN = gain;
		alEffectf(Effect, AL_AUTOWAH_PEAK_GAIN,(ALfloat)Info.PEAK_GAIN);
	}

}
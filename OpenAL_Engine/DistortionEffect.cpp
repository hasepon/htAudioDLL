#include "DistortionEffect.h"


namespace htAudio {

	/// <summary>
	/// 概要 :: ディストーション
	/// アクセス制限 :: public
	/// </summary>
	/// <param name="source">対象とするSource</param>
	DistortionEffect::DistortionEffect(ALuint source)
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
			alEffecti(Effect, AL_EFFECT_TYPE, AL_EFFECT_DISTORTION);
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


	DistortionEffect::~DistortionEffect()
	{
	}

	/// <summary>
	/// 概要 :: エッジの値を設定 高いほど歪みます
	/// アクセス制限 :: public
	/// </summary>
	/// <param name="val">エッジの値</param>
	/// MAX(1.0) :: MIN(0.0) :: Default(0.2)
	void DistortionEffect::SetEdge(float val)
	{
		Info.EDGE = val;
		alEffectf(Effect, AL_DISTORTION_EDGE, (ALfloat)Info.EDGE);
	}

	/// <summary>
	/// 概要 :: マスターボリュームの設定
	/// アクセス制限 :: public
	/// </summary>
	/// <param name="gain">ゲインの値</param>
	/// MAX(1.0) :: MIN(0.01) :: Default(0.05)
	void DistortionEffect::SetGain(float gain)
	{
		Info.GAIN = gain;
		alEffectf(Effect, AL_DISTORTION_GAIN, (ALfloat)Info.GAIN);
	}

	/// <summary>
	/// 概要 :: ローパスフィルターの設定
	/// アクセス制限 :: public
	/// </summary>
	/// <param name="val">周波数帯域</param>
	/// MAX(24000.0) :: MIN(80.0) :: Default(8000.0)
	void DistortionEffect::SetLowpassCutOff(float val)
	{
		Info.LOWPASS_CUTOFF = val;
		alEffectf(Effect, AL_DISTORTION_LOWPASS_CUTOFF, (ALfloat)Info.LOWPASS_CUTOFF);
	}

	/// <summary>
	/// 概要 :: ポストディストーション
	/// アクセス制限 :: public
	/// </summary>
	/// <param name="val">ポストディストーションの値</param>
	/// MAX(24000.0) :: MIN(80.0) :: Default(3600.0)
	void DistortionEffect::SetEQEnter(float val)
	{
		Info.EQCENTER = val;
		alEffectf(Effect, AL_DISTORTION_EQCENTER, (ALfloat)Info.EQCENTER);
	}

	/// <summary>
	/// 概要 :: ポストディストーションの差分数値を設定
	/// アクセス制限 :: public
	/// </summary>
	/// <param name="val">幅の値</param>
	/// MAX(24000.0) :: MIN(80.0) :: Default(3600.0)
	void DistortionEffect::SetEQBandWidth(float val)
	{
		Info.EQBANDWIDTH = val;
		alEffectf(Effect, AL_DISTORTION_EQBANDWIDTH, (ALfloat)Info.EQBANDWIDTH);
	}

}
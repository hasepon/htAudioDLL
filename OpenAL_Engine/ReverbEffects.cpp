#include "ReverbEffects.h"

namespace htAudio {

	/// <summary>
	/// 概要 :: リバーブの設定
	/// アクセス制限 :: public
	/// </summary>
	/// <param name="source">対象とするSource</param>
	ReverbEffects::ReverbEffects(ALuint source)
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
			alEffecti(Effect, AL_EFFECT_TYPE, AL_EFFECT_REVERB);
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


	ReverbEffects::~ReverbEffects()
	{
	}

	/// <summary>
	/// 概要 :: 密度数値の設定
	/// アクセス制限 :: public
	/// MAX(1.0) :: LOW(0.0) :: Default(1.0)
	/// </summary>
	/// <param name="density">設定する密度の値</param>
	void ReverbEffects::SetDensity(float density)
	{
		Info.DENSITY = density;
		alEffectf(Effect, AL_REVERB_DENSITY, (ALfloat)Info.DENSITY);
	}

	/// <summary>
	/// 概要 :: 拡散数値
	/// アクセス制限 :: public
	/// MAX(1.0) :: LOW(0.0) :: Default(1.0)
	/// </summary>
	/// <param name="diffusion">設定する拡散数値の値</param>
	void ReverbEffects::SetDiffusion(float diffusion)
	{
		Info.DIFFUSION = diffusion;
		alEffectf(Effect, AL_REVERB_DIFFUSION, (ALfloat)Info.DIFFUSION);
	}

	/// <summary>
	/// 概要		:: Gain数値に関する設定
	///	詳細		:: 反射音のマスターボリュームコントロール
	/// アクセス制限 :: public
	/// </summary>
	/// <param name="gain">全体音量の値</param>
	/// MAX(1.0) :: LOW(0.0) :: Default(0.32)
	/// <param name="gainhf">高音域の音量設定</param>
	/// MAX(1.0) :: LOW(0.0) :: Default(0.89)
	void ReverbEffects::SetGain(float gain, float gainhf)
	{
		Info.GAIN = gain;
		Info.GAINHF = gainhf;
		alEffectf(Effect, AL_REVERB_GAIN, (ALfloat)Info.GAIN);
		alEffectf(Effect, AL_REVERB_GAINHF, (ALfloat)Info.GAINHF);
	}

	/// <summary>
	/// 概要		:: Decay数値に関する設定
	///	詳細		:: 減衰値の設定
	/// アクセス制限 :: public
	/// </summary>
	/// <param name="time">減衰速度</param>
	/// MAX(20.0) :: LOW(1.0) :: Default(1.49)
	/// <param name="hfratio">高音域の減衰時間の設定</param>
	/// MAX(2.0) :: LOW(0.1) :: Default(0.83)
	void ReverbEffects::SetDecay(float time, float hfratio)
	{
		Info.DECAY_TIME = time;
		Info.DECAY_HFRATIO = hfratio;
		alEffectf(Effect,AL_REVERB_DECAY_TIME, (ALfloat)Info.DECAY_TIME);
		alEffectf(Effect,AL_REVERB_DECAY_HFRATIO, (ALfloat)Info.DECAY_HFRATIO);
	}

	/// <summary>
	/// 概要		:: Reflection数値に関する設定
	///	詳細		:: 反響値の設定
	/// アクセス制限 :: public
	/// </summary>
	/// <param name="gain">反響音マスタボリュームの値</param>
	/// MAX(3.16) :: LOW(0.0) :: Default(0.05)
	/// <param name="delay">反響音の時間</param>
	/// MAX(0.3) :: LOW(1.0) :: Default(0.007)
	void ReverbEffects::SetReflection(float gain, float delay)
	{
		Info.REFLECTIONS_GAIN = gain;
		Info.REFLECTIONS_DELAY = delay;

		alEffectf(Effect, AL_REVERB_REFLECTIONS_GAIN, (ALfloat)Info.REFLECTIONS_GAIN);
		alEffectf(Effect, AL_REVERB_REFLECTIONS_DELAY, (ALfloat)Info.REFLECTIONS_DELAY);
	}

	/// <summary>
	/// 概要		:: Late数値に関する設定
	///	詳細		:: 残響音値の設定
	/// アクセス制限 :: public
	/// </summary>
	/// <param name="gain">マスタボリュームの設定</param>
	/// MAX(10.0) :: LOW(0.0) :: Default(1.26)
	/// <param name="reflection">反射の強さの設定</param>
	/// MAX(0.1) :: LOW(0.0) :: Default(0.11)
	void ReverbEffects::SetLate(float gain,float reflection)
	{
		Info.LATE_GAIN = gain;
		Info.LATE_DELAY = reflection;

		alEffectf(Effect, AL_REVERB_LATE_REVERB_GAIN, (ALfloat)Info.LATE_GAIN);
		alEffectf(Effect, AL_REVERB_LATE_REVERB_DELAY, (ALfloat)Info.LATE_DELAY);
	}

	/// <summary>
	/// 概要		:: RoomRollOff数値に関する設定
	///	詳細		:: 反射減衰方法の一種らしい
	///					正直よくわからないが部屋を再現する際には使用するのかもしれない
	///					ダイレクトパスサウンドというものが大きく関わっているみたい
	/// アクセス制限 :: public
	/// </summary>
	/// <param name="val">減少値の設定</param>
	/// MAX(10.0) :: LOW(0.0) :: Default(0.0)
	void ReverbEffects::SetRoomRollOff(float val)
	{
		Info.ROOM_ROLL_OFF = val;
		alEffectf(Effect, AL_REVERB_ROOM_ROLLOFF_FACTOR, (ALfloat)Info.ROOM_ROLL_OFF);
	}

	/// <summary>
	/// 概要		:: AIR数値に関する設定
	///	詳細		:: 空気感を出すための数値らしい
	///					湿度や温度で変化する音の調整用
	/// アクセス制限 :: public
	/// </summary>
	/// <param name="gainhf">高音域のボリューム</param>
	/// MAX(1.0) :: LOW(0.892) :: Default(0.994)
	/// <param name="hflimit">高音域カットを自動で行うかどうかのフラグ</param>
	/// AL_FALSE AL_TRUE
	void ReverbEffects::SetAir(float gainhf, int hflimit)
	{
		Info.AIR_GAINHF = gainhf;
		Info.AIR_HFLIMIT = hflimit;

		alEffectf(Effect, AL_REVERB_AIR_ABSORPTION_GAINHF, (ALfloat)Info.AIR_GAINHF);
		alEffecti(Effect, AL_REVERB_DECAY_HFLIMIT, (ALint)Info.AIR_HFLIMIT);
	}

}
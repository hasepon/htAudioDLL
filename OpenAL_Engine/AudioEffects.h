#pragma once
class AudioEffects
{
public:
	AudioEffects();
	~AudioEffects();

protected:

	ALuint EffectSlot;		// エフェクトスロット
	ALuint Effect;			// エフェクト

};


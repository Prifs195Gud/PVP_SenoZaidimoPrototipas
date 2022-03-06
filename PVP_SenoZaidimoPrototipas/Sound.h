#pragma once

#include <SDL_mixer.h>
#include <string>
#include <vector>

class SoundPlayer
{
private:
	std::vector<Mix_Chunk*> soundEffects;

	static SoundPlayer* singleton;

	void LoadSoundEffects();
	void AddSoundEffect(const char* audioClipPath);
	void AddSoundEffect(std::string audioClipPath);	

public:
	SoundPlayer();
	~SoundPlayer();

	static SoundPlayer* GetReference();
	void PlaySoundEffect(int which);
};


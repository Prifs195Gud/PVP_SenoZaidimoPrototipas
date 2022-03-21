
#include <Sound.h>
#include <SDL.h>
#include <fstream>

SoundPlayer* SoundPlayer::singleton = nullptr;

SoundPlayer::SoundPlayer()
{
	singleton = this;

	// init sound
	//SDL_Init(SDL_INIT_AUDIO);

	int audio_rate = 22050;
	Uint16 audio_format = AUDIO_S16SYS;
	int audio_channels = 2;
	int audio_buffers = 512;

	if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't init audio: %s", Mix_GetError());
		return;
	}

	Mix_Volume(-1, GetVolume());
	LoadSoundEffects();
}

SoundPlayer::~SoundPlayer()
{
}

SoundPlayer* SoundPlayer::GetReference()
{
	if (singleton == nullptr)
		return new SoundPlayer();

	return singleton;
}

void SoundPlayer::PlaySoundEffect(int which)
{
	if (which >= soundEffects.size())
		return;

	Mix_PlayChannel(-1, soundEffects[which], 0);
}

void SoundPlayer::LoadSoundEffects()
{
	std::string soundFolder = "Garsai\\";

	AddSoundEffect(soundFolder + "jump_small.wav");
}

void SoundPlayer::AddSoundEffect(std::string audioClipPath)
{
	AddSoundEffect(audioClipPath.c_str());
}

void SoundPlayer::AddSoundEffect(const char* audioClipPath)
{
	Mix_Chunk* tmpChunk = Mix_LoadWAV(audioClipPath);

	if (tmpChunk != nullptr)
		soundEffects.push_back(tmpChunk);
	else
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't init audio: %s", Mix_GetError());
}

int SoundPlayer::GetVolume()
{
	int volume = 128;
	std::string key;
	std::ifstream config;
	config.open("config.txt");
	if(config)
	{
		config >> key >> volume;
		config.close();
	}
	return volume;
}
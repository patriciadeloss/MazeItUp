#include "Sound.h"


Mix_Music* loadMusic(const char* p_filepath)
{
	Mix_Music* mus = NULL;



	mus = Mix_LoadMUS(p_filepath);
	if (mus == NULL)
	{
		cout << "Failed to load music! SDL_mixer Error: %s\n" << Mix_GetError() << endl;
	}

	return mus;


}

Mix_Chunk* loadSFX(const char* p_filepath)
{
	Mix_Chunk* sfx = NULL;

	sfx = Mix_LoadWAV(p_filepath);

	if (sfx == NULL)
	{
		cout << "Failed to load Coin sound effect! SDL_mixer Error: %s\n" << Mix_GetError() << endl;
	}

	return sfx;
}

void Sound::play()
{
	Mix_PlayMusic(soundtrack, -1);
}

void Sound::play(int channel)
{
	Mix_PlayChannel(channel, sfx, 0);
}

void Sound::stop()
{
	Mix_HaltMusic();
}

bool Sound::isplaying()
{
	if (Mix_PlayingMusic() == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}
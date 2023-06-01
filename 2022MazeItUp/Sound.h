#pragma once
#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class Sound
{
private:
	Mix_Chunk* sfx;
	Mix_Music* soundtrack;

public:
	void play();
	void play(int channel);
	void stop();
	bool isplaying();


	//constructor
	Sound(Mix_Chunk* soundeffects)
		:sfx(soundeffects)
	{}

	Sound(Mix_Music* track)
		:soundtrack(track)
	{}

};

Mix_Music* loadMusic(const char* p_filepath);
Mix_Chunk* loadSFX(const char* p_filepath);





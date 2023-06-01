#include <fstream> //file handling
#include <vector>

#include "RenderWindow.h"
#include "mazegame.h"
#include "Sound.h"

using namespace std;


int main(int argc, char* argv[])
{
	//Checks if the libraries were initialized properly
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		cout << "Failed to initialize the SDL2 library. Error: " << SDL_GetError() << endl;

	}

	if (!(IMG_Init(IMG_INIT_PNG)))
	{
		cout << "Failed to initialize IMG_INIT. Error: " << SDL_GetError() << endl;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		cout << "SDL_mixer could not initialize! SDL_mixer Error: %s\n" << Mix_GetError() << endl;
	}

	Mix_Music* gameTrack = loadMusic("audio/xDeviruchi - Take some rest and eat some food!.wav");

	Sound gameMusic(gameTrack);


	//make window
	RenderWindow window("Maze Game", SCREEN_WIDTH, SCREEN_HEIGHT);

	SDL_Event mainevent;
	bool isRunning = true;

	chosenMaze mazelevel;
	chosenMaze* mazepoint = &mazelevel; //point to mazelevel struct

	int passedlvls = 0;
	bool win = false;
	bool* winpoint = &win;
	bool start = false;
	bool* startpoint = &start;
	int coinscollected = 0;
	int* coinpoint = &coinscollected;

	//number of levels per difficulty
	//difficulty (E = easy, M = medium, H = hard)
	int elvls = 4;
	int mlvls = 2;
	int hlvls = 1;

	mazelevel.dif = 'E';
	mazelevel.lvl = 1;
	int gamelevel = 0;
	int* gamelvlpoint = &passedlvls;

	//level loop


	menu(window, startpoint);

	while (isRunning && passedlvls < 7 && start == true)
	{
		if (!(gameMusic.isplaying()))
		{
			gameMusic.play();
		}

		while (SDL_PollEvent(&mainevent))
		{
			if (mainevent.type == SDL_QUIT)
			{
				isRunning = false;
			}
		}

		if (win == false && gamelevel == passedlvls)
		{
			gamelevel++;


			if (mazelevel.dif == 'E')
			{
				if (mazelevel.lvl <= elvls)
				{
					;
				}
				else
				{
					mazelevel.lvl = 1;
					mazelevel.dif = 'M';
				}
			}

			if (mazelevel.dif == 'M')
			{
				if (mazelevel.lvl <= mlvls)
				{
					;
				}
				else
				{
					mazelevel.lvl = 1;
					mazelevel.dif = 'H';
				}
			}

			if (mazelevel.dif == 'H')
			{
				if (mazelevel.lvl <= hlvls)
				{
					;
				}
				else
				{
					;
				}
			}
			

			vector<string> maze = mazepicker(mazepoint);
			mazelevel.mazechosen = maze;
			mazerun(window, mazelevel, winpoint, gamelvlpoint, coinpoint);


			mazelevel.lvl++;
		}
			
		if (win == true && gamelevel == passedlvls)
		{
			cout << "Passed level " << gamelevel << "!!" << endl;
			cout << "Coins Collected: " << coinscollected << "/3\n" << endl;

			win = false;
		}
	}

	gameMusic.stop();
		


	return 0;
}



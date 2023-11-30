#pragma once //makes sure does not get copied twice
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <iostream>

#include "RenderWindow.h"
#include "entity.h"

#define SCREEN_HEIGHT 576
#define SCREEN_WIDTH 1206


struct chosenMaze
{
	int mazeheight, mazewidth; //grid size 
	int mapheight, mapwidth; //map size
	int dif;
	int lvl;
	vector<string> mazechosen;
};

using namespace std;

void menu(RenderWindow& mainwindow, bool* start);
void mazerun(RenderWindow& mainwindow, chosenMaze mazelevel, bool* win, int* gamelvlpoint, int* coinpoint);
void update();
//vector<vector<char>> mazes(int lvl);
bool detectcollision(Entity& player, Entity& obj, int dir, int spd);
vector<string> mazepicker(chosenMaze* mazelevel);



#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include "math.h"

//Entity = all things that can be rendered to the screen
class Entity
{
private:
	//location on field
	Vector2df pos;

	SDL_Rect currentFrame;

	SDL_Texture* tex; //texture

	int multiplr; //for size multiplier (enlarge)
	
	IMGSize size; //size to display on screen

	IMGSize tot_size; //total size of image

	int speed;

	bool get; //if got coin
	


public:
	//(X pos, Y pox, pointer to texture), CONSTRUCTORS
	Entity(Vector2df ent_pos, SDL_Texture* ent_tex, IMGSize ent_size, int multiplier, int spd); //for text
	Entity(Vector2df ent_pos, SDL_Texture* ent_tex, IMGSize ent_size, int spd); //default multiplier = 3
	Entity(Vector2df ent_pos, SDL_Texture* ent_tex, IMGSize ent_size, IMGSize total_size, int multiplier, int spd); //for the ground
	Entity(Vector2df ent_pos, SDL_Texture* ent_tex, IMGSize ent_size, int spd, bool get); //for coins
	
	//DESTRUCTOR
	~Entity();


	//movement
	void move(int dir);
	void changeFrame(int numberFrames, int dir, int delay);
	void groundmove(int dir);
	void playermove(int dir);

	//void StartShift(int shiftx, int shifty);
	//void groundStartShift(int shiftx, int shifty);

	//"getter" functions
	Vector2df& getPos()
	{
		return pos;
	}

	SDL_Texture* getTex()
	{
		return tex;
	}

	SDL_Rect getCurrentFrame()
	{
		return currentFrame;
	}

	int getMultiplier()
	{
		return multiplr;
	}

	IMGSize getTotalSize()
	{
		return tot_size;
	}

	IMGSize getSize()
	{
		return size;
	}

	int getSpeed()
	{
		return speed;
	}

	bool getCoinStatus()
	{
		return get;
	}

	void changeGet(bool newget)
	{
		get = newget;
	}

	void changeTex(SDL_Texture* changetex);
	void changePos(int x, int y); //enter new x y values
	void adjustPos(int x, int y); //add subtract x y values

	void changeCurrentFrame(int x, int y); 
	
};
 
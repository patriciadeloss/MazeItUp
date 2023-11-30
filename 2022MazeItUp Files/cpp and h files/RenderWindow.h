#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "entity.h"

class RenderWindow
{
public:
	RenderWindow(const char* w_title, int w_width, int w_height); //constructor
	//pointer to texture
	SDL_Texture* loadTexture(const char* p_filepath);
	SDL_Texture* SurfacetoTexture(SDL_Surface* p_surf);
	void setColor(int r, int g, int b);
	

	
	void cleanUp();
	void clear();
	void render(Entity& p_entity);//& = pass by reference, don't make a copy
	void display();
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
};

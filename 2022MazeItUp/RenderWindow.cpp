#include "mazegame.h"
#include "RenderWindow.h"
#include "entity.h"

RenderWindow::RenderWindow(const char* w_title, int w_width, int w_height)
	//member initialization list
	:window(NULL), renderer(NULL)
{
	//(window name, x position, y posiiton, width, height, any "flags")
	//Function returns SDL pointer to a window
	window = SDL_CreateWindow(w_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w_width, w_height, SDL_WINDOW_SHOWN);
	
	//if failed to point to a window
	if (window == NULL)
	{
		cout << "Failed to initialize window. Error: " << SDL_GetError() << endl;
	}

	//(where to render, index to graphics driver, flags)
	//-1 --> Just use first that satisfies all needs
	//SDL_RENDERER_ACCELERATED --> Use whatever graphics card is fastest
	//V sync makes it so that display rate matches your screen's display rate
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED && SDL_RENDERER_PRESENTVSYNC);
	
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filepath)
{
	//pointer to a texture
	SDL_Texture* texture = NULL;

	texture = IMG_LoadTexture(renderer, p_filepath);

	//if did not manage to point to the texture
	if (texture == NULL)
	{
		cout << "Failed to load texture. Error: " << SDL_GetError() << endl;
	}

	return texture;

}

//Destroy window to avoid memory leaks
void RenderWindow::cleanUp()
{
	
	SDL_DestroyWindow(window);
}

//clear rendering target (ex. window)
void RenderWindow::clear()
{
	SDL_RenderClear(renderer);
}

SDL_Texture* RenderWindow::SurfacetoTexture(SDL_Surface* p_surf)
{
	SDL_Texture* texture = NULL;

	texture = SDL_CreateTextureFromSurface(renderer, p_surf);

	if (texture == NULL)
	{
		cout << "Failed to load texture. Error: " << SDL_GetError() << endl;
	}

	return texture;
}


void RenderWindow::setColor(int r, int g, int b)
{
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
}

//render the texture
void RenderWindow::render(Entity& p_entity)
{
	//set source rectangle and dest rec to same as entity values

	//structure with 4 members: x pos, y pos, width and height
	//position from top left of screen, all par in pixels
	SDL_Rect src; //source rectangle (for texture)
	src.x = p_entity.getCurrentFrame().x;
	src.y = p_entity.getCurrentFrame().y;
	src.w = p_entity.getCurrentFrame().w;
	src.h = p_entity.getCurrentFrame().h;

	SDL_Rect dst; //destination rectangle (for window)
	dst.x = p_entity.getPos().x * p_entity.getMultiplier();
	dst.y = p_entity.getPos().y * p_entity.getMultiplier();
	dst.w = p_entity.getCurrentFrame().w * p_entity.getMultiplier(); //multiplying dest width or height by number
	dst.h = p_entity.getCurrentFrame().h * p_entity.getMultiplier();	//will increase size of image


	/*
	Parameters:
	(render, texture, source rectangle (which part of texture), 
	destination rectangle (where on the rendering target (window)))

	NULL means entire texture or entire screen
	  
	All par are pointers
	*/
	SDL_RenderCopy(renderer, p_entity.getTex(), &src, &dst);
}

void RenderWindow::display()
{
	//Update the screen, switch the "front" with the backbuffer
	SDL_RenderPresent(renderer);
}
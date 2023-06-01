#include "entity.h"
using namespace std;

Entity::Entity(Vector2df ent_pos, SDL_Texture* ent_tex, IMGSize ent_size, int multiplier, int spd)
//member initialization list
	:pos(ent_pos), tex(ent_tex), multiplr(multiplier), size(ent_size), speed(spd)
{
	//fill out the frame for the entity
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = ent_size.w;
	currentFrame.h = ent_size.h;

}

Entity::Entity(Vector2df ent_pos, SDL_Texture* ent_tex, IMGSize ent_size, int spd)
	//member initialization list
	:pos(ent_pos), tex(ent_tex), multiplr(3), size(ent_size), speed(spd)
{
	//fill out the frame for the entity
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = ent_size.w;
	currentFrame.h = ent_size.h;

}

Entity::Entity(Vector2df ent_pos, SDL_Texture* ent_tex, IMGSize ent_size, int spd, bool get)
//member initialization list
	:pos(ent_pos), tex(ent_tex), multiplr(3), size(ent_size), speed(spd), get(get)
{
	//fill out the frame for the entity
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = ent_size.w;
	currentFrame.h = ent_size.h;

}


Entity::Entity(Vector2df ent_pos, SDL_Texture* ent_tex, IMGSize ent_size, IMGSize total_size, int multiplier, int spd)
	:pos(ent_pos), tex(ent_tex), multiplr(multiplier), size(ent_size), tot_size(total_size), speed(spd)
{
	//fill out the frame for the entity
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = ent_size.w;
	currentFrame.h = ent_size.h;

}


Entity::~Entity()
{}


void Entity::changeTex(SDL_Texture* changetex)
{
	tex = changetex;
}

void Entity::move(int dir)
{
	if (dir == 1) //up
	{
		pos.y += 1 * speed;
	}
	else if (dir == 2) //right
	{
		pos.x -= 1 * speed;
	}
	else if (dir == 3) //down
	{
		pos.y -= 1 * speed;
	}
	else if (dir == 4) //left
	{
		pos.x += 1 * speed;
	}

}

void Entity::playermove(int dir)
{
	if (dir == 1) //up
	{
		pos.y -= 1 * speed;
	}
	else if (dir == 2) //right
	{
		pos.x += 1 * speed;
	}
	else if (dir == 3) //down
	{
		pos.y += 1 * speed;
	}
	else if (dir == 4) //left
	{
		pos.x -= 1 * speed;
	}

}

//yay it works, didn't know if it would
void Entity::groundmove(int dir)
{
	if (dir == 1) //up
	{
		currentFrame.y -= 1 * speed;
	}
	else if (dir == 2) //right
	{
		currentFrame.x += 1 * speed;
	}
	else if (dir == 3) //down
	{
		currentFrame.y += 1 * speed;
	}
	else if (dir == 4) //left
	{
		currentFrame.x -= 1 * speed;
	}

}


//To animate sprites
void Entity::changeFrame(int numberFrames, int dir, int delay)
{
	//sprite set up as (from top to bottom), forward, right, back, left
	if (dir == 1) //backward
	{
		currentFrame.y = size.h * 2;
	}
	else if (dir == 2) //right
	{
		currentFrame.y = size.h * 1;
	}
	else if (dir == 3) //forward
	{
		currentFrame.y = size.h * 0;
	}
	else if (dir == 4) //left
	{
		currentFrame.y = size.h * 3;
	}

	//before last frame
	if (currentFrame.x < (size.w * (numberFrames-1)))
	{
		currentFrame.x += size.w;
	}
	//at last frame
	else
	{
		currentFrame.x = 0;
	}

	//delay between frames
	SDL_Delay(delay);
}



void Entity::changePos(int x, int y)
{
	pos.x = x;
	pos.y = y;
}


void Entity::adjustPos(int x, int y)
{
	pos.x += x;
	pos.y += y;
}

void Entity::changeCurrentFrame(int x, int y)
{
	currentFrame.x = x;
	currentFrame.y = y;
}

/*
void Entity::StartShift(int shiftx, int shifty)
{
	//invert x and y (1 = -1), from top left (subtract 1 from x and y)
	shiftx = (shiftx - 1) * -1;
	shifty = (shifty - 1) * -1;

	pos.x += (shiftx * size.w);
	pos.y += (shifty * size.h);

}

void Entity::groundStartShift(int shiftx, int shifty)
{
	float x = (float(shiftx));
	float y = (float(shifty));

	cout << x << endl;
	cout << y << endl;

	x = (x - 1);
	y = (y - 1);
	//x /= 6; //ground shift relative to number of entities on screen on x and y axis
	//y /= 5;

	cout << x << endl;
	cout << y << endl;

	
	currentFrame.x += (x * 67);
	currentFrame.y += (y * 48);

	cout << currentFrame.x << endl;
	cout << currentFrame.y << endl;
}
*/
#pragma once
#include <iostream>
using namespace std;

struct Vector2df
{
	float x, y;

	Vector2df() //constructor
		:x(0.0f), y(0.0f)
	{}

	Vector2df(float x_pos, float y_pos) //constructor
		:x(x_pos), y(y_pos)
	{}

	//for debugging
	void print()
	{
		cout << x << ", " << y << endl;
	}
		
};

struct IMGSize
{	
	//width and height
	float w, h;

	IMGSize() //constructor
		:w(0.0f), h(0.0f)
	{}

	IMGSize(float w_pos, float h_pos) //constructor
		:w(w_pos), h(h_pos)
	{}

};
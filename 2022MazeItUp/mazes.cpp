#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

#include "mazegame.h"

using namespace std;

vector<string> mazepicker(chosenMaze* mazelevel)
{
	ifstream fin;
	stringstream ss;

	int level = mazelevel->lvl;
	char dif = mazelevel->dif;

	int count;	
	char ch, chlvl;
	string row;

	ss << level;
	ss >> chlvl;
	ss.clear();

	bool founddif = false; //foundlvl = false;
	

	vector<string> maze;


	if (dif == 'E')
	{
		mazelevel->mazewidth = 8;
		mazelevel->mazeheight = 8;
		mazelevel->mapwidth = 536;
		mazelevel->mapheight = 384;
	}
	else if (dif == 'M')
	{
		mazelevel->mazewidth = 15;
		mazelevel->mazeheight = 15;
		mazelevel->mapwidth = 1005;
		mazelevel->mapheight = 720;
	}
	else //dif == 'H'
	{
		mazelevel->mazewidth = 21;
		mazelevel->mazeheight = 21;
		mazelevel->mapwidth = 1407;
		mazelevel->mapheight = 1008;
	}


	fin.open("mazes/finalprojectmazes.txt");

	if (fin.is_open() == false)
	{
		cerr << "The file does not exist." << endl;
	}

	while (fin.get(ch))
	{
		if (founddif == true)
		{
			if (ch == chlvl)
			{
				//cout << "found" << endl;
				break;
			}
			else
			{
				founddif = false;
			}

		}
		else if (ch == dif)
		{
			founddif = true;
		}

	}

	count = mazelevel->mazewidth;

	while (fin.get(ch) && count >= 0)
	{
		if (ch == '\n' && count == mazelevel->mazewidth)
		{
			count -= 1;
		}

		else if (ch == '\n')
		{
			count -= 1;
			maze.push_back(row);
			row.clear();
			//cout << ch;
		}

		else
		{
			row.push_back(ch);
			//cout << ch;
		}
	}


	return maze;
	
}
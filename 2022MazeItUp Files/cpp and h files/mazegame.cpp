#include "mazegame.h"

bool detectcollision(Entity& player, Entity& obj, int dir, int spd)
{
	//location 
	float player_x, player_y, obj_x, obj_y;
	//size
	//player is 21x21 pixels
	float player_w = 21, player_h = 21, obj_w, obj_h;

	//getting location
	player_x = player.getPos().x;
	player_y = player.getPos().y;
	obj_x = obj.getPos().x;
	obj_y = obj.getPos().y;

	
	//getting obj width
	obj_w = obj.getSize().w;
	obj_h = obj.getSize().h;
	

	//For Debugging:
	//cout << "plx: " << player_x << endl;
	//cout << "ply: " << player_y << endl;
	//cout << "obx: " << obj_x << endl;
	//cout << "oby: " << obj_y << endl;
	//cout << "obw: " << obj_w << endl;
	//cout << "obh: " << obj_h << endl;


	//reminder: location (x,y) is from TOP LEFT CORNER
	//I ended up using player_w/player_h and 21 interchangeably... (all 21)

	if (dir == 1) //up, check player y vs obj y+h (to check bottom of object) and that player is within object "range"
	{
		if ((player_y - spd <= (obj_y + obj_h) && player_y + 21 >= obj_y) && (player_x + 21 >= obj_x && player_x <= obj_x + obj_w))
		{
			//cout << "True" << endl;
			//cout << "obj: " << obj_y + obj_h << "\nplayer: " << player_y << endl;
			return true;
		}
		else
		{
			//cout << "False" << endl;
			//cout << "obj: " << obj_y + obj_h << "\nplayer: " << player_y << endl;
			return false;
		}
	}
	else if (dir == 2) //right, check player x+w vs obj x & player vs object range
	{
		if (((player_x + player_w + spd) >= obj_x && player_x <= (obj_x + obj_w)) && (player_y + 21 >= obj_y && player_y <= obj_y + obj_h))
		{
			//cout << "True" << endl;
			//cout << "obj: " << obj_x << "\nplayer: " << player_x + player_w << endl;
			return true;
		}	
		else
		{
			//cout << "False" << endl;
			//cout << "obj: " << obj_y << "\nplayer: " << player_y + player_w << endl;
			return false;
		}
	}
	else if (dir == 3) //down, check player y+h vs obj y & player vs object range
	{
		if (((player_y + player_h + spd) >= obj_y && player_y <= (obj_y + obj_h)) && (player_x + 21 >= obj_x && player_x <= obj_x + obj_w))
		{
			//cout << "True" << endl;
			//cout << "obj: " << obj_y << "\nplayer: " << player_y + player_w << endl;
			return true;
		}
		else
		{
			//cout << "False" << endl;
			//cout << "obj: " << obj_y << "\nplayer: " << player_y + player_w << endl;
			return false;
		}
			
	}
	else //left, check player x vs obj x+w & player vs object range
	{
		if ((player_x - spd <= (obj_x + obj_w) && (player_x + player_w) >= obj_x) && (player_y + 21 >= obj_y && player_y <= obj_y + obj_h))
		{
			//cout << "True" << endl;
			//cout << "obj: " << obj_x + obj_w << "\nplayer: " << player_x << endl;
			return true;
		}
		else
		{
			//cout << "False" << endl;
			//cout << "obj: " << obj_x + obj_w << "\nplayer: " << player_x << endl;
			return false;
		}
	}
		
}

/*
vector<string> mazepicker(int lvl, int* mazeheight, int* mazewidth, int* mapheight, int* mapwidth)
{
	vector<string> maze;
	//easy :)
	if (lvl >= 1 && lvl <= 3)
	{
		*mazewidth = 8;
		*mazeheight = 8;
		*mapwidth = 536;
		*mapheight = 384;

		if (lvl == 1)
		{
			vector<string> maze{
			   { "WWWWWWWW" },
			   { "W.P..WCW" },
			   { "W.WW.W.W" },
			   { "WC.....W" },
			   { "WWWW.WWW" },
			   { "WWWW.WWW" },
			   { ".E....CW" },
			   { "WWWWWWWW" }};
		}
		else if (lvl == 2)
		{
			vector<string> maze{
				{"WWWWWW.W"},
				{"WC...WEW"},
				{"W.WW.W.W"},
				{"W....W.W"},
				{"WWWWCW.W"},
				{"WWWW.W.W"},
				{"WP....CW"},
				{"WWWWWWWW"}};
		}
		else if (lvl == 3)
		{
			vector<string> maze
			{
				{"WWWWEWWW"},
				{"WC.....W"},
				{"WwWWwW.W"},
				{"WC...W.W"},
				{"WWWW.WCW"},
				{"WWWW.W.W"},
				{"WS.....W"},
				{"WWWWWWWW"}};
		}
	}

	//medium
	else if (lvl >= 4 && lvl <= 6)
	{
		*mazewidth = 15;
		*mazeheight = 15;
		*mapwidth = 1005;
		*mapheight = 720;
		
		if (lvl == 4)
		{
			vector<string> maze
			{
				{"WWWWWWWWWWWWWWW"},
				{"W.....W.......W"},
				{"W.WWW.W.WWWWWWW"},
				{"W.....W.W.....W"},
				{"W.WWWWW...WWW.W"},
				{"W.WE....W.....W"},
				{"W.WWWWWWWWWWW.W"},
				{"W.............W"},
				{"W.WWWWWWWWWWWWW"},
				{"W.............W"},
				{"WWWWWW.W......W"},
				{"W......W..WWW.W"},
				{"W.WWWWWW..WWW.W"},
				{"W.....SW......W"},
				{"WWWWWWWWWWWWWWW"}
			};
		}

	}
}
*/
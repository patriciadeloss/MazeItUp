#include "mazegame.h"
#include "math.h"
#include "entity.h"
#include "Sound.h"

#include <iostream>

void menu(RenderWindow& mainwindow, bool* start)
{
    mainwindow.setColor(191, 158, 102);

    Mix_Music* titleTrack = loadMusic("audio/xDeviruchi-And_The_Journey_Begins.wav");

    Sound titleMusic(titleTrack);

    SDL_Texture* subheadTexture = mainwindow.loadTexture("graphics/subheading.png");
    SDL_Texture* titleTexture = mainwindow.loadTexture("graphics/TitleMazeItUp.png");
    SDL_Texture* instructTexture = mainwindow.loadTexture("graphics/instructions.png");
    SDL_Texture* defaultgrassTexture = mainwindow.loadTexture("graphics/chp1grass.png");
    SDL_Texture* forestTexture = mainwindow.loadTexture("graphics/chp1forest.png");

    Entity groundgrass(Vector2df(), defaultgrassTexture, IMGSize(600, 300), IMGSize(1200, 600), 3, 6);
    Entity Title(Vector2df(25, 15), titleTexture, IMGSize(340, 96), 3, 3);
    Entity Subhead(Vector2df(100, 100), subheadTexture, IMGSize(201, 48), 3, 3);
    Entity Instructions(Vector2df(), instructTexture, IMGSize(SCREEN_WIDTH, SCREEN_HEIGHT), 1, 3);

    vector<Entity> trees;

    for (int i = 0; i < 7; i++)
    {
        for(int j = 0; j < 4; j += 3)
        trees.push_back(Entity(Vector2df(i * 67, j * 48), forestTexture, IMGSize(68, 47), 6));
    }


	bool isRunning = true;
    bool quit = false;
    bool instruct = false;
    bool up = false;

    titleMusic.play();

	//while loop to keep screen running
	while (isRunning == true)
	{
        //SDL_Event is like a struct
        SDL_Event ev;
        while (SDL_PollEvent(&ev))
        {
            if (ev.type == SDL_QUIT)
            {
                isRunning = false;
                quit == true;
                break;
            }

            if (ev.type == SDL_KEYDOWN)
            {
                switch (ev.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    isRunning = false;
                    quit == true;
                    break;
                case SDLK_SPACE:
                    //cout << "SPACE" << endl;
                    *start = true;
                    isRunning = false;
                    break;

                case SDLK_h:
                    //cout << "H" << endl;
                    mainwindow.clear();
                    mainwindow.render(Instructions);
                    mainwindow.display();
                    instruct = true;

                    while (instruct == true)
                    {
                        while (SDL_PollEvent(&ev))
                        {
                            if (ev.type == SDL_KEYDOWN)
                            {
                                if (ev.key.keysym.sym == SDLK_SPACE)
                                {
                                    //cout << "SPACE" << endl;
                                    mainwindow.clear();
                                    instruct = false;
                                }
                            }
                        }
                        
                    }
                    break;
                }

            }

        }


        for (Entity& e : trees)
        {
            e.adjustPos(3, 0);
            if (e.getPos().x > 402)
            {
                e.changePos(-67, e.getPos().y);
            }

            SDL_Delay(10);
        }

        {
           

            if (Title.getPos().y < 27 && up == false)
            {
                Title.adjustPos(0, 3);
                Subhead.adjustPos(0, 3);
                if (Title.getPos().y == 27)
                {
                    up = true;
                }
            }
            else if (Title.getPos().y > 9 && up == true)
            {
                Title.adjustPos(0, -3);
                Subhead.adjustPos(0, -3);
                if (Title.getPos().y == 9)
                {
                    up = false;
                }
            }
            


        }

        //mainwindow.render(groundgrass);

        for (Entity& e : trees)
        {
            mainwindow.render(e);
        }

        mainwindow.render(Subhead);
        mainwindow.render(Title);
        mainwindow.display();
        mainwindow.clear();

	}

    titleMusic.stop();
    mainwindow.clear();

    if (quit == true)
    {
        mainwindow.cleanUp();
        SDL_Quit();
    }
}

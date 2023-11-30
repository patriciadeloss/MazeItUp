#include <vector>

#include "mazegame.h"
#include "RenderWindow.h"
#include "entity.h"
#include "Sound.h"


void mazerun(RenderWindow& mainwindow, chosenMaze mazelevel, bool* win, int* gamelvlpoint, int* coinpoint) {

    RenderWindow window = mainwindow;

    //RenderWindow window("Maze Game", SCREEN_WIDTH, SCREEN_HEIGHT);

    Mix_Chunk* coinSound = loadSFX("audio/coinhit.wav");
    Mix_Chunk* winSound = loadSFX("audio/round_end.wav");

    Sound winSFX(winSound);
    Sound coinSFX(coinSound);

    SDL_Texture* easygrassTexture = window.loadTexture("graphics/536x384groundgrass(easy).png");
    SDL_Texture* medgrassTexture = window.loadTexture("graphics/1005x720groundgrass(medium).png");
    SDL_Texture* hardgrassTexture = window.loadTexture("graphics/1407x1008groundgrass(hard).png");
    SDL_Texture* defaultgrassTexture = window.loadTexture("graphics/chp1grass.png");

    SDL_Texture* platformTexture = window.loadTexture("graphics/platform.png");
    SDL_Texture* coinTexture = window.loadTexture("graphics/coinsprite.png");

    SDL_Texture* playerwalkTexture = window.loadTexture("graphics/playerwalk1.png");

    SDL_Texture* forestTexture = window.loadTexture("graphics/chp1forest.png");
    SDL_Texture* treeTexture = window.loadTexture("graphics/chp1treesprite.png");



    vector<string> maze = mazelevel.mazechosen;
    int mazewidth = mazelevel.mazewidth;
    int mazeheight = mazelevel.mazeheight;
    int mapheight = mazelevel.mapheight;
    int mapwidth = mazelevel.mapwidth;
    char dif = mazelevel.dif;
    int playerstartx = 0, playerstarty = 0;

    //For Debugging
    //cout << "mzwd: " << mazewidth << endl;
    //cout << "mzht: " << mazeheight << endl;
    //cout << "mpht: " << mapheight << endl;
    //cout << "mpwd: " << mapwidth << endl;

    //Vector2df ent_pos, SDL_Texture* ent_tex, IMGSize ent_size, IMGSize total_size, int multiplier, int spd
    Entity groundgrass(Vector2df(), defaultgrassTexture, IMGSize(402, 192), IMGSize(mapwidth, mapheight), 3, 6);

    // screen height = 1200, screen width = 600
    Entity Player(Vector2df(90, 62), playerwalkTexture, IMGSize(21, 21), 6);

    Entity Platform(Vector2df(), platformTexture, IMGSize(68, 47), 6);

    Entity GotCoin(Vector2df(), coinTexture, IMGSize(21, 21), 6);


    if (dif == 'E')
    {
        groundgrass.changeTex(easygrassTexture);

    }
    else if (dif == 'M')
    {
        groundgrass.changeTex(medgrassTexture);
    }
    else if (dif == 'H')
    {
        groundgrass.changeTex(hardgrassTexture);
    }


    vector<Entity> trees;
    vector<Entity> coins;



    char c;

    for (int i = 0; i < mazewidth; i++)
    {
        for (int j = 0; j < mazeheight; j++)
        {
            c = maze[i][j];
            //cout << c;
            if (c == 'W')
            {
                trees.push_back(Entity(Vector2df(j * 67, i * 48), forestTexture, IMGSize(68, 47), 6));
            }
            else if (c == 'E')
            {
                Platform.changePos(j * 67, i * 48);
            }
            else if (c == 'C')
            {
                coins.push_back(Entity(Vector2df(j * 67 + (67 / 2 - 10), i * 48 + (67 / 2 - 10)), coinTexture, IMGSize(21, 21), 6, false));
            }

            if (c == 'S')
            {
                playerstartx = j;
                playerstarty = i;
            }
        }
    }








    bool gameisRunning = true;
    bool collide = false;

    int coinframefreeze = 1;
    bool getCoin;
    int coincount = 0;
    int getcoinanim = 0;

    bool winGame = *win;

    SDL_Event gameevent;


    while (gameisRunning)
    {
        window.clear();

        while (SDL_PollEvent(&gameevent))
        {
            if (gameevent.type == SDL_QUIT)
            {
                gameisRunning = false;
            }

            if (gameevent.type == SDL_KEYDOWN)
            {
                switch (gameevent.key.keysym.sym) {

                case SDLK_UP:
                    //cout << "UP" << endl;
                    //want player in mid screen as much as possible
                    //if screen can move, move everything but player
                    //top of screen : currentFrame.y = 0
                    if ((Player.getPos().y == 86) && (groundgrass.getCurrentFrame().y > 0))
                    {
                        collide = false;
                        for (Entity& e : trees)
                        {
                            collide = detectcollision(Player, e, 1, e.getSpeed());
                            if (collide == true)
                            {
                                break;
                            }
                        }
                        if (collide == false)
                        {
                            for (Entity& e : trees)
                            {
                                e.move(1);
                            }
                            for (Entity& c : coins)
                            {
                                c.move(1);
                            }
                            Platform.move(1);
                            groundgrass.groundmove(1);
                            Player.changeFrame(4, 1, 25);
                        }

                        getCoin = false;
                        for (Entity& c : coins)
                        {
                            getCoin = detectcollision(Player, c, 1, c.getSpeed());
                            if (getCoin == true)
                            {
                                coinSFX.play(-1);
                                getcoinanim = 9;
                                c.changeGet(true);
                                //move coin out of map
                                c.changePos(groundgrass.getPos().x - 100, groundgrass.getPos().y -100);
                                coincount += 1;
                                break;
                            }
                        }

                        winGame = false;
                        {
                            winGame = detectcollision(Player, Platform, 1, 0);
                            if (winGame == true)
                            {
                                gameisRunning = false;
                                *win = winGame;
                            }
                        }
                    }

                    //if screen cannot move, move player
                    else if (Player.getPos().y - Player.getSpeed() > 0)
                    {
                        collide = false;
                        for (Entity& e : trees)
                        {
                            collide = detectcollision(Player, e, 1, e.getSpeed());
                            if (collide == true)
                            {
                                break;
                            }
                        }
                        if (collide == false)
                        {
                            Player.changeFrame(4, 1, 25);
                            Player.playermove(1);
                        }

                        getCoin = false;
                        for (Entity& c : coins)
                        {
                            getCoin = detectcollision(Player, c, 1, c.getSpeed());
                            if (getCoin == true)
                            {
                                coinSFX.play(-1);
                                getcoinanim = 9;
                                c.changeGet(true);
                                c.changePos(groundgrass.getPos().x - 100, groundgrass.getPos().y - 100);
                                coincount += 1;
                                break;
                            }
                        }

                        winGame = false;
                        {
                            winGame = detectcollision(Player, Platform, 1, 0);
                            if (winGame == true)
                            {
                                gameisRunning = false;
                                *win = winGame;
                            }
                        }
                    }
                    break;


                case SDLK_RIGHT:
                    //cout << "RIGHT" << endl;
                    //x and y of currentFrame is from top left
                    //Need to make sure curframe x is less than rightmost of image for move
                    if ((Player.getPos().x == 192) && (groundgrass.getCurrentFrame().x < groundgrass.getTotalSize().w - groundgrass.getSize().w))
                    {
                        collide = false;
                        for (Entity& e : trees)
                        {
                            collide = detectcollision(Player, e, 2, e.getSpeed());
                            if (collide == true)
                            {
                                break;
                            }
                        }
                        if (collide == false)
                        {
                            for (Entity& e : trees)
                            {
                                e.move(2);
                            }
                            for (Entity& c : coins)
                            {
                                c.move(2);
                            }
                            Platform.move(2);
                            groundgrass.groundmove(2);
                            Player.changeFrame(4, 2, 25);
                        }

                        getCoin = false;
                        for (Entity& c : coins)
                        {
                            getCoin = detectcollision(Player, c, 2, c.getSpeed());
                            if (getCoin == true)
                            {
                                coinSFX.play(-1);
                                getcoinanim = 9;
                                c.changeGet(true);
                                c.changePos(groundgrass.getPos().x - 100, groundgrass.getPos().y - 100);
                                coincount += 1;
                                break;
                            }
                        }

                        winGame = false;
                        {
                            winGame = detectcollision(Player, Platform, 2, 0);
                            if (winGame == true)
                            {
                                gameisRunning = false;
                                *win = winGame;
                            }
                        }
                    }

                    else if (Player.getPos().x + Player.getSpeed() < mapwidth)
                    {
                        collide = false;
                        for (Entity& e : trees)
                        {
                            collide = detectcollision(Player, e, 2, e.getSpeed());
                            if (collide == true)
                            {
                                break;
                            }
                        }
                        if (collide == false)
                        {
                            Player.changeFrame(4, 2, 25);
                            Player.playermove(2);
                        }

                        getCoin = false;
                        for (Entity& c : coins)
                        {
                            getCoin = detectcollision(Player, c, 2, c.getSpeed());
                            if (getCoin == true)
                            {
                                coinSFX.play(-1);
                                getcoinanim = 9;
                                c.changeGet(true);
                                c.changePos(groundgrass.getPos().x - 100, groundgrass.getPos().y - 100);
                                coincount += 1;
                                break;
                            }
                        }

                        winGame = false;
                        {
                            winGame = detectcollision(Player, Platform, 2, 0);
                            if (winGame == true)
                            {
                                gameisRunning = false;
                                *win = winGame;
                            }
                        }
                    }
                    break;


                case SDLK_DOWN:
                    //cout << "DOWN" << endl;
                    if ((Player.getPos().y == 86) && (groundgrass.getCurrentFrame().y < groundgrass.getTotalSize().h - groundgrass.getSize().h))
                    {
                        collide = false;
                        for (Entity& e : trees)
                        {
                            collide = detectcollision(Player, e, 3, e.getSpeed());
                            if (collide == true)
                            {
                                break;
                            }
                        }
                        if (collide == false)
                        {
                            for (Entity& e : trees)
                            {
                                e.move(3);
                            }
                            for (Entity& c : coins)
                            {
                                c.move(3);
                            }
                            Platform.move(3);
                            groundgrass.groundmove(3);
                            Player.changeFrame(4, 3, 25);
                        }

                        getCoin = false;
                        for (Entity& c : coins)
                        {
                            getCoin = detectcollision(Player, c, 3, c.getSpeed());
                            if (getCoin == true)
                            {
                                coinSFX.play(-1);
                                getcoinanim = 9;
                                c.changeGet(true);
                                c.changePos(groundgrass.getPos().x - 100, groundgrass.getPos().y - 100);
                                coincount += 1;
                                break;
                            }
                        }

                        winGame = false;
                        {
                            winGame = detectcollision(Player, Platform, 3, 0);
                            if (winGame == true)
                            {
                                gameisRunning = false;
                                *win = winGame;
                            }
                        }
                    }

                    else if (Player.getPos().y + Player.getSpeed() < mapheight)
                    {
                        collide = false;
                        for (Entity& e : trees)
                        {
                            collide = detectcollision(Player, e, 3, e.getSpeed());
                            if (collide == true)
                            {
                                break;
                            }
                        }
                        if (collide == false)
                        {
                            Player.changeFrame(4, 3, 25);
                            Player.playermove(3);
                        }

                        getCoin = false;
                        for (Entity& c : coins)
                        {
                            getCoin = detectcollision(Player, c, 3, c.getSpeed());
                            if (getCoin == true)
                            {
                                coinSFX.play(-1);
                                getcoinanim = 9;
                                c.changeGet(true);
                                c.changePos(groundgrass.getPos().x - 100, groundgrass.getPos().y - 100);
                                coincount += 1;
                                break;
                            }
                        }

                        winGame = false;
                        {
                            winGame = detectcollision(Player, Platform, 3, 0);
                            if (winGame == true)
                            {
                                gameisRunning = false;
                                *win = winGame;
                            }
                        }
                    }
                    break;


                case SDLK_LEFT:
                    //cout << "LEFT" << endl;
                    if ((Player.getPos().x == 192) && (groundgrass.getCurrentFrame().x > 0))
                    {
                        collide = false;
                        for (Entity& e : trees)
                        {
                            collide = detectcollision(Player, e, 4, e.getSpeed());
                            if (collide == true)
                            {
                                break;
                            }
                        }
                        if (collide == false)
                        {
                            for (Entity& e : trees)
                            {
                                e.move(4);
                            }
                            for (Entity& c : coins)
                            {
                                c.move(4);
                            }
                            Platform.move(4);
                            groundgrass.groundmove(4);
                            Player.changeFrame(4, 4, 25);
                        }

                        getCoin = false;
                        for (Entity& c : coins)
                        {
                            getCoin = detectcollision(Player, c, 4, c.getSpeed());
                            if (getCoin == true)
                            {
                                coinSFX.play(-1);
                                getcoinanim = 9;
                                c.changeGet(true);
                                c.changePos(groundgrass.getPos().x - 100, groundgrass.getPos().y - 100);
                                coincount += 1;
                                break;
                            }
                        }

                        winGame = false;
                        {
                            winGame = detectcollision(Player, Platform, 4, 0);
                            if (winGame == true)
                            {
                                gameisRunning = false;
                                *win = winGame;
                            }
                        }
                    }

                    else if (Player.getPos().x - Player.getSpeed() > 0)
                    {
                        collide = false;
                        for (Entity& e : trees)
                        {
                            collide = detectcollision(Player, e, 4, e.getSpeed());
                            if (collide == true)
                            {
                                break;
                            }
                        }
                        if (collide == false)
                        {
                            Player.changeFrame(4, 4, 25);
                            Player.playermove(4);
                        }

                        getCoin = false;
                        for (Entity& c : coins)
                        {
                            getCoin = detectcollision(Player, c, 4, c.getSpeed());
                            if (getCoin == true)
                            {
                                coinSFX.play(-1);
                                getcoinanim = 9;
                                c.changeGet(true);
                                c.changePos(groundgrass.getPos().x - 100, groundgrass.getPos().y - 100);
                                coincount += 1;
                                break;
                            }
                        }

                        winGame = false;
                        {
                            winGame = detectcollision(Player, Platform, 4, 0);
                            if (winGame == true)
                            {
                                gameisRunning = false;
                                *win = winGame;
                            }
                        }
                    }

                    break;
                }
            }

        }



        //rendered first = at the back

        window.render(groundgrass);

        //range based for loop
        //([data type] [variable for element in array] : [vector name])
        for (Entity& e : trees)
        {
            window.render(e);
        }


        if (coinframefreeze == 1)
        {
            for (Entity& c : coins)
            {
                c.changeFrame(6, 3, 25);
            }
            coinframefreeze = 0;
        }
        else
        {
            coinframefreeze = 1;
        }

        //if got coin, don't render to screen
        for (Entity c : coins)
        {
            if (c.getCoinStatus() == false)
            {
                window.render(c);
            }
        }


        //if got coin, animate coin get above head
        if (getcoinanim > 0)
        {
            if (getcoinanim > 3)
            {
                GotCoin.changePos(Player.getPos().x, Player.getPos().y - 21);
                GotCoin.changeFrame(6, 2, 25);
                window.render(GotCoin);
                getcoinanim--;
                //cout << getcoinanim << endl;

            }
            else
            {
                GotCoin.changePos(Player.getPos().x, Player.getPos().y - 21);
                window.render(GotCoin);
                getcoinanim--;
                //cout << getcoinanim << endl;
            }
        }



        window.render(Platform);
        window.render(Player);



        window.display();

    }


    if (gameisRunning == false && winGame == true)
    {
        while ((Player.getPos().x + 10) != (Platform.getPos().x + 33) || (Player.getPos().y + 10) != (Platform.getPos().y + 10))
        {

            if (Player.getPos().x + 10 > Platform.getPos().x + 33) //left
            {
                Player.adjustPos(-1, 0);
                Player.changeFrame(4, 4, 25);
            }

            else if (Player.getPos().x + 10 < Platform.getPos().x + 33) //right
            {
                Player.adjustPos(1, 0);
                Player.changeFrame(4, 2, 25);
            }

            else if (Player.getPos().y + 10 > Platform.getPos().y + 10) //up
            {
                Player.adjustPos(0, -1);
                Player.changeFrame(4, 1, 25);
            }

            else if (Player.getPos().y + 10 < Platform.getPos().y + 10) //down
            {
                Player.adjustPos(0, 1);
                Player.changeFrame(4, 3, 25);
            }


            window.render(groundgrass);
            for (Entity& e : trees)
            {
                window.render(e);
            }
            for (Entity& c : coins)
            {
                window.render(c);
            }

            window.render(Platform);
            window.render(Player);

            window.display();
            window.clear();

            SDL_Delay(50);

        }

        if ((Player.getPos().x + 10 == Platform.getPos().x + 33) && (Player.getPos().y + 10 == Platform.getPos().y + 10))
        {
            Player.changeFrame(4, 3, 25);
            Player.changeCurrentFrame(0, 0);

            window.render(groundgrass);
            for (Entity& e : trees)
            {
                window.render(e);
            }
            for (Entity& c : coins)
            {
                window.render(c);
            }

            window.render(Platform);
            window.render(Player);

            window.display();
            window.clear();

            winSFX.play(-1);

            SDL_Delay(2000);

            *coinpoint = coincount;
            *gamelvlpoint += 1;

            window.clear();
        }
    }

    else if (gameisRunning == false && winGame == false)
    {
        window.cleanUp();
        SDL_Quit();
    }

}

#ifndef TWODPLATFORMERGAME_H_INCLUDED
#define TWODPLATFORMERGAME_H_INCLUDED

#include<iostream>
#include<sstream>
#include<fstream>
#include<stdlib.h>
#include<vector>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/vec2.hpp>
#include<glm/vec3.hpp>
#include<glm/vec4.hpp>

#include "RenderEngine2D.h"

#include "2DPlatformerGameLevel.h"
#include "Weapon2D.h"

#include "Entity2D.h"
#include "Player2D.h"
#include "Enemy2D.h"

enum gameSTATE
{
    GAME_ACTIVE,
    GAME_MENU,
    GAME_LOST,
    GAME_WIN
};

class Player2D;
class Enemy2D;

class twoDPlatformerGame
{

private:
    GLboolean keysProc[1024];

    int width = 1200;
    int height = 900;
    gameSTATE gameState = GAME_MENU;
    int playMode = 0;
    float gameSpeed = 10;
    int gameRefresh = 0;

    double mouseX = 0;
    double mouseY = 0;

    float GRAVITY = 2.0f;

    int arrayGoBack = 0;

    //game variables
    int currLevel = 1;
    float enemyCounter = 3.0;
    int enemyAmount = 10;
    int enemyLimit = 1;

    Player2D* thePlayer;

    std::vector<twoDPlatformerGameLevel*> levels;

    std::vector<Weapon2D*> weaponTypes;

    std::vector<Bullet*> bulletTypes;

    std::vector<Enemy2D*> theEnemies;

public:

    twoDPlatformerGame(int, int, int);

    ~twoDPlatformerGame();

    void setupPlayer(glm::vec2, glm::vec2, int, int, int, int, float,float,int);

    void refreshGame();

    void systemInput(GLFWwindow*, float);

    void mouseInput(GLFWwindow*);

    void enemyUpdate(RenderEngine2D*);

    void mainUpdate(RenderEngine2D*, float);

    void spritePhase(RenderEngine2D*);

    void addLevel(const GLchar*, glm::vec2, int, int);

    void addWeaponType(float, float, float, float, int, int);

    int getWidth();

    int getHeight();

    gameSTATE getGameState();

    int getPlayMode();

    Player2D *getPlayer();

    float getGRAVITY();
    float getGameSpeed();
    int getGameRefresh();

    double getMouseX();
    double getMouseY();

    int getCurrLevel();
    float getEnemyCounter();
    int getEnemyAmount();
    int getEnemyLimit();

    Weapon2D* getWeaponType(int);

    std::vector<Enemy2D*>& getEnemies();

    twoDPlatformerGameLevel* getLevel(int);

    void setGameState(gameSTATE);

    void setPlayMode(int);

    void setGameSpeed(float);
    void setGameRefresh(int);

    void setCurrLevel(int);
    void setEnemyCounter(float);
    void setEnemyLimit(int);

};

#endif // 2DPLATFORMERGAME_H_INCLUDED










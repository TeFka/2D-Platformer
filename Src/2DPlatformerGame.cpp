
#include "../Inc/2DPlatformerGame.h"

#include "../Inc/Player2D.h"
#include "../Inc/Enemy2D.h"

twoDPlatformerGame::twoDPlatformerGame(int widthVal,int heightVal, int textureN)
{
    this->width = widthVal;
    this->height = heightVal;
    this->setupPlayer(glm::vec2(width/2,height/2), glm::vec2(width*0.1,height*0.2), 100, 10, 100, 10,
                      10,10, textureN);
}

twoDPlatformerGame::~twoDPlatformerGame()
{

}

void twoDPlatformerGame::setupPlayer(glm::vec2 pos, glm::vec2 dimensions, int health, int regen, int energy, int energyRegen,
                                     float speed,float jumpForce,int textureN)
{
    this->thePlayer = new Player2D(this, 0, pos, dimensions, health, regen, energy, energyRegen,
                                   speed, jumpForce,textureN);

}

void twoDPlatformerGame::refreshGame()
{
    this->gameState = GAME_ACTIVE;
    this->playMode = 0;
    this->enemyAmount = 0;
    this->enemyCounter = 3.0;
    this->gameRefresh=0;
    this->thePlayer->refresh(glm::vec2((float)this->width/2,(float)this->height/2));
    for(int n = 0; n<this->theEnemies.size(); n++)
    {
        this->theEnemies[n]->refreshEntity();
    }
    this->theEnemies.clear();


}

void twoDPlatformerGame::systemInput(GLFWwindow* window, float deltaTime)
{
    if(this->gameState==GAME_ACTIVE)
    {
        if(glfwGetKey(window,GLFW_KEY_A)==GLFW_PRESS)
        {

        }
        else if(glfwGetKey(window,GLFW_KEY_D)==GLFW_PRESS)
        {


        }
        if(glfwGetKey(window,GLFW_KEY_W)==GLFW_PRESS)
        {

        }
    }
    else if(this->gameState==GAME_MENU)
    {
        if(glfwGetKey(window,GLFW_KEY_W)==GLFW_PRESS && !keysProc[GLFW_KEY_W])
        {
            if(this->currLevel>1)
            {
                this->currLevel=this->currLevel-1;
            }
            else
            {
                this->currLevel=5;
            }
            keysProc[GLFW_KEY_W]=GL_TRUE;
        }
        else if(glfwGetKey(window,GLFW_KEY_W)==GLFW_RELEASE)
        {
            keysProc[GLFW_KEY_W]=GL_FALSE;
        }
        if(glfwGetKey(window,GLFW_KEY_S)==GLFW_PRESS && !keysProc[GLFW_KEY_S])
        {
            if(this->currLevel<5)
            {
                this->currLevel=this->currLevel+1;
            }
            else
            {
                this->currLevel=1;
            }
            keysProc[GLFW_KEY_S]=GL_TRUE;
        }
        else if(glfwGetKey(window,GLFW_KEY_S)==GLFW_RELEASE)
        {
            keysProc[GLFW_KEY_S]=GL_FALSE;
        }
        if(glfwGetKey(window,GLFW_KEY_SPACE)==GLFW_PRESS)
        {
            this->gameRefresh = 1;
        }
    }
    else if(this->gameState==GAME_WIN)
    {
        if(glfwGetKey(window,GLFW_KEY_SPACE)==GLFW_PRESS)
        {
            this->gameRefresh = 1;
            this->currLevel = 1;
        }
    }
    else if(this->gameState==GAME_LOST)
    {
        if(glfwGetKey(window,GLFW_KEY_SPACE)==GLFW_PRESS)
        {
            this->gameRefresh = 1;
        }
    }
    if(glfwGetKey(window,GLFW_KEY_ESCAPE)==GLFW_PRESS)
    {
        glfwWindowShouldClose(window);
        glfwDestroyWindow(window);
    }
}

void twoDPlatformerGame::mouseInput(GLFWwindow *windax)
{
    glfwGetCursorPos(windax, &this->mouseX, &this->mouseY);
    if(this->mouseX>this->width)
    {
        this->mouseX=this->width;
    }
    if(this->mouseX<0)
    {
        this->mouseX=0;
    }
    if(this->mouseY>this->height)
    {
        this->mouseY=this->height;
    }
    if(this->mouseY<0)
    {
        this->mouseY=0;
    }
}

void twoDPlatformerGame::enemyUpdate(RenderEngine2D *gameEngine)
{
    //enemies
    this->enemyCounter -= gameEngine->getDeltaTime();
    if(this->enemyCounter<=0.0&&this->enemyAmount<this->enemyLimit)
    {
        float randVal = (float)rand()/RAND_MAX;
        enemyCounter=3.0;
        if(this->thePlayer->getExistence())
        {
            this->enemyAmount++;
            float enX = ((float)rand()/RAND_MAX)*width;
            float enY = ((float)rand()/RAND_MAX)*height/2;
            if(randVal<0.33)
            {
                this->theEnemies.push_back(new Enemy2D(this, 0, 1,(glm::vec2(enX-width/2,enY-height/2)+this->thePlayer->getPos()),
                                                       glm::vec2(100,100),100,1,50,2,5.0f,100.0f,3,1,1,glm::vec4(1.0,0.0,0.0,1.0), 20.0f));
            }
            else if(randVal<0.66)
            {
                this->theEnemies.push_back(new Enemy2D(this, 0, 2,(glm::vec2(enX-width/2,enY-height/2)+this->thePlayer->getPos()),
                                                       glm::vec2(100,100),100,1,50,2,5.0f,150.0f,5,0,0,glm::vec4(1.0,0.0,0.0,1.0), 20.0f));
            }
            else if(randVal<1.0)
            {
                this->theEnemies.push_back(new Enemy2D(this, 0, 3,(glm::vec2(enX-width/2,enY-height/2)+this->thePlayer->getPos()),
                                                       glm::vec2(100,100),100,1,50,2,10.0f,150.0f,5,1,1,glm::vec4(1.0,0.0,0.0,1.0), 20.0f));
            }
        }
    }
    //enemies
    for(int e = enemyAmount; e--;)
    {
        if(thePlayer->getExistence())
        {
            this->theEnemies[e]->update(gameEngine, gameEngine->getDeltaTime());
            if(this->theEnemies[e]->getHp()<=0)
            {
                this->theEnemies[e]->deathEffect(gameEngine,0.2,2);
                this->theEnemies.erase(this->theEnemies.begin()+e);
                enemyAmount--;
            }
        }
    }

}

void twoDPlatformerGame::mainUpdate(RenderEngine2D *gameEngine, float deltaTime)
{
    if(this->gameRefresh)
    {
        this->refreshGame();
    }

    if(this->gameState!=GAME_MENU)
    {
        //variable and system update
        mouseInput(gameEngine->getWindow());
        //background
        gameEngine->setSprite(glm::vec2(width/2,height/2), glm::vec2(width,height), glm::vec4(0.4,0.4,0.4,1.0), 1);
        //update phase
        this->enemyUpdate(gameEngine);
        //player
        if(this->thePlayer->getExistence())
        {
            this->thePlayer->setFaceDirection(glm::vec2(this->mouseX-this->width/2+this->thePlayer->getRelativePos().x,
                                                        this->mouseY-this->height/2+this->thePlayer->getRelativePos().y));
            this->thePlayer->update(gameEngine->getWindow(), gameEngine, deltaTime);
        }
        if(this->thePlayer->getHp()<=0&&this->gameState == GAME_ACTIVE)
        {
            this->thePlayer->setExistence(0);
            this->thePlayer->deathEffect(gameEngine,2.5f,2);
            this->gameState = GAME_LOST;
            this->playMode = 2;
        }
        //level
        this->levels[this->currLevel-1]->update(this->thePlayer->getPos());

        //draw phase

    }
}

void twoDPlatformerGame::spritePhase(RenderEngine2D* gameEngine)
{
    if(this->gameState!=GAME_MENU)
    {
        if(thePlayer->getExistence())
        {
            this->thePlayer->drawPlayer(gameEngine);
        }

        //enemies
        for(int e = this->enemyAmount; e--;)
        {
            this->theEnemies[e]->drawEnemy(gameEngine, this->thePlayer->getRelativePos());
        }

        //level
        this->levels[currLevel-1]->draw(gameEngine,this->thePlayer->getRelativePos());

        //gameEngine->makeParticleEffect(glm::vec2(width/2-this->thePlayer->getPos().x,height/2-this->thePlayer->getPos().y));
        //aimer
        gameEngine->setSprite(glm::vec2(this->mouseX,this->mouseY), glm::vec2(40.0f), glm::vec4(1.0,0.0,0.0,1.0), 4);
        //health bar
        gameEngine->setSprite(glm::vec2(this->width*0.2,this->height*0.04), glm::vec2(this->width*0.2,20.0f), glm::vec4(1.0,0.0,0.0,1.0), 16);
        gameEngine->setSprite(glm::vec2(this->width*0.2-(this->width*0.2*(0.5-(float)this->thePlayer->getHp()/this->thePlayer->getFullHp()/2)),this->height*0.04),
                              glm::vec2(this->width*0.2*((float)this->thePlayer->getHp()/this->thePlayer->getFullHp()),20.0f), glm::vec4(0.0,1.0,0.0,1.0), 16);

        //energy bar
        gameEngine->setSprite(glm::vec2(this->width*0.2,this->height*0.09), glm::vec2(this->width*0.2,20.0f), glm::vec4(0.5,0.5,0.5,1.0), 16);
        gameEngine->setSprite(glm::vec2(this->width*0.2-(this->width*0.2*(0.5-(float)this->thePlayer->getEnergy()/this->thePlayer->getFullEnergy()/2)),
                                        this->height*0.09), glm::vec2(this->width*0.2*((float)this->thePlayer->getEnergy()/this->thePlayer->getFullEnergy()),20.0f), glm::vec4(1.0,1.0,0.0,1.0), 16);
    }
}

void twoDPlatformerGame::addLevel(const GLchar *file, glm::vec2 brickSiz, int textNum1, int textNum2)
{

    this->levels.push_back(new twoDPlatformerGameLevel(file, brickSiz, this->width, this->height, textNum1, textNum2));
}

void twoDPlatformerGame::addWeaponType(float damage, float speed, float cost, float bSpeed, int textr, int bulletType)
{

    this->weaponTypes.push_back(new Weapon2D(damage, speed, cost, bSpeed, textr));
}


int twoDPlatformerGame::getWidth()
{

    return this->width;

}

int twoDPlatformerGame::getHeight()
{

    return this->height;

}

gameSTATE twoDPlatformerGame::getGameState()
{
    return this->gameState;
}

int twoDPlatformerGame::getPlayMode()
{
    return this->playMode;
}

Player2D* twoDPlatformerGame::getPlayer()
{
    return this->thePlayer;
}

void twoDPlatformerGame::setGameState(gameSTATE newState)
{
    this->gameState = newState;
}

void twoDPlatformerGame::setPlayMode(int newMode)
{
    this->playMode = newMode;
}

float twoDPlatformerGame::getGRAVITY()
{

    return this->GRAVITY;
}

float twoDPlatformerGame::getGameSpeed()
{
    return this->gameSpeed;
}
int twoDPlatformerGame::getGameRefresh()
{
    return this->gameRefresh;
}

double twoDPlatformerGame::getMouseX()
{
    return this->mouseX;
}
double twoDPlatformerGame::getMouseY()
{
    return this->mouseY;
}

int twoDPlatformerGame::getCurrLevel()
{
    return this->currLevel;
}
float twoDPlatformerGame::getEnemyCounter()
{
    return this->enemyCounter;
}
int twoDPlatformerGame::getEnemyAmount()
{
    return this->enemyAmount;
}
int twoDPlatformerGame::getEnemyLimit()
{
    return this->enemyLimit;
}

Weapon2D* twoDPlatformerGame::getWeaponType(int index)
{
    return this->weaponTypes[index];
}

std::vector<Enemy2D*>& twoDPlatformerGame::getEnemies()
{
    return this->theEnemies;
}

twoDPlatformerGameLevel* twoDPlatformerGame::getLevel(int index)
{
    return this->levels[index];
}

void twoDPlatformerGame::setGameSpeed(float newSpeed)
{
    this->gameSpeed = newSpeed;
}
void twoDPlatformerGame::setGameRefresh(int newRefresh)
{
    this->gameRefresh = newRefresh;
}

void twoDPlatformerGame::setCurrLevel(int newCurrent)
{
    this->currLevel = newCurrent;
}
void twoDPlatformerGame::setEnemyCounter(float newCounter)
{
    this->enemyCounter = newCounter;
}
void twoDPlatformerGame::twoDPlatformerGame::setEnemyLimit(int newLimit)
{
    this->enemyLimit = newLimit;
}

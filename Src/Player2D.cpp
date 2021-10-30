
#include "../Inc/Player2D.h"
#include "../Inc/Enemy2D.h"

void Player2D::collisionDamage()
{
    std::vector<Enemy2D*>& enemies = this->theGame->getEnemies();
    for(int i=0; i<enemies.size(); i++)
    {
        if(glm::length(this->pos-enemies[i]->getPos())<enemies[i]->getHitBox().x/2+this->hitbox.x/2)
        {
            this->imunityCounter = imunityPeriod;
            this->health-=this->theGame->getWeaponType(enemies[i]->getActiveWeaponNum())->getAttackDamage();
            this->movementForce.x += ((glm::normalize(this->pos-enemies[i]->getPos()).x)*(this->jumpForce));
            this->movementForce.y -= (this->jumpForce*0.8);
        }
    }
}

Player2D::Player2D(twoDPlatformerGame* activeGame, int initialWeaponNum, glm::vec2 posN, glm::vec2 dimensions, int health, int regen, int energy, int energyRegen,
                   float speed,float jumpForce,int textureN,
                   int terrainEffect,int gravityEffect,glm::vec4 col)
    : Entity2D(activeGame, initialWeaponNum, pos, dimensions,
               health, regen, energy, energyRegen, speed, jumpForce, textureN, terrainEffect, gravityEffect, col)
{
    this->relativePos = posN;
    this->localPos = posN;
    this->pos = posN;
}

void Player2D::keyboardCommand(GLFWwindow* windax, float deltaTime)
{
    if(glfwGetKey(windax, GLFW_KEY_W)==GLFW_PRESS)
    {
        //this->pos+=(this->defaultSpeed*deltaTime*this->faceDirection);
        //this->this->movementSpeed.x=(this->defaultSpeed*deltaTime);
    }
    else if(glfwGetKey(windax, GLFW_KEY_S)==GLFW_PRESS)
    {
        //this->this->movementSpeed.x=-(this->defaultSpeed*deltaTime).x;
    }
    else if(glfwGetKey(windax, GLFW_KEY_D)==GLFW_PRESS)
    {
        if(!this->blockedSides[0])
        {
            if(this->localPos.x<0.7*this->theGame->getWidth())
            {
                this->localPos.x+=(this->defaultSpeed*deltaTime*this->theGame->getGameSpeed());
            }
            else
            {
                this->relativePos.x+=(this->defaultSpeed*deltaTime*this->theGame->getGameSpeed());
            }
        }
    }
    else if(glfwGetKey(windax, GLFW_KEY_A)==GLFW_PRESS)
    {
        if(!this->blockedSides[1])
        {
            if(this->localPos.x>0.3*this->theGame->getWidth())
            {
                this->localPos.x-=(this->defaultSpeed*deltaTime*this->theGame->getGameSpeed());
            }
            else
            {
                if(this->relativePos.x>this->theGame->getWidth()/2)
                {
                    this->relativePos.x-=(this->defaultSpeed*deltaTime*this->theGame->getGameSpeed());
                }
            }
        }
    }
    else
    {
        this->movementSpeed.x = 0.0;
    }
    if(this->movementSpeed.y==0.0)
    {
        if(glfwGetKey(windax, GLFW_KEY_SPACE)==GLFW_PRESS)
        {
            this->movementSpeed.y=-this->jumpForce*this->theGame->getGameSpeed();
        }
    }
    if(glfwGetMouseButton(windax, GLFW_MOUSE_BUTTON_LEFT)==GLFW_PRESS)
    {
        if(this->attackDelayValue<=0.0)
        {
            this->attackDelayValue=this->theGame->getWeaponType(this->activeWeaponNum)->getAttackDelay();
            this->shoot(glm::vec4(0.0,0.0,1.0,1.0));
        }
    }
}

void Player2D::setFaceDirection(glm::vec2 lookPos)
{
    this->faceDirection = glm::normalize(lookPos-this->pos);
}

void Player2D::refresh(glm::vec2 pos)
{
    this->refreshEntity();
    this->movementForce=glm::vec2(0.0);
    this->movementSpeed=glm::vec2(0.0);
    this->pos=glm::vec2(pos.x,pos.y);
    this->health = this->fullHealth;
    this->energy=this->fullEnergy;
    this->iteration=0;
    this->existence = 1;
}

void Player2D::reactToBullets()
{
    std::vector<Enemy2D*>& enemies = this->theGame->getEnemies();
    for(int n = 0; n<enemies.size(); n++)
    {
        for(int i = 0; i<enemies[n]->getBullets().size(); i++)
        {

            if(this->pos.x-(this->hitbox.x/2)<enemies[n]->getBullets()[i]->pos.x &&
                    this->pos.x+(this->hitbox.x/2)>enemies[n]->getBullets()[i]->pos.x &&
                    this->pos.y-(this->hitbox.y/2)<enemies[n]->getBullets()[i]->pos.y &&
                    this->pos.y+(this->hitbox.y/2)>enemies[n]->getBullets()[i]->pos.y)
            {
                this->health -= this->theGame->getWeaponType(enemies[i]->getActiveWeaponNum())->getAttackDamage();
                enemies[n]->removeBullet(i);
            }
        }
    }
}

void Player2D::updatePlayerMovement(float deltaTime)
{
    this->movementSpeed+=(this->movementForce*deltaTime*this->theGame->getGameSpeed());

    if(this->movementSpeed.x>0)
    {
        if(this->localPos.x<this->theGame->getWidth()*0.7)
        {
            this->localPos.x+=(this->movementSpeed.x*deltaTime*this->theGame->getGameSpeed());
        }
        else
        {
            this->relativePos.x+=(this->movementSpeed.x*deltaTime*this->theGame->getGameSpeed());
        }
    }
    else if(this->movementSpeed.x<0)
    {
        if(this->localPos.x>this->theGame->getWidth()*0.3)
        {
            this->localPos.x+=(this->movementSpeed.x*deltaTime*this->theGame->getGameSpeed());
        }
        else
        {
            this->relativePos.x+=(this->movementSpeed.x*deltaTime*this->theGame->getGameSpeed());
        }
    }

    if(this->movementSpeed.y>0)
    {
        if(this->localPos.y<this->theGame->getHeight()*0.7)
        {
            this->localPos.y+=(this->movementSpeed.y*deltaTime*this->theGame->getGameSpeed());
        }
        else
        {
            this->relativePos.y+=(this->movementSpeed.y*deltaTime*this->theGame->getGameSpeed());
        }
    }
    else if(this->movementSpeed.y<0)
    {
        if(this->localPos.y>this->theGame->getHeight()*0.3)
        {
            this->localPos.y+=(this->movementSpeed.y*deltaTime*this->theGame->getGameSpeed());
        }
        else
        {
            this->relativePos.y+=(this->movementSpeed.y*deltaTime*this->theGame->getGameSpeed());
        }
    }
}

void Player2D::update(GLFWwindow* windw, RenderEngine2D* engine, float deltaTime)
{
    if(iteration>10)
    {
        this->keyboardCommand(windw, deltaTime);
        this->generalUpdate(deltaTime);

        if(this->affectionByTerrain)
        {
            this->collisionDetection(engine, deltaTime);
        }

        this->updatePlayerMovement(deltaTime);

        this->pos = this->localPos - glm::vec2((this->theGame->getWidth()/2),(this->theGame->getHeight()/2)) + this->relativePos;

        this->reactToBullets();
        if(this->imunityCounter<=0)
        {
            this->collisionDamage();
        }
        else
        {
            this->imunityCounter-=deltaTime;
        }
    }
    else
    {
        iteration++;
    }
}

void Player2D::drawPlayer(RenderEngine2D *engine)
{
    for(int i = 0; i<this->shotBullets.size(); i++)
    {
        engine->setSprite(glm::vec2(this->shotBullets[i]->pos.x+this->theGame->getWidth()/2-this->relativePos.x,
                                    this->shotBullets[i]->pos.y+this->theGame->getHeight()/2-this->relativePos.y),
                          this->shotBullets[i]->siz,this->shotBullets[i]->col,this->shotBullets[i]->textureNum);

    }
    engine->setSprite(glm::vec2(this->localPos.x,this->localPos.y), this->hitbox, this->color, this->textureNum);
}

glm::vec2 Player2D::getRelativePos()
{

    return this->relativePos;
}

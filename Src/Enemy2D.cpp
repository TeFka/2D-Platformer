
#include "../Inc/Enemy2D.h"
#include "../Inc/Player2D.h"

Enemy2D::Enemy2D(twoDPlatformerGame* activeGame, int initialWeaponNum, int type, glm::vec2 pos, glm::vec2 dimensions, int health, int regen, int energy, int energyRegen,
                 float speed, float jumpForce, int textureN,
                 int terrainEffect,int gravityEffect, glm::vec4 col,
                 float reactionD)
    : Entity2D(activeGame, initialWeaponNum, pos, dimensions,
               health, regen, energy, energyRegen,speed,jumpForce, textureN,terrainEffect, gravityEffect, col)
{
    this->enemyType = type;
    this->reactionDistance=reactionD;
}

void Enemy2D::AIaction(float deltaTime)
{
    switch(this->enemyType)
    {
    case 1:
    {
        this->faceDirection = glm::normalize(this->theGame->getPlayer()->getPos()-this->pos);
        if(this->movementSpeed.y>=0.0)
        {
            if(this->blockedSides[0]||this->blockedSides[1])
            {
                this->movementForce.y=-this->jumpForce;
            }
        }
        if(glm::length(this->theGame->getPlayer()->getPos()-this->pos)>reactionDistance)
        {
            this->movementSpeed.x = this->faceDirection.x*this->defaultSpeed;
        }
        else
        {
            this->movementSpeed=glm::vec2(0.0);
            if(this->attackDelayValue<=0.0)
            {
                this->attackDelayValue=this->theGame->getWeaponType(this->activeWeaponNum)->getAttackDelay();
                this->shoot(glm::vec4(1.0,0.0,0.0,1.0));
            }
        }
        break;
    }
    case 2:
    {
        this->faceDirection = glm::normalize(this->theGame->getPlayer()->getPos()-this->pos);
        if(glm::length(this->theGame->getPlayer()->getPos()-this->pos)>reactionDistance)
        {
            this->movementSpeed.x = this->faceDirection.x*this->defaultSpeed;
            this->movementSpeed.y = this->faceDirection.y*this->defaultSpeed/2;
        }
        else
        {
            if(this->attackDelayValue<=0.0)
            {
                this->attackDelayValue=this->theGame->getWeaponType(this->activeWeaponNum)->getAttackDelay();
                this->movementForce = this->faceDirection*this->jumpForce;
            }
        }
        if(this->movementForce.x>0.5)
        {
            this->movementForce.x -= 10.0f*deltaTime;
        }
        else if(this->movementForce.x<-0.5)
        {
            this->movementForce.x += 10.0f*deltaTime;
        }
        else
        {
            this->movementForce.x = 0;
        }
        if(this->movementForce.y>0.5)
        {
            this->movementForce.y -= 10.0f*deltaTime;
        }
        else if(this->movementForce.y<-0.5)
        {
            this->movementForce.y += 10.0f*deltaTime;
        }
        else
        {
            this->movementForce.y = 0;
        }
        break;
    }
    case 3:
    {
        int bulletAmount = 10;
        if(glm::length(this->theGame->getPlayer()->getPos()-this->pos)>this->hitbox.x)
        {
            if(this->movementSpeed.y<0.01&&this->movementSpeed.y>-0.01)
            {
                if(this->movementSpeed.x != 0.0)
                {
                    this->movementSpeed.x = 0.0;
                    for(int i = 0; i<bulletAmount; i++)
                    {
                        this->faceDirection.x = (-1.0+(i*(float)2/bulletAmount));
                        this->faceDirection.y = -(1.0-((sqrt(((bulletAmount/2)-i)*((bulletAmount/2)-i))/(bulletAmount/2))));
                        this->shoot(glm::vec4(1.0,0.0,0.0,1.0));
                    }
                    this->shoot(glm::vec4(1.0,0.0,0.0,1.0));
                    this->attackDelayValue=this->theGame->getWeaponType(this->activeWeaponNum)->getAttackDelay();
                }
                if(this->attackDelayValue<=0.0)
                {
                    this->movementForce.y=-this->jumpForce;
                }
            }
            else
            {
                this->faceDirection = glm::normalize(this->theGame->getPlayer()->getPos()-this->pos);
                this->movementSpeed.x = this->faceDirection.x*this->defaultSpeed;
            }
        }
        break;
    }
    case 4:
    {

        break;
    }
    case 5:
    {

        break;
    }
    }
}

void Enemy2D::reactToBullets()
{

    for(int i = 0; i<this->theGame->getPlayer()->getBullets().size(); i++)
    {

        if(this->pos.x-(this->hitbox.x/2)<theGame->getPlayer()->getBullets()[i]->pos.x &&
                this->pos.x+(this->hitbox.x/2)>theGame->getPlayer()->getBullets()[i]->pos.x &&
                this->pos.y-(this->hitbox.y/2)<theGame->getPlayer()->getBullets()[i]->pos.y &&
                this->pos.y+(this->hitbox.y/2)>theGame->getPlayer()->getBullets()[i]->pos.y)
        {

            this->health -= theGame->getPlayer()->getBullets()[i]->damage;
            this->theGame->getPlayer()->removeBullet(i);
        }
    }
}

void Enemy2D::update(RenderEngine2D* engine, float deltaTime)
{
    if(this->iteration>10)
    {
        this->AIaction(deltaTime);
        this->generalUpdate(deltaTime);
        if(this->affectionByTerrain)
        {
            this->collisionDetection(engine, deltaTime);
        }
        this->updateMovement(deltaTime);
        this->reactToBullets();
    }
    else
    {
        this->iteration++;
    }
}

void Enemy2D::drawEnemy(RenderEngine2D *engine, glm::vec2 relativePos)
{
    for(int i = 0; i<this->shotBullets.size(); i++)
    {
        engine->setSprite(glm::vec2(this->shotBullets[i]->pos.x+this->theGame->getWidth()/2-relativePos.x,
                                    this->shotBullets[i]->pos.y+this->theGame->getHeight()/2-relativePos.y),
                          this->shotBullets[i]->siz,this->shotBullets[i]->col,this->shotBullets[i]->textureNum);

    }
    engine->setSprite(glm::vec2(this->pos.x+this->theGame->getWidth()/2-relativePos.x,
                                this->pos.y+this->theGame->getHeight()/2-relativePos.y),
                      this->hitbox, this->color, this->textureNum);
}


#include "../Inc/Enemy2D.h"
#include "../Inc/Player2D.h"

Enemy2D::Enemy2D(RenderEngine2D* engine, twoDPlatformerGame* activeGame, std::vector<weaponInfo*> weaponInf, int type, glm::vec2 pos, glm::vec2 dimensions, int health, int regen, int energy, int energyRegen,
                 float speed, float jumpForce, int textureN,
                 int terrainEffect,int gravityEffect, glm::vec4 col,
                 float reactionD)
    : Entity2D(engine, activeGame, weaponInf, pos, dimensions,
               health, regen, energy, energyRegen,speed,jumpForce, textureN,terrainEffect, gravityEffect, col)
{
    this->enemyType = type;
    this->reactionDistance=reactionD;
}

void Enemy2D::calcFaceDirection(glm::vec2 lookPos)
{
    this->faceDirection = glm::normalize(lookPos-this->pos);

}

void Enemy2D::calcWeaponDirection(int index, glm::vec2 lookPos){

    this->activeWeapons[index]->faceDirection = glm::normalize(lookPos-this->activeWeapons[index]->realPos);
        if(this->theGame->getWeaponType(this->activeWeapons[index]->num-1)->weaponIsShown())
        {
            if(lookPos.x>this->activeWeapons[index]->realPos.x)
            {
                if(!this->activeWeapons[index]->staticPos){
                    this->activeWeapons[index]->relativePos.x = 1.0;
                }
                if(lookPos.y<this->activeWeapons[index]->realPos.y)
                {
                    this->activeWeapons[index]->weaponTurn = 270 + int(90-acos((lookPos.x-this->activeWeapons[index]->realPos.x)/glm::length(lookPos-this->activeWeapons[index]->realPos))*180/PI);
                }
                else
                {
                    this->activeWeapons[index]->weaponTurn = int(acos((lookPos.x-this->activeWeapons[index]->realPos.x)/glm::length(lookPos-this->activeWeapons[index]->realPos))*180/PI);
                }
            }
            else
            {
                if(!this->activeWeapons[index]->staticPos){
                    this->activeWeapons[index]->relativePos.x = -1.0;
                }

                if(lookPos.y>this->activeWeapons[index]->realPos.y)
                {
                    this->activeWeapons[index]->weaponTurn = 90 + (90 - int(acos((this->activeWeapons[index]->realPos.x-lookPos.x)/glm::length(lookPos-this->activeWeapons[index]->realPos))*180/PI));
                }
                else
                {
                    this->activeWeapons[index]->weaponTurn = 180 + int((acos((this->activeWeapons[index]->realPos.x-lookPos.x)/glm::length(lookPos-this->activeWeapons[index]->realPos))*180/PI));
                }

            }
        }

}

void Enemy2D::AIaction()
{
    this->calcFaceDirection(this->theGame->getPlayer()->getPos());
    switch(this->enemyType)
    {
    case 1:
    {
        this->calcWeaponDirection(0, this->theGame->getPlayer()->getPos());
        if(this->movementSpeed.y>=0.0)
        {
            if(this->blockedSides[0]||this->blockedSides[1])
            {
                this->movementSpeed.y=-this->jumpForce*this->theGame->getGameSpeed();
            }
        }
        if(glm::length(this->theGame->getPlayer()->getPos()-this->pos)>reactionDistance)
        {
            this->movementSpeed.x = this->faceDirection.x*this->defaultSpeed;
        }
        else
        {
            this->movementSpeed=glm::vec2(0.0);
            if(this->activeWeapons[0]->attackDelay<=0.0)
            {
                this->activeWeapons[0]->attackDelay=this->theGame->getWeaponType(this->activeWeapons[0]->num-1)->getAttackDelay();
                this->useWeapon(glm::vec4(1.0,0.0,0.0,1.0));
            }
        }
        break;
    }
    case 2:
    {
        if(glm::length(this->theGame->getPlayer()->getPos()-this->pos)>reactionDistance)
        {
            this->movementSpeed.x = this->faceDirection.x*this->defaultSpeed;
            this->movementSpeed.y = this->faceDirection.y*this->defaultSpeed/2;
        }
        else
        {
            if(this->activeWeapons[0]->attackDelay<=0.0)
            {
                this->activeWeapons[0]->attackDelay=this->theGame->getWeaponType(this->activeWeapons[0]->num-1)->getAttackDelay();
                this->movementSpeed = this->faceDirection*this->jumpForce*this->theGame->getGameSpeed();
            }
        }
        if(length(this->movementSpeed)>2*this->defaultSpeed){
            this->entityTurn++;
            if(this->entityTurn>=360){
                this->entityTurn = 0;
            }
        }
        if(this->movementSpeed.x>0.5)
        {
            this->movementSpeed.x -= 10.0f*this->renderEngine->getDeltaTime();
        }
        else if(this->movementSpeed.x<-0.5)
        {
            this->movementSpeed.x += 10.0f*this->renderEngine->getDeltaTime();
        }
        else
        {
            this->movementSpeed.x = 0;
        }
        if(this->movementSpeed.y>0.5)
        {
            this->movementSpeed.y -= 10.0f*this->renderEngine->getDeltaTime();
        }
        else if(this->movementSpeed.y<-0.5)
        {
            this->movementSpeed.y += 10.0f*this->renderEngine->getDeltaTime();
        }
        else
        {
            this->movementSpeed.y = 0;
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
                        this->activeWeapons[0]->faceDirection.x = (-1.0+(i*(float)2/bulletAmount));
                        this->activeWeapons[0]->faceDirection.y = -(1.0-((sqrt(((bulletAmount/2)-i)*((bulletAmount/2)-i))/(bulletAmount/2))));
                        this->useWeapon(glm::vec4(1.0,0.0,0.0,1.0));
                    }
                    this->activeWeapons[0]->attackDelay=this->theGame->getWeaponType(this->activeWeapons[0]->num-1)->getAttackDelay();
                }
                if(this->activeWeapons[0]->attackDelay<=0.0)
                {
                    this->movementSpeed.y=-this->jumpForce*this->theGame->getGameSpeed();
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
    case 101:
    {
        if(glm::length(this->theGame->getPlayer()->getPos()-this->pos)>this->hitbox.x)
        {
            if(this->movementSpeed.y<0.01&&this->movementSpeed.y>-0.01)
            {
                if(this->movementSpeed.x != 0.0)
                {
                    this->movementSpeed.x = 0.0;
                }
                if(this->blockedSides[0]||this->blockedSides[1])
                {
                    this->movementSpeed.y=-3*this->jumpForce*this->theGame->getGameSpeed();
                }
                else{
                    this->movementSpeed.y=-this->jumpForce*this->theGame->getGameSpeed();
                }
            }
            else
            {
                this->faceDirection = glm::normalize(this->theGame->getPlayer()->getPos()-this->pos);
                this->movementSpeed.x = this->faceDirection.x*this->defaultSpeed;
            }
        }
        if(glm::length(this->theGame->getPlayer()->getPos()-this->pos)<this->theGame->getWidth())
        {
            for(int i = 0; i<this->activeWeapons.size(); i++){

                if(this->activeWeapons[i]->attackDelay<=0){
                    if(this->activeWeapons[i]->num == 3){

                        this->calcWeaponDirection(i, glm::vec2(this->pos.x-this->hitbox.x,this->pos.y+this->hitbox.y/100*((rand() % 20)+1-20)));

                    }
                    else if(this->activeWeapons[i]->num == 4){
                        this->calcWeaponDirection(i, glm::vec2(this->pos.x,this->pos.y-this->hitbox.y*(0.75+(((rand() % 25)+1-25)/100))));
                    }
                    else{
                        this->calcWeaponDirection(0, this->theGame->getPlayer()->getPos());
                    }

                    this->useWeapon(glm::vec4(1.0,0.0,0.0,1.0), i);
                }


            }
        }
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

void Enemy2D::update()
{
    if(this->iteration>10)
    {
        this->reactToBullets();

        this->AIaction();

        this->generalUpdate();

        if(this->health<=0){

            if(this->enemyType>100){

                this->theGame->setBossState(false);

            }

        }
    }
    else
    {
        this->iteration++;
    }
}

void Enemy2D::drawEnemy(glm::vec2 relativePos)
{
    for(int i = 0; i<this->shotBullets.size(); i++)
    {
        this->renderEngine->setSprite(this->shotBullets[i]->pos+this->theGame->getMiddlePos()-relativePos,
                                      this->shotBullets[i]->siz,this->shotBullets[i]->col,this->shotBullets[i]->textureNum);

    }

    this->renderEngine->setSprite(this->pos+this->theGame->getMiddlePos()-relativePos,
                                  this->hitbox, this->color, this->textureNum, this->entityTurn);

    for(int i = 0; i<this->activeWeapons.size(); i++)
    {
        if(this->theGame->getWeaponType(this->activeWeapons[i]->num-1)->weaponIsShown())
        {
            this->renderEngine->setSprite(this->activeWeapons[i]->realPos+this->theGame->getMiddlePos()-relativePos,
                                          glm::vec2(this->activeWeapons[i]->siz.x*this->hitbox.x, this->activeWeapons[i]->siz.y*this->hitbox.y), this->color,
                                          this->theGame->getWeaponType(this->activeWeapons[i]->num-1)->getTextureNum(),
                                          this->activeWeapons[i]->weaponTurn);
        }
    }

}

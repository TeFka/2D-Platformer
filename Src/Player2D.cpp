
#include "../Inc/Player2D.h"
#include "../Inc/Enemy2D.h"

void Player2D::collisionDamage()
{
    for(int i=0; i<this->theGame->getEnemyAmount(); i++)
    {
        if(glm::length(this->pos-this->theGame->getEnemy(i)->getPos())<this->theGame->getEnemy(i)->getHitBox().x/2+this->hitbox.x/2)
        {
            this->imunityCounter = imunityPeriod;
            this->health-=this->theGame->getWeaponType(this->theGame->getEnemy(i)->getActiveWeaponNum()-1)->getAttackDamage();
            this->movementSpeed.y -= (this->jumpForce*0.8);
        }
    }
}

Player2D::Player2D(RenderEngine2D* engine, twoDPlatformerGame* activeGame, std::vector<weaponInfo*> weaponInf, glm::vec2 posN, glm::vec2 dimensions, int health, int regen, int energy, int energyRegen,
                   float speed,float jumpForce,int textureN,
                   int terrainEffect,int gravityEffect,glm::vec4 col)
    : Entity2D(engine, activeGame, weaponInf, pos, dimensions,
               health, regen, energy, energyRegen, speed, jumpForce, textureN, terrainEffect, gravityEffect, col)
{
    this->relativePos = posN;
    this->localPos = posN;
    this->pos = posN;
}

void Player2D::keyboardCommand()
{
    if(glfwGetKey(this->renderEngine->getWindow(), GLFW_KEY_W)==GLFW_PRESS)
    {
        //this->pos+=(this->defaultSpeed*this->renderEngine->getDeltaTime()*this->faceDirection);
        //this->this->movementSpeed.x=(this->defaultSpeed*this->renderEngine->getDeltaTime());
    }
    else if(glfwGetKey(this->renderEngine->getWindow(), GLFW_KEY_S)==GLFW_PRESS)
    {
        //this->this->movementSpeed.x=-(this->defaultSpeed*this->renderEngine->getDeltaTime()).x;
    }
    else if(glfwGetKey(this->renderEngine->getWindow(), GLFW_KEY_D)==GLFW_PRESS)
    {
        this->movementSpeed.x = this->defaultSpeed;
    }
    else if(glfwGetKey(this->renderEngine->getWindow(), GLFW_KEY_A)==GLFW_PRESS)
    {
        this->movementSpeed.x = -this->defaultSpeed;
    }
    else
    {
        this->movementSpeed.x = 0.0;
    }
    if(this->movementSpeed.y==0.0 && !this->blockedSides[3])
    {
        if(glfwGetKey(this->renderEngine->getWindow(), GLFW_KEY_SPACE)==GLFW_PRESS)
        {
            this->movementForce.y=-this->jumpForce*this->theGame->getGameSpeed();
        }
    }
    if(glfwGetMouseButton(this->renderEngine->getWindow(), GLFW_MOUSE_BUTTON_LEFT)==GLFW_PRESS)
    {
        if(this->activeWeapons[this->weaponIndex]->attackDelay<=0.0)
        {
            this->activeWeapons[this->weaponIndex]->attackDelay=this->theGame->getWeaponType(this->activeWeapons[this->weaponIndex]->num-1)->getAttackDelay();
            this->useWeapon(glm::vec4(0.0,0.0,1.0,1.0));
        }
    }
}

void Player2D::calcFaceDirection(glm::vec2 lookPos)
{
    this->faceDirection = glm::normalize(lookPos-this->localPos);
    this->activeWeapons[this->weaponIndex]->faceDirection = glm::normalize(lookPos-(this->activeWeapons[this->weaponIndex]->realPos+this->theGame->getMiddlePos()-this->relativePos));
    if(lookPos.x>this->localPos.x){
        if(!this->activeWeapons[this->weaponIndex]->staticPos){
            this->activeWeapons[this->weaponIndex]->relativePos.x = 1.0;
        }
        if(lookPos.y<this->localPos.y){
            this->activeWeapons[this->weaponIndex]->weaponTurn = 270 + int(90-acos((lookPos.x-this->localPos.x)/glm::length(lookPos-this->localPos))*180/PI);
        }
        else{
            this->activeWeapons[this->weaponIndex]->weaponTurn = int(acos((lookPos.x-this->localPos.x)/glm::length(lookPos-this->localPos))*180/PI);
        }
    }
    else{
        if(!this->activeWeapons[this->weaponIndex]->staticPos){
            this->activeWeapons[this->weaponIndex]->relativePos.x = -1.0;
        }

        if(lookPos.y>this->localPos.y){
            this->activeWeapons[this->weaponIndex]->weaponTurn = 90 + (90 - int(acos((this->localPos.x-lookPos.x)/glm::length(lookPos-this->localPos))*180/PI));
        }
        else{
            this->activeWeapons[this->weaponIndex]->weaponTurn = 180 + int((acos((this->localPos.x-lookPos.x)/glm::length(lookPos-this->localPos))*180/PI));
        }

    }
}

void Player2D::refresh(glm::vec2 initialPos)
{
    this->refreshEntity();
    this->movementSpeed=glm::vec2(0.0);
    this->pos = glm::vec2(initialPos.x,initialPos.y);
    this->health = this->fullHealth;
    this->energy=this->fullEnergy;
    this->iteration=0;
    this->existence = 1;
}

void Player2D::reactToBullets()
{
    std::vector<Enemy2D*>& enemies = this->theGame->getEnemies();
    for(int n = 0; n<this->theGame->getEnemyAmount(); n++)
    {
        for(int i = 0; i<this->theGame->getEnemy(n)->getBullets().size(); i++)
        {

            if(this->pos.x-(this->hitbox.x/2)<this->theGame->getEnemy(n)->getBullets()[i]->pos.x &&
                    this->pos.x+(this->hitbox.x/2)>this->theGame->getEnemy(n)->getBullets()[i]->pos.x &&
                    this->pos.y-(this->hitbox.y/2)<this->theGame->getEnemy(n)->getBullets()[i]->pos.y &&
                    this->pos.y+(this->hitbox.y/2)>this->theGame->getEnemy(n)->getBullets()[i]->pos.y)
            {
                this->health -= this->theGame->getEnemy(n)->getBullets()[i]->damage;
                this->theGame->getEnemy(n)->removeBullet(i);
            }
        }
    }
}

void Player2D::updatePlayerMovement()
{

    if(this->pos != (this->localPos - glm::vec2((this->theGame->getWidth()/2),(this->theGame->getHeight()/2)) + this->relativePos)){

         this->localPos = this->pos - this->relativePos;
         this->localPos.x += (this->theGame->getWidth()/2);
         this->localPos.y += (this->theGame->getHeight()/2);

         if(this->localPos.x>this->theGame->getWidth()*0.7)
         {

                this->relativePos.x += this->localPos.x - this->theGame->getWidth()*0.7;
                this->localPos.x = this->theGame->getWidth()*0.7;

         }
         else if(this->localPos.x<this->theGame->getWidth()*0.3)
         {

                this->relativePos.x += this->localPos.x - this->theGame->getWidth()*0.3;
                this->localPos.x = this->theGame->getWidth()*0.3;

         }
         if(this->localPos.y>this->theGame->getHeight()*0.7)
         {

                this->relativePos.y += this->localPos.y - this->theGame->getHeight()*0.7;
                this->localPos.y = this->theGame->getHeight()*0.7;

         }
         else if(this->localPos.y<this->theGame->getHeight()*0.3)
         {

                this->relativePos.y += this->localPos.y-this->theGame->getHeight()*0.3;
                this->localPos.y = this->theGame->getHeight()*0.3;

         }
    }
}

void Player2D::update()
{
    if(iteration>10)
    {
        this->reactToBullets();

        if(this->imunityCounter<=0)
        {
            this->collisionDamage();
        }
        else
        {
            this->imunityCounter-=this->renderEngine->getDeltaTime();
        }

        this->keyboardCommand();
        this->generalUpdate();

        this->updatePlayerMovement();

        if(this->health<=0)
        {
            this->existence = 0;
            this->deathEffect(this->pos, 2.5f,2);
            this->theGame->setGameState(GAME_LOST);
            this->theGame->setPlayMode(2);
        }

    }
    else
    {
        iteration++;
    }
}

void Player2D::drawPlayer()
{
    for(int i = 0; i<this->shotBullets.size(); i++)
    {
        this->renderEngine->setSprite(this->shotBullets[i]->pos+this->theGame->getMiddlePos()-relativePos,
                          this->shotBullets[i]->siz,this->shotBullets[i]->col,this->shotBullets[i]->textureNum);

    }
    this->renderEngine->setSprite(glm::vec2(this->localPos.x,this->localPos.y), this->hitbox, this->color, this->textureNum, this->entityTurn);

        if(this->theGame->getWeaponType(this->activeWeapons[this->weaponIndex]->num-1)->weaponIsShown()){
            this->renderEngine->setSprite(this->activeWeapons[this->weaponIndex]->realPos+this->theGame->getMiddlePos()-relativePos,
                                    glm::vec2(this->activeWeapons[this->weaponIndex]->siz.x*this->hitbox.x, this->activeWeapons[this->weaponIndex]->siz.y*this->hitbox.y), this->color,
                                     this->theGame->getWeaponType(this->activeWeapons[this->weaponIndex]->num-1)->getTextureNum(),
                                     this->activeWeapons[this->weaponIndex]->weaponTurn);
        }
}

glm::vec2 Player2D::getRelativePos()
{

    return this->relativePos;
}

glm::vec2 Player2D::getLocalPos(){

    return this->localPos;
}

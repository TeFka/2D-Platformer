
#include "../Inc/Entity2D.h"

#include "../Inc/2DPlatformerGame.h"

void Entity2D::generalUpdate()
{
    for(int i = 0;i<this->activeWeapons.size();i++){
        if(this->activeWeapons[i]->attackDelay>0.0)
        {
            this->activeWeapons[i]->attackDelay -= this->renderEngine->getDeltaTime();
        }
    }
    if(this->health<this->fullHealth)
    {
        this->health+=this->healthRegeneration*this->renderEngine->getDeltaTime();
    }
    if(this->energy<this->fullEnergy)
    {
        this->energy+=this->energyRegeneration*this->renderEngine->getDeltaTime();
    }

    this->physicsUpdate();

    this->generalBulletUpdate();
}

void Entity2D::updateMovement()
{
    //wind resistance
    //this->movementSpeed.x *= 0.95;
    //this->movementSpeed.y *= 0.95;

    this->movementSpeed += this->movementForce;

    if(abs(this->movementForce.x)>0.1){
        this->movementForce.x *= 0.7;
    }
    if(abs(this->movementForce.y)>0.1){
        this->movementForce.y *= 0.7;
    }
    if(this->affectionByGravity)
    {
        this->movementSpeed.y += this->theGame->getGRAVITY()*this->renderEngine->getDeltaTime()*this->theGame->getGameSpeed();
        if(this->movementSpeed.y>1000){

            this->health = 0;

        }
    }

}

void Entity2D::collisionDetection()
{
    std::vector<gameObj*>& bricks = this->theGame->getLevel(this->theGame->getCurrLevel()-1)->getActiveBricks();
    int bricksNr = bricks.size();
    //std::cout<<bricks.size()<<std::endl;
    glm::vec2 blockSize = this->theGame->getLevel(this->theGame->getCurrLevel()-1)->getBrickSize();
    this->blockedSides[0] = 0;
    this->blockedSides[1] = 0;
    this->blockedSides[2] = 0;
    this->blockedSides[3] = 0;
    for(int i=bricksNr; i--;)
    {
        //Entity collision
        //positive X
        //Horizontal
        if(this->pos.y+(this->hitbox.y/2)<bricks[i]->pos.y+(blockSize.y/2)&&
                this->pos.y+(this->hitbox.y/2)>bricks[i]->pos.y-(blockSize.y/2)||
                this->pos.y-(this->hitbox.y/2)<bricks[i]->pos.y+(blockSize.y/2)&&
                this->pos.y-(this->hitbox.y/2)>bricks[i]->pos.y-(blockSize.y/2))
        {
            //positive x
            if(this->previousPos.x+this->hitbox.x/2<=bricks[i]->pos.x-(blockSize.x/2)){
                if(this->pos.x+this->hitbox.x/2>=bricks[i]->pos.x-(blockSize.x/2)&&
                        this->pos.x+this->hitbox.x/2<=bricks[i]->pos.x+(blockSize.x/2))
                {
                    this->blockedSides[0]=1;
                    if(this->movementSpeed.x>=0.0)
                    {
                        this->pos.x=bricks[i]->pos.x-(blockSize.x/2)-(this->hitbox.x/2);
                        this->movementSpeed.x=0.0;
                    }
                }
            }
            //negative X
            if(this->previousPos.x-this->hitbox.x/2>=bricks[i]->pos.x+(blockSize.x/2)){
                if(this->pos.x-this->hitbox.x/2<=bricks[i]->pos.x+(blockSize.x/2)&&
                        this->pos.x-this->hitbox.x/2>=bricks[i]->pos.x-(blockSize.x/2))
                {
                    this->blockedSides[1]=1;
                    if(this->movementSpeed.x<=0.0)
                    {
                        this->pos.x=bricks[i]->pos.x+(blockSize.x/2)+(this->hitbox.x/2);
                        this->movementSpeed.x=0.0;
                    }
                }
            }
        }
        //vertical
        if(this->pos.x+(this->hitbox.x/2)<bricks[i]->pos.x+(blockSize.x/2)&&
                this->pos.x+(this->hitbox.x/2)>bricks[i]->pos.x-(blockSize.x/2)||
                this->pos.x-(this->hitbox.x/2)<bricks[i]->pos.x+(blockSize.x/2)&&
                this->pos.x-(this->hitbox.x/2)>bricks[i]->pos.x-(blockSize.x/2))
        {
            if(this->pos.y>=bricks[i]->pos.y-(blockSize.y/2)&&this->previousPos.y<=bricks[i]->pos.y+(blockSize.y/2))
            {
                this->pos.y=bricks[i]->pos.y-(blockSize.y/2)-(this->hitbox.y/2);
            }
            else
            {
                //positive Y
                if(this->pos.y+this->hitbox.y/2+(this->movementSpeed.y*this->renderEngine->getDeltaTime()*this->theGame->getGameSpeed())>=bricks[i]->pos.y-(blockSize.y/2)&&
                        this->pos.y+this->hitbox.y/2+(this->movementSpeed.y*this->renderEngine->getDeltaTime()*this->theGame->getGameSpeed())<=bricks[i]->pos.y+(blockSize.y/2))
                {
                    this->blockedSides[2]=1;

                    if(this->movementSpeed.y>0.0)
                    {
                        this->pos.y=bricks[i]->pos.y-(blockSize.y/2)-(this->hitbox.y/2);
                        this->movementSpeed.y=0.0;
                    }
                }
                //negative Y
                if(this->pos.y-this->hitbox.y/2<=bricks[i]->pos.y+(blockSize.y/2)&&
                        this->pos.y-this->hitbox.y/2>=bricks[i]->pos.y-(blockSize.y/2))
                {
                    this->blockedSides[3]=1;

                    if(this->movementSpeed.y<0.0)
                    {
                        this->pos.y=bricks[i]->pos.y+(blockSize.y/2)+(this->hitbox.y/2);
                        this->movementSpeed.y=0.0;
                    }
                }
            }
        }

        for(int b = this->shotBullets.size(); b--;)
        {
            if(this->shotBullets[b]->pos.x-this->shotBullets[b]->siz.x/2<bricks[i]->pos.x+(blockSize.x/2)&&
                    this->shotBullets[b]->pos.x+this->shotBullets[b]->siz.x/2>bricks[i]->pos.x-(blockSize.x/2)&&
                    this->shotBullets[b]->pos.y-this->shotBullets[b]->siz.x/2<bricks[i]->pos.y+(blockSize.y/2)&&
                    this->shotBullets[b]->pos.y+this->shotBullets[b]->siz.y/2>bricks[i]->pos.y-(blockSize.y/2))
            {
                this->removeBullet(b);
            }
        }
    }
    this->previousPos=this->pos;
}

void Entity2D::useWeapon(glm::vec4 col, int weaponIndex)
{
    if(this->activeWeapons[weaponIndex]->num!=0){
        this->energy-=this->theGame->getWeaponType(this->activeWeapons[weaponIndex]->num-1)->getAttackCost();
        this->activeWeapons[weaponIndex]->attackDelay = this->theGame->getWeaponType(this->activeWeapons[weaponIndex]->num-1)->getAttackDelay();

        Bullet* bull = new Bullet{this->theGame->getWeaponType(this->activeWeapons[weaponIndex]->num-1)->getAttackDamage(),
                                  this->activeWeapons[weaponIndex]->realPos,
                                  this->hitbox/10.0f,
                                  this->theGame->getWeaponType(this->activeWeapons[weaponIndex]->num-1)->getBulletSpeed()*this->theGame->getGameSpeed(),
                                  (this->theGame->getWeaponType(this->activeWeapons[weaponIndex]->num-1)->getBulletSpeed()*this->theGame->getGameSpeed()*this->activeWeapons[weaponIndex]->faceDirection),
                                  col,16, this->theGame->getWeaponType(this->activeWeapons[weaponIndex]->num-1)->getType()};

        this->shotBullets.push_back(bull);
    }
}

void Entity2D::generalBulletUpdate()
{
    for(int i = this->shotBullets.size(); i--;)
    {
        if(this->shotBullets[i]->type == 1 || this->shotBullets[i]->type == 2){
            this->shotBullets[i]->pos+=this->shotBullets[i]->speed*this->renderEngine->getDeltaTime();

        }
        else if(this->shotBullets[i]->type == 3){

            this->shotBullets[i]->pos+=this->shotBullets[i]->speed*this->renderEngine->getDeltaTime();
            this->shotBullets[i]->speed.y += this->theGame->getGRAVITY()*this->renderEngine->getDeltaTime();

        }
        if(glm::length(this->pos-this->shotBullets[i]->pos)>1000.0)
        {
            this->shotBullets.erase(this->shotBullets.begin()+i);
        }
    }
}

void Entity2D::removeBullet(int index)
{

    if(this->shotBullets[index]->type==1){
        this->theGame->getParticleEngine()->createParticleEffect(this->shotBullets[index]->pos,
                0.2f, 0.2f,10,
                this->shotBullets[index]->siz,this->shotBullets[index]->defaultSpeed/2,
                2.0f*this->shotBullets[index]->siz,
                this->shotBullets[index]->col,
                16,1,0);
    }
    else if(this->shotBullets[index]->type==2){

        for(int c = 0; c<10;c++){

            Bullet* bull = new Bullet{this->shotBullets[index]->damage,
                      this->shotBullets[index]->pos,
                      this->hitbox/20.0f,
                      this->shotBullets[index]->defaultSpeed,
                      glm::vec2(cos(c*36*PI/180),sin(c*36*PI/180))*this->shotBullets[index]->defaultSpeed,
                      this->shotBullets[index]->col,16, 1};

            this->shotBullets.push_back(bull);

        }

    }
    else if(this->shotBullets[index]->type==3){

        for(int c = 0; c<30;c++){
            Bullet* bull = new Bullet{this->shotBullets[index]->damage,
                      this->shotBullets[index]->pos,
                      this->hitbox/20.0f,
                      this->shotBullets[index]->defaultSpeed,
                      glm::vec2(cos(c*12*PI/180),sin(c*12*PI/180))*this->shotBullets[index]->defaultSpeed,
                      this->shotBullets[index]->col,16, 1};

            this->shotBullets.push_back(bull);

        }

    }
    this->shotBullets.erase(this->shotBullets.begin()+index);
}

void Entity2D::physicsUpdate()
{

    this->updateMovement();

    if(this->affectionByTerrain)
    {
        this->collisionDetection();
    }

    this->previousPos = this->pos;
    this->pos+=(movementSpeed*this->renderEngine->getDeltaTime()*this->theGame->getGameSpeed());

    for(int i = 0;i<this->activeWeapons.size();i++){
        this->activeWeapons[i]->realPos = this->pos+glm::vec2(this->hitbox.x*this->activeWeapons[i]->relativePos.x, this->hitbox.y*this->activeWeapons[i]->relativePos.y)/2.0f;

    }
}

Entity2D::Entity2D(RenderEngine2D* engine, twoDPlatformerGame* activeGame, std::vector<weaponInfo*> weaponInf, glm::vec2 pos, glm::vec2 siz, int health, int regen, int energy, int energyRegen, float speed,
                   float jumpForceVal, int textureN,
                   int terrainEffect, int gravityEffect, glm::vec4 col)
{
    this->renderEngine = engine;
    this->theGame = activeGame;

    this->activeWeapons = weaponInf;

    float randm = (((float)rand())/RAND_MAX);
    this->pos=pos;
    this->previousPos = pos;
    this->entityTurn = 0;
    this->hitbox = siz;
    if(randm<0.5)
    {
        this->faceDirection=glm::vec2(1.0,0.0);
    }
    else
    {
        this->faceDirection=glm::vec2(-1.0,0.0);
    }

    this->healthRegeneration = regen;
    this->health=health;
    this->fullHealth = health;

    this->fullEnergy = energy;
    this->energy = energy;
    this->energyRegeneration = energyRegen;

    this->defaultSpeed = speed;
    this->jumpForce = jumpForceVal;

    this->textureNum = textureN;
    this->color = col;

    this->affectionByTerrain = terrainEffect;
    this->affectionByGravity = gravityEffect;
    this->existence=1;
}

void Entity2D::deathEffect(glm::vec2 effectPos, float duration,int amount)
{
    this->theGame->getParticleEngine()->createParticleEffect(effectPos,
            0.2f, duration,amount,
            this->hitbox/5.0f,this->theGame->getGameSpeed()*this->defaultSpeed/2, glm::vec2(0.0f),this->color,
            16,1,0);
}

void Entity2D::refreshEntity()
{

    this->shotBullets.clear();

}

glm::vec2 Entity2D::getPos()
{
    return this->pos;
}

int Entity2D::getHp()
{
    return this->health;
}

int Entity2D::getFullHp()
{
    return this->fullHealth;
}

int Entity2D::getAttackDelayValue(int index)
{

    return this->activeWeapons[index]->attackDelay;

}

void Entity2D::addWeapon(weaponInfo* newWeap){

    this->activeWeapons.push_back(newWeap);
}

int Entity2D::getActiveWeaponNum(int weaponIndex)
{

    return this->activeWeapons[weaponIndex]->num;

}

void Entity2D::setActiveWeaponNum(int newNum, int weaponIndex)
{

    this->activeWeapons[weaponIndex]->num = newNum;

}

int Entity2D::getEnergy()
{
    return this->energy;
}

int Entity2D::getFullEnergy()
{
    return this->fullEnergy;
}

void Entity2D::setHp(int newHp)
{
    this->health = newHp;
}

glm::vec2 Entity2D::getHitBox()
{
    return this->hitbox;
}

int Entity2D::getExistence()
{
    return this->existence;
}

int Entity2D::setExistence(int val)
{
    this->existence = val;
}

std::vector<Bullet*>& Entity2D::getBullets()
{

    return this->shotBullets;
}

int Entity2D::getBulletAmount()
{

    return this->shotBullets.size();

}

glm::vec2 Entity2D::getFaceDirection()
{

    return this->faceDirection;
}

glm::vec2 Entity2D::getMovementSpeed()
{

    return this->movementSpeed;
}

float Entity2D::getJumpForce()
{

    return this->jumpForce;
}

int* Entity2D::getBlockedSides()
{

    return this->blockedSides;
}

int Entity2D::getHealthRegeneration()
{

    return this->healthRegeneration;
}

int Entity2D::getEnergyRegeneration()
{

    return this->energyRegeneration;
}

glm::vec4 Entity2D::getColor()
{

    return this->color;
}
int Entity2D::getTextureNum()
{

    return this->textureNum;
}

int Entity2D::getAffectionByTerrain()
{

    return this->affectionByTerrain;
}

int Entity2D::getAffectionByGravity()
{

    return this->affectionByGravity;
}

void Entity2D::setFaceDirection(glm::vec2 newDirection)
{

    this->faceDirection = newDirection;
}

void Entity2D::setMovementSpeed(glm::vec2 newSpeed)
{

    this->movementSpeed = newSpeed;
}

void Entity2D::setJumpForce(float newForce)
{

    this->jumpForce = newForce;
}

void Entity2D::setBlockedSides(int newBlocks[])
{
    for(int i = 0; i<4; i++)
    {
        this->blockedSides[i] = newBlocks[i];
    }
}

void Entity2D::setHealthRegeneration(int newRegeneration)
{

    this->healthRegeneration = newRegeneration;
}

void Entity2D::setEnergyRegeneration(int newRegeneration)
{

    this->energyRegeneration = newRegeneration;
}

void Entity2D::setColor(glm::vec4 newColor)
{

    this->color = newColor;
}
void Entity2D::setTextureNum(int newNum)
{

    this->textureNum = newNum;
}

void Entity2D::setAffectionByTerrain(int newAffection)
{

    this->affectionByTerrain = newAffection;
}

void Entity2D::setAffectionByGravity(int newAffection)
{

    this->affectionByGravity = newAffection;
}

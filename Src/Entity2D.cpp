
#include "../Inc/Entity2D.h"

#include "../Inc/2DPlatformerGame.h"

void Entity2D::generalUpdate(float deltaTime)
{
    if(this->attackDelayValue>0.0)
    {
        this->attackDelayValue -= deltaTime;
    }
    if(this->health<this->fullHealth)
    {
        this->health+=this->healthRegeneration*deltaTime;
    }
    if(this->energy<this->fullEnergy)
    {
        this->energy+=this->energyRegeneration*deltaTime;
    }
    if(this->affectionByGravity)
    {
        this->movementForce.y += this->theGame->getGRAVITY()*deltaTime*this->theGame->getGameSpeed();
    }
    //wind resistance
    //this->movementForce.x -= 0.1*this->movementSpeed.x*(this->movementForce.x>0.05||this->movementForce.x<-0.05)*deltaTime*this->theGame->getGameSpeed();
    //this->movementForce.y -= 0.1*this->movementSpeed.y*(this->movementForce.y>0.05||this->movementForce.y<-0.05)*deltaTime*this->theGame->getGameSpeed();
    //fall death
    if(this->movementForce.y>(this->theGame->getGRAVITY()*100))
    {
        this->health = 0;
    }
    this->generalBulletUpdate(deltaTime);
}

void Entity2D::updateMovement(float deltaTime)
{
    this->movementSpeed+=(this->movementForce*deltaTime*this->theGame->getGameSpeed());
    this->pos+=(movementSpeed*deltaTime*this->theGame->getGameSpeed());
}

void Entity2D::collisionDetection(RenderEngine2D* engine, float deltaTime)
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
        if(this->pos.y+(this->hitbox.y/2)<=bricks[i]->pos.y+(blockSize.y/2)&&
                this->pos.y+(this->hitbox.y/2)>=bricks[i]->pos.y-(blockSize.y/2)||
           this->pos.y-(this->hitbox.y/2)<=bricks[i]->pos.y+(blockSize.y/2)&&
                this->pos.y-(this->hitbox.y/2)>=bricks[i]->pos.y-(blockSize.y/2))
        {
            //positive x
            if(this->pos.x+this->hitbox.x/2>=bricks[i]->pos.x-(blockSize.x/2)&&
                    this->pos.x+this->hitbox.x/2<=bricks[i]->pos.x+(blockSize.x/2))
            {
                this->blockedSides[0]=1;
                if(this->movementForce.x>0.0)
                {
                    this->movementForce.x=0.0;
                }
                this->pos.x=bricks[i]->pos.x-(blockSize.x/2)-(this->hitbox.x/2);
                if(this->movementSpeed.x>0.0)
                {
                    this->movementSpeed.x=0.0;
                }
            }
            //negative X
            if(this->pos.x-this->hitbox.x/2<=bricks[i]->pos.x+(blockSize.x/2)&&
                    this->pos.x-this->hitbox.x/2>=bricks[i]->pos.x-(blockSize.x/2))
            {
                this->blockedSides[1]=1;
                if(this->movementForce.x<0.0)
                {
                    this->movementForce.x=0.0;
                }
                this->pos.x=bricks[i]->pos.x+(blockSize.x/2)+(this->hitbox.x/2);
                if(this->movementSpeed.x<0.0)
                {
                    this->movementSpeed.x=0.0;
                }
            }
        }
        //vertical
        if(this->pos.x+(this->hitbox.x/2)<=bricks[i]->pos.x+(blockSize.x/2)&&
                this->pos.x+(this->hitbox.x/2)>=bricks[i]->pos.x-(blockSize.x/2)||
           this->pos.x-(this->hitbox.x/2)<=bricks[i]->pos.x+(blockSize.x/2)&&
                this->pos.x-(this->hitbox.x/2)>=bricks[i]->pos.x-(blockSize.x/2))
        {
            if(this->pos.y>=bricks[i]->pos.y&&this->previousPos.y<=bricks[i]->pos.y)
            {
                this->pos.y=bricks[i]->pos.y-(blockSize.y/2)-(this->hitbox.y/2);
            }
            else
            {
                //positive Y
                if(this->pos.y+this->hitbox.y/2+(this->movementSpeed.y*deltaTime)>=bricks[i]->pos.y-(blockSize.y/2)&&
                        this->pos.y+this->hitbox.y/2<=bricks[i]->pos.y+(blockSize.y/2))
                {
                    this->blockedSides[2]=1;
                    if(this->movementForce.y>0.0)
                    {
                        this->movementForce.y=0.0;
                    }
                    this->pos.y=bricks[i]->pos.y-(blockSize.y/2)-(this->hitbox.y/2);
                    if(this->movementSpeed.y>0.0)
                    {
                    this->movementSpeed.y=0.0;
                    }
                }
                //negative Y
                if(this->pos.y-this->hitbox.y/2<=bricks[i]->pos.y+(blockSize.y/2)&&
                        this->pos.y-this->hitbox.y/2>=bricks[i]->pos.y-(blockSize.y/2))
                {
                    this->blockedSides[3]=1;
                    if(this->movementForce.y<0.0)
                    {
                        this->movementForce.y=0.0;
                    }
                    this->pos.y=bricks[i]->pos.y+(blockSize.y/2)+(this->hitbox.y/2);
                    if(this->movementSpeed.y<0.0)
                    {
                        this->movementSpeed.y=0.0;
                    }
                }
            }
        }

        for(int b = 0; b<this->shotBullets.size(); b++)
        {
            if(this->shotBullets[b]->pos.x<bricks[i]->pos.x+(blockSize.x/2)&&
                this->shotBullets[b]->pos.x>bricks[i]->pos.x-(blockSize.x/2)&&
                this->shotBullets[b]->pos.y<bricks[i]->pos.y+(blockSize.y/2)&&
                this->shotBullets[b]->pos.y>bricks[i]->pos.y-(blockSize.y/2))
            {
                engine->createParticleEffect(glm::vec2(this->shotBullets[b]->pos.x,this->shotBullets[b]->pos.y),
                                             0.2f, 0.2f,10,
                                             this->shotBullets[b]->siz,this->shotBullets[b]->speed/2,
                                             2.0f*this->shotBullets[b]->siz,
                                             this->shotBullets[b]->col,
                                             16,1,0);

                this->shotBullets.erase(this->shotBullets.begin()+b);
                break;
            }
        }
    }
    this->previousPos=this->pos;
}

void Entity2D::shoot(glm::vec4 col)
{
    this->energy-=this->theGame->getWeaponType(this->activeWeaponNum)->getAttackCost();
    this->attackDelayValue = this->theGame->getWeaponType(this->activeWeaponNum)->getAttackDelay();

    Bullet* bull = new Bullet{this->theGame->getWeaponType(this->activeWeaponNum)->getAttackDamage(),this->pos,this->hitbox/10.0f,this->faceDirection,
                              (this->theGame->getWeaponType(this->activeWeaponNum)->getBulletSpeed()*this->theGame->getGameSpeed()),col,16};

    this->shotBullets.push_back(bull);
}

void Entity2D::generalBulletUpdate(float deltaTime)
{
    for(int i = 0; i<this->shotBullets.size(); i++)
    {

        this->shotBullets[i]->pos+=(this->shotBullets[i]->direction*this->shotBullets[i]->speed*deltaTime);
        if(glm::length(this->pos-this->shotBullets[i]->pos)>1000.0)
        {
            this->shotBullets.erase(this->shotBullets.begin()+i);
            break;
        }
    }
}

Entity2D::Entity2D(twoDPlatformerGame* activeGame, int initialWeaponNum, glm::vec2 pos, glm::vec2 siz, int health, int regen, int energy, int energyRegen, float speed,
                   float jumpForceVal, int textureN,
                   int terrainEffect, int gravityEffect, glm::vec4 col)
{
    this->theGame = activeGame;
    this->activeWeaponNum = initialWeaponNum;

    float randm = (((float)rand())/RAND_MAX);
    this->pos=pos;
    this->previousPos = pos;
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

void Entity2D::deathEffect(RenderEngine2D* engine, float duration,int amount)
{
    engine->createParticleEffect(this->pos,
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

int Entity2D::getAttackDelayValue(){

    return this->attackDelayValue;

}

int Entity2D::getActiveWeaponNum(){

    return this->activeWeaponNum;

}

void Entity2D::setActiveWeaponNum(int newNum){

    this->activeWeaponNum = newNum;

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

float Entity2D::getTakenDmg()
{
    return this->takenDamage;
}

void Entity2D::setTakenDmg(float newDmg)
{
    this->takenDamage = newDmg;
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

glm::vec2 Entity2D::getMovementForce()
{

    return this->movementForce;
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

void Entity2D::removeBullet(int index)
{

    this->shotBullets.erase(this->shotBullets.begin()+index);
}

void Entity2D::setFaceDirection(glm::vec2 newDirection)
{

    this->faceDirection = newDirection;
}

void Entity2D::setMovementSpeed(glm::vec2 newSpeed)
{

    this->movementSpeed = newSpeed;
}

void Entity2D::setMovementForce(glm::vec2 newForce)
{

    this->movementForce = newForce;
}

void Entity2D::setJumpForce(float newForce)
{

    this->jumpForce = newForce;
}

void Entity2D::setBlockedSides(int newBlocks[])
{
    for(int i = 0; i<4;i++){
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

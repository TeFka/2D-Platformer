#include "../Inc/Weapon2D.h"

Weapon2D::Weapon2D(float damage, float delay, float cost, float bSpeed, int textureN, int bType, int weaponShow)
{

    this->attackDamage = damage;
    this->attackDelay = delay;
    this->attackCost = cost;

    this->textureNum = textureN;
    this->bulletSpeed = bSpeed;
    this->bullelttType = bType;
    this->weaponShown = weaponShow;
}

float Weapon2D::getAttackDamage()
{
    return this->attackDamage;
}

float Weapon2D::getAttackDelay()
{
    return this->attackDelay;
}

float Weapon2D::getAttackCost()
{
    return this->attackCost;
}

int Weapon2D::getTextureNum()
{
    return this->textureNum;
}

int Weapon2D::getBulletSpeed()
{
    return this->bulletSpeed;
}

int Weapon2D::weaponIsShown()
{
    return this->weaponShown;
}

void Weapon2D::setAttackDamage(float newAttack)
{

    this->attackDamage = newAttack;

}

void Weapon2D::setAttackDelay(float newDelay)
{

    this->attackDelay = newDelay;

}

void Weapon2D::updateAttackDelay(float value)
{

    this->attackDelay += value;

}

void Weapon2D::setAttackCost(float newCost)
{

    this->attackCost = newCost;

}

void Weapon2D::setTextureNum(int newTexture)
{

    this->textureNum = newTexture;

}
void Weapon2D::setBulletSpeed(int newBulletSpeed)
{

    this->bulletSpeed = newBulletSpeed;

}

void Weapon2D::setWeaponShown(int newShow)
{
    this->weaponShown = newShow;
}

int Weapon2D::getType(){

    return this->bullelttType;

}

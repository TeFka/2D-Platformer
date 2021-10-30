#ifndef WEAPON_H_INCLUDED
#define WEAPON_H_INCLUDED

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

struct Bullet
{
    float damage;
    glm::vec2 pos;
    glm::vec2 siz;
    glm::vec2 direction;
    float speed;
    glm::vec4 col;
    int textureNum;
};

class Weapon2D
{
private:
    float attackDamage;
    float attackDelay;
    int textureNum;
    float bulletSpeed;
    float attackCost;

    int weaponIsShown;

public:

    Weapon2D(float, float, float, float, int, int = 1);

    float getAttackDamage();
    float getAttackDelay();
    float getAttackCost();

    int getTextureNum();
    int getBulletSpeed();

    int getWeaponShown();

    void setAttackDamage(float);
    void setAttackDelay(float);
    void updateAttackDelay(float);
    void setAttackCost(float);

    void setTextureNum(int);
    void setBulletSpeed(int);

    void setWeaponShown(int);


};

#endif // WEAPON_H_INCLUDED

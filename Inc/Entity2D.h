
#ifndef ENTITY2D_H_INCLUDED
#define ENTITY2D_H_INCLUDED

#include<glad/glad.h>
#include<GLFW/glfw3.h>

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
#include "Weapon2D.h"

class twoDPlatformerGame;

class Entity2D
{

protected:

    RenderEngine2D* renderEngine;
    twoDPlatformerGame* theGame;

    glm::vec2 pos;
    glm::vec2 previousPos;
    int entityTurn;

    glm::vec2 hitbox;
    glm::vec2 faceDirection;

    float defaultSpeed;
    glm::vec2 movementSpeed=glm::vec2(0.0);
    glm::vec2 movementForce=glm::vec2(0.0);
    float jumpForce;

    int blockedSides[4] = {0,0,0,0};

    float fullHealth;
    float health;
    float healthRegeneration;

    float energy;
    float fullEnergy;
    float energyRegeneration;

    glm::vec4 color;
    int textureNum;

    int affectionByTerrain;
    int affectionByGravity;
    int existence;

    std::vector<Bullet*> shotBullets;

    std::vector<weaponInfo*> activeWeapons;
    int weaponTurn = 0;

    int iteration = 0;

    void generalUpdate();

    void updateMovement();

    void collisionDetection();

    void useWeapon(glm::vec4, int=0);

    void generalBulletUpdate();

    void physicsUpdate();

public:
    Entity2D(RenderEngine2D*, twoDPlatformerGame*, std::vector<weaponInfo*>, glm::vec2, glm::vec2, int, int, int, int, float,
             float, int,
             int = 1, int = 1, glm::vec4 = glm::vec4(1.0));

    void deathEffect(glm::vec2, float,  int);

    void refreshEntity();

    glm::vec2 getPos();

    int getHp();

    int getFullHp();

    int getAttackDelayValue(int = 0);

    int getActiveWeaponNum(int=0);
    void setActiveWeaponNum(int, int=0);

    int getEnergy();

    int getFullEnergy();

    void setHp(int);

    void addWeapon(weaponInfo*);

    void setWeaponPos();

    glm::vec2 getHitBox();

    int getExistence();

    int setExistence(int);

    std::vector<Bullet*>& getBullets();

    int getBulletAmount();

    glm::vec2 getFaceDirection();

    glm::vec2 getMovementSpeed();

    float getJumpForce();

    int* getBlockedSides();

    int getHealthRegeneration();

    int getEnergyRegeneration();

    glm::vec4 getColor();

    int getTextureNum();

    int getAffectionByTerrain();

    int getAffectionByGravity();

    void removeBullet(int);

    void setMovementSpeed(glm::vec2);

    void setFaceDirection(glm::vec2);

    void setJumpForce(float);

    void setBlockedSides(int*);

    void setHealthRegeneration(int);

    void setEnergyRegeneration(int);
    void setColor(glm::vec4);
    void setTextureNum(int);
    void setAffectionByTerrain(int);
    void setAffectionByGravity(int);
};

#endif // ENTITY2D_H_INCLUDED

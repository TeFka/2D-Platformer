
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

    twoDPlatformerGame* theGame;

    glm::vec2 pos;
    glm::vec2 previousPos;

    glm::vec2 hitbox;
    glm::vec2 faceDirection;

    float defaultSpeed;
    glm::vec2 movementSpeed=glm::vec2(0.0);
    glm::vec2 movementForce=glm::vec2(0.0);
    float jumpForce;

    int blockedSides[4] = {0,0,0,0};

    int fullHealth;
    int health;
    int healthRegeneration;
    float takenDamage = 0;

    int energy;
    int fullEnergy;
    int energyRegeneration;

    float attackDelayValue;

    glm::vec4 color;
    int textureNum;

    int affectionByTerrain;
    int affectionByGravity;
    int existence;

    std::vector<Bullet*> shotBullets;

    int activeWeaponNum;

    int iteration = 0;

    void generalUpdate(float);

    void updateMovement(float);

    void collisionDetection(RenderEngine2D*, float);

    void shoot(glm::vec4);

    void generalBulletUpdate(float);

public:
    Entity2D(twoDPlatformerGame*, int, glm::vec2, glm::vec2, int, int, int, int, float,
             float, int,
             int = 1, int = 1, glm::vec4 = glm::vec4(1.0));

    void deathEffect(RenderEngine2D*, float,  int);

    void refreshEntity();

    glm::vec2 getPos();

    int getHp();

    int getFullHp();

    int getAttackDelayValue();

    int getActiveWeaponNum();
    void setActiveWeaponNum(int);

    int getEnergy();

    int getFullEnergy();

    void setHp(int);

    float getTakenDmg();

    void setTakenDmg(float);

    glm::vec2 getHitBox();

    int getExistence();

    int setExistence(int);

    std::vector<Bullet*>& getBullets();

    int getBulletAmount();

    glm::vec2 getFaceDirection();

    glm::vec2 getMovementSpeed();

    glm::vec2 getMovementForce();

    float getJumpForce();

    int* getBlockedSides();

    int getHealthRegeneration();

    int getEnergyRegeneration();

    glm::vec4 getColor();

    int getTextureNum();

    int getAffectionByTerrain();

    int getAffectionByGravity();

    void removeBullet(int);

    void setFaceDirection(glm::vec2);

    void setMovementSpeed(glm::vec2);

    void setMovementForce(glm::vec2);

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

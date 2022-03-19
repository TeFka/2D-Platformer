#ifndef PLAYER2D_H_INCLUDED
#define PLAYER2D_H_INCLUDED

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

#include "Entity2D.h"

class Player2D:public Entity2D
{

private:

    glm::vec2 relativePos;
    glm::vec2 localPos;
    float imunityPeriod = 1.0f;
    float imunityCounter= 1.0f;
    int weaponIndex = 0;
    void collisionDamage();
public:

    Player2D(RenderEngine2D*, twoDPlatformerGame*, std::vector<weaponInfo*>, glm::vec2, glm::vec2, int, int, int, int,
             float,float, int,
             int = 1,int = 1,glm::vec4 = glm::vec4(1.0));

    void keyboardCommand();

    void calcFaceDirection(glm::vec2);

    void refresh(glm::vec2 pos);

    void reactToBullets();

    void updatePlayerMovement();

    void update();

    void drawPlayer();

    glm::vec2 getRelativePos();
    glm::vec2 getLocalPos();
};

#endif // PLAYER2D_H_INCLUDED

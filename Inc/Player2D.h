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
    void collisionDamage();
public:

    Player2D(twoDPlatformerGame*, int, glm::vec2, glm::vec2, int, int, int, int,
             float,float, int,
             int = 1,int = 1,glm::vec4 = glm::vec4(1.0));

    void keyboardCommand(GLFWwindow*,float);

    void setFaceDirection(glm::vec2);

    void refresh(glm::vec2 pos);

    void reactToBullets();

    void updatePlayerMovement(float);

    void update(GLFWwindow*, RenderEngine2D*, float);

    void drawPlayer(RenderEngine2D *engine);

    glm::vec2 getRelativePos();
};

#endif // PLAYER2D_H_INCLUDED

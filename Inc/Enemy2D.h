#ifndef ENEMY2D_H_INCLUDED
#define ENEMY2D_H_INCLUDED

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

#include "2DPlatformerGame.h"
#include "Entity2D.h"

class Enemy2D : public Entity2D
{
private:

    int enemyType;
    float reactionDistance;

    void AIaction(float);

public:

    Enemy2D(twoDPlatformerGame*, int, int,glm::vec2, glm::vec2, int, int, int, int,
            float, float, int,
            int = 1,int = 1, glm::vec4 = glm::vec4(1.0),
            float = 20.0);

    void reactToBullets();

    void update(RenderEngine2D*, float deltaTime);

    void drawEnemy(RenderEngine2D*, glm::vec2);
};

#endif // ENEMY2D_H_INCLUDED

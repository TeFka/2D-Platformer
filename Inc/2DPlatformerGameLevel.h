
#ifndef TWODPLATFORMERGAMELEVEL_H_INCLUDED
#define TWODPLATFORMERGAMELEVEL_H_INCLUDED

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

struct gameObj
{
    int num;
    glm::vec2 pos;
    glm::vec2 siz;
    float rotat;
    glm::vec3 col;
    int textNum;
    int exsist;
};

class twoDPlatformerGameLevel
{
private:
    int windwW;
    int windwH;
    glm::vec2 activeCenter;
    int levelHeight;
    glm::vec2 brickSize;
    int brickCount = 0;
    int activeBrickCount = 0;
    int allDone = 0;
    std::vector<gameObj*> bricks;
    std::vector<gameObj*> activeBricks;
    int brickTextr;
    int solidTextr;

    glm::vec2 playerPos;
public:
    twoDPlatformerGameLevel(const GLchar*, glm::vec2, int, int, int, int);

    int getActiveBrickCount();
    glm::vec2 getBrickSize();

    std::vector<gameObj*>& getActiveBricks();

    void update(glm::vec2 pos);

    void draw(RenderEngine2D*, glm::vec2);

private:
    void init(std::vector<std::vector<int>>);
};

#endif // 2DPLATFORMERGAMELEVEL_H_INCLUDED

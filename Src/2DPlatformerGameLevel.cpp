
#include "../Inc/2DPlatformerGameLevel.h"

twoDPlatformerGameLevel::twoDPlatformerGameLevel(const GLchar *file, glm::vec2 brickSiz, int width, int height, int textNum1, int textNum2)
{
    this->brickTextr = textNum1;
    this->solidTextr = textNum2;
    this->brickSize = brickSiz;

    this->windwW = width;
    this->windwH = height;
    int tileCode;
    std::string line;
    std::ifstream fstream(file);
    std::vector<std::vector<int>> tileData;
    if(fstream)
    {
        getline(fstream,line);
        std::stringstream sstream(line);
        sstream >> this->levelHeight;
        for(int i =0; i<this->levelHeight; i++)
        {
            std::vector<int> row;
            tileData.push_back(row);
        }
        while(getline(fstream,line))
        {
            if(line[0]=='#')
            {
                for(int i =0; i<this->levelHeight; i++)
                {
                    getline(fstream,line);
                    sstream = std::stringstream(line);;
                    while(sstream >> tileCode)
                    {
                        tileData[i].push_back(tileCode);
                    }
                }
            }
        }
        if(tileData.size()>0)
        {
            this->init(tileData);
        }
    }
}

int twoDPlatformerGameLevel::getActiveBrickCount()
{
    return this->activeBrickCount;
}
glm::vec2 twoDPlatformerGameLevel::getBrickSize()
{
    return this->brickSize;
}

std::vector<gameObj*>& twoDPlatformerGameLevel::getActiveBricks()
{
    return this->activeBricks;
}

void twoDPlatformerGameLevel::update(glm::vec2 pos)
{
    this->activeBricks.clear();
    for(int i=0; i<this->brickCount; i++)
    {
        if(glm::length(this->bricks[i]->pos-pos)<2*this->windwW)
        {
            this->activeBricks.push_back(this->bricks[i]);
        }
    }
    activeBrickCount = this->activeBricks.size();
}

void twoDPlatformerGameLevel::draw(RenderEngine2D* engine, glm::vec2 pos)
{
    for(int n = 0; n<this->activeBrickCount; n++)
    {
        if(activeBricks[n]->exsist==1)
        {
            engine->setSprite(glm::vec2(activeBricks[n]->pos.x+this->windwW/2-pos.x,activeBricks[n]->pos.y+this->windwH/2-pos.y),
                              activeBricks[n]->siz,glm::vec4(activeBricks[n]->col,0.8),activeBricks[n]->textNum);
        }
    }
}

void twoDPlatformerGameLevel::init(std::vector<std::vector<int>> tileData)
{
    for(int y=0; y<tileData.size(); y++)
    {
        for(int x=0; x<tileData[y].size(); x++)
        {
            if(tileData[y][x]==1)
            {
                glm::vec2 pos(this->brickSize.x*x,this->brickSize.y*y);
                gameObj* obj = new gameObj{tileData[y][x],pos,this->brickSize,0.0,glm::vec3(0.3,0.3,0.3),solidTextr,1};
                brickCount++;
                this->bricks.push_back(obj);
            }
            else if(tileData[y][x]>1)
            {
                glm::vec3 col = glm::vec3(1.0);
                if(tileData[y][x]==2)
                {
                    col=glm::vec3(0.0,1.0,0.0);
                }
                else if(tileData[y][x]==3)
                {
                    col=glm::vec3(0.0,0.0,0.5);
                }
                else if(tileData[y][x]==4)
                {
                    col=glm::vec3(9.0,0.4,0.0);
                }
                else if(tileData[y][x]==5)
                {
                    col=glm::vec3(0.4,0.0,0.0);
                }
                glm::vec2 pos(this->brickSize.x*x,this->brickSize.y*y);
                gameObj* obj = new gameObj{tileData[y][x],pos,this->brickSize,0.0,col,brickTextr,1};
                brickCount++;
                this->bricks.push_back(obj);
            }
        }
    }
}

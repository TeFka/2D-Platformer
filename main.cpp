
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<SOIL2/SOIL2.h>
#include<ft2build.h>
#include FT_FREETYPE_H

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/vec2.hpp>
#include<glm/vec3.hpp>
#include<glm/vec4.hpp>
#include<cmath>

#include<iostream>
#include<sstream>
#include<fstream>
#include<stdlib.h>
#include<vector>
#include<map>
#include<tuple>

#include<Shader.h>
#include<Camera.h>
#include<Texture.h>

#include "RenderEngine2D.h"

#include "2DPlatformerGame.h"

#include "Inc/helpers/RootDir.h"

using namespace std;
using namespace glm;

int main()
{

    RenderEngine2D theRenderEngine("DaGame",
                              1200, 800,
                              4, 4);

    theRenderEngine.setText("C:/Windows/Fonts/arial.ttf");

    string rootDir = ROOT_DIR;
    string shaderDir = "Resources/shaders/";
    string shaderNames[8] = {"basic_vert.glsl", "basic_frag.glsl", "char_vert.glsl", "char_frag.glsl", "particle_vert.glsl", "particle_frag.glsl", "screens_vert.glsl", "screens_frag.glsl"};

    //Shaders

    int basicShaderNum = theRenderEngine.setShader((ROOT_DIR+shaderDir+shaderNames[0]).c_str(),(ROOT_DIR+shaderDir+shaderNames[1]).c_str());
    int charShaderNum = theRenderEngine.setShader((ROOT_DIR+shaderDir+shaderNames[2]).c_str(),(ROOT_DIR+shaderDir+shaderNames[3]).c_str());
    int particleShaderNum = theRenderEngine.setShader((ROOT_DIR+shaderDir+shaderNames[4]).c_str(),(ROOT_DIR+shaderDir+shaderNames[5]).c_str());
    int screenShaderNum = theRenderEngine.setShader((ROOT_DIR+shaderDir+shaderNames[6]).c_str(),(ROOT_DIR+shaderDir+shaderNames[7]).c_str());

    theRenderEngine.setShaderUniforms(charShaderNum,screenShaderNum);

    string textureDir = "Resources/textures/";
    string textureNames[11] = {"background.png", "bricks.png", "yes_piskel.png",
    "aim.png", "spinner.png", "jumper.png", "particle.png", "basicWeapon.png", "launcherWeapon.png", "artilleryWeapon.png", "roboBoss.png"};

    //Textures
    theRenderEngine.setTexture((rootDir+textureDir+textureNames[0]).c_str(),1,1);
    theRenderEngine.setTexture((rootDir+textureDir+textureNames[1]).c_str(),2,1);
    theRenderEngine.setTexture((rootDir+textureDir+textureNames[2]).c_str(),3,1);
    theRenderEngine.setTexture((rootDir+textureDir+textureNames[3]).c_str(),4,1);
    theRenderEngine.setTexture((rootDir+textureDir+textureNames[4]).c_str(),5,1);
    theRenderEngine.setTexture((rootDir+textureDir+textureNames[5]).c_str(),6,1);
    theRenderEngine.setTexture((rootDir+textureDir+textureNames[7]).c_str(),7,1);
    theRenderEngine.setTexture((rootDir+textureDir+textureNames[8]).c_str(),8,1);
    theRenderEngine.setTexture((rootDir+textureDir+textureNames[9]).c_str(),9,1);
    theRenderEngine.setTexture((rootDir+textureDir+textureNames[10]).c_str(),10,1);
    //particle textures
    theRenderEngine.setTexture((rootDir+textureDir+textureNames[6]).c_str(),1,2);

    ParticleEngine2D theParticleEngine(&theRenderEngine);
    theParticleEngine.particleSetup(1000);

    twoDPlatformerGame theGame(&theRenderEngine, &theParticleEngine, 1200, 800, 3);

    string levelsDir = "levels/";
    string levelNames[1] = {"level1.txt"};
    //Game levels
    theGame.addLevel((rootDir+levelsDir+levelNames[0]).c_str(),glm::vec2(100.0f,150.0f),2,2);
    //theGame.addLevel("./levels/level2.txt",width,height,1,2);
    //theGame.addLevel("./levels/level3.txt",width,height,1,2);
    //theGame.addLevel("./levels/level4.txt",width,height,1,2);
    //theGame.addLevel("./levels/level5.txt",width,height,1,2);*/

    theGame.addWeaponType(25.0f,10.0f,10.0f,30.0f,7,1,0);
    theGame.addWeaponType(25.0f,10.0f,10.0f,30.0f,7,1);
    theGame.addWeaponType(30.0f,10.0f,20.0f,30.0f,8,2);
    theGame.addWeaponType(50.0f,5.0f,20.0f,15.0f,9, 3);
    //shaderUpdate

    //setup
    theGame.setupPlayer(glm::vec2(600.0f, 400.0f), glm::vec2(50.0f, 100.0f), 100, 10, 100, 10,
                 40,5,3);

    while(!glfwWindowShouldClose(theRenderEngine.getWindow()))
    {

        theGame.systemInput();
        theGame.mouseInput();
        theGame.mainUpdate();

        //draw phase
        theRenderEngine.update();
        theRenderEngine.renderBegin();

        theRenderEngine.setSprite(vec2(theGame.getWidth()/2,theGame.getHeight()/2),
                              vec2(theGame.getWidth(),theGame.getHeight()),
                              vec4(0.4,0.4,0.4,1.0), 1);
        theGame.spritePhase();
        theParticleEngine.makeParticleEffect();
        theRenderEngine.drawBlocks(basicShaderNum);
        theRenderEngine.drawParticles(particleShaderNum);

        if(theGame.getGameState()!=GAME_MENU)
        {
            //text partum);
            theRenderEngine.writeText(charShaderNum,"Health",0.05f,0.95f,0.5f,vec3(0.0,1.0,0.0));
            theRenderEngine.writeText(charShaderNum,"Energy",0.05f,0.9f,0.5f,vec3(1.0,1.0,0.0));
            if(theGame.getGameState()==GAME_WIN)
            {
                theRenderEngine.writeText(charShaderNum,"You won",0.5f,0.5f,2.0,vec3(1.0));
                theRenderEngine.writeText(charShaderNum,"Press space to go again or esc to quit",0.5f,0.4f,1.0f,vec3(0.0,1.0,0.0));
            }
            else if(theGame.getGameState()==GAME_LOST)
            {
                theRenderEngine.writeText(charShaderNum,"You lost",0.5f,0.5f,2.0,vec3(1.0));
                theRenderEngine.writeText(charShaderNum,"Press space to go again or esc to quit",0.5f,0.4f,1.0f,vec3(1.0));
            }
        }
        else if(theGame.getGameState()==GAME_MENU)
        {
            theRenderEngine.writeText(charShaderNum,"Flash jump",0.5f,0.8f,2.0f,vec3(1.0,0.0,0.0));
            for(int i =0; i<5; i++)
            {
                stringstream ms;
                string dif;
                ms<<(i+1);
                dif = ms.str();
                if(i==(theGame.getCurrLevel()-1))
                {
                    theRenderEngine.writeText(charShaderNum,"Level "+dif,0.5f,((float)(6-i)/10.0f),1.0f,vec3(0.0,1.0,1.0));
                }
                else
                {
                    theRenderEngine.writeText(charShaderNum,"Level "+dif,0.5f,((float)(6-i)/10.0f),1.0f,vec3(1.0));
                }
            }
        }

        theRenderEngine.updateScreen(screenShaderNum,theGame.getPlayMode());

        theRenderEngine.renderEnd();
    }
    glfwDestroyWindow(theRenderEngine.getWindow());
    glfwTerminate();

    return 0;
}

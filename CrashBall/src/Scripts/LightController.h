#include "../Engine/Light/SpotLight.h"
#include "../Engine/Light/PointLight.h"

#define maxSpots 1
#define maxPoint 7
#define maxLightModes 3

SpotLight *spotLights[maxSpots];
PointLight *pointLights[maxPoint];
int lightMode; // 1-Spot light mode, 2-Point light mode, 3-Spot and point light mode

void LightControllerStart()
{
    spotLights[0] = new SpotLight(0, 0, 200, 0);

    pointLights[0] = new PointLight(1, 100, 50, 0);
    pointLights[1] = new PointLight(2, -100, 50, 0);
    pointLights[2] = new PointLight(3, 0, 50, 100);
    pointLights[3] = new PointLight(4, 0, 50, -100);

    pointLights[4] = new PointLight(5, 0, 0, 0);
    pointLights[5] = new PointLight(6, 0, 0, 0);
    pointLights[6] = new PointLight(7, 0, -200, 0);

    pointLights[0]->SetdiffuseColor(0.5, 1.0, 1.0, 1.0);
    pointLights[0]->SetspecularColor(0.5, 1.0, 1.0, 1.0);
    pointLights[1]->SetdiffuseColor(0.5, 1.0, 1.0, 1.0);
    pointLights[1]->SetspecularColor(0.5, 1.0, 1.0, 1.0);
    pointLights[2]->SetdiffuseColor(0.5, 1.0, 1.0, 1.0);
    pointLights[2]->SetspecularColor(0.5, 1.0, 1.0, 1.0);
    pointLights[3]->SetdiffuseColor(0.5, 1.0, 1.0, 1.0);
    pointLights[3]->SetspecularColor(0.5, 1.0, 1.0, 1.0);
    pointLights[4]->SetdiffuseColor(1.0, 0.5, 1.0, 1.0);
    pointLights[4]->SetspecularColor(1.0, 0.5, 1.0, 1.0);
    pointLights[5]->SetdiffuseColor(1.0, 0.5, 0.0, 1.0);
    pointLights[5]->SetspecularColor(1.0, 0.5, 0.0, 1.0);
    pointLights[6]->SetdiffuseColor(0.5, 1.0, 1.0, 1.0);
    pointLights[6]->SetspecularColor(0.5, 1.0, 1.0, 1.0);

    float spotAttenuation = 0.001;
    glLightf(pointLights[0]->Getglenum(), GL_QUADRATIC_ATTENUATION, spotAttenuation);
    glLightf(pointLights[1]->Getglenum(), GL_QUADRATIC_ATTENUATION, spotAttenuation);
    glLightf(pointLights[2]->Getglenum(), GL_QUADRATIC_ATTENUATION, spotAttenuation);
    glLightf(pointLights[3]->Getglenum(), GL_QUADRATIC_ATTENUATION, spotAttenuation);
    glLightf(pointLights[4]->Getglenum(), GL_QUADRATIC_ATTENUATION, spotAttenuation);
    glLightf(pointLights[5]->Getglenum(), GL_QUADRATIC_ATTENUATION, spotAttenuation);
    glLightf(pointLights[6]->Getglenum(), GL_QUADRATIC_ATTENUATION, 0.0000005);

    for(int i = 0; i < maxSpots; i++)
    {
        spotLights[i]->SetspotDir(0.0, -1.0, 0.0);
    }

    lightMode = 1;
}

void LightControllerKeyboard(int gameStatus, unsigned char key, bool state)
{
    switch(gameStatus)
    {
        //1-menu, 2-single player, 3-multi player 4-ranking 5-developer mode 6-level screen 7-pause screen
        case 1:
        break;
        case 2:
        break;
        case 3:
        break;
        case 4:
        break;
        case 5:
            if(state)
            {
                switch(tolower(key))
                {
                    case 'l':
                        lightMode = (lightMode +1) % maxLightModes;
                        std::cout<<"lightmode changed to "<< lightMode<< std::endl;
                    break;
                }
            }
        break;
        case 6:
        break;
        case 7:
        break;
    }
}

void LightControllerDraw()
{
    if(lightMode == 0)
    {
        for(int i = 0; i < maxSpots; i++)
        {
            glEnable(spotLights[i]->Getglenum());
            spotLights[i]->ShowLight();
        }
        for(int i = 0; i < maxPoint; i++)
        {
            glDisable(pointLights[i]->Getglenum());
        }
    }
    else if(lightMode == 1)
    {
        for(int i = 0; i < maxSpots; i++)
        {
            glDisable(spotLights[i]->Getglenum());
        }
        for(int i = 0; i < maxPoint; i++)
        {
            glEnable(pointLights[i]->Getglenum());
            pointLights[i]->ShowLight();
        }
    }
    else if(lightMode == 2)
    {
        for(int i = 0; i < maxSpots; i++)
        {
            glEnable(spotLights[i]->Getglenum());
            spotLights[i]->ShowLight();
        }
        for(int i = 0; i < maxPoint; i++)
        {
            glEnable(pointLights[i]->Getglenum());
            pointLights[i]->ShowLight();
        }
    }

}

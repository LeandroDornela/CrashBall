#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H


#include "../Engine/Camera/Camera.h"

#define maxCameraMods 2

Camera *camera;
int cameraMode;

inline void CameraControllerStart()
{
    camera = new Camera();
    camera->Orthogonal(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
    cameraMode = 2;
}

inline void DefineCameraMode3d()
{
    switch(cameraMode)
    {
        case 1:
            camera->Orthographic(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
        break;
        case 2:
            camera->Perspective(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
        break;
    }
}

inline void CameraControllerMotion(int gameStatus, int x, int y)
{
    switch(gameStatus)
    {
        //1-menu, 2-single player, 3-multi player 4-ranking 5-developer mode 6-level screen 7-pause screen
        case 1:
        break;
        case 2:
            //this->camera->cameraMotion(x, y);
        break;
        case 3:
            //this->camera->cameraMotion(x, y);
        break;
        case 4:
        break;
        case 5:
            camera->cameraMotion(x, y);
        break;
        case 6:
        break;
        case 7:
        break;
    }
}

inline void CameraControllerKeyboard(int gameStatus, unsigned char key, bool state)
{
    switch(gameStatus)
    {
        //1-menu, 2-single player, 3-multi player 4-ranking 5-developer mode 6-level screen 7-pause screen
        case 1:
        break;
        case 2:
            camera->cameraKeyboard(key);
        break;
        case 3:
            camera->cameraKeyboard(key);
        break;
        case 4:
        break;
        case 5:
            camera->cameraKeyboard(key);
            if(state)
            switch(tolower(key))
            {
                case 'r':
                    camera = new Camera();
                break;
                case 'c':
                    if(cameraMode < maxCameraMods)
                    {
                        cameraMode++;
                    }
                    else
                    {
                        cameraMode = 1;
                    }
                break;
            }
        break;
        case 6:
        break;
        case 7:
        break;
    }
}

inline void CameraControllerDraw(int gameStatus)
{
    switch(gameStatus)
    {
        //1-menu, 2-single player, 3-multi player 4-ranking 5-developer mode 6-level screen 7-pause screen
        case 1:
            camera->Orthogonal(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
        break;
        case 2:
            DefineCameraMode3d();
        break;
        case 3:
            DefineCameraMode3d();
        break;
        case 4:
            camera->Orthogonal(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
        break;
        case 5:
            DefineCameraMode3d();
        break;
        case 6:
            camera->Orthogonal(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
        break;
        case 7:
            camera->Orthogonal(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
        break;
        case 8:
            camera->Orthogonal(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
        break;
    }
}

#endif // CAMERACONTROLLER_H

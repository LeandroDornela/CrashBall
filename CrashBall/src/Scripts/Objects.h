#include "../Objects/Ball.h"
#include "../Objects/Player.h"

Ball *ball;
Player *p1, *p2;
bool hittedPlayer, hittedObj;

void ObjectsStart()
{
    cout << "Starting dinamic objects..." << endl;
    ball = new Ball(80, 30, 80, 7);
    ball->SetspeedX(-2.0);
    ball->SetspeedY(1.0);
    ball->SetspeedZ(-2.1);

    p1 = new Player(20, frontWall);
    p1->SetspeedX(1);
    p1->SetspeedY(1);
    p2 = new Player(20, backWall);

    GLfloat player1Position[3] = {0, 15, 0};
    GLfloat player2Position[3] = {0, 15, 0};
    GLfloat player1ReflectionPosition[3] = {0, -15, 0};
    GLfloat player2ReflectionPosition[3] = {0, -15, 0};
    GLfloat player1Rotation[4] = {180, 0, 1, 0};
    GLfloat player2Rotation[4] = {0, 0, 1, 0};
    int playerSize = 20;

    GLfloat diffuse[4] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat diffusePlayer1[4] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat diffusePlayer2[4] = { 1.0, 1.0, 1.0, 1.0 };

    LoadDinamicObject("player1", 2, player1Position, player1Rotation, playerSize, p1, true, 1, diffusePlayer1);
    LoadDinamicObject("player21", 2, player1Position, player1Rotation, playerSize, p1, true, 4, diffusePlayer1);
    LoadDinamicObject("player1", 2, player1ReflectionPosition, player1Rotation, playerSize, p1, false, 1, diffusePlayer1);
    LoadDinamicObject("player21", 2, player1ReflectionPosition, player1Rotation, playerSize, p1, false, 4, diffusePlayer1);
    LoadDinamicObject("player3", 2, player1Position, player1Rotation, playerSize, p1, true, 3, diffusePlayer1);
    LoadDinamicObject("player1", 3, player2Position, player2Rotation, playerSize, p2, true, 1, diffusePlayer2);
    LoadDinamicObject("player2", 3, player2Position, player2Rotation, playerSize, p2, true, 4, diffusePlayer2);
    LoadDinamicObject("player1", 3, player2ReflectionPosition, player2Rotation, playerSize, p2, false, 1, diffusePlayer2);
    LoadDinamicObject("player2", 3, player2ReflectionPosition, player2Rotation, playerSize, p2, false, 4, diffusePlayer2);
    LoadDinamicObject("player3", 3, player2Position, player2Rotation, playerSize, p2, true, 3, diffusePlayer2);
}

void ObjectsUpdate(int gameStatus, int level)
{
    hittedPlayer = false;
    hittedObj = false;
    switch(gameStatus)
    {
        //1-menu, 2-single player, 3-multi player 4-ranking 5-developer mode 6-level screen 7-pause screen
        case 1:
        break;
        case 2:
            p2->ComputerMovement(ball, level);
            ball->Move();

            hittedPlayer = ball->Getcollider()->Collides(p1) || ball->Getcollider()->Collides(p2);
            hittedObj = ball->Getcollider()->Collides(object1) || ball->Getcollider()->Collides(object2) ||
                        ball->Getcollider()->Collides(object3) || ball->Getcollider()->Collides(object4);

            pointLights[4]->Setposition(p2->GetpositionX() + 0, p2->GetpositionY() + 10, p2->GetpositionZ() + -30, 1);
            pointLights[5]->Setposition(p1->GetpositionX() + 0, p1->GetpositionY() + 10, p1->GetpositionZ() + 30, 1);

            for(int i = 0; i < maxPoint; i++)
            {
                glLightfv(pointLights[i]->Getglenum(), GL_POSITION, pointLights[i]->Getposition());
            }

            //ball->SpeedUp(this->interface->InGameUpdate(this->p1->Getscore(), this->p2->Getscore()), this->Getlevel());
        break;
        case 3:
            p2->Movement(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
            ball->Move();

            hittedPlayer = ball->Getcollider()->Collides(p1) || ball->Getcollider()->Collides(p2);
            hittedObj = ball->Getcollider()->Collides(object1) || ball->Getcollider()->Collides(object2) ||
                        ball->Getcollider()->Collides(object3) || ball->Getcollider()->Collides(object4);

            pointLights[4]->Setposition(p2->GetpositionX() + 0, p2->GetpositionY() + 10, p2->GetpositionZ() + -30, 1);
            pointLights[5]->Setposition(p1->GetpositionX() + 0, p1->GetpositionY() + 10, p1->GetpositionZ() + 30, 1);

            for(int i = 0; i < maxPoint; i++)
            {
                glLightfv(pointLights[i]->Getglenum(), GL_POSITION, pointLights[i]->Getposition());
            }

        break;
        case 4:
        break;
        case 5:
            pointLights[4]->Setposition(p2->GetpositionX() + 0, p2->GetpositionY() + 10, p2->GetpositionZ() + -30, 1);
            pointLights[5]->Setposition(p1->GetpositionX() + 0, p1->GetpositionY() + 10, p1->GetpositionZ() + 30, 1);

            for(int i = 0; i < maxPoint; i++)
            {
                glLightfv(pointLights[i]->Getglenum(), GL_POSITION, pointLights[i]->Getposition());
            }
        break;
        case 6:
        break;
        case 7:
        break;
    }
}

void ObjectsMousePassiveMotion(int gameStatus, int x, int y)
{
    switch(gameStatus)
    {
        //1-menu, 2-single player, 3-multi player 4-ranking 5-developer mode 6-level screen 7-pause screen
        case 1:
        break;
        case 2:
            p1->MouseMovement(x, y, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
        break;
        case 3:
            p1->MouseMovement(x, y, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
        break;
        case 4:
        break;
        case 5:
        break;
        case 6:
        break;
        case 7:
        break;
    }
}

void ObjectsKeyboardControls(int gameStatus, unsigned char key, bool state)
{
    switch(gameStatus)
    {
        //1-menu, 2-single player, 3-multi player 4-ranking 5-developer mode 6-level screen 7-pause screen
        case 1:
        break;
        case 2:
            p2->KeyboardMovement(key, state);
        break;
        case 3:
            p2->KeyboardMovement(key, state);
        break;
        case 4:
        break;
        case 5:
        break;
        case 6:
        break;
        case 7:
        break;
    }
}

void ObjectsDraw()
{
    GLfloat diffuse[4] = { 1.0, 1.0, 1.0, 1.0 };
    selectMaterial(1, diffuse);
    ball->Draw();
    if(!lowGraphcis){
        DrawDinamicObjects();
    } else{

        ball->Getcollider()->DrawCollider();
        p1->Getcollider()->DrawCollider();
        p2->Getcollider()->DrawCollider();
        p1->Draw();
        p2->Draw();
    }


}

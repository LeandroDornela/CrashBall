#include "GameManager.h"
#include "../Engine/Mesh.h"
#include <time.h>
#include "../Scripts/LightController.h"
#include "../Scripts/Cenario.h"
#include "../Scripts/Objects.h"
#include "../Scripts/CameraController.h"
#include "../Engine/ShadowCreator.h"

#define WIN32_LEAN_AND_MEAN
//#include <windows.h>
#include <stdio.h>
#include <GL/glut.h>

GameManager::GameManager()
{
    //ctor
}

GameManager::~GameManager()
{
    //dtor
}

void GameManager::Start(int width, int height)
{
    cout << "Starting the game..." << endl;
    CameraControllerStart();

    Sprite(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), glutGet(GLUT_WINDOW_WIDTH)/2, glutGet(GLUT_WINDOW_HEIGHT)/2, 0, 0, 0, 1, 0, "load");

    this->Setlevel(1);
    this->Setwidth(width);
    this->Setheight(height);
    this->SetgameStatus(1);//1-menu, 2-single player, 3-multi player 4-ranking 5-developer mode 6-level screen 7-pause screen

    this->interface = new Interface(fullscreen);
    this->defaultMaterial = new Material();

    StartObjReader();
    CenarioStart();
    LightControllerStart();
    ObjectsStart();
    FinishObjReader();

    this->SM->Start();
    this->interface->SetnBestTimes(0);

    this->SM->menuMusic();
}

void GameManager::Update()
{
    ObjectsUpdate(this->GetgameStatus(), this->Getlevel());

    if(hittedObj){
        this->SM->hitObjects();
    }

    if(hittedPlayer){
        this->SM->hitPlayer();
    }

    switch(this->GetgameStatus())
    {
        //1-menu, 2-single player, 3-multi player 4-ranking 5-developer mode 6-level screen 7-pause screen
        case 1:
            glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
        break;
        case 2:
            glutSetCursor(GLUT_CURSOR_NONE);
            /** Atualiza tempo de jogo e score mostrados no topo da tela*/
            this->interface->InGameUpdate(p1->Getscore(), p2->Getscore());
            this->VerifyWin();
        break;
        case 3:
            glutSetCursor(GLUT_CURSOR_NONE);
            this->interface->InGameUpdate(p1->Getscore(), p2->Getscore());
            this->VerifyWin();
        break;
        case 4:
            glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
        break;
        case 5:
            glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
        break;
        case 6:
            glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
        break;
        case 7:
            glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
        break;
        case 8:
        break;
    }

}

void GameManager::VerifyWin()
{
    bool needPlayerName, ballHittedWall;
    /**Verifica se a bola bateu nas paredes para tovar o som correspondente*/
    ballHittedWall = ball->Getcollider()->Collides(rightWall) ||  ball->Getcollider()->Collides(leftWall);
    /** PLayer2 faz ponto quando a bola bate na parede do player1 e vice versa*/
    bool p2score = ball->Getcollider()->Collides(p1->Getwall());
    bool p1score = ball->Getcollider()->Collides(p2->Getwall());

    if(ballHittedWall) {
        this->SM->hitObjects();
    }

    if(p2score)
    {
        p2->Setscore(p2->Getscore() + 1);
        this->SM->scoreSound();
        //Sleep(1000);
        this->MySleepStart();
        while(this->getElapsedSleepTime() < 1000){}
        this->Reset();
        if(p2->Getscore() >= 3)
        {
            p1->Setscore(0);
            p2->Setscore(0);
            this->interface->SetstartTime(-1);
            this->interface->Ranking(this->Getlevel());
            this->SetgameStatus(4);
            this->SM->gameOverSound();
        }
    }

    if(p1score)
    {
        p1->Setscore(p1->Getscore() + 1);
        this->SM->scoreSound();
        //Sleep(1000);
        this->MySleepStart();
        while(this->getElapsedSleepTime() < 1000){}
        this->Reset();
        if(p1->Getscore() >= 3)
        {
            p1->Setscore(0);
            p2->Setscore(0);
            if(this->GetgameStatus() == 2){ //Caso seja single player o p1 pode ir pro ranking
                needPlayerName = this->interface->Ranking(this->Getlevel());
                std::cout<<"needPlayerName = "<<needPlayerName<<std::endl;
                /**Se o player1 venceu um jogo single player e entrou no ranking
                    pego o nome dele, caso contrário só mostro o ranking
                */
                needPlayerName ? this->SetgameStatus(8) : this->SetgameStatus(4);
            } else{
                this->interface->SetstartTime(-1);
                this->interface->Ranking(this->Getlevel());
                this->SetgameStatus(4);
            }
            this->SM->gameOverSound();
        }
    }
}

void GameManager::Motion(int x, int y)
{
    CameraControllerMotion(this->GetgameStatus(), x, y);

    switch(this->GetgameStatus())
    {
        //1-menu, 2-single player, 3-multi player 4-ranking 5-developer mode 6-level screen 7-pause screen 8- input screen
        case 1:
        break;
        case 2:
        break;
        case 3:
        break;
        case 4:
        break;
        case 5:
        break;
        case 6:
        break;
        case 7:
        break;
        case 8:
        break;
    }
}

void GameManager::MousePassiveControls(int x, int y)
{
    /** Interface cuida das suas próprias atualizações de movimento passivo do mouse*/
    this->SM->itemSelected(this->interface->MousePassiveMovement(x, y, this->GetgameStatus()));

    ObjectsMousePassiveMotion(this->GetgameStatus(), x, y);

    switch(this->GetgameStatus())
    {
        //1-menu, 2-single player, 3-multi player 4-ranking 5-developer mode 6-level screen 7-pause screen 8- input screen
        case 1:
        break;
        case 2:
        break;
        case 3:
        break;
        case 4:
        break;
        case 5:
        break;
        case 6:
        break;
        case 7:
        break;
        case 8:
        break;
    }
}

void GameManager::KeyboardControls(unsigned char key, bool state)
{
    CameraControllerKeyboard(this->GetgameStatus(), key, state);
    ObjectsKeyboardControls(this->GetgameStatus(), key, state);
    LightControllerKeyboard(this->GetgameStatus(), key, state);

    if(key == 'f' && state){
        fullscreen = !fullscreen;
        (fullscreen) ? glutFullScreen() : glutReshapeWindow(this->Getwidth(),this->Getheight());
        this->interface->UpdateWindow(
                                      (fullscreen) ? glutGet(GLUT_SCREEN_WIDTH) : this->Getwidth(),
                                      (fullscreen) ? glutGet(GLUT_SCREEN_HEIGHT): this->Getheight()
                                      );
    }


    switch(this->GetgameStatus())
    {
        //1-menu, 2-single player, 3-multi player 4-ranking 5-developer mode 6-level screen 7-pause screen 8- input screen
        case 1:
        break;
        case 2:
            if(key == 32)
            {
                this->interface->SetpauseTime(time(NULL));
                this->SetgameStatus(7);
            }
        break;
        case 3:
            if(key == 32)
            {
                this->interface->SetpauseTime(time(NULL));
                this->SetgameStatus(7);
            }
        break;
        case 4:
        break;
        case 5:
            if(key == 32)
            {
                this->SetgameStatus(this->GetprevGameStatus());
                this->SetgameStatus(7);
            }
        break;
        case 6:
        break;
        case 7:
        break;
        case 8:
            if(state){
                this->SetgameStatus(this->interface->dealWithKey(key, this->Getlevel()));
            }
        break;
    }
}

void GameManager::MouseClick(int button, int x, int y)
{
    int temp;

    if( (button == 3 || button == 4) && this->GetgameStatus() == 5)
    {
        camera->cameraClick(button);
    }
    else
    {
        switch(this->GetgameStatus())
        {
            //1-menu, 2-single player, 3-multi player 4-ranking 5-developer mode 6-level screen 7-pause screen 8- input screen
            case 1:
                this->SetgameStatus(this->interface->MainMenuUpdate(x, y, this->Getlevel()));
                if(this->GetgameStatus() == 2 || this->GetgameStatus() == 3){
                    this->SM->gameMusic();
                }
            break;
            case 2:
                if((ball->GetspeedX() == 0) && (ball->GetspeedZ() == 0))
                {
                    switch(this->Getlevel())
                    {
                        case 0:
                            ball->SetspeedZ(4.0);
                            ball->SetspeedX(0);
                        break;
                        case 1:
                            ball->SetspeedZ(-4.0);
                            ball->SetspeedX(-0.5);
                        break;
                        case 2:
                            ball->SetspeedZ(-4.0);
                            ball->SetspeedX(-4.0);
                        break;
                    }
                }
            break;
            case 3:
                if((ball->GetspeedX() == 0) && (ball->GetspeedY() == 0))
                {
                    ball->SetspeedZ(-4.0);
                    ball->SetspeedX(-0.5);
                }
            break;
            case 4:
                this->SetgameStatus(1);
                this->SM->menuMusic();
            break;
            case 5:
            break;
            case 6:
                temp = this->interface->LevelMenuUpdate(x, y);
                this->Setlevel(temp < 3 ? temp : this->Getlevel()) ;
                this->SetgameStatus(temp == 6 ? temp : 1);
            break;
            case 7:
                temp = this->interface->PauseMenuUpdate(x, y);
                switch(temp)
                {
                    case 0:
                        //cuida pra quando o jogo é single ou multi
                        this->SetgameStatus(GetprevGameStatus());
                    break;
                    case 1:
                        this->Reset();
                        p1->Setscore(0);
                        p2->Setscore(0);
                        this->SetgameStatus(GetprevGameStatus());
                    break;
                    case 2:
                        this->SetgameStatus(GetprevGameStatus());
                        this->SetgameStatus(5);
                    break;
                    case 3:
                        this->Reset();
                        p1->Setscore(0);
                        p2->Setscore(0);
                        this->SetgameStatus(1);
                        this->SM->menuMusic();
                    break;
                }
            break;
            case 8:
            break;
        }
    }
}

void GameManager::DrawScn()
{
    CameraControllerDraw(this->GetgameStatus());

    switch(this->GetgameStatus())
    {
        //1-menu, 2-single player, 3-multi player 4-ranking 5-developer mode 6-level screen 7-pause screen 8- input screen
        case 1:
            this->interface->DrawMainMenu(fullscreen);
        break;
        case 2:
            this->interface->DrawInGame(fullscreen);
            defaultMaterial->DefaultMaterial();
            ObjectsDraw();
            CenarioDraw();
            LightControllerDraw();
        break;
        case 3:
            this->interface->DrawInGame(fullscreen);
            defaultMaterial->DefaultMaterial();
            ObjectsDraw();
            CenarioDraw();
            LightControllerDraw();
        break;
        case 4:
            this->interface->DrawRanking(this->Getlevel(), fullscreen);
        break;
        case 5:
            Grid();
            //this->interface->DrawInGame();
            defaultMaterial->DefaultMaterial();
            ObjectsDraw();
            CenarioDraw();
            LightControllerDraw();
        break;
        case 6:
            this->interface->DrawLevelMenu(fullscreen);
        break;
        case 7:
            this->interface->DrawInGame(fullscreen);
            this->interface->DrawPauseMenu(fullscreen);
        break;
        case 8:
            this->interface->DrawPlayerName(fullscreen);
        break;
    }
}

void GameManager::Draw(bool isShadow)
{
    if(isShadow && cameraMode != 1 && (this->GetgameStatus()==2 || this->GetgameStatus()==3 || this->GetgameStatus()==5 ))
    {
        DrawShadows(models, modelsPositions, spotLights, pointLights, lightMode);
    }
    else
    {
        DrawScn();
    }
}

void GameManager::Reset()
{
    ball->SetspeedX(-2.0);
    ball->SetspeedY(1.0);
    ball->SetspeedZ(-2.1);

    ball->SetpositionX(80);
    ball->SetpositionY(30);
    ball->SetpositionZ(80);

    int p1score = p1->Getscore(),
        p2score = p2->Getscore();

    //p1 = new Player(25, *frontWall);
    //p1->SetspeedX(1);
    //p1->SetspeedY(1);
    //p2 = new Player(25, *backWall);

    p1->Setscore(p1score);
    p2->Setscore(p2score);
}

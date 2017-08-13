#ifndef INTERFACE_H
#define INTERFACE_H
#include "GL/glut.h"

#include "../Engine/GameObject.h"
#include "../Engine/glcText.h"
#include "../Engine/Material/glcTexture.h"
#include "Menu.h"
#include <time.h>
#include <stdio.h>
#include <iostream>
#include <string>


class Interface : public GameObject
{
    public:
        Interface(bool fullscreen);
        virtual ~Interface();
        int MainMenuUpdate(int x, int y, int level);
        int PauseMenuUpdate(int x, int y);
        int LevelMenuUpdate(int x, int y);
        int InGameUpdate(int scoreP1, int scoreP2);
        void DrawMainMenu(bool fullscreen);
        void DrawLevelMenu(bool fullscreen);
        void DrawPauseMenu(bool fullscreen);
        void DrawInGame(bool fullscreen);
        int MousePassiveMovement(int x, int y, int gameStatus);
        //score/time stuff
        int GetstartTime() { return startTime; };
        void SetstartTime(int val) { startTime = val; };
        int GetpauseTime() { return pauseTime; };
        void SetpauseTime(int val) { pauseTime = val; };
        //ranking after gameover stuff
        int Getindex() { return index; };
        void Setindex(int val) { index = val; };
        int GetnBestTimes() { return nBestTimes; };
        void SetnBestTimes(int val) { nBestTimes = val; };
        bool Ranking(int level);
        void DrawRanking(int level, bool fullscreen);
        int ConvertStringTimeToInt(std::string myTime);
        std::string ConvertIntToStringTime(int myInt);
        void LoadRanking(int level);
        void SaveRanking(int level);
        void bgMenu(float width, float length, float x, float y, float z, int nx, int ny, int nz, bool fullscreen);
        void UpdateWindow(int w, int h);

        int dealWithKey(char key, int level);
        void DrawPlayerName(bool fullscreen);
        void GameOverMenu();
        void DrawGameOverMenu();
        char* stringToChar(std::string c);


    protected:

    private:
        glcTexture *bgTexture;
        glcText *score;
        glcText *timeElapsed;
        Menu *mainMenu;
        Menu *levelMenu;
        Menu *pauseMenu;
        int startTime;
        int pauseTime;
        int index;
        int bestTimes[10];
        std::string bestNames[10];
        std::string playername ="";
        int nBestTimes;
};

#endif // INTERFACE_H

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include "../Objects/Ball.h"
#include "../Objects/Player.h"
#include <time.h>
#include <stdio.h>
#include "../Interface/Interface.h"
#include "../Engine/Material/Material.h"
#include "../Sounds/SoundManager.h"
#include <SFML/System/Clock.hpp>

class GameManager
{
    public:
        GameManager();
        virtual ~GameManager();
        void Start(int width, int height);
        int Getlevel() { return level; }
        void Setlevel(int val) { level = val%3; }
        int Getwidth() { return width; }
        void Setwidth(int val) { width = val; }
        int Getheight() { return height; }
        void Setheight(int val) { height = val; }
        int GetgameStatus() { return gameStatus; }
        void SetgameStatus(int val) {
            SetprevGameStatus(gameStatus);
            gameStatus = val; }
        int GetprevGameStatus() { return prevGameStatus; }
        void Update();
        void DrawScn();
        void Draw(bool isShadow);
        void VerifyWin();
        void Motion(int x, int y);
        void MousePassiveControls(int x, int y);
        void KeyboardControls(unsigned char key, bool state);
        void MouseClick(int button, int x, int y);
        void Ranking();
        void Reset();

        void MySleepStart(){ clock.restart(); };
        int getElapsedSleepTime(){ return clock.getElapsedTime().asMilliseconds();};

    protected:
        void SetprevGameStatus(int val) { prevGameStatus = val; }
    private:
        SoundManager* SM = new SoundManager();
        sf::Clock clock;
        int level;
        int width;
        int height;
        Interface *interface;
        Material *defaultMaterial;
        int gameStatus, prevGameStatus;
};

#endif // GAMEMANAGER_H

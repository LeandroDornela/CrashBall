#ifndef PLAYER_H
#define PLAYER_H

#include <math.h>
#define CIRCLE_PRECISION 90
#include <GL/glut.h>
#include "../Engine/GameObject.h"
#include "Ball.h"
#include "Wall.h"
#include "../Engine/Physics/SphereCollider.h"

//Evitando referência cruzada
class Ball;

class Player : public GameObject
{
    public:
        Player(float r, Wall* atWall);
        virtual ~Player();
        float Getradius() { return radius; }
        void Setradius(float val) { radius = val; }
        float GetspeedX() { return speedX; }
        void SetspeedX(float val) { speedX = val; }
        float GetspeedY() { return speedY; }
        void SetspeedY(float val) { speedY = val; }
        float GetspeedZ() { return speedZ; }
        void SetspeedZ(float val) { speedZ = val; }
        Wall* Getwall() { return wall; }
        void Setwall(Wall* val) { wall = val; }
        int Getside() { return side; }
        void Setside(int val) { side = val; }
        int Getscore() { return score; }
        void Setscore(int val) { score = val; }
        SphereCollider *Getcollider() { return collider; }
        void Setcollider(SphereCollider *val) { collider = val; }
        void Draw();
        void MouseMovement(int x, int y, int width, int height);
        void KeyboardMovement(unsigned char key, bool state);
        void Movement(int width, int height);
        void ComputerMovement(Ball *ball, int level);
    protected:
    private:
        float radius;
        float speedX;
        float speedY;
        float speedZ;
        Wall* wall;
        int score, side;
        SphereCollider *collider;
};

#endif // PLAYER_H

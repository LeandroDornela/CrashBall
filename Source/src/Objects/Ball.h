#ifndef BALL_H
#define BALL_H

#define CIRCLE_PRECISION 360
#include <GL/glut.h>
#include <math.h>
#include "../Engine/GameObject.h"
#include "Player.h"
#include "iostream"
#include "../Engine/Physics/SphereCollider.h"
#include <stdio.h>

//Evitando referência cruzada
class Player;

class Ball : public GameObject
{
    public:
        Ball(float x, float y, float z, float r);
        virtual ~Ball();
        float Getradius() { return radius; }
        void Setradius(float val) { radius = val; }
        float GetspeedX() { return speedX; }
        void SetspeedX(float val) { speedX = val; }
        float GetspeedY() { return speedY; }
        void SetspeedY(float val) { speedY = val; }
        float GetspeedZ() { return speedZ; }
        void SetspeedZ(float val) { speedZ = val; }
        SphereCollider *Getcollider() { return collider; }
        void Setcollider(SphereCollider *val) { collider = val; }
        void Draw();
        void Move();
        void SpeedUp(int sec, int level);
        int WallCollision(int width, int height);
    protected:
    private:
        float radius;
        float speedX;
        float speedY;
        float speedZ;
        SphereCollider *collider;
};

#endif // BALL_H

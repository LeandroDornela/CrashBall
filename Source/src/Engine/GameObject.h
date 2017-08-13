#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <stdio.h>
class Collider;

class GameObject
{
    public:
        GameObject();
        virtual ~GameObject();
        float GetpositionX() { return positionX; }
        void SetpositionX(float val) {
            //printf("Ball oldx %f newx %f\n", positionX, val);
            positionX = val; }
        float GetpositionY() { return positionY; }
        void SetpositionY(float val) {
            //printf("Ball oldy %f newy %f\n", positionY, val);
            positionY = val; }
        float GetpositionZ() { return positionZ; }
        void SetpositionZ(float val) {
            //printf("Ball oldz %f newz %f\n", positionZ, val);
            positionZ = val; }
        virtual float GetspeedX() {};
        virtual void SetspeedX(float) {};
        virtual float GetspeedY() {};
        virtual void SetspeedY(float) {};
        virtual float GetspeedZ() {};
        virtual void SetspeedZ(float) {};
        virtual float Getradius() {};
        virtual void Setradius(float) {};
        virtual Collider *Getcollider() {};
        virtual void Setcollider() {};
    protected:
    private:
        float positionX;
        float positionY;
        float positionZ;
};

#endif // GAMEOBJECT_H

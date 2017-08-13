#ifndef COLLIDER_H
#define COLLIDER_H
#include <string>
#include <iostream>
#include "../GameObject.h"


class Collider
{
    public:
        Collider();
        virtual ~Collider();

        virtual float Getwidth() {};
        virtual void Setwidth() { };
        virtual float Getheight() { };
        virtual void Setheight(float val) { };
        virtual float Getlength() { };
        virtual void Setlength(float val) { };

        float GetpositionX() { return positionX; }
        void SetpositionX(float val) { positionX = val; }
        float GetpositionY() { return positionY; }
        void SetpositionY(float val) { positionY = val; }
        float GetpositionZ() { return positionZ; }
        void SetpositionZ(float val) { positionZ = val; }
        float GetrelativePosX() { return relativePosX; }
        void SetrelativePosX(float val) { relativePosX = val; }
        float GetrelativePosY() { return relativePosY; }
        void SetrelativePosY(float val) { relativePosY = val; }
        float GetrelativePosZ() { return relativePosZ; }
        void SetrelativePosZ(float val) { relativePosZ = val; }
        std::string Getshape() { return shape; }
        void Setshape(std::string val) { shape = val; }
        GameObject *Getobject() { return object; }
        void Setobject(GameObject *val) { object = val; }
        virtual int *Getnormal() {};
        virtual void Setnormal() {};
        virtual float Getradius() {};
        virtual void Setradius() {};
        virtual bool Collides(GameObject*) {};
        virtual void Move() {};
        virtual void DrawCollider() {};

    protected:

    private:
        float positionX;
        float positionY;
        float positionZ;
        float relativePosX;
        float relativePosY;
        float relativePosZ;
        std::string shape;
        GameObject *object;
};

#endif // COLLIDER_H

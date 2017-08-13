#ifndef PLANECOLLIDER_H
#define PLANECOLLIDER_H

#include "Collider.h"


class PlaneCollider : public Collider
{
    public:
        PlaneCollider(GameObject *object, float width, float height, float length, float relativeX, float relativeY, float relativeZ, int normalX, int normalY, int normalZ);
        virtual ~PlaneCollider();

        float Getwidth() { return width; }
        void Setwidth(float val) { width = val; }
        float Getheight() { return height; }
        void Setheight(float val) { height = val; }
        float Getlength() { return length; }
        void Setlength(float val) { length = val; }
        int *Getnormal() { return normal; }
        void Setnormal(int x, int y, int z) { normal[0] = x; normal[1] = y; normal[2] = z; }
        float dotProduct(float x1, float y1, float x2, float y2);
        bool CollidesWithPlane(GameObject *object);
        bool CollidesWithCube(GameObject *object);
        bool CollidesWithSphere(GameObject *object);
        bool Collides(GameObject *object);
        void Move(float x, float y, float z);
        void DrawCollider();

    protected:

    private:
        float width;
        float height;
        float length;
        int normal[3];
};

#endif // PLANECOLLIDER_H

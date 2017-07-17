#ifndef VERTEX3D_H
#define VERTEX3D_H

#include <stdio.h>
#include <stdlib.h>

class Vertex3d
{
    public:
        Vertex3d();
        ~Vertex3d();

        float GetX() { return posX; }
        void SetX(float val) { posX = val; }
        float GetY() { return posY; }
        void SetY(float val) { posY = val; }
        float GetZ() { return posZ; }
        void SetZ(float val) { posZ = val; }
        void print();

    protected:

    private:
        float posX;
        float posY;
        float posZ;
};

#endif // VERTEX3D_H

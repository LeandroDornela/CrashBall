#ifndef WALL_H
#define WALL_H

#include "../Engine/GameObject.h"
#include "../Engine/Mesh.h"
#include "../Engine/Physics/PlaneCollider.h"


class Wall : public GameObject
{
    public:
        Wall();
        Wall(int x, int y, int z, int w, int h, int d, int w_p, int h_p, int d_p, int normalX, int normalY, int normalZ);
        virtual ~Wall();

        int Getwidth() { return width; }
        void Setwidth(int val) { width = val; }

        int Getwidth_prec() { return width_prec; }
        void Setwidth_prec(int val) { width_prec = val; }

        int Getheight() { return height; }
        void Setheight(int val) { height = val; }

        int Getheight_prec() { return height_prec; }
        void Setheight_prec(int val) { height_prec = val; }

        int Getdepth() { return depth; }
        void Setdepth(int val) { depth = val; }

        int Getdepth_prec() { return depth_prec; }
        void Setdepth_prec(int val) { depth_prec = val; }

        int *Getnormal() { return normal; }
        void Setnormal(int x, int y, int z) { normal[0] = x; normal[1] = y; normal[2] = z; }

        PlaneCollider *Getcollider() { return collider; }
        void Setcollider(PlaneCollider *val) { collider = val; }

        void Draw();

    protected:

    private:
        int width;
        int height;
        int depth;
        int depth_prec;
        int height_prec;
        int width_prec;
        int normal[3];
        PlaneCollider *collider;
};

#endif // WALL_H

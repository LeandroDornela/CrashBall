#include "Wall.h"

Wall::Wall(){

}

Wall::Wall(int x, int y, int z, int w, int h, int d, int w_p, int h_p, int d_p, int normalX, int normalY, int normalZ)
{
    //ctor
    SetpositionX(x);
    SetpositionY(y);
    SetpositionZ(z);
    Setwidth(w);
    Setwidth_prec(w_p);
    Setheight(h);
    Setheight_prec(h_p);
    Setdepth(d);
    Setdepth_prec(d_p);
    this->Setnormal(normalX, normalY, normalZ);
    this->collider = new PlaneCollider(this, w, h, d, 0, 0, 0, normalX, normalY, normalZ);
}

void Wall::Draw(){
    Cube(this->Getwidth(), this->Getheight(), this->Getdepth(),
         this->GetpositionX(), this->GetpositionY(), this->GetpositionZ(),
         this->Getwidth_prec(), this->Getheight_prec(), this->Getdepth_prec());
    //this->collider->DrawCollider();
}

Wall::~Wall()
{
    //dtor
}

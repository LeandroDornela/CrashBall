#include "Vertex3d.h"
#include <math.h>

Vertex3d::Vertex3d()
{
    this->posX = 0.0;
    this->posY = 0.0;
    this->posZ = 0.0;
    //ctor
}

Vertex3d::~Vertex3d()
{
    //dtor
}


void Vertex3d::print(){
    printf("\n::: (x = %f, y = %f, z = %f) :::\n", this->GetX(), this->GetY(), this->GetZ());
}


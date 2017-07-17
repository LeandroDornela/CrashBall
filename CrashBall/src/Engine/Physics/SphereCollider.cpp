#include "SphereCollider.h"
#include "typeinfo"
#include <iostream>
#include <GL/glut.h>
#include <math.h>
#include "../../Objects/Wall.h"

bool firstcol =false;

SphereCollider::SphereCollider(GameObject *object,float radius, float relativeX, float relativeY, float relativeZ)
{
    this->Setobject(object);
    this->Setshape("sphere");
    this->Setradius(radius);
    this->SetpositionX(this->Getobject()->GetpositionX() + relativeX);
    this->SetpositionY(this->Getobject()->GetpositionY() + relativeY);
    this->SetpositionZ(this->Getobject()->GetpositionZ() + relativeZ);
    this->SetrelativePosX(relativeX);
    this->SetrelativePosY(relativeY);
    this->SetrelativePosZ(relativeZ);
}

SphereCollider::~SphereCollider()
{
    //dtor
}

float SphereCollider::dotProduct(float x1, float y1, float x2, float y2)
{
    return (x1*x2 + y1*y2)/sqrt(x2*x2 + y2*y2);
}

bool SphereCollider::CollidesWithPlane(GameObject *object)
{
    float limit = ((object->Getcollider()->Getnormal()[0])*(object->Getcollider()->GetpositionX()) +
                   (object->Getcollider()->Getnormal()[1])*(object->Getcollider()->GetpositionY()) +
                   (object->Getcollider()->Getnormal()[2])*(object->Getcollider()->GetpositionZ()));
    float ballPos = ((object->Getcollider()->Getnormal()[0])*(this->GetpositionX()) +
                     (object->Getcollider()->Getnormal()[1])*(this->GetpositionY()) +
                     (object->Getcollider()->Getnormal()[2])*(this->GetpositionZ()));

    float offset;
    int *normal = {object->Getcollider()->Getnormal()};

    if(normal[0] != 0 && normal[1] == 0 && normal[2] == 0){
        offset = object->Getcollider()->Getwidth()/2;
       // printf("normal0 %i offset %f\n", normal[0],offset);
    } else if(normal[0] == 0 && normal[1] == 0 && normal[2] != 0){
        offset = object->Getcollider()->Getlength()/2;
        //printf("normal2 %i offset %f\n", normal[2],offset);
    } else if(normal[0] == 0 && normal[1] != 0 && normal[2] == 0){
        offset = object->Getcollider()->Getlength()/2;
        //printf("normal1 %i offset %f\n", normal[1],offset);
    }

    if( (limit < 0 && limit + offset >= ballPos - this->Getradius()) || (limit > 0 && limit - offset <= ballPos + this->Getradius()))
    {
        //firstcol = !firstcol;
        offset = (abs(ballPos) + this->Getradius()) - (abs(limit) - offset);
        if(object->Getcollider()->Getnormal()[0] != 0)
        {
            this->Getobject()->SetspeedX(-this->Getobject()->GetspeedX());
            this->Getobject()->SetpositionX(this->Getobject()->GetpositionX() + offset * object->Getcollider()->Getnormal()[0]);

            return true;
        }
        else if(object->Getcollider()->Getnormal()[1] != 0)
        {
            this->Getobject()->SetspeedY(-this->Getobject()->GetspeedY());
            this->Getobject()->SetpositionY(this->Getobject()->GetpositionY() + offset * object->Getcollider()->Getnormal()[1]);

            return true;
        }
        else if(object->Getcollider()->Getnormal()[2] != 0)
        {
            this->Getobject()->SetspeedZ(-this->Getobject()->GetspeedZ());
            this->Getobject()->SetpositionZ(this->Getobject()->GetpositionZ() + offset * object->Getcollider()->Getnormal()[2]);

            return true;
        }
    }
    return false;
}

bool SphereCollider::CollidesWithCube(GameObject *object)
{

}

bool SphereCollider::CollidesWithSphere(GameObject *obj)
{
    float Nx, Nz, mag, normalParProj, normalPerpProj;
    float distance =  sqrt( pow(this->GetpositionX() - obj->Getcollider()->GetpositionX(), 2) + pow(this->GetpositionZ() - obj->Getcollider()->GetpositionZ(), 2));
    /** Detectando a colisão **/
    if( distance < this->Getradius() + obj->Getcollider()->Getradius() && this->GetpositionY() < 10)
    {

        /** Calculando a normal relativa ao ponto de colisão **/
        Nx = this->GetpositionX() - (this->GetpositionX() * obj->Getcollider()->Getradius() + obj->Getcollider()->GetpositionX() * this->Getradius())/(this->Getradius() + obj->Getcollider()->Getradius());
        Nz = this->GetpositionZ() - (this->GetpositionZ() * obj->Getcollider()->Getradius() + obj->Getcollider()->GetpositionZ() * this->Getradius())/(this->Getradius() + obj->Getcollider()->Getradius());

        /** Normalizando a normal **/
        mag = sqrt(Nx*Nx + Nz*Nz);
        Nx = Nx/mag;
        Nz = Nz/mag;

        /** Retirando a bola de dentro do player **/
        this->Getobject()->SetpositionX(this->Getobject()->GetpositionX() + 1*Nx*(this->Getobject()->Getradius() + obj->Getcollider()->Getradius() - distance));
        this->Getobject()->SetpositionZ(this->Getobject()->GetpositionZ() + 1*Nz*(this->Getobject()->Getradius() + obj->Getcollider()->Getradius() - distance));

        /** Projeções da velocidade em relação aos vetores paralelo e perpendicular a normal **/
        normalParProj = dotProduct(this->Getobject()->GetspeedX(), this->Getobject()->GetspeedZ(), Nx, Nz);
        normalPerpProj = dotProduct(this->Getobject()->GetspeedX(), this->Getobject()->GetspeedZ(), Nz, -Nx);
        /** Refletindo a componente paralela a normal **/
        normalParProj = -normalParProj;

        /** Novas velocidades **/
        this->Getobject()->SetspeedX(normalPerpProj*Nz + normalParProj*Nx);
        this->Getobject()->SetspeedZ(normalPerpProj*(-Nx) + normalParProj*Nz);

        return true;
    }
    else
        return false;
}

bool SphereCollider::Collides(GameObject *gameObject)
{
    std::string shape = gameObject->Getcollider()->Getshape();
    if(shape == "plane")
    {
        return CollidesWithPlane(gameObject);
    }
    else if(shape == "cube")
    {
        return CollidesWithCube(gameObject);
    }
    else if(shape == "sphere")
    {
        return CollidesWithSphere(gameObject);
    }
}

void SphereCollider::Move(float x, float y, float z)
{
    this->SetpositionX(x + this->GetrelativePosX());
    this->SetpositionY(y + this->GetrelativePosY());
    this->SetpositionZ(z + this->GetrelativePosZ());
}

void SphereCollider::DrawCollider()
{
    //std::cout << "desenhando colider " << this->Getshape() << " em " << this->GetpositionX() << ", " << this->GetpositionY() << ", " << this->GetpositionZ() << " com raio " << this->Getradius() << std::endl;
    glColor3f(0.0, 1.0, 0.0);
    glDisable(GL_LIGHTING);
    glPushMatrix();
        glTranslatef(this->GetpositionX(), this->GetpositionY(), this->GetpositionZ());
        glutWireSphere(this->Getradius(), 8, 8);
    glPopMatrix();
    glEnable(GL_LIGHTING);
}

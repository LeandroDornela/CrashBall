#include "PlaneCollider.h"
#include "GL/glut.h"
#include "math.h"

PlaneCollider::PlaneCollider(GameObject *object, float width, float height, float length, float relativeX, float relativeY, float relativeZ, int normalX, int normalY, int normalZ)
{
    this->Setobject(object);
    this->Setshape("plane");
    this->Setwidth(width);
    this->Setheight(height);
    this->Setlength(length);
    this->Setnormal(normalX, normalY, normalZ);
    this->SetpositionX(this->Getobject()->GetpositionX() + relativeX);
    this->SetpositionY(this->Getobject()->GetpositionY() + relativeY);
    this->SetpositionZ(this->Getobject()->GetpositionZ() + relativeZ);
    this->SetrelativePosX(relativeX);
    this->SetrelativePosY(relativeY);
    this->SetrelativePosZ(relativeZ);
}

PlaneCollider::~PlaneCollider()
{
    //dtor
}

float PlaneCollider::dotProduct(float x1, float y1, float x2, float y2)
{
    return (x1*x2 + y1*y2)/sqrt(x2*x2 + y2*y2);
}

bool PlaneCollider::CollidesWithPlane(GameObject *object)
{

}

bool PlaneCollider::CollidesWithCube(GameObject *object)
{

}

bool PlaneCollider::CollidesWithSphere(GameObject *object)
{

}

bool PlaneCollider::Collides(GameObject *gameObject)
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

void PlaneCollider::Move(float x, float y, float z)
{
    this->SetpositionX(x + this->GetrelativePosX());
    this->SetpositionY(y + this->GetrelativePosY());
    this->SetpositionZ(z + this->GetrelativePosZ());
}

void PlaneCollider::DrawCollider()
{
    glColor3f(0.0, 1.0, 0.0);
    glDisable(GL_LIGHTING);
    if(this->Getnormal()[0] == 1 || this->Getnormal()[0] == -1)
    {
        glBegin(GL_LINE_LOOP);
            glVertex3f(this->GetpositionX(), this->GetpositionY() + this->Getheight()/2, this->GetpositionZ() - this->Getlength()/2);
            glVertex3f(this->GetpositionX(), this->GetpositionY() - this->Getheight()/2, this->GetpositionZ() - this->Getlength()/2);
            glVertex3f(this->GetpositionX(), this->GetpositionY() - this->Getheight()/2, this->GetpositionZ() + this->Getlength()/2);
            glVertex3f(this->GetpositionX(), this->GetpositionY() + this->Getheight()/2, this->GetpositionZ() + this->Getlength()/2);
        glEnd();
    }
    else if(this->Getnormal()[1] == 1 || this->Getnormal()[1] == -1)
    {
        glBegin(GL_LINE_LOOP);
            glVertex3f(this->GetpositionX() + this->Getwidth()/2, this->GetpositionY(), this->GetpositionZ() - this->Getlength()/2);
            glVertex3f(this->GetpositionX() - this->Getwidth()/2, this->GetpositionY(), this->GetpositionZ() - this->Getlength()/2);
            glVertex3f(this->GetpositionX() - this->Getwidth()/2, this->GetpositionY(), this->GetpositionZ() + this->Getlength()/2);
            glVertex3f(this->GetpositionX() + this->Getwidth()/2, this->GetpositionY(), this->GetpositionZ() + this->Getlength()/2);
        glEnd();
    }
    else if(this->Getnormal()[2] == 1 || this->Getnormal()[2] == -1)
    {
        glBegin(GL_LINE_LOOP);
            glVertex3f(this->GetpositionX() + this->Getwidth()/2, this->GetpositionY() - this->Getheight()/2, this->GetpositionZ());
            glVertex3f(this->GetpositionX() - this->Getwidth()/2, this->GetpositionY() - this->Getheight()/2, this->GetpositionZ());
            glVertex3f(this->GetpositionX() - this->Getwidth()/2, this->GetpositionY() + this->Getheight()/2, this->GetpositionZ());
            glVertex3f(this->GetpositionX() + this->Getwidth()/2, this->GetpositionY() + this->Getheight()/2, this->GetpositionZ());
        glEnd();
    }
    glEnable(GL_LIGHTING);
}

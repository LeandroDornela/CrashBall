#include "PointLight.h"
#include "iostream"

PointLight::PointLight(int id, float x, float y, float z)
{
    switch(id)
    {
        case 0:
            this->Setglenum(GL_LIGHT0);
        break;
        case 1:
            this->Setglenum(GL_LIGHT1);
        break;
        case 2:
            this->Setglenum(GL_LIGHT2);
        break;
        case 3:
            this->Setglenum(GL_LIGHT3);
        break;
        case 4:
            this->Setglenum(GL_LIGHT4);
        break;
        case 5:
            this->Setglenum(GL_LIGHT5);
        break;
        case 6:
            this->Setglenum(GL_LIGHT6);
        break;
        case 7:
            this->Setglenum(GL_LIGHT7);
        break;
    }
    glEnable(this->Getglenum());
    this->SetambientColor(0.5, 0.5, 0.5, 1.0);
    this->SetdiffuseColor(1.0, 1.0, 1.0, 1.0);
    this->SetspecularColor(1.0, 1.0, 1.0, 1.0);
    this->Setposition(x, y, z, 1.0);
    glLightfv(this->Getglenum(), GL_AMBIENT, this->GetambientColor());
    glLightfv(this->Getglenum(), GL_DIFFUSE, this->GetdiffuseColor());
    glLightfv(this->Getglenum(), GL_SPECULAR, this->GetspecularColor());
    glLightfv(this->Getglenum(), GL_POSITION, this->Getposition());
}

PointLight::~PointLight()
{
    //dtor
}

void PointLight::ShowLight()
{
    glDisable(GL_LIGHTING);
    glPushMatrix();
        glLightfv(glenum,GL_POSITION,this->Getposition());
        glColor3f(this->GetdiffuseColor()[0], this->GetdiffuseColor()[1], this->GetdiffuseColor()[2]);
        glTranslatef(this->Getposition()[0], this->Getposition()[1], this->Getposition()[2]);
        glLightfv(glenum, GL_POSITION, this->Getposition());
        //glutSolidSphere(5, 16, 16);
    glPopMatrix();
    glEnable(GL_LIGHTING);

    glutPostRedisplay();
}

void PointLight::UpdatePosition()
{
    glLightfv(glenum,GL_POSITION,this->Getposition());
}

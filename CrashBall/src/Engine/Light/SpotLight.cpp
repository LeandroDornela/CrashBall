#include "SpotLight.h"
#include "../Material/Material.h"

SpotLight::SpotLight(int id, float x, float y, float z)
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
    this->SetambientColor(1.0, 1.0, 1.0, 1.0);
    this->SetdiffuseColor(1.0, 1.0, 1.0, 1.0);
    this->SetspecularColor(1.0, 1.0, 1.0, 1.0);
    this->Setposition(x, y, z, 1.0);
    this->Setcutoff(50.0);
    this->Setexponent(1.0);
    glLightfv(this->Getglenum(), GL_AMBIENT, this->GetambientColor());
    glLightfv(this->Getglenum(), GL_DIFFUSE, this->GetdiffuseColor());
    glLightfv(this->Getglenum(), GL_SPECULAR, this->GetspecularColor());
    glLightfv(this->Getglenum(), GL_POSITION, this->Getposition());
    // Specific spot effects
    // Cut off angle is 60 degrees
    glLightf(this->Getglenum(),GL_SPOT_CUTOFF,this->Getcutoff());

    // Fairly shiny spot
    glLightf(this->Getglenum(),GL_SPOT_EXPONENT,this->Getexponent());
}

SpotLight::~SpotLight()
{
    //dtor
}

void SpotLight::ShowLight()
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
            Material *material = new Material();
            material->Polished_silver();
            glLightfv(this->Getglenum(),GL_POSITION,this->Getposition());
            glLightfv(this->Getglenum(),GL_SPOT_DIRECTION,this->GetspotDir());
            glColor3f(0.5, 0.5, 0.5);
            glTranslatef(this->Getposition()[0],this->Getposition()[1],this->Getposition()[2]);
            glRotatef(-90, 1, 0, 0);
            glutSolidCone(8.0f,6.0f, 16, 16);
            glPushAttrib(GL_LIGHTING_BIT);
                    glDisable(GL_LIGHTING);
                    glColor3f(this->GetdiffuseColor()[0], this->GetdiffuseColor()[1], this->GetdiffuseColor()[2]);
                    glutSolidSphere(3.0f, 16, 16);
            glPopAttrib();
    glPopMatrix();
    glFlush();
    glEnable(GL_LIGHTING);

    glutPostRedisplay();
}

void SpotLight::UpdatePosition()
{
    glLightfv(glenum,GL_POSITION,this->Getposition());
    glLightfv(glenum,GL_SPOT_DIRECTION,this->GetspotDir());
}

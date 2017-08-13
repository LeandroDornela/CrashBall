#ifndef LIGHT_H
#define LIGHT_H
#include "GL/glut.h"


class PointLight
{
    public:
        PointLight(int id, float x, float y, float z);
        virtual ~PointLight();

        GLenum Getglenum() { return glenum; }
        void Setglenum(GLenum val) { glenum = val; }
        void SetambientColor(float r, float g, float b, float a) {  ambientColor[0] = r;
                                                                    ambientColor[1] = g;
                                                                    ambientColor[2] = b;
                                                                    ambientColor[3] = a;
                                                                    glLightfv(this->Getglenum(), GL_AMBIENT, this->GetambientColor()); }
        GLfloat *GetambientColor() { return ambientColor; }
        void SetdiffuseColor(float r, float g, float b, float a) {  diffuseColor[0] = r;
                                                                    diffuseColor[1] = g;
                                                                    diffuseColor[2] = b;
                                                                    diffuseColor[3] = a;
                                                                    glLightfv(this->Getglenum(), GL_DIFFUSE, this->GetdiffuseColor());}
        GLfloat *GetdiffuseColor() { return diffuseColor; }
        void SetspecularColor(float r, float g, float b, float a) { specularColor[0] = r;
                                                                    specularColor[1] = g;
                                                                    specularColor[2] = b;
                                                                    specularColor[3] = a;
                                                                    glLightfv(this->Getglenum(), GL_SPECULAR, this->GetspecularColor());}
        GLfloat *GetspecularColor() { return specularColor; }
        void Setposition(float x, float y, float z, float a) {  position[0] = x;
                                                                position[1] = y;
                                                                position[2] = z;
                                                                position[3] = a;
                                                                glLightfv(this->Getglenum(), GL_POSITION, this->Getposition());}
        GLfloat *Getposition() { return position; }
        void ShowLight();
        void UpdatePosition();

    protected:

    private:
        GLenum glenum;
        GLfloat ambientColor[4];
        GLfloat diffuseColor[4];
        GLfloat specularColor[4];
        GLfloat position[4];
};

#endif // LIGHT_H

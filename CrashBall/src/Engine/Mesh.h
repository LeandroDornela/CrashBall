#ifndef MESH_H
#define MESH_H

#include "GL/glut.h"
#include "Vertex3d.h"
#include <math.h>
#include "../Engine/Material/glcTexture.h"
#include <string.h>
#include <iostream>

#define maxMeshTextures 100

using namespace std;

inline void Cube(int width, int height, int depth, int x, int y, int z, int quad_width, int quad_height, int quad_depth)
{
    if(quad_depth > 0 && quad_width > 0 && quad_height > 0){
        // face que aponta pra +x
        for(float i=0; i <= depth - depth/quad_depth; i+=depth/quad_depth){
            for(float j=0; j <= height - height/quad_height; j+=height/quad_height){
                glBegin(GL_QUADS);
                    glNormal3f(1.0, 0.0, 0.0);
                    glVertex3f( x + width/2, y - height/2 + j, z - depth/2 + i);
                    glVertex3f( x + width/2, y - height/2 + j, z - depth/2 + i+depth/quad_depth);
                    glVertex3f( x + width/2, y - height/2 + j+height/quad_height, z - depth/2 + i+depth/quad_depth);
                    glVertex3f( x + width/2, y - height/2 + j+height/quad_height, z - depth/2 + i);
                glEnd();
            }
        }
        // face que aponta pra -x
        for(float i=0; i <= depth - depth/quad_depth; i+=depth/quad_depth){
            for(float j=0; j <= height - height/quad_height; j+=height/quad_height){
                glBegin(GL_QUADS);
                    glNormal3f(-1.0, 0.0, 0.0);
                    glVertex3f( x - width/2, y - height/2 + j, z - depth/2 + i);
                    glVertex3f( x - width/2, y - height/2 + j+height/quad_height, z - depth/2 + i);
                    glVertex3f( x - width/2, y - height/2 + j+height/quad_height, z - depth/2 + i+depth/quad_depth);
                    glVertex3f( x - width/2, y - height/2 + j, z - depth/2 + i+depth/quad_depth);
                glEnd();
            }
        }
        // face que aponta pra +y
        for(float i=0; i <= depth - depth/quad_depth; i+=depth/quad_depth){
            for(float j=0; j <= width - width/quad_width; j+=width/quad_width){
                glBegin(GL_QUADS);
                    glNormal3f(0.0, 1.0, 0.0);
                    glVertex3f( x + width/2 - j, y + height/2, z - depth/2 + i);
                    glVertex3f( x + width/2 - j, y + height/2, z - depth/2 + i+depth/quad_depth);
                    glVertex3f( x + width/2 - (j+width/quad_width), y + height/2, z - depth/2 + i+depth/quad_depth);
                    glVertex3f( x + width/2 - (j+width/quad_width), y + height/2, z - depth/2 + i);
                glEnd();
            }
        }
        // face que aponta pra -y
        for(float i=0; i <= depth - depth/quad_depth; i+=depth/quad_depth){
            for(float j=0; j <= width - width/quad_width; j+=width/quad_width){
                glBegin(GL_QUADS);
                    glNormal3f(0.0, -1.0, 0.0);
                    glVertex3f( x + width/2 - j, y - height/2, z - depth/2 + i);
                    glVertex3f( x + width/2 - (j+width/quad_width), y - height/2, z - depth/2 + i);
                    glVertex3f( x + width/2 - (j+width/quad_width), y - height/2, z - depth/2 + i+depth/quad_depth);
                    glVertex3f( x + width/2 - j, y - height/2, z - depth/2 + i+depth/quad_depth);
                glEnd();
            }
        }
        // face que aponta pra +z
        for(float i=0; i <= width - width/quad_width; i+=width/quad_width){
            for(float j=0; j <= height - height/quad_height; j+=height/quad_height){
                glBegin(GL_QUADS);
                    glNormal3f(0.0, 0.0, 1.0);
                    glVertex3f( x - width/2 + i, y - height/2 + j, z + depth/2);
                    glVertex3f( x - width/2 + i, y - height/2 + j+height/quad_height, z + depth/2);
                    glVertex3f( x - width/2 + i+width/quad_width, y - height/2 + j+height/quad_height, z + depth/2);
                    glVertex3f( x - width/2 + i+width/quad_width, y - height/2 + j, z + depth/2);
                glEnd();
            }
        }
        // face que aponta pra -z
        for(float i=0; i <= width - width/quad_width; i+=width/quad_width){
            for(float j=0; j <= height - height/quad_height; j+=height/quad_height){
                glBegin(GL_QUADS);
                    glNormal3f(0.0, 0.0, -1.0);
                    glVertex3f( x - width/2 + i, y - height/2 + j, z - depth/2);
                    glVertex3f( x - width/2 + i+width/quad_width, y - height/2 + j, z - depth/2);
                    glVertex3f( x - width/2 + i+width/quad_width, y - height/2 + j+height/quad_height, z - depth/2);
                    glVertex3f( x - width/2 + i, y - height/2 + j+height/quad_height, z - depth/2);
                glEnd();
            }
        };
    }

}

/**
 **     Regra da mão direita aplicada para o cálculo de normal
 **     p1 é a ponta do seu dedo médio (dedo do meio, maior dedo da mão, acho que vc já deve ter entendido de qual dedo to falando)
 **     p2 é a ponta do seu dedo indicador
 **     p3 é de onde os dois pontos partem e de onde a normal também partirá
 **/
inline Vertex3d CalculateSurfaceNormal(Vertex3d p1, Vertex3d p3, Vertex3d p2, bool normalized){
  Vertex3d n1, n2, n3;

  n1.SetX(p1.GetX() - p3.GetX());
  n1.SetY(p1.GetY() - p3.GetY());
  n1.SetZ(p1.GetZ() - p3.GetZ());

  n2.SetX(p2.GetX() - p3.GetX());
  n2.SetY(p2.GetY() - p3.GetY());
  n2.SetZ(p2.GetZ() - p3.GetZ());

  n3.SetX(n1.GetY()*n2.GetZ() - n1.GetZ()*n2.GetY());
  n3.SetY(n1.GetZ()*n2.GetX() - n1.GetX()*n2.GetZ());
  n3.SetZ(n1.GetX()*n2.GetY() - n1.GetY()*n2.GetX());

  if(normalized){
    float mod;
    mod = sqrt( pow(n3.GetX(), 2) + pow(n3.GetY(), 2) + pow(n3.GetZ(), 2));

    n3.SetX(n3.GetX() / mod);
    n3.SetY(n3.GetY() / mod);
    n3.SetZ(n3.GetZ() / mod);
  }

  return n3;
}

inline void Plane(float width, float length, float x, float y, float z)
{
    glBegin(GL_QUADS);
        glNormal3f(0.0, 0.0, 1.0);
        glTexCoord2f(0, 1);
        glVertex3f(-width/2 + x, -length/2 + y, z);
        glTexCoord2f(0, 0);
        glVertex3f(-width/2 + x, length/2 + y, z);
        glTexCoord2f(1, 0);
        glVertex3f(width/2 + x, length/2 + y, z);
        glTexCoord2f(1, 1);
        glVertex3f(width/2 + x, -length/2 + y, z);
    glEnd();
    glutPostRedisplay();
}

inline void Sprite(float width, float length, float x, float y, float z, int nx, int ny, int nz, int id, string image)
{
    glcTexture *meshTextureManager;
    int totalMeshTextures = 0;

    meshTextureManager = new glcTexture();            // Criação do arquivo que irá gerenciar as texturas
    meshTextureManager->SetNumberOfTextures(maxMeshTextures);       // Estabelece o número de texturas que será utilizado
    meshTextureManager->SetWrappingMode(GL_REPEAT);

    string imagePath = "../data/" + image + ".png";
    meshTextureManager->CreateTexture(imagePath, totalMeshTextures);

    glMatrixMode(GL_MODELVIEW);
    glDisable(GL_LIGHTING);
	glPushMatrix();
	    meshTextureManager->Bind(id);
	    glBegin(GL_QUADS);
            glNormal3f(nx, ny, nz);
            glTexCoord2f(0, 1);
            glVertex3f(-width/2 + x, -length/2 + y, z);
            glTexCoord2f(0, 0);
            glVertex3f(-width/2 + x, length/2 + y, z);
            glTexCoord2f(1, 0);
            glVertex3f(width/2 + x, length/2 + y, z);
            glTexCoord2f(1, 1);
            glVertex3f(width/2 + x, -length/2 + y, z);
        glEnd();
    glPopMatrix();
    glEnable(GL_LIGHTING);
    glutSwapBuffers();

    glutPostRedisplay();
}

inline void Grid()
{
    glLineWidth(2);
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
    // Eixo X
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f( 0, 0.0, 0.0);
        glVertex3f( 1280, 0.0, 0.0);
    // Eixo Y
        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 1280, 0.0);
    // Eixo Z
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(0.0, 0.0, 0);
        glVertex3f(0.0, 0.0, 1280);
    glEnd();
    glEnable(GL_LIGHTING);
    glutPostRedisplay();
}

#endif // MESH_H


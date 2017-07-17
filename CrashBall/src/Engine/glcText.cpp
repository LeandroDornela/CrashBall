/*
  Name:        glcText.cpp
  Copyright:   Version 0.1
  Author:      Rodrigo Luis de Souza da Silva
  Date:        19/10/2004
  Last Update: 09/02/2013
  Description: Text class for OpenGL Programs (functions)
*/

#include <stdio.h>
#include <string.h>
#include <GL/glut.h>
#include "glcText.h"

// glcText Constructor
glcText::glcText()
{
   strcpy(str, "");
   for(int i=0;i<3;i++) color[i] = 0.5;
   type = 0;
}

// Set color value in RGB mode
void glcText::setColor(float R, float G, float B)
{
   color[0] = R;
   color[1] = G;
   color[2] = B;
   glColor3fv(color);
}

// Set String Value
void glcText::setString(char *s)
{
   if(s)
      strcpy(str,s);
}

// Get String Value
char* glcText::getString()
{
    return str;
}

// Set type of the string
void glcText::setType(int n)
{
   switch(n)
   {
      case 0: type = GLUT_BITMAP_HELVETICA_18;     break;
      case 1: type = GLUT_BITMAP_HELVETICA_12;     break;
      case 2: type = GLUT_BITMAP_HELVETICA_10;     break;
      case 3: type = GLUT_BITMAP_TIMES_ROMAN_10;   break;
      case 4: type = GLUT_BITMAP_TIMES_ROMAN_24;   break;
      case 5: type = GLUT_BITMAP_9_BY_15;          break;
      case 7: type = GLUT_BITMAP_8_BY_13;          break;
      default:type = GLUT_BITMAP_HELVETICA_18;
   }
}

// Set Raster Position
void glcText::setPos(int x, int y)
{
   rasterPos[0] = x;
   rasterPos[1] = y;
}

// Get X Raster Position
int glcText::getPosX()
{
   return rasterPos[0];
}

// Get Y Raster Position
int glcText::getPosY()
{
   return rasterPos[1];
}

// Render string in the window
void glcText::render()
{
	char* p = (char*) str;
	glRasterPos2f(rasterPos[0], rasterPos[1]);
	while (*p != '\0') glutBitmapCharacter(type, *p++);
}

// Set all variables and render the result
void glcText::setAll(char *s, int type, int posx, int posy, float r, float g, float b)
{
   this->setString(s);
   this->setType(type);
   this->setPos(posx, posy);
   this->setColor(r,g,b);
   this->render();
}



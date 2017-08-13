#ifndef GLCTEXT_H
#define GLCTEXT_H
/*
(Some changes were made in the original code for academic purposes)
  Name:        glcText.h
  Copyright:   Version 0.1
  Author:      Rodrigo Luis de Souza da Silva
  Date:        19/10/2004
  Description: Text class for OpenGL Programs

   Examples of use:

   // Using setAll method
   glcText t1;
   t1.setAll("teste", 0, (int)p[current].x, (int)p[current].y-10,1.0,1.0,1.0 );

   // Using separated Methods
   glcText *text2 = new glcText;
      text2->setString("P4");
      text2->setColor(1.0,1.0,1.0);
      text2->setPos((int)p[3].x, (int)p[3].y-10);
      text2->setType(3);
      text2->render();

   delete text2;

*/
class glcText
{
   private:
      char str[128];    // String to be rendered
      float color[3];   // Color of the text
      void* type;       // Type of the text (view glcText.cpp)
      int rasterPos[2]; // Position of the Text on the Screen
   public:
      glcText();
      void setString(char *);
      char* getString();
      void setColor(float, float, float);
      void setType(int);
      void setPos(int, int);
      int getPosX();
      int getPosY();
      void render();
      void setAll(char *s, int type, int posx, int posy, float r, float g, float b);
};

#endif // GLCTEXT_H

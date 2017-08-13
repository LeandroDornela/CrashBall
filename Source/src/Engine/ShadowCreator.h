#include "../Engine/Material/glcTexture.h"

using namespace std;

float l[] = { 0.0,  100.0, 0.0 }; // the position of the light source
float l2[] = { 0.0,  100.0, 100.0 }; // the position of the light source
float n[] = { 0.0,  -1.0, 0.0 }; // is the normal vector of the plane.
float e[] = { 0.0,   0.01, 0.0 }; // point on within the plane on which the shadow is to be projected.
float shadow[] = {0.25f, 0.25f, 0.25f, 1.0f};
float h = 0.01;

void glShadowProjection(float * l, float * e, float * n)
{
  	float d, c;
  	float mat[16];

  	// These are c and d (corresponding to the tutorial)
  	d = n[0]*l[0] + n[1]*l[1] + n[2]*l[2];
  	c = e[0]*n[0] + e[1]*n[1] + e[2]*n[2] - d;

  	// Create the matrix. OpenGL uses column by column ordering
  	mat[0]  = l[0]*n[0]+c;
  	mat[4]  = n[1]*l[0];
  	mat[8]  = n[2]*l[0];
  	mat[12] = -l[0]*c-l[0]*d;

  	mat[1]  = n[0]*l[1];
  	mat[5]  = l[1]*n[1]+c;
  	mat[9]  = n[2]*l[1];
  	mat[13] = -l[1]*c-l[1]*d;

  	mat[2]  = n[0]*l[2];
  	mat[6]  = n[1]*l[2];
  	mat[10] = l[2]*n[2]+c;
  	mat[14] = -l[2]*c-l[2]*d;

  	mat[3]  = n[0];
  	mat[7]  = n[1];
  	mat[11] = n[2];
  	mat[15] = -d;

  	// Finally multiply the matrices together *plonk*
  	glMultMatrixf(mat);
}

void DrawShadows(GLMmodel *models[100], GLfloat modelsPositions[100][3], SpotLight *spotLights[], PointLight *pointLights[], int lightMode)
{
    float fadeDistance = 1, fadePrecison = 1, heightFactor = 0;
    switch(lightMode)
    {
        case 0:
            for(int j = 0; j < maxSpots; j++)
            {
                l[0] = spotLights[j]->Getposition()[0];
                l[1] = spotLights[j]->Getposition()[1];
                l[2] = spotLights[j]->Getposition()[2];

                for(int i = 0; i < totalStaticObjects; i++)
                {
                    if(staticObjectShadow[i])
                    {
                        glDisable(GL_LIGHTING);
                        glMatrixMode(GL_MODELVIEW);
                        glPushMatrix();
                            glShadowProjection(l,e,n);
                            glColor4f(0,0,0,1);
                            glTranslatef(modelsPositions[i][0], modelsPositions[i][1], modelsPositions[i][2] + 0.5);
                            glmDraw(models[i], GLM_FLAT | GLM_MATERIAL);
                        glPopMatrix();
                        glEnable(GL_LIGHTING);
                        e[1] += h;
                    }
                }
            }

            e[1] = h;
        break;
        case 1:
            //Spot em objetos estaticos
            for(int j = 0; j < maxSpots; j++)
            {
                l[0] = spotLights[j]->Getposition()[0];
                l[1] = spotLights[j]->Getposition()[1];
                l[2] = spotLights[j]->Getposition()[2];

                for(int i = 0; i < totalStaticObjects; i++)
                {
                    if(staticObjectShadow[i])
                    {
                        glDisable(GL_LIGHTING);
                        glMatrixMode(GL_MODELVIEW);
                        glPushMatrix();
                            glShadowProjection(l,e,n);
                            glColor4f(0,0,0,0.9);
                            glTranslatef(modelsPositions[i][0], modelsPositions[i][1], modelsPositions[i][2]);
                            glmDraw(models[i], GLM_FLAT | GLM_MATERIAL);
                        glPopMatrix();
                        glEnable(GL_LIGHTING);
                        e[1] += h;
                    }
                }
            }
            //Spot em objetos dinamicos
            for(float p = 0; p < fadeDistance; p += fadePrecison)
            {
            for(int j = 0; j < maxSpots; j++)
            {
                l[0] = spotLights[j]->Getposition()[0];
                l[1] = spotLights[j]->Getposition()[1] + heightFactor;
                l[2] = spotLights[j]->Getposition()[2];

                for(int i = 0; i < totalDinamicObjects; i++)
                {
                    if(dinamicObjectShadow[i])
                    {
                        glDisable(GL_LIGHTING);
                        glMatrixMode(GL_MODELVIEW);
                        glPushMatrix();
                            glShadowProjection(l,e,n);
                            glColor4f(0,0,0,1);
                            glTranslatef(dinamicObjectsFollows[i]->GetpositionX() + dinamicModelsPositions[i][0],
                                         dinamicObjectsFollows[i]->GetpositionY() + dinamicModelsPositions[i][1],
                                         dinamicObjectsFollows[i]->GetpositionZ() + dinamicModelsPositions[i][2]);
                            glRotatef(dinamicModelsRotation[i][0], dinamicModelsRotation[i][1], dinamicModelsRotation[i][2], dinamicModelsRotation[i][3]);
                            glmDraw(dinamicModels[i], GLM_FLAT | GLM_MATERIAL);
                        glPopMatrix();
                        glEnable(GL_LIGHTING);
                        e[1] += h;
                    }
                }
            }
            heightFactor += 10;
            }
            //Point na bola
            for(int i = 0; i < maxPoint - 1; i++)
            {
                l[0] = 2*pointLights[i]->Getposition()[0];
                l[1] = 2*pointLights[i]->Getposition()[1];
                l[2] = 2*pointLights[i]->Getposition()[2];

                float distX = pow(ball->GetpositionX() - l[0] , 3);
                float distY = pow(ball->GetpositionY() - l[1] , 3);
                float distZ = pow(ball->GetpositionZ() - l[2] , 3);

                float intensit = 0;

                if(i >= maxPoint -3)
                {
                    intensit = 100000/(sqrt(distX*distX + distY*distY + distZ*distZ));
                }
                else
                {
                    intensit = 800000/(sqrt(distX*distX + distY*distY + distZ*distZ));
                }

                glDisable(GL_LIGHTING);
                glMatrixMode(GL_MODELVIEW);
                glPushMatrix();
                    glShadowProjection(l,e,n);
                    glColor4f(0,0,0,intensit);
                    glTranslatef(ball->GetpositionX(), ball->GetpositionY(), ball->GetpositionZ());
                    glutSolidSphere(ball->Getradius(), 16, 16);
                glPopMatrix();
                glEnable(GL_LIGHTING);
                e[1] += h;
            }

            //Spot na bola
            for(int j = 0; j < maxSpots; j++)
            {
                l[0] = spotLights[j]->Getposition()[0];
                l[1] = spotLights[j]->Getposition()[1];
                l[2] = spotLights[j]->Getposition()[2];

                glDisable(GL_LIGHTING);
                glMatrixMode(GL_MODELVIEW);
                glPushMatrix();
                    glShadowProjection(l,e,n);
                    glColor4f(0,0,0,0.5);
                    glTranslatef(ball->GetpositionX(), ball->GetpositionY(), ball->GetpositionZ());
                    glutSolidSphere(ball->Getradius(), 16, 16);
                glPopMatrix();
                glEnable(GL_LIGHTING);
                e[1] += h;
            }
            e[1] = h;
        break;
        case 2:
            //Spot em objetos estaticos
            for(int j = 0; j < maxSpots; j++)
            {
                l[0] = spotLights[j]->Getposition()[0];
                l[1] = spotLights[j]->Getposition()[1];
                l[2] = spotLights[j]->Getposition()[2];

                for(int i = 0; i < totalStaticObjects; i++)
                {
                    if(staticObjectShadow[i])
                    {
                        glDisable(GL_LIGHTING);
                        glMatrixMode(GL_MODELVIEW);
                        glPushMatrix();
                            glShadowProjection(l,e,n);
                            glColor4f(0,0,0,0.9);
                            glTranslatef(modelsPositions[i][0], modelsPositions[i][1], modelsPositions[i][2]);
                            glmDraw(models[i], GLM_FLAT | GLM_MATERIAL);
                        glPopMatrix();
                        glEnable(GL_LIGHTING);
                        e[1] += h;
                    }
                }
            }

            //Spot em objetos dinamicos
            for(float p = 0; p < fadeDistance; p += fadePrecison)
            {
            for(int j = 0; j < maxSpots; j++)
            {
                l[0] = spotLights[j]->Getposition()[0];
                l[1] = spotLights[j]->Getposition()[1] + heightFactor;
                l[2] = spotLights[j]->Getposition()[2];

                for(int i = 0; i < totalDinamicObjects; i++)
                {
                    if(dinamicObjectShadow[i])
                    {
                        glDisable(GL_LIGHTING);
                        glMatrixMode(GL_MODELVIEW);
                        glPushMatrix();
                            glShadowProjection(l,e,n);
                            glColor4f(0,0,0,0.25);
                            glTranslatef(dinamicObjectsFollows[i]->GetpositionX() + dinamicModelsPositions[i][0],
                                         dinamicObjectsFollows[i]->GetpositionY() + dinamicModelsPositions[i][1],
                                         dinamicObjectsFollows[i]->GetpositionZ() + dinamicModelsPositions[i][2]);
                            glRotatef(dinamicModelsRotation[i][0], dinamicModelsRotation[i][1], dinamicModelsRotation[i][2], dinamicModelsRotation[i][3]);
                            glmDraw(dinamicModels[i], GLM_FLAT | GLM_MATERIAL);
                        glPopMatrix();
                        glEnable(GL_LIGHTING);
                        e[1] += h;
                    }
                }
            }
            heightFactor += 10;
            }

            //Point em objetos estaticos
            for(int j = 0; j < maxPoint; j++)
            {
                l[0] = pointLights[j]->Getposition()[0];
                l[1] = pointLights[j]->Getposition()[1];
                l[2] = pointLights[j]->Getposition()[2];

                for(int i = 0; i < totalStaticObjects; i++)
                {
                    if(staticObjectShadow[i])
                    {
                        glDisable(GL_LIGHTING);
                        glMatrixMode(GL_MODELVIEW);
                        glPushMatrix();
                            glShadowProjection(l,e,n);
                            glColor4f(0,0,0,0.1);
                            glTranslatef(modelsPositions[i][0], modelsPositions[i][1], modelsPositions[i][2]);
                            glmDraw(models[i], GLM_FLAT | GLM_MATERIAL);
                        glPopMatrix();
                        glEnable(GL_LIGHTING);
                        e[1] += h;
                    }
                }
            }

            //Point em objetos dinamicos
//            for(int j = 0; j < maxPoint; j++)
//            {
//                l[0] = 2*pointLights[j]->Getposition()[0];
//                l[1] = 2*pointLights[j]->Getposition()[1];
//                l[2] = 2*pointLights[j]->Getposition()[2];
//
//                for(int i = 0; i < totalDinamicObjects; i++)
//                {
//                    if(dinamicObjectShadow[i])
//                    {
//                        glDisable(GL_LIGHTING);
//                        glMatrixMode(GL_MODELVIEW);
//                        glPushMatrix();
//                            glShadowProjection(l,e,n);
//                            glColor4f(0,0,0,0.1);
//                            glTranslatef(dinamicObjectsFollows[i]->GetpositionX() + dinamicModelsPositions[i][0],
//                                         dinamicObjectsFollows[i]->GetpositionY() + dinamicModelsPositions[i][1],
//                                         dinamicObjectsFollows[i]->GetpositionZ() + dinamicModelsPositions[i][2]);
//                            glRotatef(dinamicModelsRotation[i][0], dinamicModelsRotation[i][1], dinamicModelsRotation[i][2], dinamicModelsRotation[i][3]);
//                            glmDraw(dinamicModels[i], GLM_FLAT | GLM_MATERIAL);
//                        glPopMatrix();
//                        glEnable(GL_LIGHTING);
//                        e[1] += h;
//                    }
//                }
//            }

            //Point na bola
            for(int i = 0; i < maxPoint; i++)
            {
                l[0] = 2*pointLights[i]->Getposition()[0];
                l[1] = 2*pointLights[i]->Getposition()[1];
                l[2] = 2*pointLights[i]->Getposition()[2];
                glDisable(GL_LIGHTING);
                glMatrixMode(GL_MODELVIEW);
                glPushMatrix();
                    glShadowProjection(l,e,n);
                    glColor4f(0,0,0,0.1);
                    glTranslatef(ball->GetpositionX(), ball->GetpositionY(), ball->GetpositionZ());
                    glutSolidSphere(ball->Getradius(), 16, 16);
                glPopMatrix();
                glEnable(GL_LIGHTING);
                e[1] += h;
            }

            //Spot na bola
            for(int j = 0; j < maxSpots; j++)
            {
                l[0] = spotLights[j]->Getposition()[0];
                l[1] = spotLights[j]->Getposition()[1];
                l[2] = spotLights[j]->Getposition()[2];

                glDisable(GL_LIGHTING);
                glMatrixMode(GL_MODELVIEW);
                glPushMatrix();
                    glShadowProjection(l,e,n);
                    glColor4f(0,0,0,0.5);
                    glTranslatef(ball->GetpositionX(), ball->GetpositionY(), ball->GetpositionZ());
                    glutSolidSphere(ball->Getradius(), 16, 16);
                glPopMatrix();
                glEnable(GL_LIGHTING);
                e[1] += h;
            }

            e[1] = h;
        break;
    }
    glutPostRedisplay();
}

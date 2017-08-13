#include "glm.h"
#include "../Material/glcTexture.h"

#define maxStaticObjects 100
#define maxDinamicObjects 100
#define maxTextures 100

using namespace std;

glcTexture *textureManager;
GLMmodel *models[maxStaticObjects];
GLfloat modelsPositions[maxStaticObjects][3];
bool staticObjectShadow[maxStaticObjects];
int totalStaticObjects = 0;
int staticObjectsMaterials[maxStaticObjects];
GLfloat staticObjectsColors[maxStaticObjects][4];

glcTexture *textureManagerDin;
GLMmodel *dinamicModels[maxStaticObjects];
GLfloat dinamicModelsPositions[maxStaticObjects][3];
GLfloat dinamicModelsRotation[maxStaticObjects][4];
GameObject *dinamicObjectsFollows[maxDinamicObjects];
bool dinamicObjectShadow[maxDinamicObjects];
int totalDinamicObjects = 0;
int dinamicObjectsMaterials[maxDinamicObjects];
int dynimaicObjectsId[maxDinamicObjects];
GLfloat dynamicObjectsColors[maxDinamicObjects][4];

Material *material;
GLuint id;
GLuint id2;
char *objectName;
int selected = 0;

void StartObjReader()
{
    textureManager = new glcTexture();            // Criação do arquivo que irá gerenciar as texturas
    textureManager->SetNumberOfTextures(maxTextures);       // Estabelece o número de texturas que será utilizado
    textureManager->SetWrappingMode(GL_REPEAT);
    textureManagerDin = new glcTexture();            // Criação do arquivo que irá gerenciar as texturas
    textureManagerDin->SetNumberOfTextures(maxTextures);       // Estabelece o número de texturas que será utilizado
    textureManagerDin->SetWrappingMode(GL_REPEAT);
    material = new Material();
}

void LoadObjTexture(string image)
{
    cout << "Loading " << image << " texture... ";
    string imagePath = "../data/" + image + ".png";
    textureManager->CreateTexture(imagePath, totalStaticObjects);
    cout << "Load Finished." << endl;
}

void LoadDinamicObjTexture(string image)
{
    cout << "Loading " << image << " texture... ";
    string imagePath = "../data/" + image + ".png";
    textureManagerDin->CreateTexture(imagePath, totalDinamicObjects);
    cout << "Load Finished." << endl;
}

char *stringToChar(string c)
{
    char *ch = new char[c.length()+1];
    memcpy(ch, c.c_str(), c.length() + 1);
    return ch;
}

void LoadStaticObject(string model, GLfloat x, GLfloat y, GLfloat z, GLfloat scale, bool shadow, int material, GLfloat diffuse[])
{
    cout << "Loading " << model << " model... " << endl;
    string modelPath = "../data/objFiles/" + model + ".obj";
    objectName = stringToChar(modelPath);

    LoadObjTexture(model);

    modelsPositions[totalStaticObjects][0] = x;
    modelsPositions[totalStaticObjects][1] = y;
    modelsPositions[totalStaticObjects][2] = z;

    staticObjectShadow[totalStaticObjects] = shadow;

    staticObjectsMaterials[totalStaticObjects] = material;

    staticObjectsColors[totalStaticObjects][0] = diffuse[0];
    staticObjectsColors[totalStaticObjects][1] = diffuse[1];
    staticObjectsColors[totalStaticObjects][2] = diffuse[2];
    staticObjectsColors[totalStaticObjects][3] = diffuse[3];

    glEnable(GL_TEXTURE_2D);
    if(!models[totalStaticObjects])
    {
		models[totalStaticObjects] = glmReadOBJ(objectName);
		if(!models[totalStaticObjects]) exit(0);
		glmUnitize(models[totalStaticObjects]);
		glmFacetNormals(models[totalStaticObjects]);
		glmVertexNormals(models[totalStaticObjects], 90.0);
		glmScale(models[totalStaticObjects], scale);
		totalStaticObjects++;
	}
	glDisable(GL_TEXTURE_2D);
}

void LoadDinamicObject(string model, int id, GLfloat position[], GLfloat rotation[], GLfloat scale, GameObject *gameObject, bool shadow, int material, GLfloat diffuse[])
{
    cout << "Loading " << model << " model... " << endl;
    string modelPath = "../data/objFiles/" + model + ".obj";
    objectName = stringToChar(modelPath);

    LoadDinamicObjTexture(model);

    dinamicModelsPositions[totalDinamicObjects][0] = position[0];
    dinamicModelsPositions[totalDinamicObjects][1] = position[1];
    dinamicModelsPositions[totalDinamicObjects][2] = position[2];
    dinamicModelsRotation[totalDinamicObjects][0] = rotation[0];
    dinamicModelsRotation[totalDinamicObjects][1] = rotation[1];
    dinamicModelsRotation[totalDinamicObjects][2] = rotation[2];
    dinamicModelsRotation[totalDinamicObjects][3] = rotation[3];

    dinamicObjectsFollows[totalDinamicObjects] = gameObject;

    dinamicObjectShadow[totalDinamicObjects] = shadow;

    dinamicObjectsMaterials[totalDinamicObjects] = material;

    dynimaicObjectsId[totalDinamicObjects] = id;

    dynamicObjectsColors[totalDinamicObjects][0] = diffuse[0];
    dynamicObjectsColors[totalDinamicObjects][1] = diffuse[1];
    dynamicObjectsColors[totalDinamicObjects][2] = diffuse[2];
    dynamicObjectsColors[totalDinamicObjects][3] = diffuse[3];

    glEnable(GL_TEXTURE_2D);
    if(!dinamicModels[totalDinamicObjects])
    {
		dinamicModels[totalDinamicObjects] = glmReadOBJ(objectName);
		if(!dinamicModels[totalDinamicObjects]) exit(0);
		glmUnitize(dinamicModels[totalDinamicObjects]);
		glmFacetNormals(dinamicModels[totalDinamicObjects]);
		glmVertexNormals(dinamicModels[totalDinamicObjects], 90.0);
		glmScale(dinamicModels[totalDinamicObjects], scale);
		totalDinamicObjects++;
	}
	glDisable(GL_TEXTURE_2D);
}

void selectMaterial(int material, GLfloat diffuse[])
{
        //metalico
        if(material == 1)
        {
            const GLfloat ambient[] = { 0.05, 0.05, 0.05, 1.0 };
            //const GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
            const GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
            const GLfloat shininess[] = { 256.0f };
            const GLfloat emission[] = { 0, 0, 0, 0 };
            glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
            glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
            glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
            glMaterialfv(GL_FRONT, GL_EMISSION, emission);
        }
        //translucido
        else if(material == 2)
        {
            glDisable(GL_CULL_FACE);
            const GLfloat ambient[] = { 0.05, 0.05, 0.05, 1.0 };
            const GLfloat diffuse[] = { 1.0, 1.0, 1.0, 0.8 };
            const GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
            const GLfloat shininess[] = { 256.0f };
            const GLfloat emission[] = { 0, 0, 0, 0 };
            glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
            glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
            glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
            glMaterialfv(GL_FRONT, GL_EMISSION, emission);
        }
        //opaco
        else if(material == 3)
        {
            const GLfloat ambient[] = { 0.05, 0.05, 0.05, 1.0 };
            //const GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
            const GLfloat specular[] = { 0.0, 0.0, 0.0, 1.0 };
            const GLfloat shininess[] = { 256.0f };
            const GLfloat emission[] = { 0, 0, 0, 0 };
            glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
            glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
            glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
            glMaterialfv(GL_FRONT, GL_EMISSION, emission);
        }
        //luminoso
        else if(material == 4)
        {
            const GLfloat ambient[] = { 1.0, 1.0, 1.0, 1.0 };
            //const GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
            const GLfloat specular[] = { 0.0, 0.0, 0.0, 1.0 };
            const GLfloat shininess[] = { 256.0f };
            const GLfloat emission[] = { 256, 256, 256, 1 };
            glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
            glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
            glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
            glMaterialfv(GL_FRONT, GL_EMISSION, emission);
        }
}

void DrawStaticObjects()
{
    glCallList(id);
}

void DrawDinamicObjects()
{
    for(int i = 0; i < totalDinamicObjects; i++)
    {
        glPushMatrix();
            glTranslatef(dinamicObjectsFollows[i]->GetpositionX() + dinamicModelsPositions[i][0],
                         dinamicObjectsFollows[i]->GetpositionY() + dinamicModelsPositions[i][1],
                         dinamicObjectsFollows[i]->GetpositionZ() + dinamicModelsPositions[i][2]);
            glCallList(id2 + i);
        glPopMatrix();
    }
}

void AddModelsToList()
{
    glNewList(id, GL_COMPILE);
        for(int i = 0; i < totalStaticObjects; i++)
        {
            glEnable(GL_TEXTURE_2D);
            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
                textureManager->Bind(i);
                selectMaterial(staticObjectsMaterials[i], staticObjectsColors[i]);
                glTranslatef(modelsPositions[i][0], modelsPositions[i][1], modelsPositions[i][2]);
                glmDraw(models[i], GLM_SMOOTH | GLM_TEXTURE);
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);
            glEnable(GL_CULL_FACE);
        }
    glEndList();
}

void AddDynamicModelsToList()
{
        for(int i = 0; i < totalDinamicObjects; i++)
        {
            glNewList(id2 + i, GL_COMPILE);
                glEnable(GL_TEXTURE_2D);
                glEnable(GL_LIGHTING);
                glMatrixMode(GL_MODELVIEW);
                glPushMatrix();
                    selectMaterial(dinamicObjectsMaterials[i], dynamicObjectsColors[i]);
                    textureManagerDin->Bind(i);
                    glRotatef(dinamicModelsRotation[i][0], dinamicModelsRotation[i][1], dinamicModelsRotation[i][2], dinamicModelsRotation[i][3]);
                    glmDraw(dinamicModels[i], GLM_SMOOTH | GLM_TEXTURE);
                glPopMatrix();
                glDisable(GL_TEXTURE_2D);
            glEndList();
        }
}

void FinishObjReader()
{
    id = glGenLists(1);
    id2 = glGenLists(totalDinamicObjects);
    AddModelsToList();
    AddDynamicModelsToList();
}


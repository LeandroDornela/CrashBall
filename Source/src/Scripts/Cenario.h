#include "../Objects/Wall.h"
#include "../Engine/ObjReader/ObjReader.h"

bool lowGraphcis = false;
bool fullscreen = true;

int comprimento = 136, altura = 16, profundidade = 136, grossura = 2;
Wall *leftWall, *rightWall, *frontWall, *backWall, *floorWall, *cenarioFloor;
GameObject *object1, *object2, *object3, *object4;
SphereCollider *cenarioCollider1, *cenarioCollider2, *cenarioCollider3, *cenarioCollider4;

void CenarioStart()
{
    cout << "Starting cenario..." << endl;
    rightWall = new Wall(-110, altura/2, 0, grossura, altura, profundidade,  1, 1/*8*/, 1/*40*/,  1, 0,  0);
    leftWall = new Wall(110, altura/2, 0, grossura, altura, profundidade,    1, 1/*8*/, 1/*40*/, -1, 0,  0);
    frontWall = new Wall(0, altura/2, -110, comprimento, altura, grossura, 1/*30*/, 1/*8*/,  1,  0, 0,  1);
    backWall = new Wall(0, altura/2, 110, comprimento, altura, grossura,   1/*30*/, 1/*8*/,  1,  0, 0, -1);
    floorWall = new Wall(0, -grossura/2, 0, comprimento, grossura, profundidade, 1/*30*/, 1, 1/*40*/,  0, 1,  0);

    cenarioFloor = new Wall(0, -10*grossura, 0, 10*comprimento, grossura, 10*profundidade, 1/*60*/, 1, 1/*80*/,  0, 1,  0);

    int cenarioHeight = 199.9;
    int cenarioSize = 300;
    GLfloat diffuse[4] = { 1.0, 1.0, 1.0, 1.0};
    LoadStaticObject("cenario1", 0, cenarioHeight, 0, cenarioSize, false, 1, diffuse);
    LoadStaticObject("cenario2", 0, cenarioHeight, 0, cenarioSize, false, 4, diffuse);
    LoadStaticObject("cenario3", 0, cenarioHeight, 0, cenarioSize, false, 1, diffuse);
    LoadStaticObject("cenario4", 0, cenarioHeight, 0, cenarioSize, true, 1, diffuse);
    LoadStaticObject("cenario5", 0, cenarioHeight, 0, cenarioSize, true, 1, diffuse);

    LoadStaticObject("cenario4reflection", 0, cenarioHeight - 60, 0, cenarioSize, false, 1, diffuse);
    LoadStaticObject("cenario5reflection", 0, cenarioHeight - 57, 0, cenarioSize, false, 1, diffuse);
    LoadStaticObject("cenarioLightsReflection", 0, cenarioHeight - 53, 0, cenarioSize, false, 4, diffuse);

    LoadStaticObject("cenario6", 0, cenarioHeight, 0, cenarioSize, false, 2, diffuse);
    LoadStaticObject("cenario7", 0, cenarioHeight, 0, cenarioSize, false, 4, diffuse);
    LoadStaticObject("cenarioLights", 0, cenarioHeight, 0, cenarioSize, false, 4, diffuse);

    object1 = new Ball(100, 8, 100, 30);
    cenarioCollider1 = new SphereCollider(object1, 30, 0, 0, 0);
    object2 = new Ball(-100, 8, 100, 30);
    cenarioCollider2 = new SphereCollider(object2, 30, 0, 0, 0);
    object3 = new Ball(-100, 8, -100, 30);
    cenarioCollider3 = new SphereCollider(object3, 30, 0, 0, 0);
    object4 = new Ball(100, 8, -100, 30);
    cenarioCollider4 = new SphereCollider(object4, 30, 0, 0, 0);
}

void CenarioDraw()
{
    if(!lowGraphcis){
        DrawStaticObjects();

    } else{

        frontWall->Getcollider()->DrawCollider();
        backWall->Getcollider()->DrawCollider();
        leftWall->Getcollider()->DrawCollider();
        rightWall->Getcollider()->DrawCollider();

        cenarioCollider1->DrawCollider();
        cenarioCollider2->DrawCollider();
        cenarioCollider3->DrawCollider();
        cenarioCollider4->DrawCollider();


        //Chão
        floorWall->Draw();
        //Parede fontral, na frente do player1
        frontWall->Draw();
        //Parede traseira, atrás do player2
        backWall->Draw();
        //Parede lateral esquerda
        leftWall->Draw();
        //Parede lateral direita
        rightWall->Draw();

        cenarioFloor->Draw();
    }

}

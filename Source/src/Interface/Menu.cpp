#include "Menu.h"
#include <stdio.h>
#include <string.h>
#include <GL/glut.h>

Menu::Menu(float R, float G, float B, int items, int itemWitdh, int itemHeight, char *s[], bool fullscreen)
{

    int font = 5; // tipo referente a fonte GLUT_BITMAP_9_BY_15
    Setwidth(glutGet((fullscreen) ? GLUT_SCREEN_WIDTH : GLUT_WINDOW_WIDTH));
    Setheight(glutGet((fullscreen) ? GLUT_SCREEN_HEIGHT : GLUT_WINDOW_HEIGHT));
    SetitemHeight(64);
    SetitemWidth(512);
    Setitems(items);
    SetR(R);
    SetG(G);
    SetB(B);

    std::cout<<"Setting interface..."<< items <<" items"
    <<"\nWidth: "<< glutGet((fullscreen) ? GLUT_SCREEN_WIDTH : GLUT_WINDOW_WIDTH) << "->"<<Getwidth()
    <<"\nHeight: "<< glutGet((fullscreen) ? GLUT_SCREEN_HEIGHT : GLUT_WINDOW_HEIGHT) << "->"<<Getheight()
    <<"\nItems width: "<< itemWidth << "->"<<GetitemWidth()
    <<"\nItems height "<< itemHeight << "->"<<GetitemHeight()
    <<std::endl;

    int fw, fh;
    fw = 9;
    fh = 15
    + 10 /*offset da caixa de seleção do item, 5 pra cima e 5 pra baixo*/
    + 6 /*offset de separação das caixas de seleção dos itens, 3 pra cima e 3 pra baixo*/ ;

    std::string imagePath = "../data/Menu/Buttons/.png";
    std::string selectedImagePath = "../data/Menu/Buttons/Selected.png";

    itemsTextureManager = new glcTexture();            // Criação do arquivo que irá gerenciar as texturas
    itemsTextureManager->SetNumberOfTextures(items);       // Estabelece o número de texturas que será utilizado
    itemsTextureManager->SetWrappingMode(GL_REPEAT);

    selectedItemsTextureManager = new glcTexture();            // Criação do arquivo que irá gerenciar as texturas
    selectedItemsTextureManager->SetNumberOfTextures(items);       // Estabelece o número de texturas que será utilizado
    selectedItemsTextureManager->SetWrappingMode(GL_REPEAT);


    for(int i = 0; i < items; i++){
        glcText temp;
        strlen(s[i]);
        temp.setAll(s[i], font, (-strlen(s[i])*fw + Getwidth())/2, (-items*fh + Getheight())/2 + i*fh, GetR(), GetG(), GetB());
        this->menuItems.push_back(temp);

        //imagePath = "../data/Menu/Buttons/" + s[i] + ".png";
        imagePath.insert(21,s[i]); //insiro na posição exata para tornar o path válido
        std::cout<<"Paths: "<<imagePath<<std::endl;
        itemsTextureManager->CreateTexture(imagePath, i);
        imagePath = "../data/Menu/Buttons/.png";

        selectedImagePath.insert(21,s[i]); //insiro na posição exata para tornar o path válido
        std::cout<<"Paths: "<<selectedImagePath<<std::endl;
        selectedItemsTextureManager->CreateTexture(selectedImagePath, i);
        selectedImagePath = "../data/Menu/Buttons/Selected.png";

    }

    this->SetselectedItem(-1);

}

void Menu::SetPos(bool fullscreen){

    int fw, fh, i;
    fw = 9;
    fh = 15
    + 10 /*offset da caixa de seleção do item, 5 pra cima e 5 pra baixo*/
    + 6 /*offset de separação das caixas de seleção dos itens, 3 pra cima e 3 pra baixo*/ ;

    Setwidth(glutGet((fullscreen) ? GLUT_SCREEN_WIDTH : GLUT_WINDOW_WIDTH));
    Setheight(glutGet((fullscreen) ? GLUT_SCREEN_HEIGHT : GLUT_WINDOW_HEIGHT));

    std::list<glcText>::iterator iter;
        for ( iter = this->menuItems.begin(); iter != this->menuItems.end(); iter++, i++){
        glcText *temp = &*iter;
        char *s = temp->getString();
        strlen((const char*) s);
        temp->setPos((-strlen((const char*) s[i])*fw + Getwidth())/2, (-Getitems()*fh + Getheight())/2 + i*fh);
    }
}

void Menu::textureDraw(){

    int auxHeight = (this->Getheight() - this->Getitems()*this->GetitemHeight()) / 2;

    glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);

//        glMatrixMode(GL_PROJECTION);
//        glLoadIdentity();
//        glOrtho(0.0, glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT), 0.0, -1.0, 1.0);
//        glMatrixMode(GL_MODELVIEW);
//        glLoadIdentity();

        for(int i=0; i<this->Getitems(); i++){
            if(i == this->GetselectedItem()){
                selectedItemsTextureManager->Bind(i);
            } else{
                itemsTextureManager->Bind(i);
            }

            glBegin(GL_QUADS);
                glNormal3f(0.0, 0.0, 1.0);

                glTexCoord2f(0.0, 1.0);
                glVertex3f( (this->Getwidth() - this->GetitemWidth())/2, auxHeight + i*this->GetitemHeight(), 0.0);

                glTexCoord2f(0.0, 0.0);
                glVertex3f((this->Getwidth() - this->GetitemWidth())/2, auxHeight + (i+1)*this->GetitemHeight(), 0.0);

                glTexCoord2f(1.0, 0.0);
                glVertex3f((this->Getwidth() + this->GetitemWidth())/2, auxHeight + (i+1)*this->GetitemHeight(), 0.0);

                glTexCoord2f(1.0, 1.0);
                glVertex3f((this->Getwidth() + this->GetitemWidth())/2, auxHeight + i*this->GetitemHeight(), 0.0);

            glEnd();

            if(i == this->GetselectedItem()){
                selectedItemsTextureManager->Disable();
            } else{
                itemsTextureManager->Disable();
            }
        }
        glDisable(GL_TEXTURE_2D);
        glEnable(GL_LIGHTING);
    glutPostRedisplay();

}

int Menu::texturePassiveSelection(int x, int y){

    int auxHeight = (this->Getheight() - this->Getitems()*this->GetitemHeight()) / 2;
    this->SetselectedItem(-1);
    for(int i=0; i<this->Getitems(); i++){
        /** se a posição passada estiver dentro da caixa de seleção do item */
        if( x > (this->Getwidth() - this->GetitemWidth())/2 &&
            x < (this->Getwidth() + this->GetitemWidth())/2 &&
            y < auxHeight + (i+1)*this->GetitemHeight() &&
            y > auxHeight + i*this->GetitemHeight() ){
                this->SetselectedItem(i);
//                std::cout<<"Selected "<< i
//                <<"square x-min: "<< (this->Getwidth() - this->GetitemWidth())/2
//                << " :: x-max: "<< (this->Getwidth() + this->GetitemWidth())/2
//                << " :: y-min: "<< auxHeight + i*this->GetitemHeight()
//                << " :: y-max: "<< auxHeight + (i+1)*this->GetitemHeight()
//                <<std::endl;
                break;
        }
    }
    return this->GetselectedItem();
}

void Menu::Draw(){

    int str_size = 12, i = 0;
    //SetPos();
    glDisable(GL_LIGHTING);
    std::list<glcText>::iterator iter;
    for ( iter = this->menuItems.begin(); iter != this->menuItems.end(); iter++, i++){
        glcText *temp = &*iter;
        if(i == this->GetselectedItem()){
            temp->setColor(1.0, 1.0, 0.0);
        } else{
            temp->setColor(this->GetR(), this->GetG(), this->GetB());
        }
        temp->render();
        char *s = temp->getString();
        str_size = strlen((const char*) s);
        glBegin(GL_LINE_LOOP);
            glVertex3f(temp->getPosX() - 5.0, temp->getPosY() + 5.0, 0.0);
            glVertex3f(temp->getPosX() - 5.0, temp->getPosY() - 20, 0.0);
            glVertex3f(temp->getPosX() +str_size*9+5, temp->getPosY() - 20, 0.0);
            glVertex3f(temp->getPosX() +str_size*9+5, temp->getPosY() + 5.0, 0.0);
        glEnd();
    }
    glEnable(GL_LIGHTING);
}

int Menu::PassiveSelection(int x, int y){

    int str_size = 12, i = 0;
    this->SetselectedItem(-1);
    std::list<glcText>::iterator iter;
    for ( iter = this->menuItems.begin(); iter != this->menuItems.end(); iter++, i++){
        glcText *temp = &*iter;
        char *s = temp->getString();
        str_size = strlen((const char*) s);
        /** se a posição passada estiver dentro da caixa de seleção do item */
        if( x > temp->getPosX() - 5.0 &&
            x < temp->getPosX() + str_size * 9.0 + 5.0 &&
            y < temp->getPosY() + 5.0 &&
            y > temp->getPosY() - 20.0 ){
                this->SetselectedItem(i);
                return i;
        }
    }
}

Menu::~Menu()
{
    //dtor
}

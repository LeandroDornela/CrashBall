#ifndef MENU_H
#define MENU_H
#include "GL/glut.h"
#include <iostream>
#include <list>
#include "../Engine/glcText.h"
#include "../Engine/Material/glcTexture.h"

class Menu
{
    public:
        Menu(float R, float G, float B, int items, int itemWitdh, int itemHeight, char *s[], bool fullscreen);
        virtual ~Menu();
        float GetR() { return R; }
        void SetR(float val) { R = val; }
        float GetG() { return G; }
        void SetG(float val) { G = val; }
        float GetB() { return B; }
        void SetB(float val) { B = val; }
        int Getitems() { return items; }
        void Setitems(int val) { items = val; }
        void SetselectedItem(int val){ selectedItem = val;}
        int GetselectedItem(){ return selectedItem;}
        int PassiveSelection(int x, int y);
        int texturePassiveSelection(int x, int y);
        void SetPos(bool fullscreen);
        void addItem(char *s);
        void textureDraw();
        void Draw();
        int Getwidth() { return width; }
        void Setwidth(int val) { width = val; }
        int Getheight() { return height; }
        void Setheight(int val) { height = val; }
        int GetitemWidth() { return itemWidth; }
        void SetitemWidth(int val) { itemWidth = val; }
        int GetitemHeight() { return itemHeight; }
        void SetitemHeight(int val) { itemHeight = val; }
    private:
        std::list<glcText> menuItems;
        glcTexture *itemsTextureManager;
        glcTexture *selectedItemsTextureManager;
        int selectedItem;
        int items;
        int width;
        int height;
        int itemWidth;
        int itemHeight;
        int pos;
        float R;
        float G;
        float B;
};

#endif // MENU_H

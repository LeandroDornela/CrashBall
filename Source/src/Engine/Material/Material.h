#ifndef MATERIAL_H
#define MATERIAL_H
#include "GL/glut.h"


class Material
{
    public:
        Material();
        virtual ~Material();
        void DefaultMaterial();
        void ShadowMaterial();
        void Player1Material();
        void Iluminating(const GLfloat* ambient, const GLfloat* diffuse, const GLfloat* specular, const GLfloat* shineness);
        void Brass();
        void Bronze();
        void Polished_bronze();
        void Chrome();
        void Copper();
        void Polished_copper();
        void Gold();
        void Polished_gold();
        void Tin();
        void Silver();
        void Polished_silver();
        void Emerald();
        void Jade();
        void Obsidian();
        void Perl();
        void Ruby();
        void Turquoise();
        void Black_plastic();
        void Cyan_plastic();
        void Green_plastic();
        void Red_plastic();
        void White_plastic();
        void Yellow_plastic();
        void Black_rubber();
        void Cyan_rubber();
        void Green_rubber();
        void Red_rubber();
        void White_rubber();
        void Yellow_rubber();



    protected:

    private:
};

#endif // MATERIAL_H

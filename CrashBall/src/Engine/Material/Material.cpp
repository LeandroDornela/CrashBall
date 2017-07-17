#include "Material.h"

Material::Material()
{
    //ctor
}

Material::~Material()
{
    //dtor
}
void Material::Iluminating(const GLfloat* ambient, const GLfloat* diffuse, const GLfloat* specular, const GLfloat* shininess){
    // Define os parametros da superficie a ser iluminada
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}

void Material::DefaultMaterial()
{
    // Material do objeto. Parametros em RGBA
    GLfloat ambient[] = { 0.05, 0.05, 0.05, 1.0 };
    GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat shininess[] = { 256.0f };

    Iluminating(ambient, diffuse, specular, shininess);
}

void Material::ShadowMaterial()
{
    // Material do objeto. Parametros em RGBA
    GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat diffuse[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat specular[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat shininess[] = { 0.0f };

    Iluminating(ambient, diffuse, specular, shininess);
}

void Material::Player1Material()
{
    // Material do objeto. Parametros em RGBA
    GLfloat ambient[] = { 1.0, 0.5, 0.1, 1.0 };
    GLfloat diffuse[] = { 1.0, 0.5, 0.8, 1.0 };
    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat shininess[] = { 50.0f };

    Iluminating(ambient, diffuse, specular, shininess);
}
/**
Above materials copied from http://www.it.hiof.no/~borres/j3d/explain/light/p-materials.html
*/


void Material::Brass()
{
//Brass
const GLfloat mat_ambient[] ={ 0.329412f, 0.223529f, 0.027451f,1.0f };
const GLfloat mat_diffuse[] ={ 0.780392f, 0.568627f, 0.113725f, 1.0f };
const GLfloat mat_specular[] ={ 0.992157f, 0.941176f, 0.807843f, 1.0f };
const GLfloat shine = 27.8974f;

Iluminating(&mat_ambient[0], &mat_diffuse[0], &mat_specular[0], &shine);
}

void Material::Bronze()
{
// Bronze
const GLfloat mat_ambient[] ={ 0.2125f, 0.1275f, 0.054f, 1.0f };
const GLfloat mat_diffuse[] ={ 0.714f, 0.4284f, 0.18144f, 1.0f };
const GLfloat mat_specular[] ={ 0.393548f, 0.271906f, 0.166721f, 1.0f };
const GLfloat shine = 25.6f;

Iluminating(&mat_ambient[0], &mat_diffuse[0], &mat_specular[0], &shine);
}

void Material::Polished_bronze()
{
//Polished bronze
const GLfloat mat_ambient[] ={0.25f, 0.148f, 0.06475f, 1.0f  };
const GLfloat mat_diffuse[] ={0.4f, 0.2368f, 0.1036f, 1.0f };
const GLfloat mat_specular[] ={0.774597f, 0.458561f, 0.200621f, 1.0f };
const GLfloat shine =76.8f ;

Iluminating(&mat_ambient[0], &mat_diffuse[0], &mat_specular[0], &shine);
}

void Material::Chrome()
{
//Chrome
const GLfloat mat_ambient[] ={0.25f, 0.25f, 0.25f, 1.0f  };
const GLfloat mat_diffuse[] ={0.4f, 0.4f, 0.4f, 1.0f };
const GLfloat mat_specular[] ={0.774597f, 0.774597f, 0.774597f, 1.0f };
const GLfloat shine = 76.8f;

Iluminating(&mat_ambient[0], &mat_diffuse[0], &mat_specular[0], &shine);
}

void Material::Copper()
{
//Copper
const GLfloat mat_ambient[] ={ 0.19125f, 0.0735f, 0.0225f, 1.0f };
const GLfloat mat_diffuse[] ={0.7038f, 0.27048f, 0.0828f, 1.0f };
const GLfloat mat_specular[] ={0.256777f, 0.137622f, 0.086014f, 1.0f };
const GLfloat shine = 12.8f;

Iluminating(&mat_ambient[0], &mat_diffuse[0], &mat_specular[0], &shine);
}

void Material::Polished_copper()
{
//Polished copper
const GLfloat mat_ambient[] ={ 0.2295f, 0.08825f, 0.0275f, 1.0f };
const GLfloat mat_diffuse[] ={0.5508f, 0.2118f, 0.066f, 1.0f };
const GLfloat mat_specular[] ={0.580594f, 0.223257f, 0.0695701f, 1.0f };
const GLfloat shine =51.2f ;

Iluminating(&mat_ambient[0], &mat_diffuse[0], &mat_specular[0], &shine);
}

void Material::Gold()
{
//Gold
const GLfloat mat_ambient[] ={ 0.24725f, 0.1995f, 0.0745f, 1.0f };
const GLfloat mat_diffuse[] ={0.75164f, 0.60648f, 0.22648f, 1.0f };
const GLfloat mat_specular[] ={0.628281f, 0.555802f, 0.366065f, 1.0f };
const GLfloat shine =51.2f ;

Iluminating(&mat_ambient[0], &mat_diffuse[0], &mat_specular[0], &shine);
}

void Material::Polished_gold()
{
//Polished gold
const GLfloat mat_ambient[] ={ 0.24725f, 0.2245f, 0.0645f, 1.0f };
const GLfloat mat_diffuse[] ={0.34615f, 0.3143f, 0.0903f, 1.0f };
const GLfloat mat_specular[] ={ 0.797357f, 0.723991f, 0.208006f, 1.0f};
const GLfloat shine =83.2f ;

Iluminating(&mat_ambient[0], &mat_diffuse[0], &mat_specular[0], &shine);
}

void Material::Tin()
{
//Tin
const GLfloat mat_ambient[] ={ 0.105882f, 0.058824f, 0.113725f, 1.0f };
const GLfloat mat_diffuse[] ={0.427451f, 0.470588f, 0.541176f, 1.0f };
const GLfloat mat_specular[] ={0.333333f, 0.333333f, 0.521569f, 1.0f };
const GLfloat shine = 9.84615f;

Iluminating(&mat_ambient[0], &mat_diffuse[0], &mat_specular[0], &shine);
}

void Material::Silver()
{
//Silver
const GLfloat mat_ambient[] ={ 0.19225f, 0.19225f, 0.19225f, 1.0f };
const GLfloat mat_diffuse[] ={ 0.50754f, 0.50754f, 0.50754f, 1.0f};
const GLfloat mat_specular[] ={0.508273f, 0.508273f, 0.508273f, 1.0f };
const GLfloat shine = 51.2f;

Iluminating(&mat_ambient[0], &mat_diffuse[0], &mat_specular[0], &shine);
}

void Material::Polished_silver()
{
//Polished silver
const GLfloat mat_ambient[] ={ 0.23125f, 0.23125f, 0.23125f, 1.0f };
const GLfloat mat_diffuse[] ={0.2775f, 0.2775f, 0.2775f, 1.0f };
const GLfloat mat_specular[] ={0.773911f, 0.773911f, 0.773911f, 1.0f };
const GLfloat shine =89.6f ;

Iluminating(&mat_ambient[0], &mat_diffuse[0], &mat_specular[0], &shine);
}

void Material::Emerald()
{
//Emerald
const GLfloat mat_ambient[] ={ 0.0215f, 0.1745f, 0.0215f, 0.55f };
const GLfloat mat_diffuse[] ={0.07568f, 0.61424f, 0.07568f, 0.55f };
const GLfloat mat_specular[] ={0.633f, 0.727811f, 0.633f, 0.55f };
const GLfloat shine = 76.8f;

Iluminating(&mat_ambient[0], &mat_diffuse[0], &mat_specular[0], &shine);
}

void Material::Jade()
{
//Jade
const GLfloat mat_ambient[] ={ 0.135f, 0.2225f, 0.1575f, 0.95f };
const GLfloat mat_diffuse[] ={0.54f, 0.89f, 0.63f, 0.95f };
const GLfloat mat_specular[] ={0.316228f, 0.316228f, 0.316228f, 0.95f };
const GLfloat shine = 12.8f;

Iluminating(&mat_ambient[0], &mat_diffuse[0], &mat_specular[0], &shine);
}

void Material::Obsidian()
{
//Obsidian
const GLfloat mat_ambient[] ={ 0.05375f, 0.05f, 0.06625f, 0.82f };
const GLfloat mat_diffuse[] ={ 0.18275f, 0.17f, 0.22525f, 0.82f};
const GLfloat mat_specular[] ={0.332741f, 0.328634f, 0.346435f, 0.82f };
const GLfloat shine =38.4f ;

Iluminating(&mat_ambient[0], &mat_diffuse[0], &mat_specular[0], &shine);
}

void Material::Perl()
{
//Perl
const GLfloat mat_ambient[] ={ 0.25f, 0.20725f, 0.20725f, 0.922f };
const GLfloat mat_diffuse[] ={1.0f, 0.829f, 0.829f, 0.922f };
const GLfloat mat_specular[] ={0.296648f, 0.296648f, 0.296648f, 0.922f };
const GLfloat shine = 11.264f;

Iluminating(&mat_ambient[0], &mat_diffuse[0], &mat_specular[0], &shine);
}

void Material::Ruby()
{
//Ruby
const GLfloat mat_ambient[] ={ 0.1745f, 0.01175f, 0.01175f, 0.55f };
const GLfloat mat_diffuse[] ={0.61424f, 0.04136f, 0.04136f, 0.55f };
const GLfloat mat_specular[] ={0.727811f, 0.626959f, 0.626959f, 0.55f };
const GLfloat shine =76.8f ;

Iluminating(&mat_ambient[0], &mat_diffuse[0], &mat_specular[0], &shine);
}

void Material::Turquoise()
{
//Turquoise
const GLfloat mat_ambient[] ={ 0.1f, 0.18725f, 0.1745f, 0.8f };
const GLfloat mat_diffuse[] ={0.396f, 0.74151f, 0.69102f, 0.8f };
const GLfloat mat_specular[] ={0.297254f, 0.30829f, 0.306678f, 0.8f };
const GLfloat shine = 12.8f;

Iluminating(&mat_ambient[0], &mat_diffuse[0], &mat_specular[0], &shine);
}

void Material::Black_plastic()
{
//Black plastic
const GLfloat mat_ambient[] ={0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat mat_diffuse[] ={0.01f, 0.01f, 0.01f, 1.0f };
const GLfloat mat_specular[] ={0.50f, 0.50f, 0.50f, 1.0f };
const GLfloat shine =32.0f ;

Iluminating(&mat_ambient[0], &mat_diffuse[0], &mat_specular[0], &shine);
}

void Material::Cyan_plastic()
{
//Cyan plastic
const GLfloat mat_ambient[] ={ 0.0f,0.1f,0.06f ,1.0f};
const GLfloat mat_diffuse[] ={ 0.0f,0.50980392f,0.50980392f,1.0f};
const GLfloat mat_specular[] ={0.50196078f,0.50196078f,0.50196078f,1.0f };
const GLfloat shine =32.0f ;

Iluminating(&mat_ambient[0], &mat_diffuse[0], &mat_specular[0], &shine);
}

void Material::Green_plastic()
{
//Green plastic
const GLfloat mat_ambient[] ={ 0.0f,0.0f,0.0f,1.0f };
const GLfloat mat_diffuse[] ={ 0.1f,0.35f,0.1f,1.0f};
const GLfloat mat_specular[] ={0.45f,0.55f,0.45f,1.0f };
const GLfloat shine = 32.0f ;

Iluminating(&mat_ambient[0], &mat_diffuse[0], &mat_specular[0], &shine);
}

void Material::Red_plastic()
{
//Red plastic
const GLfloat mat_ambient[] ={ 0.0f,0.0f,0.0f,1.0f };
const GLfloat mat_diffuse[] ={ 0.5f,0.0f,0.0f,1.0f};
const GLfloat mat_specular[] ={0.7f,0.6f,0.6f,1.0f };
const GLfloat shine =32.0f ;

Iluminating(&mat_ambient[0], &mat_diffuse[0], &mat_specular[0], &shine);
}

void Material::White_plastic()
{
//White plastic
const GLfloat mat_ambient[] ={ 0.0f,0.0f,0.0f,1.0f };
const GLfloat mat_diffuse[] ={ 0.55f,0.55f,0.55f,1.0f};
const GLfloat mat_specular[] ={0.70f,0.70f,0.70f,1.0f };
const GLfloat shine = 32.0f ;

Iluminating(&mat_ambient[0], &mat_diffuse[0], &mat_specular[0], &shine);
}

void Material::Yellow_plastic()
{
//Yellow plastic
const GLfloat mat_ambient[] ={0.0f,0.0f,0.0f,1.0f };
const GLfloat mat_diffuse[] ={0.5f,0.5f,0.0f,1.0f };
const GLfloat mat_specular[] ={0.60f,0.60f,0.50f,1.0f };
const GLfloat shine = 32.0f ;

Iluminating(&mat_ambient[0], &mat_diffuse[0], &mat_specular[0], &shine);
}

void Material::Black_rubber()
{
//Black rubber
const GLfloat mat_ambient[] ={ 0.02f, 0.02f, 0.02f, 1.0f };
const GLfloat mat_diffuse[] ={ 0.01f, 0.01f, 0.01f, 1.0f};
const GLfloat mat_specular[] ={0.4f, 0.4f, 0.4f, 1.0f };
const GLfloat shine = 10.0f;

Iluminating(&mat_ambient[0], &mat_diffuse[0], &mat_specular[0], &shine);
}

void Material::Cyan_rubber()
{
//Cyan rubber
const GLfloat mat_ambient[] ={ 0.0f,0.05f,0.05f,1.0f };
const GLfloat mat_diffuse[] ={0.4f,0.5f,0.5f,1.0f };
const GLfloat mat_specular[] ={0.04f,0.7f,0.7f,1.0f };
const GLfloat shine = 10.0f;

Iluminating(&mat_ambient[0], &mat_diffuse[0], &mat_specular[0], &shine);
}

void Material::Green_rubber()
{
//Green rubber
const GLfloat mat_ambient[] ={ 0.0f,0.05f,0.0f,1.0f };
const GLfloat mat_diffuse[] ={ 0.4f,0.5f,0.4f,1.0f};
const GLfloat mat_specular[] ={0.04f,0.7f,0.04f,1.0f };
const GLfloat shine =  10.0f;

Iluminating(&mat_ambient[0], &mat_diffuse[0], &mat_specular[0], &shine);
}

void Material::Red_rubber()
{
//Red rubber
const GLfloat mat_ambient[] ={ 0.05f,0.0f,0.0f,1.0f };
const GLfloat mat_diffuse[] ={ 0.5f,0.4f,0.4f,1.0f};
const GLfloat mat_specular[] ={ 0.7f,0.04f,0.04f,1.0f};
const GLfloat shine = 10.0f;

Iluminating(&mat_ambient[0], &mat_diffuse[0], &mat_specular[0], &shine);
}

void Material::White_rubber()
{
//White rubber
const GLfloat mat_ambient[] ={ 0.05f,0.05f,0.05f,1.0f };
const GLfloat mat_diffuse[] ={ 0.5f,0.5f,0.5f,1.0f};
const GLfloat mat_specular[] ={ 0.7f,0.7f,0.7f,1.0f};
const GLfloat shine = 10.0f;

Iluminating(&mat_ambient[0], &mat_diffuse[0], &mat_specular[0], &shine);
}

void Material::Yellow_rubber()
{
//Yellow rubber
const GLfloat mat_ambient[] ={ 0.05f,0.05f,0.0f,1.0f };
const GLfloat mat_diffuse[] ={0.5f,0.5f,0.4f,1.0f};
const GLfloat mat_specular[] ={0.7f,0.7f,0.04f,1.0f };
const GLfloat shine = 10.0f;

Iluminating(&mat_ambient[0], &mat_diffuse[0], &mat_specular[0], &shine);
}

#include "Ball.h"
#include <stdio.h>
int quick_counter = 2;

Ball::Ball(float x, float y, float z, float r)
{
    this->SetpositionX(x);
    this->SetpositionY(y);
    this->SetpositionZ(z);
    this->Setradius(r);
    this->SetspeedX(0);
    this->SetspeedY(0);
    this->SetspeedZ(0);
    this->collider = new SphereCollider(this, r, 0, 0, 0);
}

Ball::~Ball()
{
    //dtor
}

/**
    Método efeciente para desenho do círculo foi baseado no código desta página:
    http://slabode.exofire.net/circle_draw.shtml
    Acessado em 14/05/2016
**/
void Ball::Draw()
{

    /*
    glLineWidth(1);
    glColor3f (1.0, 0.5, 0.0);

    float theta = 2 * 3.1415926 / float(CIRCLE_PRECISION);
	float tangetial_factor = tanf(theta);//calculate the tangential factor

	float radial_factor = cosf(theta);//calculate the radial factor

	float x = this->Getradius();//we start at angle = 0

	float y = 0;

	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
        for(int i = 0; i < CIRCLE_PRECISION; i++)
        {
            glVertex2f(x + this->GetpositionX(), y + this->GetpositionY());//output vertex
            //calculate the tangential vector
            //remember, the radial vector is (x, y)
            //to get the tangential vector we flip those coordinates and negate one of them
            float tx = -y;
            float ty = x;
            //add the tangential vector
            x += tx * tangetial_factor;
            y += ty * tangetial_factor;
            //correct using the radial factor
            x *= radial_factor;
            y *= radial_factor;
        }
	glEnd();
	glEnable(GL_LIGHTING);
	*/
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
        glTranslatef(this->GetpositionX(), this->GetpositionY(), this->GetpositionZ());
        glutSolidSphere(this->Getradius(), 60, 20);
    glPopMatrix();
    //this->collider->DrawCollider();
    glutPostRedisplay();
}

void Ball::Move()
{
    if(this->GetpositionY() > 8)
    {
        this->SetspeedY(this->GetspeedY() - 0.1);
    }
    else
    {
        this->SetpositionY(8);
        int vel = -this->GetspeedY()/2;
        this->SetspeedY(vel);
    }
    this->SetpositionX(this->GetpositionX() + this->GetspeedX());
    this->SetpositionY(this->GetpositionY() + this->GetspeedY());
    this->SetpositionZ(this->GetpositionZ() + this->GetspeedZ());
    this->collider->Move(this->GetpositionX(), this->GetpositionY(), this->GetpositionZ());
}

/**
    Atualiza velocidade da bolinha até o limite de 2px por update
**/
void Ball::SpeedUp(int sec, int level)
{
    if(sec % 10 == 10 - 4*level && sqrt( pow(this->GetspeedZ(), 2) + pow(this->GetspeedX(), 2) ) < 20 + 10*level){
        this->SetspeedZ(this->GetspeedZ() + 0.0005*this->GetspeedZ());
        this->SetspeedX(this->GetspeedX() + 0.0005*this->GetspeedX());
    }
}

/**
    Detecta a colisao com cada uma das paredes com uma correcao
    para as bordas e retorna a id da parede onde bateu
**/
int Ball::WallCollision(int width, int height)
{
    if((this->GetpositionX() - this->Getradius()) < 0 +50){
        /** Colidiu com a lateral esquerda **/
        this->SetspeedX(-this->GetspeedX());
        this->SetpositionX(this->Getradius()+50);
        return 0;
    }
    if((this->GetpositionX() + this->Getradius()) > width -50){
        /** Colidiu com a lateral direita **/
        this->SetspeedX(-this->GetspeedX());
        this->SetpositionX(width - this->Getradius()-50);
        return 1;
    }
    if((this->GetpositionY() + this->Getradius()) > height -50){
        /** Bateu na parte de cima **/
        this->SetspeedY(-this->GetspeedY());
        this->SetpositionY(height - this->Getradius()-50);
        return 2;
    }
    if((this->GetpositionY() - this->Getradius()) < 0 +50){
        /** Bateu na parte de baixo **/
        this->SetspeedY(-this->GetspeedY());
        this->SetpositionY(this->Getradius()+50);
        return 3;
    }
    return -1;
}

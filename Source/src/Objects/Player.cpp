#include "Player.h"
#include <stdio.h>

/**
    Valores 0, 1, 2, 3 indicam repectivamente lados frente, trás, esquerda, direita
**/
Player::Player(float r, Wall* atWall)
{
    this->Setwall(atWall);
    this->Setradius(r);
    this->Setscore(0);
    this->SetspeedX(0);
    this->SetspeedY(0);

    if(this->Getwall()->GetpositionX() == 0){
        if(this->Getwall()->GetpositionZ() < 0){
            this->Setside(0);
        } else{
            this->Setside(1);
        }
    } else {
        if(this->Getwall()->GetpositionX() < 0){
            this->Setside(2);
        } else{
            this->Setside(3);
        }
    }
    switch(this->Getside()){
        case 0:
            this->SetpositionX(this->Getwall()->GetpositionX());
            this->SetpositionY(this->Getwall()->GetpositionY());
            this->SetpositionZ(this->Getwall()->GetpositionZ());
            break;
        case 1:
            this->SetpositionX(this->Getwall()->GetpositionX());
            this->SetpositionY(this->Getwall()->GetpositionY());
            this->SetpositionZ(this->Getwall()->GetpositionZ());
            break;
        case 2:
            this->SetpositionX(this->Getwall()->GetpositionX() - this->Getradius() * sinf(M_PI_4) + this->Getwall()->Getwidth()/2);
            this->SetpositionY(this->Getwall()->GetpositionY());
            this->SetpositionZ(this->Getwall()->GetpositionZ());
            break;
        case 3:
            this->SetpositionX(this->Getwall()->GetpositionX() + this->Getradius() * sinf(M_PI_4) - this->Getwall()->Getwidth()/2);
            this->SetpositionY(this->Getwall()->GetpositionY());
            this->SetpositionZ(this->Getwall()->GetpositionZ());
            break;
    }
    this->collider = new SphereCollider(this, r, 0, 0, 0);

}

void Player::Draw()
{
    glLineWidth(1);
    //glColor3fv (this->Getcolor());
    int player_precision = 90;
    float theta = M_PI_2 / float(player_precision-1);
	float tangetial_factor = tanf(theta);//calculate the tangential factor
	float radial_factor = cosf(theta);//calculate the radial factor
	float x = 0, y = 0, z = 0;//we start in a different angle depending on side
	Vertex3d playerCenter;
	playerCenter.SetX(this->GetpositionX());
    playerCenter.SetY(this->GetpositionY());
    playerCenter.SetZ(this->GetpositionZ());

    switch(this->Getside()){
        case 0:
            z = Getradius() * sinf(M_PI_4);
            x = - Getradius() * cosf(M_PI_4);
            playerCenter.SetZ(playerCenter.GetZ() + z);
            break;
        case 1:
            z = - Getradius() * sinf(M_PI_4);
            x = Getradius() * cosf(M_PI_4);
            playerCenter.SetZ(playerCenter.GetZ() + z);
            break;
        case 2:
            z = - Getradius() * cos(M_PI_4);
            x = - Getradius() * sin(M_PI_4);
            playerCenter.SetX(playerCenter.GetX() + x);
            break;
        case 3:
            z = Getradius() * cos(M_PI_4);
            x = Getradius() * sin(M_PI_4);
            playerCenter.SetX(playerCenter.GetX() + x);
            break;
    }

    //glDisable(GL_LIGHTING);
        for(int i = 0; i < player_precision; i++)
        {
            Vertex3d p1, p2, p3, p4, normalFace;

            p1.SetX(x + this->GetpositionX());
            p1.SetZ(z + this->GetpositionZ());

            p4.SetX(x + this->GetpositionX());
            p4.SetZ(z + this->GetpositionZ());

            //calculate the tangential vector
            //remember, the radial vector is (x, y)
            //to get the tangential vector we flip those coordinates and negate one of them
            float tz = -x;
            float tx = +z;
            //add the tangential vector
            z += tz * tangetial_factor;
            x += tx * tangetial_factor;
            //correct using the radial factor
            z *= radial_factor;
            x *= radial_factor;

            p2.SetX(x + this->GetpositionX());
            p2.SetZ(z + this->GetpositionZ());

            p3.SetX(x + this->GetpositionX());
            p3.SetZ(z + this->GetpositionZ());

            playerCenter.SetY(y); //reseto a altura pra voltar a fazer o trinagulo de baixo
            normalFace = CalculateSurfaceNormal(p1, p2, playerCenter, true);

            glBegin(GL_TRIANGLES);
            glNormal3f(normalFace.GetX(), normalFace.GetY(), normalFace.GetZ());

            glVertex3f(p1.GetX(), p1.GetY(), p1.GetZ());//output vertex
            glVertex3f(p2.GetX(), p2.GetY(), p2.GetZ());
            glVertex3f(playerCenter.GetX(), playerCenter.GetY(), playerCenter.GetZ());
            glEnd();

            for(float j = 0;
                j <= this->Getwall()->Getheight() - this->Getwall()->Getheight()/this->Getwall()->Getheight_prec();
                j+= this->Getwall()->Getheight()/this->Getwall()->Getheight_prec()){

                p1.SetY(j);
                p2.SetY(j);
                p3.SetY(j + this->Getwall()->Getheight()/this->Getwall()->Getheight_prec());
                p4.SetY(j + this->Getwall()->Getheight()/this->Getwall()->Getheight_prec());

                normalFace = CalculateSurfaceNormal(p3, p2, p1, true);

                glBegin(GL_QUADS);
                glNormal3f(normalFace.GetX(), normalFace.GetY(), normalFace.GetZ());

                glVertex3f(p1.GetX(), p1.GetY(), p1.GetZ());//output vertex
                glVertex3f(p2.GetX(), p2.GetY(), p2.GetZ());
                glVertex3f(p3.GetX(), p3.GetY(), p3.GetZ());
                glVertex3f(p4.GetX(), p4.GetY(), p4.GetZ());
                glEnd();

            }

            playerCenter.SetY(this->Getwall()->Getheight()); //reseto a altura pra voltar a fazer o trinagulo de cima
            normalFace = CalculateSurfaceNormal(p3, p4, playerCenter, true);

            glBegin(GL_TRIANGLES);
            glNormal3f(normalFace.GetX(), normalFace.GetY(), normalFace.GetZ());

            glVertex3f(p3.GetX(), p3.GetY(), p3.GetZ());//output vertex
            glVertex3f(p4.GetX(), p4.GetY(), p4.GetZ());
            glVertex3f(playerCenter.GetX(), playerCenter.GetY(), playerCenter.GetZ());
            glEnd();

        }

	//glEnable(GL_LIGHTING);
	//this->collider->DrawCollider();
	glutPostRedisplay();
}

/**
    Move o player de um determinado lado com as coordenadas obtidas na funcao
    de motion, com um limite de deslocamento estabelecido
**/
void Player::MouseMovement(int x, int y, int width, int height)
{
   switch(this->Getside())
   {
        case 0:
        case 1:
            /** Pego a posição relativa do mouse em relação a janela e posiciono o player na parede de acordo*/
            this->SetpositionX(this->Getwall()->Getwidth()/2 - ((float)(x)/glutGet(GLUT_WINDOW_WIDTH) * this->Getwall()->Getwidth()));
            if(this->GetpositionX() < (-this->Getwall()->Getwidth()+this->Getwall()->Getdepth())/2 + this->Getradius() * sin(M_PI_4)){
                this->SetpositionX((-this->Getwall()->Getwidth()+this->Getwall()->Getdepth())/2 + this->Getradius() * sin(M_PI_4));
            }
            else if(this->GetpositionX() > (this->Getwall()->Getwidth()-this->Getwall()->Getdepth())/2 - this->Getradius() * sin(M_PI_4)){
                this->SetpositionX((this->Getwall()->Getwidth()-this->Getwall()->Getdepth())/2 - this->Getradius() * sin(M_PI_4));
            }
        break;
        case 2:
        case 3:
            this->SetpositionZ(this->GetpositionZ() - (this->GetpositionZ() - y)/this->GetspeedZ());
            if(this->GetpositionZ() < -this->Getwall()->Getdepth()/2 + this->Getradius() * cos(M_PI_4)){
                this->SetpositionZ(-this->Getwall()->Getdepth()/2 + this->Getradius() * cos(M_PI_4));
            }
            else if(this->GetpositionZ() > this->Getwall()->Getdepth()/2 - this->Getradius() * cos(M_PI_4)){
                this->SetpositionZ(this->Getwall()->Getdepth()/2 - this->Getradius() * cos(M_PI_4));
            }
            break;
   }
   this->collider->Move(this->GetpositionX(), this->GetpositionY(), this->GetpositionZ());

}

/**
    Movimenta o jogador do computador com um velocidade constante
    acompanhando o deslocamento em y da bola e com atrasos para o
    deslocamento em ambas as coordenadas
**/
void Player::ComputerMovement(Ball* ball, int level)
{
    if(level == 0 && this->GetpositionZ() - ball->GetpositionZ() < 50){
        this->SetpositionX( (ball->GetpositionX() - this->GetpositionX())*0.03 + this->GetpositionX());
    } else if(level == 1 && this->GetpositionZ() - ball->GetpositionZ() < 100){
        this->SetpositionX( (ball->GetpositionX() - this->GetpositionX())*0.05 + this->GetpositionX());
    } else if(level == 2){
        this->SetpositionX( (ball->GetpositionX() - this->GetpositionX())*0.1 + this->GetpositionX());
    }


    if(this->GetpositionX() < (-this->Getwall()->Getwidth()+this->Getwall()->Getdepth())/2 + this->Getradius() * sin(M_PI_4))
    {
        this->SetpositionX((-this->Getwall()->Getwidth()+this->Getwall()->Getdepth())/2 + this->Getradius() * sin(M_PI_4));
    }
    else if(this->GetpositionX() > (this->Getwall()->Getwidth()-this->Getwall()->Getdepth())/2 - this->Getradius() * sin(M_PI_4))
    {
        this->SetpositionX((this->Getwall()->Getwidth()-this->Getwall()->Getdepth())/2 - this->Getradius() * sin(M_PI_4));
    }
    this->collider->Move(this->GetpositionX(), this->GetpositionY(), this->GetpositionZ());
}

/**
    Determina a velocidade do player 2 com base na tecla pressionada
**/
void Player::KeyboardMovement(unsigned char key, bool state)
{

    switch(key)
    {
        case 'w':
        case 'W':
            if(this->Getside() == 2 || this->Getside() == 3)
            {
                if(state)
                {
                    this->SetspeedZ(-4);
                }
                else
                {
                    if(this->GetspeedZ() < 0){
                        this->SetspeedZ(0);
                    }

                }
            }
            break;
        case 's':
        case 'S':
            if(this->Getside() == 2 || this->Getside() == 3)
            {
                if(state)
                {
                    this->SetspeedZ(4);
                }
                else
                {
                    if(this->GetspeedZ() > 0){
                        this->SetspeedZ(0);
                    }

                }
            }
            break;
        case 'a':
        case 'A':
            if(this->Getside() == 0 || this->Getside() == 1)
            {
                if(state)
                {
                    this->SetspeedX(4);
                }
                else
                {
                    if(this->GetspeedX() > 0){
                        this->SetspeedX(0);
                    }
                }
            }
            break;
        case 'd':
        case 'D':
            if(this->Getside() == 0 || this->Getside() == 1)
            {
                if(state)
                {
                    this->SetspeedX(-4);
                }
                else
                {
                    if(this->GetspeedX() < 0){
                        this->SetspeedX(0);
                    }
                }
            }
            break;
    }
}

void Player::Movement(int width, int height)
{
    if(this->Getside() == 0 || this->Getside() == 1)
    {
        this->SetpositionX(this->GetpositionX() + this->GetspeedX());
        if(this->GetpositionX() < (-this->Getwall()->Getwidth()+this->Getwall()->Getdepth())/2 + this->Getradius() * sin(M_PI_4))
        {
            this->SetpositionX((-this->Getwall()->Getwidth()+this->Getwall()->Getdepth())/2 + this->Getradius() * sin(M_PI_4));
        }
        else if(this->GetpositionX() > (this->Getwall()->Getwidth()-this->Getwall()->Getdepth())/2 - this->Getradius() * sin(M_PI_4))
        {
            this->SetpositionX((this->Getwall()->Getwidth()-this->Getwall()->Getdepth())/2 - this->Getradius() * sin(M_PI_4));
        }
    }

    if(this->Getside() == 2 || this->Getside() == 3)
    {
        this->SetpositionZ(this->GetpositionZ() + this->GetspeedZ());
        if(this->GetpositionZ() < -this->Getwall()->Getdepth()/2 + this->Getradius() * cos(M_PI_4))
        {
            this->SetpositionZ(-this->Getwall()->Getdepth()/2 + this->Getradius() * cos(M_PI_4));
        }
        else if(this->GetpositionZ() > this->Getwall()->Getdepth()/2 - this->Getradius() * cos(M_PI_4))
        {
            this->SetpositionZ(this->GetpositionZ() > this->Getwall()->Getdepth()/2 - this->Getradius() * cos(M_PI_4));
        }
    }
    this->collider->Move(this->GetpositionX(), this->GetpositionY(), this->GetpositionZ());

}

Player::~Player()
{
    //dtor
}

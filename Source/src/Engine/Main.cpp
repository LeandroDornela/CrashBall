#include <iostream>
#include <stdio.h>
#include "../Engine/GameManager.h"
#include <GL/glut.h>
#include "GL/glext.h"
#define WIDTH 960
#define HEIGHT 540

GameManager *GM = new GameManager();
bool start = true;

//void display(void);

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_BLEND);
    glEnable(GL_CULL_FACE);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);
}

void idle()
{
    GM->Update();
}

void display(void)
{
  	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  	if(start)
    {
        GM->Start(WIDTH, HEIGHT);
        start = false;
    }
    else
    {
        GM->Draw(false);
        GM->Draw(true);
    }
	glutSwapBuffers();
}

void motion(int x, int y)
{
    GM->Motion(x, y);
}

void passiveMotion(int x, int y)
{
    /** Movimento passivo do mouse pra controlar o rebatedor **/
    GM->MousePassiveControls(x, y);
}

void mouse(int button, int state, int x, int y)
{
	if ( button == GLUT_LEFT_BUTTON)
	{
		if(state == GLUT_DOWN)
		{
			GM->MouseClick(button, x, y);
		}
	}
	if ( button == 3 || button == 4){
        GM->MouseClick(button, x, y);
	}

}

void keyboard(unsigned char key, int x, int y)
{
    switch(key){
        case 27:
        case 'q':
        case 'Q':
            exit(0);
            break;
    }
    /** Jogador2 inicia o movimento do rebatedor **/
    GM->KeyboardControls(key, true);
}

void keyboardUp(unsigned char key, int x, int y)
{
    /** Jogador2 para de mover o rebatedor **/
    GM->KeyboardControls(key, false);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH|GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(150, 150);
    glutCreateWindow("Pong 3D");
    init();
    glutFullScreen();
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMotionFunc(motion);
    glutPassiveMotionFunc(passiveMotion);
    glutMouseFunc(mouse);
    glutIgnoreKeyRepeat(0);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutMainLoop();
    return 0;
}





#ifndef _WIN32
#include <SOIL/SOIL.h>
#else
#include <SOIL.h>
#endif

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


#include "skybox.h"


using namespace std;


bool movimento = true;


void desenhar(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor4f(1, 1, 1, 1);

    glPushMatrix();
        glTranslated(0, 0, -3);
        // glRotated(0,0,0,1);
        glutSolidCube(1);
    glPopMatrix();

    glutSwapBuffers();
}


static void teclado(unsigned char key, int x, int y){
    switch (key){
        case 27 :     // Tecla 'ESC
            exit(0);
            break;
        case ' ':
            if (movimento){
                glLoadIdentity();
                gluLookAt(20, 0, 0, 0, 0, -3, 0, 1, 0);
                movimento = false;
            }
            break;
        case 'a':
            if (!movimento){
                glLoadIdentity();
                gluLookAt(-20, 0, 0, 0, 0, -3, 0, 1, 0);
                movimento = true;
            }
            break;
    }

    glutPostRedisplay();
}

static void atoa(void){
    glutPostRedisplay();
}

void redimensionar (int width, int height){

    glViewport(0, 0, width, height);
    float razaoAspecto = (float) glutGet(GLUT_WINDOW_WIDTH) / (float) glutGet(GLUT_WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0f, razaoAspecto, 1.0, 20.0);
    //glFrustum(-razaoAspecto, razaoAspecto, -1.0, 1.0, 2.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("O Garra!");
    glutReshapeFunc(redimensionar);
    glutDisplayFunc(desenhar);
    glutKeyboardFunc(teclado);
    glutIdleFunc(atoa);

    glClearColor(0,0,0,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glutMainLoop();

    return 0;
}

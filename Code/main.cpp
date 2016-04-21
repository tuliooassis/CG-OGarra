#ifndef _WIN32
#include <SOIL/SOIL.h>
#else
#include <SOIL.h>
#endif

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <math.h>
#include <iostream>

#include "skybox.h"
#include "garra.h"
using namespace std;

struct posicao posicaoSkyboxMachine;
struct posicao posicaoSkyboxWorld;
struct garra posicaoGarra;
double angle = -.8;
double anguloOmbro = 0;
double anguloCutuvelo = 0;

enum { top = 0 };
GLint texturaSkyboxWorld[6];

void desenha (){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor4f(1, 1, 1, 1);
    glLoadIdentity();
    gluLookAt(5*sin(angle) + 5*cos(angle), 1, 5*cos(angle) - 5*sin(angle), 0, 0, posicaoGarra.z, 0, 1, 0);

    drawGarra (&posicaoGarra, &anguloOmbro, &anguloCutuvelo);
    drawSkyboxWorld(&posicaoSkyboxWorld, texturaSkyboxWorld);
    drawSkyboxMachine(&posicaoSkyboxMachine);


    glutSwapBuffers();
}

void teclado (unsigned char key, int x, int y){
    switch (key){
        case 27 :     // Tecla 'ESC
            exit(0);
            break;
        case ' ':
            if (angle >= -2)
                angle -= .2;
            //cout << angle << endl;
            break;
        case 'a':
            if (angle <= .4)
                angle += .2;
            //cout << angle << endl;
            break;
        case 'O':
            anguloOmbro++;
            break;
        case 'o':
            anguloOmbro--;
            break;
        case 'C':
            anguloCutuvelo++;
            break;
        case 'c':
            anguloCutuvelo--;
            break;
    }
    glutPostRedisplay();
}

static void atualizaCena(int idx){
    glutTimerFunc(33, atualizaCena, 0);
    glutPostRedisplay();
}


void init (){
    //Instancia variáveis do skybox da maquina
    posicaoSkyboxMachine.zFundo = -12.0;
    posicaoSkyboxMachine.zFrente = -6.0;
    posicaoSkyboxMachine.yCima = 3.0;
    posicaoSkyboxMachine.yBaixo = -4.5;
    posicaoSkyboxMachine.xInicio = -3;
    posicaoSkyboxMachine.xFim = 3;

    //Instancia variáveis doskybox do mundo
    posicaoSkyboxWorld.zFundo = -20.0;
    posicaoSkyboxWorld.zFrente = 0.0;
    posicaoSkyboxWorld.yCima = 5.0;
    posicaoSkyboxWorld.yBaixo = -5.0;
    posicaoSkyboxWorld.xInicio = -7.0;
    posicaoSkyboxWorld.xFim = 7.0;

    //Instancia variáveis garra
    posicaoGarra.x = 0.0;
    posicaoGarra.y = 0.0;
    posicaoGarra.z = -5.0;


    texturaSkyboxWorld[top] = SOIL_load_OGL_texture(
        "./img/ceil.jpeg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
	);
    texturaSkyboxWorld[1] = SOIL_load_OGL_texture(
        "./img/floor.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    texturaSkyboxWorld[2] = SOIL_load_OGL_texture(
        "./img/arcade.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
}

void redimensiona (int width, int height){

    glViewport(0, 0, width, height);
    float razaoAspecto = (float) glutGet(GLUT_WINDOW_WIDTH) / (float) glutGet(GLUT_WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0f, razaoAspecto, 1.0, 50.0);
    //glFrustum(-razaoAspecto, razaoAspecto, -1.0, 1.0, 2.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitWindowSize(1000,700);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("O Garra!");
    init();
    glutReshapeFunc(redimensiona);
    glutDisplayFunc(desenha);
    glutKeyboardFunc(teclado);
    glutTimerFunc(0, atualizaCena, 0);
    glClearColor(0,0,0,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    glutMainLoop();

    return 0;
}

#ifndef _WIN32
#include <SOIL/SOIL.h>
#else
#include <SOIL.h>
#endif

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "skybox.h"

using namespace std;

struct posicao posicaoSkyboxMachine;
struct posicao posicaoSkyboxWorld;

void desenha (){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor4f(1, 1, 1, 1);
    drawSkyboxWorld(&posicaoSkyboxWorld);
    drawSkyboxMachine(&posicaoSkyboxMachine);


    glutSwapBuffers();
}

void teclado (unsigned char key, int x, int y){
    switch (key){
        case 27 :     // Tecla 'ESC
            exit(0);
            break;
        case ' ':
            glLoadIdentity();
            gluLookAt(5, 1, 0, 0, 0, posicaoSkyboxMachine.zFundo, 0, 1, 0);
            break;
        case 'a':
            glLoadIdentity();
            gluLookAt(-5, 1, 0, 0, 0, posicaoSkyboxMachine.zFundo, 0, 1, 0);
            break;
    }
    glutPostRedisplay();
}

static void atoa(void){
    glutPostRedisplay();
}

void init (){
    //Instancia variáveis do skybox da maquina
    posicaoSkyboxMachine.zFundo = -15.0;
    posicaoSkyboxMachine.zFrente = -10.0;
    posicaoSkyboxMachine.yCima = 3.0;
    posicaoSkyboxMachine.yBaixo = -3.0;
    posicaoSkyboxMachine.xInicio = -2.5;
    posicaoSkyboxMachine.xFim = 2.5;

    //Instancia variáveis doskybox do mundo
    posicaoSkyboxWorld.zFundo = -20.0;
    posicaoSkyboxWorld.zFrente = -1.0;
    posicaoSkyboxWorld.yCima = 5.0;
    posicaoSkyboxWorld.yBaixo = -5.0;
    posicaoSkyboxWorld.xInicio = -5.0;
    posicaoSkyboxWorld.xFim = 5.0;
}

void redimensiona (int width, int height){

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
    glutReshapeFunc(redimensiona);
    glutDisplayFunc(desenha);
    glutKeyboardFunc(teclado);
    glutIdleFunc(atoa);
    init();
    glClearColor(0,0,0,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glutMainLoop();

    return 0;
}

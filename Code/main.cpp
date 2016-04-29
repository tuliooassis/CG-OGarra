#ifndef _WIN32
#include <SOIL/SOIL.h>
#else
#include <SOIL.h>
#endif

#include <GL/glew.h>
#include <GL/freeglut.h>
// #include <SFML/Audio.hpp>

#include <math.h>
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "skybox.h"
#include "garra.h"
#include "objects.h"
#include "menu.h"

float colorFog[] = { 1.0f, 1.0f, 1.0f };

//var arq objects


#define qtdObjects 10

using namespace std;
// configura alguns parâmetros do modelo de iluminação: FONTE DE LUZ
const GLfloat light_ambient[]  = { 0.1f, 0.1f, 0.1f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

// configura alguns parâmetros do modelo de iluminação: MATERIAL
const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 50.0f };

const GLfloat light_diffuse1[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_ambient1[]   = { 0.3f, 0.3f, 0.3f, 1.0f };
const GLfloat light_position1[] = { 0.0f, 3.0f, -1.0f, 0.0f };


struct texturas texturaSkyboxWorld;
struct objects objects[qtdObjects];
struct posicao posicaoSkyboxMachine;
struct posicao posicaoSkyboxWorld;
struct garra posicaoGarra;
struct menu menu[4];
struct ponto mouse;

double angle = -.8;

float anguloRaiz=-30;
float anguloCutuvelo=30;
float anguloOmbro=30;



int situation = menuGeral;

void init (){

    //Instancia variáveis do skybox da maquina
    posicaoSkyboxMachine.zFundo = -10.5;
    posicaoSkyboxMachine.zFrente = -5.5;
    posicaoSkyboxMachine.yCima = 3.0;
    posicaoSkyboxMachine.yBaixo = -4.9;
    posicaoSkyboxMachine.xInicio = -3.5;
    posicaoSkyboxMachine.xFim = 3.5;

    //Instancia variáveis doskybox do mundo
    posicaoSkyboxWorld.zFundo = -20.0;
    posicaoSkyboxWorld.zFrente = 0.0;
    posicaoSkyboxWorld.yCima = 5.0;
    posicaoSkyboxWorld.yBaixo = -5.0;
    posicaoSkyboxWorld.xInicio = -7.0;
    posicaoSkyboxWorld.xFim = 7.0;

    //Instancia variáveis garra
    posicaoGarra.posicao.x = -1.5;
    posicaoGarra.posicao.y = 2.75;
    posicaoGarra.posicao.z = -8.5;
    posicaoGarra.distanciaBasePerninha = 1.5;

    posicaoGarra.desceGarra = false;
    posicaoGarra.moveGarraBase = false;
    posicaoGarra.abrindoGarra = false;
    posicaoGarra.fechandoGarra = false;

    posicaoGarra.xo = -1.5;
    posicaoGarra.yo = 2.75;
    posicaoGarra.zo = -8.0;

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glLightfv(GL_LIGHT1, GL_AMBIENT,  light_ambient1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE,  light_diffuse1);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position1);


    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    initObjects(qtdObjects, objects, &posicaoSkyboxMachine);
    initSkybox(&texturaSkyboxWorld);
    initFog(colorFog);
    initMenu(menu);
}


void redimensiona (int width, int height){
    glViewport(0, 0, width, height);
    float razaoAspecto = (float) glutGet(GLUT_WINDOW_WIDTH) / (float) glutGet(GLUT_WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    switch (situation) {
        case menuGeral:
            glOrtho(razaoAspecto*-5, razaoAspecto*5, -5, 5, -3.0, 3.0);
            break;
        case game:
            gluPerspective(50.0f, razaoAspecto, 1.0, 30.0);
            //glFrustum(-razaoAspecto, razaoAspecto, -1.0, 1.0, 2.0, 100.0);
            break;
        }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void desenha (){
    double razaoAspecto = (float) glutGet(GLUT_WINDOW_WIDTH) / (float) glutGet(GLUT_WINDOW_HEIGHT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor4f(1, 1, 1, 1);
    glLoadIdentity();
    switch (situation) {
        case menuGeral:
            drawMenu(menu, situation);
            break;

        case game:
            if (posicaoGarra.desceGarra)
                gluLookAt(posicaoGarra.posicao.x, 10,  posicaoGarra.posicao.x, posicaoGarra.posicao.x, posicaoGarra.posicao.y, posicaoGarra.posicao.z, 0, 1, 0);
            else
                gluLookAt(5*sin(angle) + 5*cos(angle), 1, 5*cos(angle) - 5*sin(angle), 0, 0, -9.0, 0, 1, 0);

            drawGarra (&posicaoGarra, anguloRaiz, anguloCutuvelo, anguloOmbro);
            drawSkyboxWorld(&posicaoSkyboxWorld, &texturaSkyboxWorld);
            drawObjects(qtdObjects, objects);
            drawMachine(&posicaoSkyboxMachine);

            break;

        default:
            break;
    }


    glutSwapBuffers();
}

void teclado (unsigned char key, int x, int y){
    if (!posicaoGarra.desceGarra){ // se a garra n estiver descendo
        switch (key){
            case 'm':
                if (situation != menuGeral)
                    situation = menuGeral;
                else
                    situation = game;
                redimensiona((int) glutGet(GLUT_WINDOW_WIDTH), (int) glutGet(GLUT_WINDOW_HEIGHT));
                break;
            case 27 :     // Tecla 'ESC
                exit(0);
                break;
            case 'd':
                    if (angle < 0.5)
                        angle += 0.05;
                //cout << angle << endl;
                break;
            case 'a':
                    if (angle > -2)
                        angle -= 0.05;
                //cout << angle << endl;
                break;
            case 'O':
                    anguloOmbro++;
                // cout << anguloOmbro << " " << anguloCutuvelo << endl;
                break;
            case 'o':
                    anguloOmbro--;
                break;
            case 'C':
                    anguloCutuvelo++;
                // cout << anguloOmbro << " " << anguloCutuvelo << endl;
                break;
            case 'c':
                    anguloCutuvelo--;
                break;
            case ' ':
                posicaoGarra.abrindoGarra = true;
                break;
            case 'f':
                if (glIsEnabled(GL_FOG))
                    glDisable(GL_FOG);
                else
                    glEnable(GL_FOG);
                break;
        }
    }
    glutPostRedisplay();
}

void tecladoSpecial (int key, int x, int y){
    if (!posicaoGarra.desceGarra && !posicaoGarra.moveGarraBase){ // se a garra n estiver descendo
        switch (situation) {
            case menuGeral:
                if (key == GLUT_KEY_UP){
                    menu[situation].positionTextureMenu += menu[situation].incrementoTextureMenu;
                    if (menu[situation].positionTextureMenu >= 1.0)
                        menu[situation].positionTextureMenu = 0;
                }
                break;
            case game:
                if (key == GLUT_KEY_UP){
                    for (int i = 0; i < 4; i++){
                        if (posicaoGarra.posicao.z-1.5 > posicaoSkyboxMachine.zFundo)
                        posicaoGarra.posicao.z -= 0.1;
                    }
                }
                else if (key == GLUT_KEY_DOWN){
                    for (int i = 0; i < 4; i++){
                        if (posicaoGarra.posicao.z+1.5 < posicaoSkyboxMachine.zFrente)
                        posicaoGarra.posicao.z += 0.1;
                    }
                }
                else if (key == GLUT_KEY_LEFT){
                    for (int i = 0; i < 4; i++){
                        if (posicaoGarra.posicao.x+1.5 < posicaoSkyboxMachine.xFim)
                            posicaoGarra.posicao.x += 0.1;
                    }
                }
                else if (key == GLUT_KEY_RIGHT){
                    for (int i = 0; i < 4; i++){
                        if (posicaoGarra.posicao.x-1.5 > posicaoSkyboxMachine.xInicio)
                            posicaoGarra.posicao.x -= 0.1;
                    }
                }
                // cout << posicaoGarra.posicao.x << " "  << posicaoGarra.posicao.y << " " << posicaoGarra.posicao.z << endl;

                break;
        }
    }
    glutPostRedisplay();

}


void atualizaCena(int idx){

    for (int i = 0; i < qtdObjects; i++){
        if (objects[i].situation == pego)
            upObjects (i, objects, &posicaoGarra);

        if (objects[i].situation == solto)
            soltaObjects (objects, qtdObjects, &posicaoSkyboxMachine);
    }

    if (posicaoGarra.moveGarraBase)
        moveGarraBase(&posicaoGarra, qtdObjects, objects);

    if (posicaoGarra.fechandoGarra)
        fechaGarra(&posicaoGarra, &anguloRaiz, &anguloOmbro, &anguloCutuvelo);

    if (posicaoGarra.abrindoGarra)
        abreGarra(&posicaoGarra, &anguloRaiz, &anguloOmbro, &anguloCutuvelo);

    if (posicaoGarra.desceGarra)
        downGarra(&posicaoGarra, objects, qtdObjects);



    // Menu com mouse (valores atribuidos de acordo com limites dos botões)
    if (mouse.porcentagemX > 45 && mouse.porcentagemX < 65 && mouse.porcentagemY > 45 && mouse.porcentagemY < 53)
        menu[situation].positionTextureMenu = 0.0;
    if (mouse.porcentagemX > 45 && mouse.porcentagemX < 65 && mouse.porcentagemY > 59 && mouse.porcentagemY < 67)
        menu[situation].positionTextureMenu = 0.25;
    if (mouse.porcentagemX > 45 && mouse.porcentagemX < 65 && mouse.porcentagemY > 74 && mouse.porcentagemY < 81)
        menu[situation].positionTextureMenu = 0.50;
    if (mouse.porcentagemX > 45 && mouse.porcentagemX < 65 && mouse.porcentagemY > 86 && mouse.porcentagemY < 93)
        menu[situation].positionTextureMenu = 0.75;

    glutPostRedisplay();

    glutTimerFunc(33, atualizaCena, 0);
}

void mouseControl (int x, int y){
    float tamW = (float) glutGet(GLUT_WINDOW_WIDTH);
    float tamH = (float) glutGet(GLUT_WINDOW_HEIGHT);
    mouse.x = x;
    mouse.y = y;
    mouse.porcentagemX = 100 * mouse.x / tamW;
    mouse.porcentagemY = 100 * mouse.y / tamH;

    // cout << mouse.porcentagemX << " " << mouse.porcentagemY << endl;

    if (x > (tamW-tamW/3)){
        if (angle < 0.5)
            angle += 0.05;
    }
    else if (x < tamW/3){
        if (angle > -2)
            angle -= 0.05;
    }
    // cout << angle << endl;
}

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitWindowSize(1000,700);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("O Garra!");
    glutReshapeFunc(redimensiona);
    glutDisplayFunc(desenha);

    glutKeyboardFunc(teclado);
    glutSpecialFunc(tecladoSpecial);

    glutPassiveMotionFunc(mouseControl);
    glutTimerFunc(0, atualizaCena, 0);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    init();

    glutMainLoop();

    return 0;
}

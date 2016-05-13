#ifndef _WIN32
#include <SOIL/SOIL.h>
#else
#include <SOIL.h>
#endif

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SFML/Audio.hpp>

#include <math.h>
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "skybox.h"
#include "garra.h"
#include "objects.h"
#include "menu.h"

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

// configura parametros da segunda luz
const GLfloat light_diffuse1[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_ambient1[]   = { 0.3f, 0.3f, 0.3f, 1.0f };
const GLfloat light_position1[] = { 0.0f, 3.0f, -1.0f, 0.0f };

int qtdObjects = 15; // Quantidade de objetos e vetor de objetos
struct objects objects[15];

float colorFog[] = { 1.0f, 1.0f, 1.0f };
struct texturas texturaSkyboxWorld;
struct posicao posicaoSkyboxMachine;
struct posicao posicaoSkyboxWorld;
struct garra garra;
struct menu menu[10];
struct ponto mouse;

double angle = -.8;
float tempo = 0, tempoContador = 0;

int situation = menuGeral; // situacao do jogo;
int objetosPegos = 0;
bool som = true;
bool moveLeft, moveRight, moveFront, moveBack;
bool somMovimentoAutomatico = false;
bool auxSomMovimentoAut = false;
bool somMovendo = false;
bool somMovendoPlay = false;
bool auxSomLaser = false;
bool auxMusicaAmbiente = false;
sf::Music musicaAmbiente, musicaDescendo, musicaMovendo, musicaLaser;

void init (){
    // Inicia itens
    initMenu(menu);
    initFog(colorFog);
    initSkybox(&texturaSkyboxWorld, &posicaoSkyboxMachine, &posicaoSkyboxWorld, &garra);
    initObjects(qtdObjects, objects, &posicaoSkyboxMachine);

    // Carrega sons
    musicaAmbiente.openFromFile("sound/ambiente.wav");
    musicaDescendo.openFromFile("sound/descendo.wav");
    musicaMovendo.openFromFile("sound/movendo.wav");
    musicaLaser.openFromFile("sound/laser.flac");
    // musicaAmbiente
    musicaAmbiente.play();
    musicaAmbiente.setVolume(10);
    musicaAmbiente.setLoop(true);
    musicaLaser.setVolume(50);

    // Luzes
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);


    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);


    glLightfv(GL_LIGHT1, GL_AMBIENT,  light_ambient1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE,  light_diffuse1);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
}


void redimensiona (int width, int height){
    glViewport(0, 0, width, height);
    float razaoAspecto = (float) glutGet(GLUT_WINDOW_WIDTH) / (float) glutGet(GLUT_WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(50.0f, razaoAspecto, 1.0, 30.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void desenha2D (){
    // Ajuda de PedroHLopes & GustavoMarques
    float razaoAspecto = (float) glutGet(GLUT_WINDOW_WIDTH) / (float) glutGet(GLUT_WINDOW_HEIGHT);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode (GL_PROJECTION);
    glPushMatrix();
        glLoadIdentity();
        glOrtho(razaoAspecto * -5, razaoAspecto * 5, -5, 5, -3.0, 3.0);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
            glLoadIdentity();

            switch (situation) {
                case menuGeral:
                    drawMenu(menu, situation);
                    break;
                case game:
                    drawBarraProgresso(qtdObjects, &objetosPegos);
                    break;
                default:
                    desenhaTela(menu, situation);
                    if (situation == carregando){
                        if (tempo > 200){
                            tempo = 0;
                            tempoContador = 0;
                            situation = game;
                        }
                    }
                    break;
            }
            glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 1, 0, 0, 0, -9.0, 0, 1, 0);
}

void desenha (){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor4f(1, 1, 1, 1);
    glLoadIdentity();
    desenha2D();

    switch (situation) {
        case game:
            if (garra.situation == descendo) // visão inclinada ao descer a garra
                gluLookAt(garra.posicao.x, 10,  garra.posicao.x, garra.posicao.x, garra.posicao.y, garra.posicao.z, 0, 1, 0);
            else // visão normal
                gluLookAt(5*sin(angle) + 5*cos(angle), 1, 5*cos(angle) - 5*sin(angle), 0, 0, -9.0, 0, 1, 0);

            drawGarra (&garra);
            drawSkyboxWorld(&posicaoSkyboxWorld, &texturaSkyboxWorld);
            drawObjects(qtdObjects, objects);
            drawMachine(&posicaoSkyboxMachine);
            if (garra.situation == laser){ // Desenha laser
                explode (&garra, objects, &objetosPegos);
            }
            break;
        default:
            break;
    }
    glutSwapBuffers();
}

void teclado (unsigned char key, int x, int y){
    switch (situation){
        case menuGeral:
            if (key == 13){
                if (menu[situation].positionTextureMenu == 0.0)
                    situation = carregando;
                else if (menu[situation].positionTextureMenu == 0.25)
                    situation = menuConfiguracao;
                else if (menu[situation].positionTextureMenu == 0.50)
                    situation = menuCreditos;
                else if (menu[situation].positionTextureMenu == 0.75)
                    exit(0);
            }
            break;
        case pause:
            if (key == 'p' || key == 'P')
                situation = game;
            break;
        case game:
            if (key == '+'){
                if (qtdObjects < 15)
                    qtdObjects++;
            }
            if (key == '-'){
                if (qtdObjects > 0)
                    qtdObjects--;
            }
            if (key == 'd' || key == 'D'){// angulo de visao
                if (angle < 0.5)
                    angle += 0.05;
            }
            if (key == 'a' || key == 'A'){//angulo de visao
                if (angle > -2)
                    angle -= 0.05;
            }
            if (key == ' '){ //desce garra
                if (garra.situation == base)
                    garra.situation = abrindo;
            }
            if (key == 'f' || key == 'F'){ // habilita e desabilita FOG
                if (glIsEnabled(GL_FOG))
                    glDisable(GL_FOG);
                else
                    glEnable(GL_FOG);
            }
            if (key == 'p' || key == 'P') // pausar
                situation = pause;

            if (key == 'r' || key == 'R') // reiniciar
                situation = reiniciar;
            if (key == 27) // sair
                exit(0);
            break;
        case reiniciar:
            if (key == 27)
                situation = game;
            else if (key == 13){
                initObjects(qtdObjects, objects, &posicaoSkyboxMachine);
                qtdObjects = 15;
                objetosPegos = 0;
                situation = game;
            }
            break;
        case menuCreditos:
            if (key == 27)
                situation = menuGeral;
            break;
        case gameover:
            if (key == 13){
                situation = menuGeral;
                initObjects(qtdObjects, objects, &posicaoSkyboxMachine);
            }
            break;
        case menuConfiguracao:
            if (key == 27)
                situation = menuGeral;
            if (key == 's' || key == 'S'){
                if (!som)
                    som = true;
                else
                    som = false;
            }
            if (key == 'f' || key == 'F')
                glutFullScreen();
        default:
            break;
    }
    glutPostRedisplay();
}

void tecladoSpecial (int key, int x, int y){
    switch (situation) {
        case menuGeral: // altera sprite menu
            if (key == GLUT_KEY_DOWN){
                menu[situation].positionTextureMenu += menu[situation].incrementoTextureMenu;
                if (menu[situation].positionTextureMenu >= 1.0)
                    menu[situation].positionTextureMenu = 0;
            }
            else if (key == GLUT_KEY_UP){
                if (menu[situation].positionTextureMenu <= 0.0)
                    menu[situation].positionTextureMenu = 1;
                menu[situation].positionTextureMenu -= menu[situation].incrementoTextureMenu;
            }
            break;
        case game:
            if (garra.situation == base && situation == game){
                if (key == GLUT_KEY_UP){
                    moveFront = true;
                    somMovendo = true;
                }
                else if (key == GLUT_KEY_DOWN){
                    moveBack = true;
                    somMovendo = true;
                }
                else if (key == GLUT_KEY_LEFT){
                    moveLeft = true;
                    somMovendo = true;
                }
                else if (key == GLUT_KEY_RIGHT){
                    moveRight = true;
                    somMovendo = true;
                }
                break;
            }
        default:
            break;
    }
}

void tecladoSpecialOcioso (int key, int x, int y){
    switch (situation) {
        case game:
            if (key == GLUT_KEY_UP)
                moveFront = false;
            else if (key == GLUT_KEY_DOWN)
                moveBack = false;
            else if (key == GLUT_KEY_LEFT)
                moveLeft = false;
            else if (key == GLUT_KEY_RIGHT)
                moveRight = false;
            break;
        default:
            break;
    }
}

void movimentaGarra (){
    // Movimenta a garra quando a tecla está pressionada (de acorco com limites da máquina)
    switch (situation) {
        case game:
            if (moveFront){
                if (garra.posicao.z - 1.5 > posicaoSkyboxMachine.zFundo)
                garra.posicao.z -= 0.09;
            }
            else if (moveBack){
                if (garra.posicao.z + 1.5 < posicaoSkyboxMachine.zFrente)
                garra.posicao.z += 0.09;
            }
            else if (moveLeft){
                if (garra.posicao.x - 1.5 > posicaoSkyboxMachine.xInicio)
                    garra.posicao.x -= 0.09;
            }
            else if (moveRight){
                if (garra.posicao.x + 1.5 < posicaoSkyboxMachine.xFim)
                    garra.posicao.x += 0.09;
            }
            break;
        default:
            break;
    }
}

void atualizaCena(int idx){
    movimentaGarra();
    tentaPegarObjeto (&garra, objects, qtdObjects, &objetosPegos, &somMovimentoAutomatico);
    if (situation == carregando){ // tempo somenta para exibir tela bonita de carregamento
        tempo++; //Soma +1 a cada milisegundo
        if (tempoContador >= 100){ // 100 vezes que passar por aqui terá 1 segundo decorrido
            tempo++; // Soma +1 a cada segundo
            tempoContador = 0;
        }
    }

    if (objetosPegos == qtdObjects){ // se pegar todos os objetos, fim de jogo.
        situation = gameover;
        objetosPegos = 0;
        qtdObjects = 15;
    }
    // Controle do som (movendo)
    if (!moveRight && !moveLeft && !moveBack && !moveFront)
        somMovendo = false;

    if (somMovendo){
        if (!somMovendoPlay && som){
            somMovendoPlay = true;
            musicaMovendo.play();
        }
    }
    else {
        musicaMovendo.stop();
        somMovendoPlay = false;
    }

    // Controle de som subida e descida automático
    if (somMovimentoAutomatico){
        if (!auxSomMovimentoAut && som){
            musicaDescendo.play();
            auxSomMovimentoAut = true;
        }
    }
    else{
        musicaDescendo.stop();
        auxSomMovimentoAut = false;
    }

    //Controle som laser
    if (garra.somLaser){
        if (!auxSomLaser && som){
            auxSomLaser = true;
            musicaLaser.play();
        }
    }
    else {
        musicaLaser.stop();
        auxSomLaser = false;
    }

    // Controle som ambiente
    if (som) {
        if (!auxMusicaAmbiente){
            musicaAmbiente.play();
            auxMusicaAmbiente = true;
        }

    }
    else{
        musicaAmbiente.stop();
        auxMusicaAmbiente = false;
    }

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
    glutTimerFunc(20, atualizaCena, 0);
}

void mouseControl (int x, int y){
    // Recebe tamanho de tela
    float tamW = (float) glutGet(GLUT_WINDOW_WIDTH);
    float tamH = (float) glutGet(GLUT_WINDOW_HEIGHT);
    mouse.x = x;
    mouse.y = y;

    // Calcula valor percentual na tela na posição do mouse
    mouse.porcentagemX = 100 * mouse.x / tamW;
    mouse.porcentagemY = 100 * mouse.y / tamH;

    // Modifica o angulo de visão
    if (situation == game){
        if (x > (tamW-tamW/3)){
            if (angle < 0.5)
                angle += 0.05;
        }
        else if (x < tamW/3){
            if (angle > -2)
                angle -= 0.05;
        }
    }
}

void mouseControlCliqueMenu (int button, int state, int x, int y){
    // Botões clicáveis no menu =o
    if (situation == menuGeral && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        if (menu[situation].positionTextureMenu == 0.0)
            situation = carregando;
        else if (menu[situation].positionTextureMenu == 0.25)
            situation = menuConfiguracao;
        else if (menu[situation].positionTextureMenu == 0.50)
            situation = menuCreditos;
        else if (menu[situation].positionTextureMenu == 0.75)
            exit(0);
    }
}

int main(int argc, char *argv[]){
    srand(time(0));

    glutInit(&argc, argv);
    glutInitWindowSize(1000,700);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("O Garra!");
    glutReshapeFunc(redimensiona);
    glutDisplayFunc(desenha);

    glutKeyboardFunc(teclado);
    glutSpecialFunc(tecladoSpecial);
    glutSpecialUpFunc(tecladoSpecialOcioso);

    glutPassiveMotionFunc(mouseControl);
    glutMouseFunc(mouseControlCliqueMenu);
    glutTimerFunc(0, atualizaCena, 0);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_BLEND);
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glutSetCursor(GLUT_CURSOR_FULL_CROSSHAIR); // Muda desenhinho do mouse

    init();
    glutMainLoop();
    return 0;
}

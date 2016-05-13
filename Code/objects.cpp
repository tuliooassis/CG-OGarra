#ifndef _WIN32
#include <SOIL/SOIL.h>
#else
#include <SOIL.h>
#endif

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "objects.h"
#include "skybox.h"
#include "garra.h"
using namespace std;



bool controleBolasLocalDiferente (int num, struct objects objects[]){
    if (num == 0) // Verifica se a bola está dentro da outra
        return false;
    for (int i = 0; i < num; i++){
        if (sqrt (pow(objects[num].x - objects[i].x, 2) + pow(objects[num].z - objects[i].z, 2) / 2) <= objects[num].raio)
            return true;
    }
    return false;
}

void initObjects (int qtdeObjects, struct objects objects[], struct posicao *posicaoSkyboxMachine){
    float distanciaBorda = 0.6;
    for (int i = 0; i < qtdeObjects; i++){ // distribui as bolinhas aleatóriamente
        objects[i].raio = 0.5;
        do {
            do {
                objects[i].z = -10 + rand()%20;
            } while (objects[i].z - objects[i].raio < posicaoSkyboxMachine->zFundo+distanciaBorda || objects[i].z + objects[i].raio > posicaoSkyboxMachine->zFrente-distanciaBorda);

            do {
                objects[i].x = -10 + rand()%20;
            } while (objects[i].x - objects[i].raio  < posicaoSkyboxMachine->xInicio+distanciaBorda || objects[i].x + objects[i].raio > posicaoSkyboxMachine->xFim-distanciaBorda);

        }while (controleBolasLocalDiferente(i, objects));

        objects[i].y = posicaoSkyboxMachine->yBaixo + objects[i].raio;
        objects[i].situation = padrao;
        objects[i].colisionStatus = false;
        objects[i].r = (float)rand()/(float)(RAND_MAX);
        objects[i].g = (float)rand()/(float)(RAND_MAX);
        objects[i].b = (float)rand()/(float)(RAND_MAX);
        objects[i].o = 1;
    }
}

void drawObjects (int qtdObects, struct objects objects[]){
    for (int i = 0; i < qtdObects; i ++){
        if (objects[i].situation != explodido && objects[i].situation != destruido){
            glPushMatrix();
                glColor4f(objects[i].r, objects[i].g, objects[i].b, objects[i].o);
                glTranslatef(objects[i].x, objects[i].y, objects[i].z);
                glutSolidSphere(objects[i].raio, 100, 100);
            glPopMatrix();
        }
    }
}

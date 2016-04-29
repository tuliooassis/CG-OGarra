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
#include "objects.h"
#include "skybox.h"
#include "garra.h"
using namespace std;

void initObjects (int qtdeObjects, struct objects objects[], struct posicao *posicaoSkyboxMachine){
    srand(time(0));
    for (int i = 0; i < qtdeObjects; i++){
        do {
            objects[i].z = -10 + rand()%20;
        } while (objects[i].z + objects[i].raio < (*posicaoSkyboxMachine).zFundo || objects[i].z + objects[i].raio > (*posicaoSkyboxMachine).zFrente);

        do {
            objects[i].x = -10 + rand()%20;
        } while (objects[i].x + objects[i].raio  < (*posicaoSkyboxMachine).xInicio  || objects[i].x +objects[i].raio > (*posicaoSkyboxMachine).xFim);

        objects[i].y = -4.5;
        objects[i].raio = 0.5;
        objects[i].situation = vivo;
        // cout << objects[i].x << " " << objects[i].y << " " <<  objects[i].z << " " << endl;


        objects[i].r = (float)rand()/(float)(RAND_MAX);
        objects[i].g = (float)rand()/(float)(RAND_MAX);
        objects[i].b = (float)rand()/(float)(RAND_MAX);
        objects[i].o = 1;
    }
}

void upObjects (int numObjeto, struct objects objects[], struct garra *posicaoGarra){
    objects[numObjeto].x = (*posicaoGarra).posicao.x;
    objects[numObjeto].y = (*posicaoGarra).posicao.y - (*posicaoGarra).distanciaBasePerninha - 0.5;
    objects[numObjeto].z = (*posicaoGarra).posicao.z;
}


void drawObjects (int qtdObects, struct objects objects[]){
    for (int i = 0; i < qtdObects; i ++){
        glPushMatrix();
            glColor4f(objects[i].r, objects[i].g, objects[i].b, objects[i].o);
            glTranslatef(objects[i].x, objects[i].y, objects[i].z);
            glutSolidSphere(objects[i].raio, 100, 100);
        glPopMatrix();
    }
}

void soltaObjects (struct objects objects[], int qtdObjects, struct posicao *posicaoSkyboxMachine){
    for (int i = 0; i < qtdObjects; i++){
        if (objects[i].situation == solto && objects[i].y > (*posicaoSkyboxMachine).yBaixo + 1)
            objects[i].y -= 0.1;
        else if (objects[i].situation == solto) {
            objects[i].z = (*posicaoSkyboxMachine).zFrente + 1;
            objects[i].y = (*posicaoSkyboxMachine).yBaixo + 0.5;
            objects[i].x = (*posicaoSkyboxMachine).xInicio - 1.5;

            objects[i].situation = ganho;
        }
    }
}

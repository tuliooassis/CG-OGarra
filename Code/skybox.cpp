#ifndef _WIN32
#include <SOIL/SOIL.h>
#else
#include <SOIL.h>
#endif

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <math.h>
#include <iostream>
#include <stdio.h>

#include "skybox.h"
#include "garra.h"
using namespace std;

void initSkybox (struct texturas *texturaSkyboxWorld, struct posicao *posicaoSkyboxMachine, struct posicao *posicaoSkyboxWorld, struct garra *garra){
    texturaSkyboxWorld->top = SOIL_load_OGL_texture(
        "./img/ceil.jpeg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
	);
    if (texturaSkyboxWorld->top == 0 ) {
        printf("Erro carregando textura: '%s'\n", SOIL_last_result());
    }
    texturaSkyboxWorld->down = SOIL_load_OGL_texture(
        "./img/floor.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    if (texturaSkyboxWorld->down == 0 ) {
        printf("Erro carregando textura: '%s'\n", SOIL_last_result());
    }
    texturaSkyboxWorld->side = SOIL_load_OGL_texture(
        "./img/arcade.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    if (texturaSkyboxWorld->side == 0 ) {
        printf("Erro carregando textura: '%s'\n", SOIL_last_result());
    }

    //Instancia variáveis do skybox da maquina
    posicaoSkyboxMachine->zFundo = -11.5;
    posicaoSkyboxMachine->zFrente = -5.5;
    posicaoSkyboxMachine->yCima = 3.0;
    posicaoSkyboxMachine->yBaixo = -4.9;
    posicaoSkyboxMachine->xInicio = -4.2;
    posicaoSkyboxMachine->xFim = 4.2;

    //Instancia variáveis doskybox do mundo
    posicaoSkyboxWorld->zFundo = -20.0;
    posicaoSkyboxWorld->zFrente = 0.0;
    posicaoSkyboxWorld->yCima = 5.0;
    posicaoSkyboxWorld->yBaixo = -5.0;
    posicaoSkyboxWorld->xInicio = -7.0;
    posicaoSkyboxWorld->xFim = 7.0;

    //Instancia variáveis garra
    garra->posicao.x = -1.5;
    garra->posicao.y = posicaoSkyboxMachine->yCima - .25;
    garra->posicao.z = -8.5;
    garra->alturaGarra = 0.9 + 0.9 * cos(45) + 0.85 * cos (45);
    garra->xo = -1.5;
    garra->yo = 2.75;
    garra->zo = -8.0;
    garra->posicaoDefault = true;
    garra->angulo.raiz = -30;
    garra->angulo.cutuvelo = 30;
    garra->angulo.ombro = 30;
    garra->situation = base;
    garra->tamLaser = 0;
    garra->variacaoTexturaExplosao = 0.1;
    garra->parteAtualTextura = 0;
    garra->somLaser = false;
}

void initFog (float colorFog[]){ // FOG
    glClearColor(colorFog[0], colorFog[1], colorFog[2], 1.0f);
    glFogi(GL_FOG_MODE, GL_EXP);
    glFogfv(GL_FOG_COLOR, colorFog);
    glFogf(GL_FOG_DENSITY, .008f);
    glHint(GL_FOG_HINT, GL_DONT_CARE);
    glFogf(GL_FOG_START, 10.f);
    glFogf(GL_FOG_END, 20.f);
}


void drawMachine (struct posicao *posicao){
    glPushMatrix();
        glColor4f(.2, .2, .2, .5);
        glBegin(GL_QUADS);			// Face posterior
    		glVertex3f(posicao->xFim, posicao->yCima, posicao->zFundo);
    		glVertex3f(posicao->xInicio, posicao->yCima, posicao->zFundo);
    		glVertex3f(posicao->xInicio, posicao->yBaixo, posicao->zFundo);
    		glVertex3f(posicao->xFim, posicao->yBaixo, posicao->zFundo);
    	glEnd();

        glColor4f(1.0, 0.0, 0.0, .5);
    	glBegin(GL_QUADS);			// Face lateral esquerda
    		glVertex3f(posicao->xInicio, posicao->yCima, posicao->zFundo);
    		glVertex3f(posicao->xInicio, posicao->yCima, posicao->zFrente);
    		glVertex3f(posicao->xInicio, posicao->yBaixo, posicao->zFrente);
    		glVertex3f(posicao->xInicio, posicao->yBaixo, posicao->zFundo);
    	glEnd();

        glColor4f(0.0, 1.0, 0.0, .5);
    	glBegin(GL_QUADS);			// Face lateral direita
    		glVertex3f(posicao->xFim, posicao->yCima, posicao->zFundo);
    		glVertex3f(posicao->xFim, posicao->yBaixo, posicao->zFundo);
    		glVertex3f(posicao->xFim, posicao->yBaixo, posicao->zFrente);
    		glVertex3f(posicao->xFim, posicao->yCima, posicao->zFrente);
    	glEnd();

        glColor4f(0.0, 0.0, 1.0, 1.0);
    	glBegin(GL_QUADS);			// Face superior
    		glVertex3f(posicao->xInicio, posicao->yCima, posicao->zFrente);
    		glVertex3f(posicao->xInicio, posicao->yCima, posicao->zFundo);
    		glVertex3f(posicao->xFim, posicao->yCima, posicao->zFundo);
    		glVertex3f(posicao->xFim, posicao->yCima, posicao->zFrente);
    	glEnd();

        glColor4f(.360784314, 0.047058824, 0.545098039, .9);
    	glBegin(GL_QUADS);			// Face inferior
    		glVertex3f(posicao->xInicio, posicao->yBaixo, posicao->zFrente);
    		glVertex3f(posicao->xFim, posicao->yBaixo, posicao->zFrente);
    		glVertex3f(posicao->xFim, posicao->yBaixo, posicao->zFundo);
    		glVertex3f(posicao->xInicio, posicao->yBaixo, posicao->zFundo);
    	glEnd();

        glColor4f(1.0, 1.0, 1.0, 0.5); // Espelho ***** dando errim
            glVertex3f(posicao->xInicio, posicao->yCima, posicao->zFrente);
            glVertex3f(posicao->xInicio, posicao->yBaixo, posicao->zFrente);
            glVertex3f(posicao->xFim, posicao->yBaixo, posicao->zFrente);
            glVertex3f(posicao->xFim, posicao->yCima, posicao->zFrente);
        glEnd();

    glPopMatrix();

}


void drawSkyboxWorld (struct posicao *posicao, struct texturas *texturaSkyboxWorld){ // Colocar texturas do mundo
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);

        glColor4f(1.0, 1.0, 1.0, 1.0);
        glBindTexture(GL_TEXTURE_2D, texturaSkyboxWorld->side);
        glBegin(GL_QUADS);			// Face posterior
    		glTexCoord2f(0, 1); glVertex3f(posicao->xFim, posicao->yCima, posicao->zFundo);
    		glTexCoord2f(1, 1); glVertex3f(posicao->xInicio, posicao->yCima, posicao->zFundo);
    		glTexCoord2f(1, 0); glVertex3f(posicao->xInicio, posicao->yBaixo, posicao->zFundo);
    		glTexCoord2f(0, 0); glVertex3f(posicao->xFim, posicao->yBaixo, posicao->zFundo);
    	glEnd();

        glColor4f(1.0, 1.0, 1.0, 1.0);
        glBindTexture(GL_TEXTURE_2D, texturaSkyboxWorld->side);
    	glBegin(GL_QUADS);			// Face lateral esquerda
    		glTexCoord2f(0, 1); glVertex3f(posicao->xInicio, posicao->yCima, posicao->zFundo);
    		glTexCoord2f(1, 1); glVertex3f(posicao->xInicio, posicao->yCima, posicao->zFrente);
    		glTexCoord2f(1, 0); glVertex3f(posicao->xInicio, posicao->yBaixo, posicao->zFrente);
    		glTexCoord2f(0, 0); glVertex3f(posicao->xInicio, posicao->yBaixo, posicao->zFundo);
    	glEnd();

        glColor4f(1.0, 1.0, 1.0, 1.0);
        glBindTexture(GL_TEXTURE_2D, texturaSkyboxWorld->side);
    	glBegin(GL_QUADS);			// Face lateral direita
    		glTexCoord2f(0, 1); glVertex3f(posicao->xFim, posicao->yCima, posicao->zFundo);
    		glTexCoord2f(0, 0); glVertex3f(posicao->xFim, posicao->yBaixo, posicao->zFundo);
    		glTexCoord2f(1, 0); glVertex3f(posicao->xFim, posicao->yBaixo, posicao->zFrente);
    		glTexCoord2f(1, 1); glVertex3f(posicao->xFim, posicao->yCima, posicao->zFrente);
    	glEnd();

        glColor4f(0.0, 0.0, 1.0, 1.0);
        glBindTexture(GL_TEXTURE_2D, texturaSkyboxWorld->top);
        glBegin(GL_QUADS);			// Face superior
    		glTexCoord2f(1, 0); glVertex3f(posicao->xInicio, posicao->yCima, posicao->zFrente);
    		glTexCoord2f(1, 1); glVertex3f(posicao->xInicio, posicao->yCima, posicao->zFundo);
    		glTexCoord2f(0, 1); glVertex3f(posicao->xFim, posicao->yCima, posicao->zFundo);
    		glTexCoord2f(0, 0); glVertex3f(posicao->xFim, posicao->yCima, posicao->zFrente);
    	glEnd();

        glColor4f(1.0, 1.0, 1.0, 1.0);
        glBindTexture(GL_TEXTURE_2D, texturaSkyboxWorld->down);
    	glBegin(GL_QUADS);			// Face inferior
    		glTexCoord2f(1, 0); glVertex3f(posicao->xInicio, posicao->yBaixo, posicao->zFrente);
    		glTexCoord2f(1, 1); glVertex3f(posicao->xFim, posicao->yBaixo, posicao->zFrente);
    		glTexCoord2f(0, 1); glVertex3f(posicao->xFim, posicao->yBaixo, posicao->zFundo);
    		glTexCoord2f(0, 0); glVertex3f(posicao->xInicio, posicao->yBaixo, posicao->zFundo);
    	glEnd();

        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void drawBarraProgresso (int qtdObects, int *objetosPegos){
    float tamW = 1;
    float tamH = 5;
    float posicaoX = -7;
    float posicaoY = -1;
    float preenchimentoBarraPegos = (float) tamH / qtdObects * (*objetosPegos);

    glColor4f(1, 1, 1, 0.1);
    glPushMatrix();
    glTranslatef(posicaoX, posicaoY, -1);
    glBegin(GL_POLYGON); // Desenha a barra no fundo
        glVertex3f(0, 0, 0);
        glVertex3f(tamW, 0, 0);
        glVertex3f(tamW, tamH, 0);
        glVertex3f(0, tamH, 0);
    glEnd();
    glPopMatrix();

    glColor4f(0, 0, 1, 1.0);
    glPushMatrix();
    glTranslatef(posicaoX, posicaoY, 0);
    glBegin(GL_POLYGON); // Desenha o progresso
        glVertex3f(0, 0, 0);
        glVertex3f(tamW, 0, 0);
        glVertex3f(tamW, preenchimentoBarraPegos, 0);
        glVertex3f(0, preenchimentoBarraPegos, 0);
    glEnd();
    glPopMatrix();
}

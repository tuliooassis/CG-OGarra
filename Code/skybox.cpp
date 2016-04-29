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

using namespace std;

void initSkybox (struct texturas *texturaSkyboxWorld){
    (*texturaSkyboxWorld).top = SOIL_load_OGL_texture(
        "./img/ceil.jpeg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
	);
    if ((*texturaSkyboxWorld).top == 0 ) {
        printf("Erro carregando textura: '%s'\n", SOIL_last_result());
    }
    (*texturaSkyboxWorld).down = SOIL_load_OGL_texture(
        "./img/floor.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    if ((*texturaSkyboxWorld).down == 0 ) {
        printf("Erro carregando textura: '%s'\n", SOIL_last_result());
    }
    (*texturaSkyboxWorld).side = SOIL_load_OGL_texture(
        "./img/arcade.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    if ((*texturaSkyboxWorld).side == 0 ) {
        printf("Erro carregando textura: '%s'\n", SOIL_last_result());
    }
}

void initFog (float colorFog[]){
    glClearColor(colorFog[0], colorFog[1], colorFog[2], 1.0f);
    glFogi(GL_FOG_MODE, GL_EXP);        // Linear, exp. ou exp²
    glFogfv(GL_FOG_COLOR, colorFog);    // Cor
    glFogf(GL_FOG_DENSITY, .008f);     // Densidade
    glHint(GL_FOG_HINT, GL_DONT_CARE);  // Não aplicar se não puder
    glFogf(GL_FOG_START, 10.f);        // Fog Start Depth
    glFogf(GL_FOG_END, 20.f);         // Fog End Depth
    glEnable(GL_FOG);                   // Liga GL_FOG
}


void drawMachine (struct posicao *posicao){

    glPushMatrix();

        glColor4f(1.0, 1.0, 1.0, 1.0);
        glBegin(GL_QUADS);			// Face posterior
    		glVertex3f((*posicao).xFim, (*posicao).yCima, (*posicao).zFundo);
    		glVertex3f((*posicao).xInicio, (*posicao).yCima, (*posicao).zFundo);
    		glVertex3f((*posicao).xInicio, (*posicao).yBaixo, (*posicao).zFundo);
    		glVertex3f((*posicao).xFim, (*posicao).yBaixo, (*posicao).zFundo);
    	glEnd();

        glColor4f(1.0, 0.0, 0.0, 1.0);
    	glBegin(GL_QUADS);			// Face lateral esquerda
    		glVertex3f((*posicao).xInicio, (*posicao).yCima, (*posicao).zFundo);
    		glVertex3f((*posicao).xInicio, (*posicao).yCima, (*posicao).zFrente);
    		glVertex3f((*posicao).xInicio, (*posicao).yBaixo, (*posicao).zFrente);
    		glVertex3f((*posicao).xInicio, (*posicao).yBaixo, (*posicao).zFundo);
    	glEnd();

        glColor4f(0.0, 1.0, 0.0, 1.0);
    	glBegin(GL_QUADS);			// Face lateral direita
    		glVertex3f((*posicao).xFim, (*posicao).yCima, (*posicao).zFundo);
    		glVertex3f((*posicao).xFim, (*posicao).yBaixo, (*posicao).zFundo);
    		glVertex3f((*posicao).xFim, (*posicao).yBaixo, (*posicao).zFrente);
    		glVertex3f((*posicao).xFim, (*posicao).yCima, (*posicao).zFrente);
    	glEnd();

        glColor4f(0.0, 0.0, 1.0, 1.0);
    	glBegin(GL_QUADS);			// Face superior
    		glVertex3f((*posicao).xInicio, (*posicao).yCima, (*posicao).zFrente);
    		glVertex3f((*posicao).xInicio, (*posicao).yCima, (*posicao).zFundo);
    		glVertex3f((*posicao).xFim, (*posicao).yCima, (*posicao).zFundo);
    		glVertex3f((*posicao).xFim, (*posicao).yCima, (*posicao).zFrente);
    	glEnd();

        glColor4f(0.0, 0.0, 0.0, 1.0);
    	glBegin(GL_QUADS);			// Face inferior
    		glVertex3f((*posicao).xInicio, (*posicao).yBaixo, (*posicao).zFrente);
    		glVertex3f((*posicao).xFim, (*posicao).yBaixo, (*posicao).zFrente);
    		glVertex3f((*posicao).xFim, (*posicao).yBaixo, (*posicao).zFundo);
    		glVertex3f((*posicao).xInicio, (*posicao).yBaixo, (*posicao).zFundo);
    	glEnd();

        glColor4f(1.0, 1.0, 1.0, 0.1); // Espelho ***** dando errim
            glVertex3f((*posicao).xInicio, (*posicao).yCima, (*posicao).zFrente);
            glVertex3f((*posicao).xInicio, (*posicao).yBaixo, (*posicao).zFrente);
            glVertex3f((*posicao).xFim, (*posicao).yBaixo, (*posicao).zFrente);
            glVertex3f((*posicao).xFim, (*posicao).yCima, (*posicao).zFrente);
        glEnd();

    glPopMatrix();
}


void drawSkyboxWorld (struct posicao *posicao, struct texturas *texturaSkyboxWorld){ // Colocar texturas do mundo
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);

        glColor4f(1.0, 1.0, 1.0, 1.0);
        glBindTexture(GL_TEXTURE_2D, (*texturaSkyboxWorld).side);
        glBegin(GL_QUADS);			// Face posterior
    		glTexCoord2f(0, 1); glVertex3f((*posicao).xFim, (*posicao).yCima, (*posicao).zFundo);
    		glTexCoord2f(1, 1); glVertex3f((*posicao).xInicio, (*posicao).yCima, (*posicao).zFundo);
    		glTexCoord2f(1, 0); glVertex3f((*posicao).xInicio, (*posicao).yBaixo, (*posicao).zFundo);
    		glTexCoord2f(0, 0); glVertex3f((*posicao).xFim, (*posicao).yBaixo, (*posicao).zFundo);
    	glEnd();

        //
    	// glBegin(GL_QUADS);			// Face frontal
    	// 	glVertex3f(40.0, 40.0, -40.0);
    	// 	glVertex3f(40.0, -40.0, -40.0);
    	// 	glVertex3f(-40.0, -40.0, -40.0);
    	// 	glVertex3f(-40.0, 40.0, -40.0);
    	// glEnd();

        glColor4f(1.0, 1.0, 1.0, 1.0);
        glBindTexture(GL_TEXTURE_2D, (*texturaSkyboxWorld).side);
    	glBegin(GL_QUADS);			// Face lateral esquerda
    		glTexCoord2f(0, 1); glVertex3f((*posicao).xInicio, (*posicao).yCima, (*posicao).zFundo);
    		glTexCoord2f(1, 1); glVertex3f((*posicao).xInicio, (*posicao).yCima, (*posicao).zFrente);
    		glTexCoord2f(1, 0); glVertex3f((*posicao).xInicio, (*posicao).yBaixo, (*posicao).zFrente);
    		glTexCoord2f(0, 0); glVertex3f((*posicao).xInicio, (*posicao).yBaixo, (*posicao).zFundo);
    	glEnd();

        glColor4f(1.0, 1.0, 1.0, 1.0);
        glBindTexture(GL_TEXTURE_2D, (*texturaSkyboxWorld).side);
    	glBegin(GL_QUADS);			// Face lateral direita
    		glTexCoord2f(0, 1); glVertex3f((*posicao).xFim, (*posicao).yCima, (*posicao).zFundo);
    		glTexCoord2f(0, 0); glVertex3f((*posicao).xFim, (*posicao).yBaixo, (*posicao).zFundo);
    		glTexCoord2f(1, 0); glVertex3f((*posicao).xFim, (*posicao).yBaixo, (*posicao).zFrente);
    		glTexCoord2f(1, 1); glVertex3f((*posicao).xFim, (*posicao).yCima, (*posicao).zFrente);
    	glEnd();

        glColor4f(0.0, 0.0, 1.0, 1.0);
        glBindTexture(GL_TEXTURE_2D, (*texturaSkyboxWorld).top);
        glBegin(GL_QUADS);			// Face superior
    		glTexCoord2f(1, 0); glVertex3f((*posicao).xInicio, (*posicao).yCima, (*posicao).zFrente);
    		glTexCoord2f(1, 1); glVertex3f((*posicao).xInicio, (*posicao).yCima, (*posicao).zFundo);
    		glTexCoord2f(0, 1); glVertex3f((*posicao).xFim, (*posicao).yCima, (*posicao).zFundo);
    		glTexCoord2f(0, 0); glVertex3f((*posicao).xFim, (*posicao).yCima, (*posicao).zFrente);
    	glEnd();

        glColor4f(1.0, 1.0, 1.0, 1.0);
        glBindTexture(GL_TEXTURE_2D, (*texturaSkyboxWorld).down);
    	glBegin(GL_QUADS);			// Face inferior
    		glTexCoord2f(1, 0); glVertex3f((*posicao).xInicio, (*posicao).yBaixo, (*posicao).zFrente);
    		glTexCoord2f(1, 1); glVertex3f((*posicao).xFim, (*posicao).yBaixo, (*posicao).zFrente);
    		glTexCoord2f(0, 1); glVertex3f((*posicao).xFim, (*posicao).yBaixo, (*posicao).zFundo);
    		glTexCoord2f(0, 0); glVertex3f((*posicao).xInicio, (*posicao).yBaixo, (*posicao).zFundo);
    	glEnd();

        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

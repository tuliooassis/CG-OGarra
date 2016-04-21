#ifndef _WIN32
#include <SOIL/SOIL.h>
#else
#include <SOIL.h>
#endif

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <math.h>
#include <iostream>
using namespace std;

#include "skybox.h"

void drawSkyboxMachine (struct posicao *posicao){

    glPushMatrix();

        glColor4f(1.0, 1.0, 1.0, 1.0);
        glBegin(GL_QUADS);			// Face posterior
    		glNormal3f(0.0, 0.0, 1.0);	// Normal da face
    		glVertex3f((*posicao).xFim, (*posicao).yCima, (*posicao).zFundo);
    		glVertex3f((*posicao).xInicio, (*posicao).yCima, (*posicao).zFundo);
    		glVertex3f((*posicao).xInicio, (*posicao).yBaixo, (*posicao).zFundo);
    		glVertex3f((*posicao).xFim, (*posicao).yBaixo, (*posicao).zFundo);
    	glEnd();

        // glColor4f(1.0, 1.0, 1.0, 0.2); // Espelho ***** dando errim
    	// glBegin(GL_QUADS);			// Face frontal
    	// 	glNormal3f(0.0, 0.0, -1.0); 	// Normal da face
    	// 	glVertex3f((*posicao).xInicio, (*posicao).yCima, (*posicao).zFrente);
    	// 	glVertex3f((*posicao).xInicio, (*posicao).yBaixo, (*posicao).zFrente);
    	// 	glVertex3f((*posicao).xFim, (*posicao).yBaixo, (*posicao).zFrente);
    	// 	glVertex3f((*posicao).xFim, (*posicao).yCima, (*posicao).zFrente);
    	// glEnd();

        glColor4f(1.0, 0.0, 0.0, 1.0);
    	glBegin(GL_QUADS);			// Face lateral esquerda
    		glNormal3f(-1.0, 0.0, 0.0); 	// Normal da face
    		glVertex3f((*posicao).xInicio, (*posicao).yCima, (*posicao).zFundo);
    		glVertex3f((*posicao).xInicio, (*posicao).yCima, (*posicao).zFrente);
    		glVertex3f((*posicao).xInicio, (*posicao).yBaixo, (*posicao).zFrente);
    		glVertex3f((*posicao).xInicio, (*posicao).yBaixo, (*posicao).zFundo);
    	glEnd();

        glColor4f(0.0, 1.0, 0.0, 1.0);
    	glBegin(GL_QUADS);			// Face lateral direita
    		glNormal3f(1.0, 0.0, 0.0);	// Normal da face
    		glVertex3f((*posicao).xFim, (*posicao).yCima, (*posicao).zFundo);
    		glVertex3f((*posicao).xFim, (*posicao).yBaixo, (*posicao).zFundo);
    		glVertex3f((*posicao).xFim, (*posicao).yBaixo, (*posicao).zFrente);
    		glVertex3f((*posicao).xFim, (*posicao).yCima, (*posicao).zFrente);
    	glEnd();

        glColor4f(0.0, 0.0, 1.0, 1.0);
    	glBegin(GL_QUADS);			// Face superior
    		glNormal3f(0.0, 1.0, 0.0);  	// Normal da face
    		glVertex3f((*posicao).xInicio, (*posicao).yCima, (*posicao).zFrente);
    		glVertex3f((*posicao).xInicio, (*posicao).yCima, (*posicao).zFundo);
    		glVertex3f((*posicao).xFim, (*posicao).yCima, (*posicao).zFundo);
    		glVertex3f((*posicao).xFim, (*posicao).yCima, (*posicao).zFrente);
    	glEnd();

        glColor4f(1.0, 1.0, 1.0, 1.0);
    	glBegin(GL_QUADS);			// Face inferior
    		glNormal3f(0.0, -1.0, 0.0); 	// Normal da face
    		glVertex3f((*posicao).xInicio, (*posicao).yBaixo, (*posicao).zFrente);
    		glVertex3f((*posicao).xFim, (*posicao).yBaixo, (*posicao).zFrente);
    		glVertex3f((*posicao).xFim, (*posicao).yBaixo, (*posicao).zFundo);
    		glVertex3f((*posicao).xInicio, (*posicao).yBaixo, (*posicao).zFundo);
    	glEnd();
    glPopMatrix();
}


void drawSkyboxWorld (struct posicao *posicao, GLint texturaSkyboxWorld[]){ // Colocar texturas do mundo
    glPushMatrix();
        glColor4f(1.0, 1.0, 1.0, 1.0);
        glBegin(GL_QUADS);			// Face posterior
    		glNormal3f(0.0, 0.0, 1.0);	// Normal da face
    		glVertex3f((*posicao).xFim, (*posicao).yCima, (*posicao).zFundo);
    		glVertex3f((*posicao).xInicio, (*posicao).yCima, (*posicao).zFundo);
    		glVertex3f((*posicao).xInicio, (*posicao).yBaixo, (*posicao).zFundo);
    		glVertex3f((*posicao).xFim, (*posicao).yBaixo, (*posicao).zFundo);
    	glEnd();

        //
    	// glBegin(GL_QUADS);			// Face frontal
    	// 	glNormal3f(0.0, 0.0, -1.0); 	// Normal da face
    	// 	glVertex3f(40.0, 40.0, -40.0);
    	// 	glVertex3f(40.0, -40.0, -40.0);
    	// 	glVertex3f(-40.0, -40.0, -40.0);
    	// 	glVertex3f(-40.0, 40.0, -40.0);
    	// glEnd();

        glColor4f(1.0, 0.0, 0.0, 1.0);
    	glBegin(GL_QUADS);			// Face lateral esquerda
    		glNormal3f(-1.0, 0.0, 0.0); 	// Normal da face
    		glVertex3f((*posicao).xInicio, (*posicao).yCima, (*posicao).zFundo);
    		glVertex3f((*posicao).xInicio, (*posicao).yCima, (*posicao).zFrente);
    		glVertex3f((*posicao).xInicio, (*posicao).yBaixo, (*posicao).zFrente);
    		glVertex3f((*posicao).xInicio, (*posicao).yBaixo, (*posicao).zFundo);
    	glEnd();

        glColor4f(0.0, 1.0, 0.0, 1.0);
    	glBegin(GL_QUADS);			// Face lateral direita
    		glNormal3f(1.0, 0.0, 0.0);	// Normal da face
    		glVertex3f((*posicao).xFim, (*posicao).yCima, (*posicao).zFundo);
    		glVertex3f((*posicao).xFim, (*posicao).yBaixo, (*posicao).zFundo);
    		glVertex3f((*posicao).xFim, (*posicao).yBaixo, (*posicao).zFrente);
    		glVertex3f((*posicao).xFim, (*posicao).yCima, (*posicao).zFrente);
    	glEnd();

        glColor4f(0.0, 0.0, 1.0, 1.0);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texturaSkyboxWorld[0]);

        glBegin(GL_QUADS);			// Face superior
    		glNormal3f(0.0, 1.0, 0.0);  	// Normal da face
    		glTexCoord2f(1, 0); glVertex3f((*posicao).xInicio, (*posicao).yCima, (*posicao).zFrente);
    		glTexCoord2f(1, 1); glVertex3f((*posicao).xInicio, (*posicao).yCima, (*posicao).zFundo);
    		glTexCoord2f(0, 1); glVertex3f((*posicao).xFim, (*posicao).yCima, (*posicao).zFundo);
    		glTexCoord2f(0, 0); glVertex3f((*posicao).xFim, (*posicao).yCima, (*posicao).zFrente);
    	glEnd();
        glDisable(GL_TEXTURE_2D);

        glColor4f(1.0, 1.0, 1.0, 1.0);
    	glBegin(GL_QUADS);			// Face inferior
    		glNormal3f(0.0, -1.0, 0.0); 	// Normal da face
    		glVertex3f((*posicao).xInicio, (*posicao).yBaixo, (*posicao).zFrente);
    		glVertex3f((*posicao).xFim, (*posicao).yBaixo, (*posicao).zFrente);
    		glVertex3f((*posicao).xFim, (*posicao).yBaixo, (*posicao).zFundo);
    		glVertex3f((*posicao).xInicio, (*posicao).yBaixo, (*posicao).zFundo);
    	glEnd();
    glPopMatrix();
}

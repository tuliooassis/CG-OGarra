#ifndef _WIN32
#include <SOIL/SOIL.h>
#else
#include <SOIL.h>
#endif

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "skybox.h"

void drawSkyboxMachine (struct posicao *posicao, double angle){

    glPushMatrix();
        gluLookAt(1*sin(angle) - 1*cos(angle), 1,  1*cos(angle) - 1*sin(angle), 0, 0, (*posicao).zFundo, 0, 1, 0);

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


void drawSkyboxWorld (struct posicao *posicao){ // Colocar texturas do mundo
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

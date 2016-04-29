#ifndef _WIN32
#include <SOIL/SOIL.h>
#else
#include <SOIL.h>
#endif

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <iostream>
#include <math.h>

#include "garra.h"
#include "skybox.h"
#include "objects.h"

#define PI 3.141592653589793

using namespace std;

float esse_raio=1.0;

void cor(float a,float b,float c){

  glColor3f(a/255,b/255,c/255);
}

void drawCilindro (int numero_segmentos, float raio, float altura){
	float grau_pra_lado;
	int i;
	glBegin(GL_TRIANGLE_FAN);
	for( i=0; i<numero_segmentos; i++) {
	 grau_pra_lado= i* (2*PI)/numero_segmentos;
	glVertex3f(raio*sin(grau_pra_lado),altura/2,raio*cos(grau_pra_lado));
	}glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	for( i=0; i<=numero_segmentos; i++) {
	 grau_pra_lado= i* (2*PI)/numero_segmentos;
	glVertex3f(raio*sin(grau_pra_lado),altura,raio*cos(grau_pra_lado));
	glVertex3f(raio*sin(grau_pra_lado),0,raio*cos(grau_pra_lado));
	}glEnd();

	glBegin(GL_TRIANGLE_FAN);
	for( i=numero_segmentos; i>0; i--) {
	 grau_pra_lado= i* (2*PI)/numero_segmentos;
	glVertex3f(raio*sin(grau_pra_lado),0,raio*cos(grau_pra_lado));
	}
	glEnd();
}


void drawDisco (int numero_segmentos,float raio_maior,float altura,float raio_menor,float Gap_do_Meio){
 	float grau_pra_lado;
 	int i;
	// Desenhar as Bases:
 	glBegin(GL_TRIANGLE_FAN);
	for( i=0; i<numero_segmentos; i++) {
		grau_pra_lado= i* (2*PI)/numero_segmentos;
		glVertex3f(raio_menor*sin(grau_pra_lado),altura/2,raio_menor*cos(grau_pra_lado));
	}
	glEnd();
	// (altura - gap)/2 = distancia que desce
	glBegin(GL_TRIANGLE_STRIP);
	for(i=0;i<=numero_segmentos;i++){
		grau_pra_lado= i* (2*PI)/numero_segmentos;
		glVertex3f(raio_menor*sin(grau_pra_lado),altura/2,raio_menor*cos(grau_pra_lado));
		glVertex3f(raio_maior*sin(grau_pra_lado),Gap_do_Meio/2,raio_maior*cos(grau_pra_lado));
	}
	glEnd();

	/*cor(0,162,232);*/
	glBegin(GL_TRIANGLE_STRIP);
	for(i=0;i<=numero_segmentos;i++){
		grau_pra_lado= i* (2*PI)/numero_segmentos;
		glVertex3f(raio_maior*sin(grau_pra_lado),Gap_do_Meio/2,raio_maior*cos(grau_pra_lado));
		glVertex3f(raio_maior*sin(grau_pra_lado),-Gap_do_Meio/2,raio_maior*cos(grau_pra_lado));
	}
	glEnd();
	cor(0,0,0);
	glBegin(GL_TRIANGLE_STRIP);
	for(i=0;i<=numero_segmentos;i++){
		grau_pra_lado= i* (2*PI)/numero_segmentos;
		glVertex3f(raio_maior*sin(grau_pra_lado),-Gap_do_Meio/2,raio_maior*cos(grau_pra_lado));
		glVertex3f(raio_menor*sin(grau_pra_lado),-altura/2,raio_menor*cos(grau_pra_lado));
	}
	glEnd();
	glPushMatrix();
	glTranslatef(0,-1*altura/2,0);
	glBegin(GL_TRIANGLE_FAN);
	for( i=numero_segmentos; i>0; i--) {
		grau_pra_lado= i* (2*PI)/numero_segmentos;
		glVertex3f(raio_menor*sin(grau_pra_lado),0,raio_menor*cos(grau_pra_lado));
	}
	glEnd();
	glPopMatrix();
}


void desenha_dedo(float anguloRaiz, float anguloCutuvelo, float anguloOmbro){
    glRotatef(anguloRaiz, 0, 0, 1); //Inicio das rotações
    drawCilindro(100,0.1,0.9); //Desenha Raiz
    glTranslatef ( 0.0,0.9, 0.0); //Move para a ponta da raiz
    glRotatef ( anguloOmbro,0.0, 0.0, 1.0); // Rotaciona o ombro
    drawCilindro(100,0.1,0.9); //Desenha o Ombro
    glTranslatef ( 0.0,0.9, 0.0); //Move para a ponta do ombro
    glRotatef ( anguloCutuvelo,0, 0.0, 1.0); // Rotaciona o Cotovelo
    drawCilindro(100,0.08,0.7);//Desenha o Cotovelo
}

void desenha_os_dedos(float anguloRaiz, float anguloCutuvelo, float anguloOmbro){
	//glRotatef(10,0,0,1);
//1º dedo
        glPushMatrix();{// Desenha Dedos
            glTranslatef(esse_raio, 0, 0); //Move o inicio para a ponta da base
            desenha_dedo(anguloRaiz, anguloCutuvelo, anguloOmbro);
        }glPopMatrix();//Desfaz todos os translates e rotates
//

//2º dedo
        glPushMatrix();{ // Desenha Dedos
            glRotatef(120, 0, 1, 0); //Inicio das rotações, para posicionar o 2 dedo
            glTranslatef(esse_raio, 0, 0); //Move o inicio para a ponta da base
            desenha_dedo(anguloRaiz, anguloCutuvelo, anguloOmbro);
        }glPopMatrix();//Desfaz todos os translates e rotates
//

//3º dedo
        glPushMatrix();{ // Desenha Dedos
            glRotatef(-120, 0, 1, 0); //Inicio das rotações, para posicionar o 3 dedo
            glTranslatef(esse_raio, 0, 0); //Move o inicio para a ponta da base
            desenha_dedo(anguloRaiz, anguloCutuvelo, anguloOmbro);
        }glPopMatrix();//Desfaz todos os translates e rotates
}

void drawGarra(struct garra *posicaoGarra, float anguloRaiz, float anguloCutuvelo, float anguloOmbro){
    glPushMatrix();
    glColor4f(1.0, 0.0, 1.0, 1.0);
    glTranslatef((*posicaoGarra).posicao.x, (*posicaoGarra).posicao.y, (*posicaoGarra).posicao.z);
    glRotatef(180, 3.5, 0, 1);
	drawDisco(100,esse_raio+0.2,0.4,esse_raio,0.2);
	drawCilindro(100,esse_raio,0.1);
	glTranslatef(0,0.1,0);
	desenha_os_dedos(anguloRaiz, anguloCutuvelo, anguloOmbro);
    glPopMatrix();

}

void moveGarraBase (struct garra *posicaoGarra, int qtdObjects, struct objects objects[]){
    if ((*posicaoGarra).posicao.y < (*posicaoGarra).yo)
        (*posicaoGarra).posicao.y += 0.1;

    if ((*posicaoGarra).posicao.y >= (*posicaoGarra).yo && (*posicaoGarra).posicao.x > (*posicaoGarra).xo)
        (*posicaoGarra).posicao.x -= 0.1;

    if ((*posicaoGarra).posicao.y >= (*posicaoGarra).yo && (*posicaoGarra).posicao.x <= (*posicaoGarra).xo && (*posicaoGarra).posicao.z >= (*posicaoGarra).zo)
        (*posicaoGarra).posicao.z -= 0.15;

    if ((*posicaoGarra).posicao.y >= (*posicaoGarra).yo && (*posicaoGarra).posicao.x <= (*posicaoGarra).xo && (*posicaoGarra).posicao.z <= (*posicaoGarra).zo){
        (*posicaoGarra).moveGarraBase = false;
        for (int i = 0; i < qtdObjects; i++){
        int temporaria = verifyCollision (qtdObjects, objects, posicaoGarra);
        if (temporaria != -1)
            objects[temporaria].situation = solto;
        }
    }
}

void abreGarra (struct garra *posicaoGarra, float *anguloRaiz, float *anguloOmbro, float *anguloCutuvelo){
    *anguloOmbro -= 2;
    *anguloCutuvelo -= 2;
    if (*anguloOmbro < 10.0 && *anguloCutuvelo < 10.0){
        (*posicaoGarra).abrindoGarra = false;
        (*posicaoGarra).desceGarra = true;
    }
}

void fechaGarra (struct garra *posicaoGarra, float *anguloRaiz, float *anguloOmbro, float *anguloCutuvelo){
    *anguloOmbro += 2;
    *anguloCutuvelo += 2;
    if (*anguloOmbro > 45.0 && *anguloCutuvelo > 45.0){
        (*posicaoGarra).fechandoGarra = false;
        (*posicaoGarra).moveGarraBase = true;
    }
}

void downGarra (struct garra *posicaoGarra, struct objects objects[], int qtdObjects){
    for (int i = 0; i < qtdObjects; i++){
        if (verifyCollision (qtdObjects, objects, posicaoGarra) != -1 || (*posicaoGarra).posicao.y - (*posicaoGarra).distanciaBasePerninha < objects[i].y + objects[i].raio){
            (*posicaoGarra).desceGarra = false;
            (*posicaoGarra).fechandoGarra = true;
        }
    }
    (*posicaoGarra).posicao.y -= 0.10;
}

int verifyCollision (int qtdObjects, struct objects objects[], struct garra *posicaoGarra){
    double distancia;
    for (int i = 0; i < qtdObjects; i++){
        distancia = sqrt(pow((*posicaoGarra).posicao.x - objects[i].x, 2) +
            pow((*posicaoGarra).posicao.y - (*posicaoGarra).distanciaBasePerninha - 0.5 - objects[i].y, 2) +
            pow((*posicaoGarra).posicao.z - objects[i].z, 2));

        if ((*posicaoGarra).distanciaBasePerninha > distancia + objects[i].raio) {
            objects[i].situation = pego;
            return i;
        }
    }
    return -1;
}

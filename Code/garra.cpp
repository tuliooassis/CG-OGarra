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
	for( i=0; i<numero_segmentos; i++){
        grau_pra_lado= i* (2*PI)/numero_segmentos;
        glVertex3f(raio*sin(grau_pra_lado),altura/2,raio*cos(grau_pra_lado));
	}
    glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	for( i=0; i<=numero_segmentos; i++){
        grau_pra_lado= i* (2*PI)/numero_segmentos;
        glVertex3f(raio*sin(grau_pra_lado),altura,raio*cos(grau_pra_lado));
        glVertex3f(raio*sin(grau_pra_lado),0,raio*cos(grau_pra_lado));
	}
    glEnd();

	glBegin(GL_TRIANGLE_FAN);
	for( i=numero_segmentos; i>0; i--){
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


void desenha_dedo(struct garra *garra){
    glRotatef(garra->angulo.raiz, 0, 0, 1); //Inicio das rotações
    drawCilindro(100,0.1,0.9); //Desenha Raiz
    glTranslatef (0.0,0.9, 0.0); //Move para a ponta da raiz
    glutSolidSphere(0.12, 10, 10);
    glRotatef (garra->angulo.ombro, 0.0, 0.0, 1.0); // Rotaciona o ombro
    drawCilindro(100,0.1,0.9); //Desenha o Ombro
    glTranslatef ( 0.0,0.9, 0.0); //Move para a ponta do ombro
    glutSolidSphere(0.12, 10, 10);
    glRotatef (garra->angulo.cutuvelo, 0, 0.0, 1.0); // Rotaciona o Cotovelo
    drawCilindro(100,0.08,0.85);//Desenha o Cotovelo
}

void desenha_os_dedos(struct garra *garra){
    //glRotatef(10,0,0,1);
    //1º dedo
    glPushMatrix();// Desenha Dedos
        glTranslatef(esse_raio, 0, 0); //Move o inicio para a ponta da base
        desenha_dedo(garra);
    glPopMatrix();//Desfaz todos os translates e rotates
    //

    //2º dedo
    glPushMatrix(); // Desenha Dedos
        glRotatef(120, 0, 1, 0); //Inicio das rotações, para posicionar o 2 dedo
        glTranslatef(esse_raio, 0, 0); //Move o inicio para a ponta da base
        desenha_dedo(garra);
    glPopMatrix();//Desfaz todos os translates e rotates
    //

    //3º dedo
    glPushMatrix(); // Desenha Dedos
        glRotatef(-120, 0, 1, 0); //Inicio das rotações, para posicionar o 3 dedo
        glTranslatef(esse_raio, 0, 0); //Move o inicio para a ponta da base
        desenha_dedo(garra);
    glPopMatrix();//Desfaz todos os translates e rotates
}

void drawGarra(struct garra *garra){
    glPushMatrix();
        glColor4f(1.0, 0.0, 1.0, 1.0);
        glTranslatef(garra->posicao.x, garra->posicao.y, garra->posicao.z);
        glRotatef(180, 3.5, 0, 1);

        drawDisco(100,esse_raio+0.2,0.4,esse_raio,0.2);
    	drawCilindro(100,esse_raio,0.1);

        glTranslatef(0,0.1,0);
    	desenha_os_dedos(garra);
    glPopMatrix();

}

int posSituacao = 0;

void abreGarra (struct garra *garra){
    garra->angulo.ombro -= 2;
    garra->angulo.cutuvelo -= 2;
    if (garra->angulo.ombro < 10.0 && garra->angulo.cutuvelo < 10.0){
        garra->situation = descendo;
    }
}

void fechaGarra (struct garra *garra){
    if (posSituacao == descendo){
        garra->angulo.ombro += 2;
        garra->angulo.cutuvelo += 2;
        if (garra->angulo.ombro > 45.0 && garra->angulo.cutuvelo > 45.0){
            garra->situation = descendo;
        }
    }
    else if (posSituacao == subindo){
        garra->angulo.ombro += 2;
        garra->angulo.cutuvelo += 2;
        if (garra->angulo.ombro > 45.0 && garra->angulo.cutuvelo > 45.0){
            garra->situation = subindo;
        }
    }
}

void desceGarra (struct garra *garra, struct objects objects[], int qtdObects, bool *somMovimentoAutomatico){
    *somMovimentoAutomatico = true;
    garra->posicao.y -= 0.1;
    if (verifyCollision(qtdObects, objects, garra) != -1 || garra->posicao.y - garra->alturaGarra <= -4){
        garra->situation = fechando;
        posSituacao = subindo;
        *somMovimentoAutomatico = false;
    }
}

void sobeGarra (struct garra *garra, bool *somMovimentoAutomatico){
    *somMovimentoAutomatico = true;
    garra->posicao.y += 0.1;
    if (garra->posicao.y >= garra->yo){
        garra->situation = laser;
        *somMovimentoAutomatico = false;
    }
}

int objetoEmCollision;

void explode (struct garra *garra, struct objects objects[], int *objetosPegos){
    if (garra->tamLaser < garra->alturaGarra){ // desenha laser
        garra->somLaser = true;
        garra->tamLaser += 0.1;
        if (garra->tamLaser >= garra->alturaGarra){
                if (objects[objetoEmCollision].colisionStatus == true){
                    *objetosPegos += 1;
                    objects[objetoEmCollision].situation = explodido;
                    objects[objetoEmCollision].colisionStatus = false;

                }
                garra->situation = base;
                garra->tamLaser = 0;
                garra->somLaser = false;
        }
    }

    glPushMatrix();
        glTranslatef(garra->posicao.x, garra->posicao.y - garra->tamLaser, garra->posicao.z);

        glColor4f(.88, 1.0, .88, 1.0); // desenha parte de dentro
        drawCilindro(100, 0.05, garra->tamLaser);

        glColor4f(0.2, 1.0, 0.0, 0.7); // desenha parte de fora
        drawCilindro(100, 0.1, garra->tamLaser);

    glPopMatrix();
}

void objetoPego (int qtdObjects, struct objects objects[], struct garra *garra){
    for (int i = 0; i < qtdObjects; i++){// Se o objeto for pego, faz ele "seguir" a garra
        if (objects[i].colisionStatus == true){
            objects[i].x = garra->posicao.x;
            objects[i].z = garra->posicao.z;
            objects[i].y = garra->posicao.y - garra->alturaGarra - objects[i].raio;
        }

    }
}

void tentaPegarObjeto (struct garra *garra, struct objects objects[], int qtdObjects, int *objetosPegos, bool *somMovimentoAutomatico){
    objetoPego(qtdObjects, objects, garra); // Se o objeto for pego, faz ele "seguir" a garra
    switch (garra->situation) { // faz a garra realizar certas ações dependendo do seu estado;
        case abrindo:
            abreGarra(garra);
            break;
        case fechando:
            fechaGarra(garra);
            break;
        case descendo:
            desceGarra(garra, objects, qtdObjects, somMovimentoAutomatico);
            break;
        case subindo:
            sobeGarra(garra, somMovimentoAutomatico);
            break;
        case laser:
            explode(garra, objects, objetosPegos);
            break;
        default:
            break;
    }

}

int verifyCollision (int qtdObjects, struct objects objects[], struct garra *garra){
    double distancia;
    for (int i = 0; i < qtdObjects; i++){
        distancia = sqrt(pow(garra->posicao.x - objects[i].x, 2) +
            pow((garra->posicao.y - garra->alturaGarra) - objects[i].y, 2) +
            pow(garra->posicao.z - objects[i].z, 2));

        if (objects[i].situation == padrao && distancia <= objects[i].raio){
            objetoEmCollision = i;
            objects[i].situation = colisao;
            objects[i].colisionStatus = true;
            return i;
        }
    }
    return -1; // se nao colidir, retorna -1
}

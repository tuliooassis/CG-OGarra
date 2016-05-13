#ifndef _WIN32
#include <SOIL/SOIL.h>
#else
#include <SOIL.h>
#endif

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <iostream>
using namespace std;
#include "menu.h"

void drawMenu (struct menu menu[], int sit){
    glClearColor(0,0,0,1);
    glColor3f(1, 1, 1); // Função que desenha menu.
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, menu[sit].textureMenu);
    glEnable(GL_TEXTURE_2D);
    glTranslatef(-5, -5, 1);
    glBegin(GL_POLYGON);
        glTexCoord2f(menu[sit].positionTextureMenu, 0);                                     glVertex3f(0, 0, 0);
        glTexCoord2f(menu[sit].positionTextureMenu + menu[sit].incrementoTextureMenu, 0); glVertex3f(10, 0, 0);
        glTexCoord2f(menu[sit].positionTextureMenu + menu[sit].incrementoTextureMenu, 1); glVertex3f(10, 10, 0);
        glTexCoord2f(menu[sit].positionTextureMenu, 1);                                     glVertex3f(0, 10, 0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void desenhaTela(struct menu menu[], int sit){ // desenha tela de acordo com a situação
    glClearColor(0,0,0,1);
    glColor4f(1, 1, 1, 1);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, menu[sit].textureMenu); //e.g. menu[pause].textureMenu
    glEnable(GL_TEXTURE_2D);
    glTranslatef(-5, -5, 1);
    glBegin(GL_POLYGON);
        glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
        glTexCoord2f(1, 0); glVertex3f(10, 0, 0);
        glTexCoord2f(1, 1); glVertex3f(10, 10, 0);
        glTexCoord2f(0, 1); glVertex3f(0, 10, 0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void initMenu (struct menu menu[]){
    menu[menuGeral].textureMenu = SOIL_load_OGL_texture(
      "img/menuPrincipal.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
    );
    if (menu[menuGeral].textureMenu == 0)
        cout << "Erro" << endl;

    menu[menuConfiguracao].textureMenu = SOIL_load_OGL_texture(
      "img/menuConfiguracao.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
    );
    if (menu[menuConfiguracao].textureMenu == 0)
        cout << "Erro" << endl;

    menu[menuCreditos].textureMenu = SOIL_load_OGL_texture(
      "img/menuCredito.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
    );
    if (menu[menuCreditos].textureMenu == 0)
        cout << "Erro" << endl;

    menu[pause].textureMenu = SOIL_load_OGL_texture(
      "img/pause.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
    );
    if (menu[pause].textureMenu == 0)
        cout << "Erro" << endl;

    menu[reiniciar].textureMenu = SOIL_load_OGL_texture(
      "img/reiniciar.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
    );
    if (menu[reiniciar].textureMenu == 0)
        cout << "Erro" << endl;

    menu[gameover].textureMenu = SOIL_load_OGL_texture(
      "img/gameover.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
    );
    if (menu[gameover].textureMenu == 0)
        cout << "Erro" << endl;

    menu[carregando].textureMenu = SOIL_load_OGL_texture(
      "img/menuiniciando.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
    );
    if (menu[carregando].textureMenu == 0)
        cout << "Erro" << endl;


    menu[menuGeral].incrementoTextureMenu = 0.25;
    menu[menuGeral].positionTextureMenu = 0;

}

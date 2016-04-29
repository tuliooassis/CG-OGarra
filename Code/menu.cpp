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
    glColor3f(1, 1, 1); // Função que desenha menu.
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, menu[sit].textureMenu);
    glEnable(GL_TEXTURE_2D);
    glTranslatef(-5, -5, 1);
    glBegin(GL_POLYGON);
        glTexCoord2f(menu[sit].positionTextureMenu, 0);     glVertex3f(0, 0, 0);
        glTexCoord2f(menu[sit].positionTextureMenu+ menu[sit].incrementoTextureMenu, 0); glVertex3f(10, 0, 0);
        glTexCoord2f(menu[sit].positionTextureMenu+ menu[sit].incrementoTextureMenu, 1); glVertex3f(10, 10, 0);
        glTexCoord2f(menu[sit].positionTextureMenu, 1);     glVertex3f(0, 10, 0);
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
        cout << "errorrrr" << endl;

    menu[menuGeral].incrementoTextureMenu = 0.25;
    menu[menuGeral].positionTextureMenu = 0;

}

#ifndef _WIN32
#include <SOIL/SOIL.h>
#else
#include <SOIL.h>
#endif

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "garra.h"

void drawGarra (struct garra *m, double *anguloOmbro, double *anguloCutuvelo){
    for (int i = 0; i < 3; i++){
        int k = 0;


        glTranslatef(0, 0, k);

        glPushMatrix();

            glColor4f(0.0, 1.0, 1.0, 1.0);
            glRotatef(-90, 0, 0, 1);
            glTranslatef (-1.0, 0.0, (*m).z);
            glRotatef (*anguloOmbro, 0.0, 0.0, 1.0);
            glTranslatef (1.0, 0.0, 0.0);
            glPushMatrix();
                glScalef (2.0, 0.4, 1.0);
                glutSolidCube (1.0);
            glPopMatrix();

            glTranslatef (1.0, 0.0, 0.0);
            glRotatef (*anguloCutuvelo, 0.0, 0.0, 1.0);
            glTranslatef (1.0, 0.0, 0.0);
            glPushMatrix();
                glScalef (2.0, 0.4, 1.0);
                glutSolidCube (1.0);
            glPopMatrix();
        glPopMatrix();

        k-=1;
    }
}

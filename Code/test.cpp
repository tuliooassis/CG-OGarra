//gcc dedinho2.c -o algo -D FREEGLUT_STATIC -lSOIL -lfreeglut_static -lglu32  -lopengl32 -lwinmm -lgdi32 -Wl,--subsystem,windows
struct garra {
    float x, y, z;
    float angleX, angleY, angleZ;
};

#include <GL/freeglut.h>
#include <GL/glu.h>
#include <math.h>
#include <bits/stdc++.h>

#define PI (3.141592653589793)
		float anguloRaiz=-30;
		float anguloCutuvelo=30;
		float anguloOmbro=30;
double xis,yis,zis2,zis=0;
int aldoeu=0;
int angulo_rotacao=0;
float Angulo_rotar,Angulo_rotarZ,Angulo_rotarZz=0;
int raios =10;
float esse_raio=1.0;
 long font = (long)GLUT_BITMAP_8_BY_13;   // Fonte usada para imprimir na tela
 char theStringBuffer[10];                // String buffer

void cor(float a,float b,float c){

  glColor3f(a/255,b/255,c/255);
}
void escreveTextoNaTela(void *font, char *string)
{
    char *c;
    for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}
void floatParaString(char * destStr, int precision, float val)
{
    sprintf(destStr,"%f",val);
    destStr[precision] = '\0';
}
escrevendo(){
    glRasterPos3f(1.0, 1.05, -2.0);
     floatParaString(theStringBuffer, 4, anguloRaiz);
    escreveTextoNaTela((void*)font, (char*)" anguloRaiz ");
    escreveTextoNaTela((void*)font, theStringBuffer);
    glRasterPos3f(1.0, 1.00, -2.0);
     floatParaString(theStringBuffer, 4, anguloCutuvelo);
    escreveTextoNaTela((void*)font, (char*)" anguloCutuvelo ");
    escreveTextoNaTela((void*)font, theStringBuffer);
    glRasterPos3f(1.0, 0.95, -2.0);
     floatParaString(theStringBuffer, 4, anguloOmbro);
    escreveTextoNaTela((void*)font, (char*)" anguloOmbro");
    escreveTextoNaTela((void*)font, theStringBuffer);

}

// configura alguns parâmetros do modelo de iluminação: FONTE DE LUZ
const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 10.0f, 10.0f, 10.0f, 10.0f };

// configura alguns parâmetros do modelo de iluminação: MATERIAL
const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 0.1f, 0.1f, 0.1f, 0.1f };
const GLfloat high_shininess[] = { 20.0f };
void lights(){
	/*glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	float d = 4.0;           // Intensidade da cor difusa da luz branca
 	float e = 5.0;
 	float p =1.0;
	float lightAmb[] = { 0.0, 0.0, 0.0, 1.0 };
    float lightDif0[] = { d, d, d, 1.0 };
    float lightSpec0[] = { e, e, e, 1.0 };
    float lightPos0[] = { 10.0, 10.0, 30.0, p };
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDif0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpec0);
 	float globAmb[] = { 10, 10, 10, 1.0 };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);     // Luz ambiente global*/
     glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

}
void inicializa(){
  glClearColor (0.0, 0.0, 0.0, 0.0);
  glShadeModel (GL_FLAT);
}


void desenha_cilindro(int numero_segmentos,float raio,float altura){
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

void desenha_disco_1(int numero_segmentos,float raio_maior,float altura,float raio_menor,float Gap_do_Meio){
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
	cor(255,255,255);
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

void desenha_dedo(){
    glRotatef(anguloRaiz, 0, 0, 1); //Inicio das rotações
    desenha_cilindro(100,0.1,0.9); //Desenha Raiz
    glTranslatef ( 0.0,0.9, 0.0); //Move para a ponta da raiz
    glRotatef ( anguloOmbro,0.0, 0.0, 1.0); // Rotaciona o ombro
    desenha_cilindro(100,0.1,0.9); //Desenha o Ombro
    glTranslatef ( 0.0,0.9, 0.0); //Move para a ponta do ombro
    glRotatef ( anguloCutuvelo,0, 0.0, 1.0); // Rotaciona o Cotovelo
    desenha_cilindro(100,0.08,0.7);//Desenha o Cotovelo
}void desenha_os_dedos(){
	//glRotatef(10,0,0,1);
//1º dedo
        glPushMatrix();{// Desenha Dedos
            glTranslatef(esse_raio, 0, 0); //Move o inicio para a ponta da base
            desenha_dedo();
        }glPopMatrix();//Desfaz todos os translates e rotates
//

//2º dedo
        glPushMatrix();{ // Desenha Dedos
            glRotatef(120, 0, 1, 0); //Inicio das rotações, para posicionar o 2 dedo
            glTranslatef(esse_raio, 0, 0); //Move o inicio para a ponta da base
            desenha_dedo();
        }glPopMatrix();//Desfaz todos os translates e rotates
//

//3º dedo
        glPushMatrix();{ // Desenha Dedos
            glRotatef(-120, 0, 1, 0); //Inicio das rotações, para posicionar o 3 dedo
            glTranslatef(esse_raio, 0, 0); //Move o inicio para a ponta da base
            desenha_dedo();
        }glPopMatrix();//Desfaz todos os translates e rotates
}

void desenha_a_garra(){
	desenha_disco_1(100,esse_raio+0.2,0.4,esse_raio,0.2);
	//desenha_cilindro(100,esse_raio,0.1);
	glTranslatef(0,0.1,0);
	desenha_os_dedos();
}

void rotacione(){
	Angulo_rotar= angulo_rotacao*(2*PI)/360;
	xis=raios*sin(Angulo_rotar);
	yis=raios*cos(Angulo_rotar);
}
void desenha()
{
	lights();
	rotacione();
 	glLoadIdentity();
	gluLookAt(xis,zis,yis,0,0,0,0,1,0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1,1,1);
	glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    //desenha_disco_1(100,esse_raio,0.2,esse_raio-1,0.1);
	desenha_a_garra();
	//desenha_cilindro(3000,1,1);
		/*glTranslatef(0,-5,0);desenha_cilindro(900,0.3,10);
		glTranslatef(0,5,0);
	    desenha_disco_1(396,2,1,1.5,0.5);
*/
	   /* desenha_disco_1(3,20,10,15,0.5);*/
	glutSwapBuffers();
    glutPostRedisplay();
 }

void redimensiona(int w, int h){
 	w = (GLfloat) w;
 	h = (GLfloat) h;
 	glViewport (0, 0,((GLfloat) w),((GLfloat) h));
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(50.0f, w/h, 1.0, 300.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef (0.0, 0.0, -5.0);
}

void teclado(unsigned char key, int x, int y){
    switch (key) {
       // Tecla ESC
       case 27:
           exit(0);
           break;
        case'+':
            zis++;
            break;
        case'-':
            zis--;
            break;
        case 'r':
	       raios=10; angulo_rotacao=0;
	         break;

        case 'c':
        	angulo_rotacao++;
        	break;
        case 'x':
        	raios--;
        	break;
        case 'z':
        	raios++;
        	break;
       	case 'q':
            anguloRaiz++;
            anguloCutuvelo++;
            anguloOmbro++;
            break;
		case 'w':
            anguloRaiz--;
            anguloCutuvelo--;
            anguloOmbro--;
            break;
       	default:
          break;
    }
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("cilindros");
    inicializa();

    glutDisplayFunc(desenha);
    glutReshapeFunc(redimensiona);
    glutKeyboardFunc(teclado);
 	glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glutMainLoop();
    return 0;
}

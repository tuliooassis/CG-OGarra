#include "globals.h"
struct garra {
    coordenadas posicao;
    float xo, yo, zo;
    bool desceGarra;
    bool moveGarraBase;
    bool abrindoGarra;
    bool fechandoGarra;
    float distanciaBasePerninha;
};

void drawGarra (struct garra *posicaoGarra, float anguloRaiz, float anguloCutuvelo, float anguloOmbro);
void downGarra (struct garra *posicaoGarra, struct objects objects[], int qtdObects);
void moveGarraBase (struct garra *posicaoGarra, int qtdObjects, struct objects objects[]);
void abreGarra (struct garra *posicaoGarra, float *anguloRaiz, float *anguloOmbro, float *anguloCutuvelo);
void fechaGarra (struct garra *posicaoGarra, float *anguloRaiz, float *anguloOmbro, float *anguloCutuvelo);
int verifyCollision (int qtdObjects, struct objects objects[], struct garra *posicaoGarra);

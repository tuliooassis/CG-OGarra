#include "globals.h"
struct garra {
    coordenadas posicao;
    angulos angulo;
    int situation;
    float xo, yo, zo;
    float alturaGarra;
    float tamLaser;

    bool posicaoDefault;
    bool somLaser;

    GLint texturaExplosao;
    float variacaoTexturaExplosao;
    float parteAtualTextura;

};

void abreGarra (struct garra *garra);
void fechaGarra (struct garra *garra);
int verifyCollision (int qtdObjects, struct objects objects[], struct garra *garra);
void drawGarra (struct garra *garra);
void tentaPegarObjeto (struct garra *garra, struct objects objects[], int qtdObjects, int *objetosPegos, bool *somMovimentoAutomatico);
void desceGarra (struct garra *garra, struct objects objects[], int qtdObects, bool *somMovimentoAutomatico);
void sobeGarra (struct garra *garra, bool *somMovimentoAutomatico);
void explode (struct garra *garra, struct objects objects[], int *objetosPegos);

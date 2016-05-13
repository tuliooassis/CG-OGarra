struct posicao {
    float zFundo;
    float zFrente;
    float yCima;
    float yBaixo;
    float xInicio;
    float xFim;
};

struct texturas {
    GLint top;
    GLint down;
    GLint side;
};

void initFog (float colorFog[]);
void initSkybox (struct texturas *texturaSkyboxWorld, struct posicao *posicaoSkyboxMachine, struct posicao *posicaoSkyboxWorld, struct garra *garra);
void drawMachine (struct posicao *posicao);
void drawSkyboxWorld (struct posicao *posicao, struct texturas *texturaSkyboxWorld);
void drawCilindro (int numeroSegmentos, float raio, float altura);
void drawBarraProgresso (int qtdObects, int *objetosPegos);

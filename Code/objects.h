struct objects {
    float x, y, z;
    float r, g, b, o;
    float raio;
    int situation;
};

void initObjects (int qtdeObjects, struct objects objects[], struct posicao *posicaoSkyboxMachine);
void drawObjects (int qtdObects, struct objects objects[]);
void upObjects (int numObjeto, struct objects objects[], struct garra *posicaoGarra);
void soltaObjects (struct objects objects[], int qtdObjects, struct posicao *posicaoSkyboxMachine);

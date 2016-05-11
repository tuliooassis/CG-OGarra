struct objects {
    float x, y, z;
    float r, g, b, o;
    float raio;
    int situation;
    bool colisionStatus;
};

void initObjects (int qtdeObjects, struct objects objects[], struct posicao *posicaoSkyboxMachine);
void drawObjects (int qtdObects, struct objects objects[]);
void upObjects (int numObjeto, struct objects objects[], struct garra *garra);
void soltaObjects (struct objects objects[], int qtdObjects, struct posicao *posicaoSkyboxMachine);
bool controleBolasLocalDiferente (int num, struct objects objects[]);

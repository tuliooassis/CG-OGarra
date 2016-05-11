struct coordenadas {
    float x, y, z;
    float r, g, b, a;
    float raio;
};


struct ponto {
    float x, y, z;
    float porcentagemX, porcentagemY;
};

struct angulos {
    float raiz;
    float ombro;
    float cutuvelo;
};

enum situationobject { padrao = 0, colisao, explodido, destruido };
enum situationGarra { base = 0,abrindo, fechando, descendo, subindo, explodindoBolas, laser};

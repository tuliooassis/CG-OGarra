struct posicao {
    float zFundo;
    float zFrente;
    float yCima;
    float yBaixo;
    float xInicio;
    float xFim;
};

void drawSkyboxMachine (struct posicao *posicao, double angle);
void drawSkyboxWorld (struct posicao *posicao);

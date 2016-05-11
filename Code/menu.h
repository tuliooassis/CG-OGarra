struct menu {
    double positionTextureMenu;
    double incrementoTextureMenu;
    GLint textureMenu;

};
enum situation { menuGeral = 0, game, menuCreditos, menuConfiguracao, pause, reiniciar, gameover, carregando };


void drawMenu (struct menu menu[], int sit);
void initMenu (struct menu menu[]);
void desenhaTela(struct menu menu[], int sit);

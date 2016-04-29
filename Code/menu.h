struct menu {
    double positionTextureMenu;
    double incrementoTextureMenu;
    GLint textureMenu;
};
enum situation { menuGeral = 0, menuCreditos, game };


void drawMenu (struct menu menu[], int sit);
void initMenu (struct menu menu[]);

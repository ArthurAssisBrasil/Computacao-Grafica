/***
    Classe que representa a biela do motor
***/
#ifndef BIELA_H
#define BIELA_H

#include <GL/glut.h>

class Biela
{
    public:
        Biela(int tipo);
        void draw(float angRotacao); //desenha a biela

    protected:

    private:
        float altura;
        float raio;
        float xBiela, yBiela, zBiela;
        int dirRotacao;
        int tipo;   //tipo=0 comeca no alto, tipo =1 comeca para baixo
};

#endif // BIELA_H

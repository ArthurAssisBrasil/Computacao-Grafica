/***
    Classe que representa o pistao do motor
***/
#ifndef PISTAO_H
#define PISTAO_H

#include <GL/glut.h>

class Pistao
{
    public:
        Pistao(int tipo);
        void draw(float angRotacao); // desenha o pistao


    protected:

    private:
        float altura;
        float raio;
        float xPistao, yPistao, zPistao;
        int tipo; //tipo=0 comeca no alto, tipo =1 comeca para baixo
};

#endif // PISTAO_H

/***
    Classe que representa o virabrequim do motor
***/
#ifndef VIRABREQUIM_H
#define VIRABREQUIM_H

#include <GL/glut.h>

class Virabrequim
{
    public:
        Virabrequim(int tipo);
        void draw(float angRotacao); //desenha o virabrequim

    protected:

    private:
        float alturaFixo, alturaMovel, alturaLigacao;
        float raioFixo, raioMovel, raioLigacao;
        int tipo; //tipo=0 comeca no alto, tipo =1 comeca para baixo
};

#endif // VIRABREQUIM_H

/***
    Classe que representa a camisa do motor
***/
#ifndef CAMISA_H
#define CAMISA_H

#include <GL/glut.h>

class Camisa
{
    public:
        Camisa();
        void draw(float angRotacao); // desenha a camisa

    protected:

    private:
        float raio;
};

#endif // CAMISA_H

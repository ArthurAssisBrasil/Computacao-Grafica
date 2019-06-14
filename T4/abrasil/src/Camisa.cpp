/***
    Classe que representa a camisa do pistao
***/
#include "Camisa.h"
#include <math.h>

Camisa::Camisa()
{
    raio = 1.005;
}
//desenha camisa
void Camisa::draw(float angRotacao)
{
    //amarelo e transparente
    GLfloat mat_diffuse[] = { 1, 1, 0, 0.5};
    GLfloat mat_ambient[] = { 1, 1, 0, 0.5};

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  mat_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  mat_ambient);

    float x;
    float y1 = 1;
    float y2 = -2.2;
    float z = 0;
    //cilindro menor
    glBegin(GL_QUAD_STRIP);
    for(float i=0; i<= (2*M_PI) + 0.01; i+=0.01)
    {
        glNormal3f(cos(i), 0, sin(i));
        x = (cos(i)*raio);
        z = (sin(i)*raio);
        glVertex3d(x, y1,z);
        glVertex3d(x, y2,z);
    }
    glEnd();

    //tampas entre os cilindros
    float raioExt = raio + 0.2;
    glBegin(GL_QUAD_STRIP);
    glNormal3d(0,1,0);
    for(double i=0; i<2*M_PI; i+=0.01)
    {
        glVertex3f(cos(i)*raio, y1, sin(i)*raio);
        glVertex3f(cos(i)*raioExt, y1, sin(i) * raioExt);
    }
    glEnd();

    glNormal3d(0,-1,0);
    glBegin(GL_QUAD_STRIP);
    for(double i=0; i<2*M_PI; i+=0.01)
    {
        glVertex3f(cos(i)*raio, y2, sin(i)*raio);
        glVertex3f(cos(i)*raioExt, y2, sin(i) * raioExt);
    }
    glEnd();

    //cilindro maior
    glBegin(GL_QUAD_STRIP);
    for(float i=0; i<= (2*M_PI) + 0.01; i+=0.01)
    {
        glNormal3f(cos(i), 0, sin(i));
        x = (cos(i)*raioExt);
        z = (sin(i)*raioExt);
        glVertex3d(x, y1,z);
        glVertex3d(x, y2,z);
    }
    glEnd();
}

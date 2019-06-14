/***
    Classe que representa o virabrequim do motor
***/
#include "Virabrequim.h"
#include <math.h>

Virabrequim::Virabrequim(int t)
{
    alturaFixo = 1; raioFixo = 0.4;
    alturaMovel = 1.5; raioMovel = 0.4;
    alturaLigacao = 1.5; raioLigacao = 0.2;
    this->tipo = t;
}
//desenha o virabrequim
void Virabrequim::draw(float angRotacao)
{
    //verde
    GLfloat mat_diffuse[] = { 0, 1, 0, 1 };
    GLfloat mat_ambient[] = { 0, 1, 0, 1 };

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  mat_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  mat_ambient);

    glPushMatrix();
    //objeto na posicao correta
    if(tipo == 0)
    {
        glTranslated(0, -2.5 - raioMovel, -alturaMovel/2.0 );
        //rotacao em torno do eixo fixo
        glTranslated(0, -alturaLigacao, 0);
        glRotatef(angRotacao, 0,0,1);
        glTranslated(0, alturaLigacao, 0);
    }
    else
    {
        glTranslated(0, -2.5 - raioMovel - 2*alturaLigacao, -alturaMovel/2.0 );
        //rotacao em torno do eixo fixo
        glTranslated(0, alturaLigacao, 0);
        glRotatef(angRotacao, 0,0,1);
        glTranslated(0, -alturaLigacao, 0);
    }
    //parte movel do virabrequim
    GLUquadricObj *movel = gluNewQuadric();
    gluCylinder(movel, raioMovel, raioMovel, alturaMovel, 50, 50);

    glBegin(GL_POLYGON);
    glNormal3d(0,0,1);
    for(double i=0; i<2*M_PI; i+=0.1)
    {
        glVertex3f(cos(i) * raioMovel, sin(i) * raioMovel, alturaMovel);
    }
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3d(0,0,-1);
    for(double i=0; i<2*M_PI; i+=0.1)
    {
        glVertex3f(cos(i) * raioMovel, sin(i) * raioMovel, 0);
    }
    glEnd();

    glPopMatrix();

    glPushMatrix();
    //objeto na posicao correta
    glRotatef(270, 1,0,0);
    glTranslated(0,raioLigacao -alturaMovel/2.0, -2.5 - alturaLigacao - raioMovel);
    if(tipo == 1)
    {
        glRotatef(180,0,1,0);
    }
    //rotacao em torno do eixo fixo
    glRotatef(angRotacao, 0,-1,0);
    //ligacao entre parte movel e parte fixa
    GLUquadricObj *ligacao1 = gluNewQuadric();
    gluCylinder(ligacao1, raioLigacao, raioLigacao, alturaLigacao, 30, 30);
    glPopMatrix();

    glPushMatrix();
    //objeto na posicao correta
    glRotatef(270, 1,0,0);
    glTranslated(0,-raioLigacao +alturaMovel/2.0 - 0.05, -2.5 - alturaLigacao - raioMovel);
    if(tipo == 1)
    {
        glRotatef(180,0,1,0);
    }
    //rotacao em torno do eixo fixo
    glRotatef(angRotacao, 0,-1,0);
    //ligacao entre parte movel e parte fixa
    GLUquadricObj *ligacao2 = gluNewQuadric();
    gluCylinder(ligacao2, raioLigacao, raioLigacao, alturaLigacao, 30, 30);
    glPopMatrix();
    //eixo fixo 1
    glPushMatrix();
    glTranslated(0, -2.5 - alturaLigacao - raioFixo, alturaMovel/2.0 - 2*raioLigacao - 0.03);

    //rotacao em torno do eixo fixo
    glRotatef(angRotacao, 0,0,1);

    GLUquadricObj *fixo1 = gluNewQuadric();
    gluCylinder(fixo1, raioFixo, raioFixo, alturaFixo, 80, 50);
    //tampa do cilindro
    glNormal3d(0,0,1);
    glBegin(GL_POLYGON);
    for(double i=0; i<2*M_PI; i+=0.1)
    {
        glVertex3f(cos(i) * raioFixo, sin(i) * raioFixo, alturaFixo);
    }
    glEnd();
    glBegin(GL_POLYGON);
    glNormal3d(0,0,-1);
    for(double i=0; i<2*M_PI; i+=0.1)
    {
        glVertex3f(cos(i) * raioFixo, sin(i) * raioFixo, 0);
    }
    glEnd();
    glPopMatrix();

    //eixo fixo 2
    glPushMatrix();
    glTranslated(0, -2.5 - alturaLigacao - raioFixo, -alturaMovel+ raioLigacao + 0.03);
    //rotacao em torno do eixo fixo
    glRotatef(angRotacao, 0,0,1);

    GLUquadricObj *fixo2 = gluNewQuadric();
    gluCylinder(fixo2, raioFixo, raioFixo, alturaFixo, 80, 50);
    //tampa do cilindro
    glNormal3d(0,0,1);
    glBegin(GL_POLYGON);
    for(double i=0; i<2*M_PI; i+=0.1)
    {
        glVertex3f(cos(i) * raioFixo, sin(i) * raioFixo, alturaFixo);
    }
    glEnd();
    glNormal3d(0,0,-1);
    glBegin(GL_POLYGON);
    for(double i=0; i<2*M_PI; i+=0.1)
    {
        glVertex3f(cos(i) * raioFixo, sin(i) * raioFixo, 0);
    }
    glEnd();
    glPopMatrix();
}

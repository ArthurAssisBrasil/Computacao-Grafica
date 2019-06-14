/***
    Classe que representa a biela do motor
***/
#include "Biela.h"
#include <math.h>
#include "myMath.h"

Biela::Biela(int t)
{
    this->tipo = t;
    altura = 2.5;
    raio = 0.2;
    xBiela = 0.0;
    if(t ==0)
    {
        yBiela = 0.0;
        dirRotacao = 1;
    }
    else
    {
        yBiela = -1.5;
        dirRotacao = -1;
    }
    zBiela =0.0;
}
//desenha biela
void Biela::draw(float angRotacao)
{
    //vermelho
    GLfloat mat_diffuse[] = { 1, 0, 0, 1 };
    GLfloat mat_ambient[] = { 1, 0, 0, 1 };

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  mat_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  mat_ambient);

    //desenha anel da biela que envolve a parte movel do virabrequim
    glPushMatrix();
    if(this->tipo == 0)
    {
        glTranslated(0, -2.5 - 0.4, -1.5/2.0 );
        //rotacao em torno do eixo fixo
        glTranslated(0, -1.5, 0);
        glRotatef(angRotacao, 0,0,1);
        glTranslated(0, 1.5, 0);
    }
    else
    {
        glTranslated(0, -2.5 -0.4 - 2*1.5, -1.5/2.0 );
        //rotacao em torno do eixo fixo
        glTranslated(0, 1.5, 0);
        glRotatef(angRotacao, 0,0,1);
        glTranslated(0, -1.5, 0);
    }
    glTranslatef(0,0, 1.5/2.0);
    float raioAnel = 0.4 + 0.01;
    float x;
    float y;
    float z1 = 1.5/7.0;
    float z2 = -1.5/7.0;
    //cilindro menor
    glBegin(GL_QUAD_STRIP);
    for(float i=0; i<= 2*M_PI + 0.1; i+=0.1)
    {
        glNormal3f(cos(i), sin(i), 0);
        x = (cos(i)*raioAnel);
        y = (sin(i)*raioAnel) ;
        glVertex3d(x, y,z1);
        glVertex3d(x, y,z2);
    }
    glEnd();
    //tampas entre os cilindros
    glNormal3d(0,0,1);
    glBegin(GL_QUAD_STRIP);
    for(double i=0; i<=2*M_PI + 0.1; i+=0.1)
    {
        glVertex3f(cos(i)*raioAnel, sin(i)*raioAnel, z1);
        glVertex3f(cos(i)*(raioAnel+0.2), sin(i) * (raioAnel+0.2), z1);
    }
    glEnd();

    glNormal3d(0,0,-1);
    glBegin(GL_QUAD_STRIP);
    for(double i=0; i<=2*M_PI + 0.1; i+=0.1)
    {
        glVertex3f(cos(i)*raioAnel, sin(i)*raioAnel, z2);
        glVertex3f(cos(i)*(raioAnel+0.2), sin(i) * (raioAnel+0.2), z2);
    }
    glEnd();
    //cilindro maior
    raioAnel += 0.2;
    glBegin(GL_QUAD_STRIP);
    for(float i=0; i<= 2*M_PI +0.1; i+=0.1)
    {
        glNormal3f(cos(i), sin(i), 0);
        x = (cos(i)*raioAnel);
        y = (sin(i)*raioAnel) ;
        glVertex3d(x, y,z1);
        glVertex3d(x, y,z2);
    }
    glEnd();
    glPopMatrix();

    float xVB, yVB;
    if(this->tipo == 0)
    {
        xVB = -1.5 * sin(grauParaRad(angRotacao));
        yVB = (1.5 * cos(grauParaRad(angRotacao))) -altura -1.5;
    }
    else
    {
        xVB = 1.5 * sin(grauParaRad(angRotacao));
        yVB = (-1.5 * cos(grauParaRad(angRotacao))) -altura -1.5;
    }
    float zVB = 0;

            //posiciona na posicao correta
    //h^2 = c1^2 + c2^2
    yBiela =  yVB + sqrt(pow(altura,2) -pow(xVB,2));
    glTranslated(0, yBiela, 0);
    glRotatef(90,1,0,0);

                //rotaciona para encostar no virabrequim
    if(xVB > 0){
        dirRotacao = 1;
    }
    else{
        dirRotacao = -1;
    }
    glRotatef(angVetores(xVB, yVB -yBiela, zVB,  0, -1, 0), 0, dirRotacao, 0);

    GLUquadricObj *biela = gluNewQuadric();
    gluCylinder(biela, raio, raio, altura, 30, 30);
    //tampas
    glNormal3d(0,0,1);
    glBegin(GL_POLYGON);
    for(double i=0; i<2*M_PI; i+=0.3)
    {
        glVertex3f(cos(i)* raio, sin(i)* raio, altura);
    }
    glEnd();

    glNormal3d(0,0,-1);
    glBegin(GL_POLYGON);
    for(double i=0; i<2*M_PI; i+=0.3)
    {
        glVertex3f(cos(i)* raio, sin(i)* raio, 0);
    }
    glEnd();
}


/***
    Classe que representa o pistao do motor
***/
#include "Pistao.h"
#include "myMath.h"
#include  <math.h>

Pistao::Pistao(int t)
{
    this->tipo = t;
    altura =1.1;
    raio = 1;
    xPistao =0.0; zPistao =0.0;
    if(t == 0){
        yPistao =0.0;
    }
    else{
        yPistao = -1.5;
    }
}
//desenha o pistao
void Pistao::draw(float angRotacao){
    //azul
    GLfloat mat_diffuse[] = { 0, 0, 1, 1 };
    GLfloat mat_ambient[] = { 0, 0, 1, 1 };

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  mat_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  mat_ambient);

    float xVB, yVB;
    if(this->tipo == 0){
        xVB = -1.5 * sin(grauParaRad(angRotacao));
        yVB = (1.5 * cos(grauParaRad(angRotacao))) -2.5 -1.5;
    }
    else{
        xVB = 1.5 * sin(grauParaRad(angRotacao));
        yVB = (-1.5 * cos(grauParaRad(angRotacao))) -2.5 -1.5;
    }

        //posiciona na posicao correta
    yPistao =  yVB + sqrt(pow(2.5,2) -pow(xVB,2));
    glTranslated(0, yPistao - 0.2, 0);

    glRotatef(270,1,0,0);
    GLUquadricObj *pistao = gluNewQuadric();
    gluCylinder(pistao, raio, raio, altura, 30, 30);


    glNormal3d(0,0,1);
    glBegin(GL_POLYGON);
    for(double i=0;i<2*M_PI; i+=0.05){
        glVertex3f(cos(i), sin(i), altura);
    }
    glEnd();
    glNormal3d(0,0,-1);
    glBegin(GL_POLYGON);
    for(double i=0;i<2*M_PI; i+=0.05){
        glVertex3f(cos(i), sin(i), 0);
    }
    glEnd();
}

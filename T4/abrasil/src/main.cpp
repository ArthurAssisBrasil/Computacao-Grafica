/***
    Arthur Medeiros de Assis Brasil
    abrasil@inf.ufsm.br

    Pressione 'Esc' para fechar o programa.

    O fps aparece no canto superior esquerdo.

    Pode aumentar e diminuir a rotacao do eixo variavel pressionando barra de espaco
        e a tecla 'c', respectivamente.

    Visualizacao ortografica do fps.
    Visualizacao perspectiva em wireframe/preenchimento do motor
    Para trocar a visualizacao para wireframe e apagar a parte do motor, pressione '1', '2', '3' e 4
    para alterar a camisa, pistao, biela e virabrequim, respectivamente.

    É feita iluminacao difusa e especular do motor.

    Pode-se rotacionar o motor clicando com o mouse e arrastando.

    Pode-se mover a camera com as setas para o eixo x e y, e a teclas 'home' e 'end', para o eixo z.
    Ela sempre se mantera olhando para o motor.
    Pode-se controlar a abertura da camera pressionando a tecla 'a' e 's',
        para aumentar e diminuir, respectivamente.

    Pode-se adicionar e remover pistoes do virabrequim, pressionando 'q' e 'w', respectivamente.

    As camisas dos pistoes sao transparentes.

    As camisas e o anel da biela que envolve a parte movel do virabrequim sao cilindros com espessura.

***/
#include <GL/glut.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <vector>

#include <Pistao.h>
#include <Biela.h>
#include <Virabrequim.h>
#include <Camisa.h>
#include <Frames.h>
#include <GLFont.h>

#define SCREEN_X 600
#define SCREEN_Y 600

int nPistoes = 4;

std::vector<Camisa> camisa;
std::vector<Pistao> pistao;
std::vector<Biela> biela;
std::vector<Virabrequim> virabrequim;

GLdouble obsX=10, obsY=0, obsZ=-15;

int cTipo = 0, pTipo = 0, bTipo = 0, vTipo = 0;

float angRotacao =0, step = 6;

float abertura = 45.0;
float znear  = 1;
float zfar   = 200;
float aspect = 1;

GLFont	* font;
Frames  * frames;
float     fps = 100.0;

GLfloat mat_specular[] = { 1, 1, 1, 1 };
GLfloat mat_shininess[] = { 5 };

GLfloat light_0_position[] = { 0, 8, 0, 1 };  //em cima da origem
GLfloat light_0_direction[] = {0, -1, 0};   //para a origem

GLfloat light_0_difuse[]   = { 0.7, 0.7, 0.7 };
GLfloat light_0_specular[] = { 1, 1, 1 };
GLfloat light_0_ambient[]  = { 0.1, 0.1, 0.1 };
GLint   light_0_cutoff     = 20; //angulo de abertura. Max eh 180.

float rx = 0, rz = 0;

void init()
{
    for(int i=0; i< nPistoes;i++){
        pistao.push_back( *new Pistao(i%2));
        biela.push_back( *new Biela(i%2));
        virabrequim.push_back( *new Virabrequim(i%2));
        camisa.push_back( *new Camisa());
    }
    frames  = new Frames();
    font    = new GLFont();

    glClearColor(0, 0, 0, 1);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);

    glLightfv(GL_LIGHT0, GL_POSITION,       light_0_position);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_0_direction);

    glLightfv(GL_LIGHT0, GL_DIFFUSE,        light_0_difuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR,       light_0_specular);
    glLightfv(GL_LIGHT0, GL_AMBIENT,        light_0_ambient);
    glLightf (GL_LIGHT0, GL_SPOT_CUTOFF,    light_0_cutoff);

    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    //habilita transparencia
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
}

////////////////////////////////////////////////////////////////////////////////////////
void display(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity( );
    //visao perspectiva
    gluPerspective(abertura, aspect, znear, zfar);
    glMatrixMode(GL_MODELVIEW);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity( );
    gluLookAt(obsX, obsY, obsZ,  //from. Posicao onde a camera esta posicionada
              0, 0, 0,  //to. Posicao absoluta onde a camera esta vendo
              0, 1, 0); //up. Vetor Up.
    //posicao e direcao da luz
    glLightfv(GL_LIGHT0, GL_POSITION,       light_0_position);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_0_direction);

    //transformacao dos modelos
    glRotatef ((GLfloat) rx, 0.0f, 1.0f, 0.0f);
    glRotatef ((GLfloat) rz, 1.0f, 0.0f, 0.0f);

     glTranslatef(0,2,0);
    //desenha pistoes, bielas, virabrequins e camisas
    for(int i=0; i<nPistoes; i++){
        glPushMatrix();
        if(pTipo == 0)
        {
            glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
            pistao[i].draw(angRotacao);
        }
        else if(pTipo == 1)
        {
            glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
            pistao[i].draw(angRotacao);
        }
        glPopMatrix();

        glPushMatrix();
        if(bTipo == 0)
        {
            glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
            biela[i].draw(angRotacao);
        }
        else if(bTipo == 1)
        {
            glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
            biela[i].draw(angRotacao);
        }
        glPopMatrix();

        glPushMatrix();
        if(vTipo == 0)
        {
            glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
            virabrequim[i].draw(angRotacao);
        }
        else if(vTipo == 1)
        {
            glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
            virabrequim[i].draw(angRotacao);
        }
        glPopMatrix();

        glPushMatrix();
        if(cTipo == 0)
        {
            glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
            camisa[i].draw(angRotacao);
        }
        else if(cTipo == 1)
        {
            glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
            camisa[i].draw(angRotacao);
        }
        glPopMatrix();

        glTranslatef(0,0, 2.5);
    }

    angRotacao+= step;

    glPushMatrix();

    //controle de fps e mostra na tela
    fps = frames->getFrames();

    static char text[50];
    font->startText();
    glColor3f(1,1,1);
    sprintf(text, "FPS:  %.0f", fps);
    font->print(20, 20, text);
    font->endText();
    glPopMatrix();

    glutSwapBuffers();
}


//faz a leitura da entrada do usuario
void keyboard(unsigned char key, int x, int y)
{
    key = tolower(key);
    switch(key)
    {
    case 27:
        exit(0);
        break;

    case ' ':
        step++;
        break;

    case 'c':
        if(step > 0)
            step--;
        break;

    case 'a':
        if(abertura < 170)
            abertura++;
        break;

    case 's':
        if(abertura > 10)
            abertura--;
        break;

    case '1':
        if(cTipo < 2)
            cTipo++;
        else
            cTipo = 0;
        break;

    case '2':
        if(pTipo < 2)
            pTipo++;
        else
            pTipo = 0;
        break;

    case '3':
        if(bTipo < 2)
            bTipo++;
        else
            bTipo = 0;
        break;

    case '4':
        if(vTipo < 2)
            vTipo++;
        else
            vTipo = 0;
        break;

    case 'q':
        if(pistao.size() < 255){
            pistao.push_back( *new Pistao(pistao.size()%2));
            biela.push_back( *new Biela(biela.size()%2));
            virabrequim.push_back( *new Virabrequim(virabrequim.size()%2));
            camisa.push_back( *new Camisa());
            nPistoes++;
        }
        break;

    case 'w':
        if(pistao.size() > 0){
            pistao.pop_back();
            biela.pop_back();
            virabrequim.pop_back();
            camisa.pop_back();
            nPistoes--;
        }
        break;
    }
}

void SpecialKeys(int key, int x, int y){
	switch (key) {
        case GLUT_KEY_LEFT :
            obsX -=2;
            break;
        case GLUT_KEY_RIGHT :
            obsX +=2;
            break;
        case GLUT_KEY_UP :
            obsY +=2;
            break;
        case GLUT_KEY_DOWN :
            obsY -=2;
            break;
        case GLUT_KEY_HOME :
            obsZ +=2;
            break;
        case GLUT_KEY_END :
            obsZ -=2;
            break;
		}
}

void MotionFunc(int x, int y)
{
    rx = x;
    rz = y;
}


////////////////////////////////////////////////////////////////////////////////////////
int main (int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );

    glutInitWindowSize (SCREEN_X, SCREEN_Y);
    glutInitWindowPosition (450, 10);
    // cria janela
    glutCreateWindow ("Motor 3D");
    init();

    glutDisplayFunc(display);
    glutMotionFunc(MotionFunc);
    glutIdleFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(SpecialKeys);
    glutMainLoop();
    return 0;
}

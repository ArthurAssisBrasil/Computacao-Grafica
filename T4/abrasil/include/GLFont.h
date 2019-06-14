/***
    Classe para desenhar algo na janela criada com OpenGL

    baseado no demo fps
***/
#ifndef GLFONT_H
#define GLFONT_H

#include <GL/gl.h>
#include <GL/glut.h>

class GLFont
{
public:
	void print(int x, int y, char *string);
	void endText();
	void startText();
	GLFont(){}
protected:
	GLboolean color_material, texture_2d, fog, lighting, depth_test;
};

#endif // GLFONT_H

/*
 *  SimpleView : reference design
 *  Author: HBF
 *  Version: 2022-10-06
 */
#include "Pyramid.hpp"
#include "Vector.hpp"

Pyramid::Pyramid()
{
    vertex[0][0] = -1;  vertex[0][1] = -1;  vertex[0][2] = 0;
    vertex[1][0] = 1;	vertex[1][1] = -1;  vertex[1][2] = 0;
    vertex[2][0] = 1;	vertex[2][1] =  1; 	vertex[2][2] = 0;
    vertex[3][0] = -1;	vertex[3][1] =  1;	vertex[3][2] = 0;
    vertex[4][0] = 0;	vertex[4][1] = 0.0;	vertex[4][2] = 1.5;

    face[0][0] = 0;	   face[0][1] = 1;	face[0][2] = 4;
    face[1][0] = 1;	   face[1][1] = 2;	face[1][2] = 4;
    face[2][0] = 2;	   face[2][1] = 3;	face[2][2] = 4;
    face[3][0] = 3;	   face[3][1] = 0;	face[3][2] = 4;

    r = 1.0;
    g = 1.0;
    b = 0;
}

void Pyramid::drawFace(GLint i)
{
	glColor3f(r, g, b);
	glBegin(GL_LINE_LOOP);
	for (int j=0; j<3; j++) {
	   glVertex3fv(vertex[face[i][j]]);
	}
	glEnd();
}

void Pyramid::draw()
{
    glPushMatrix();
    this->ctmMultiply();
	glScalef(s, s, s);
	for (int i = 0; i < 4; i++) {
		drawFace(i);
	}
    glPopMatrix();
}

/*
 *  SimpleView : reference design
 *  Author: HBF
 *  Version: 2022-10-06
 */
#ifndef CCUBE_H
#define CCUBE_H

#include <GL/glut.h>
#include "Shape.hpp"
#include "Vector.hpp"

#include "Camera.hpp"
#include "Light.hpp"

class Cube: public Shape {

protected:
	GLfloat vertex[8][3];
	GLint face[6][4];

	/* SimpleView2 properties */
	GLfloat faceColor[6][3];
	GLfloat faceNormal[6][3];
	GLfloat vertexColor[8][3];
	GLfloat vertexNormal[8][3];

	GLfloat r, g, b;

public:
	Cube();
	void draw();
	void drawFace(int);

	/* SimpleView2 properties */
	bool isFrontface(int faceindex, Camera camera);
	GLfloat getFaceShade(int faceindex, Light light);
	GLfloat getVertexShade(int vertexindex, Light light);

};

#endif

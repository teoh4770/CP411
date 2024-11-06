/*
 *  SimpleView : reference design
 *  Author: HBF
 *  Version: 2022-10-03 (update)
 */
#include "Cube.hpp"
#include "Camera.hpp"
#include <stdio.h>

extern Camera myCamera;
extern Light myLight;
extern CullMode cullMode;
extern RenderMode renderMode;

Cube::Cube() {
    vertex[0][0] = -1; vertex[0][1] = -1; vertex[0][2] = -1;
    vertex[1][0] = -1; vertex[1][1] = 1;  vertex[1][2] = -1;
    vertex[2][0] = 1;  vertex[2][1] = 1;  vertex[2][2] = -1;
    vertex[3][0] = 1;  vertex[3][1] = -1; vertex[3][2] = -1;
    vertex[4][0] = -1; vertex[4][1] = -1; vertex[4][2] = 1;
    vertex[5][0] = -1; vertex[5][1] = 1;  vertex[5][2] = 1;
    vertex[6][0] = 1;  vertex[6][1] = 1;  vertex[6][2] = 1;
    vertex[7][0] = 1;  vertex[7][1] = -1; vertex[7][2] = 1;

    face[0][0] = 0; face[0][1] = 1; face[0][2] = 2; face[0][3] = 3;
    face[1][0] = 7; face[1][1] = 6; face[1][2] = 5; face[1][3] = 4;
    face[2][0] = 0; face[2][1] = 4; face[2][2] = 5; face[2][3] = 1;
    face[3][0] = 2; face[3][1] = 1; face[3][2] = 5; face[3][3] = 6;
    face[4][0] = 3; face[4][1] = 2; face[4][2] = 6; face[4][3] = 7;
    face[5][0] = 0; face[5][1] = 3; face[5][2] = 7; face[5][3] = 4;

	// faceColor
	faceColor[0][0] = 1.0, faceColor[0][1] = 0.0; faceColor[0][2] = 0.0;
	// more

	// set or compute face normals
	faceNormal[0][0] = 0.0, faceNormal[0][1] = 0.0, faceNormal[0][2] = -1.0,
	// more
	
	
	// vertex color
	vertexColor[0][0] = 1.0, vertexColor[0][1] = 0.0; vertexColor[0][2] = 0.0;
	// more
	
	// vertex normal 
	vertexNormal[0][0] = -1; vertexNormal[0][1] = -1; vertexNormal[0][2] = -1;
	// more
	

	r = 1.0;
	g = 0.0;
	b = 0.0;
}

void Cube::drawFace(int i) {
	GLfloat shade = 1;
	switch (renderMode) {
	case WIRE:
	   glColor3f(r, g, b);
	   glBegin(GL_LINE_LOOP);
	   for (int j=0; j<4; j++) {
		   glVertex3fv(vertex[face[i][j]]);
	   }
       glEnd();
	   break;
	case CONSTANT:
	  if (myLight.on == true) shade = getFaceShade(i, myLight);
	   glColor3f(faceColor[i][0]*shade, faceColor[i][1]*shade, faceColor[i][2]*shade);
	   glBegin(GL_POLYGON);
	   for (int j=0; j<4; j++) {
		   glVertex3fv(vertex[face[i][j]]);
	   }
	   glEnd();
	  break;
	case FLAT:

	case SMOOTH:

	break;

	}
}

void Cube::draw() {
	glPushMatrix();
	this->ctmMultiply();
	glScalef(s, s, s);

	for (int i = 0; i < 6; i++) {
		if  (cullMode == BACKFACE ) {
			if (isFrontface(i, myCamera)) {
				drawFace(i);
			}
		}
		else {
			drawFace(i);
		}
	}
	
	
	glPopMatrix();
}

bool Cube::isFrontface(int faceindex, Camera camera) {
// your implementation
}


GLfloat Cube::getFaceShade(int faceindex, Light light) {
	GLfloat shade = 1, v[4], s[4], temp;

	// your implementation
	return shade;
}


GLfloat Cube::getVertexShade(int i, Light light) {
	GLfloat shade = 1, v[4], s[4], temp;
// your implementation
	return shade;
}


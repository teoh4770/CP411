#include "Surface.hpp"

extern RenderMode renderMode;

Surface::Surface() {
	reset();
}

void Surface::reset() {
	row = 0;
	col = 0;
}

void Surface::drawSurface() {
	switch (renderMode) {
	case WIRE:
        // your code to mesh wire
		for (int i = 0; i < row - 1; i++) {
			glBegin(GL_LINE_LOOP);
			for (int j = 0; j < col; j++) {
				glNormal3f(Normal[i][j].x, Normal[i][j].y, Normal[i][j].z); // Normal vector of that point
				glVertex3f(Pts[i][j].x, Pts[i][j].y, Pts[i][j].z); // Row i
				glVertex3f(Pts[i+1][j].x, Pts[i+1][j].y, Pts[i+1][j].z); // Row i + 1
			}
			glEnd();
		}
		break;
	case CONSTANT:
	case FLAT:
	case SMOOTH:
	case PHONG:
	case TEXTURE:
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_LINE);

        // your code to draw filled mesh, using GL_QUAD_STRIP
		for (int i = 0; i < row - 1; i++) {
			glBegin(GL_QUAD_STRIP);
			for (int j = 0; j < col; j++) {
				printf("");

				glNormal3f(Normal[i][j].x, Normal[i][j].y, Normal[i][j].z); // Normal vector of that point
				glVertex3f(Pts[i][j].x, Pts[i][j].y, Pts[i][j].z); // Row i
				glVertex3f(Pts[i+1][j].x, Pts[i+1][j].y, Pts[i+1][j].z); // Row i + 1
			}
			glEnd();
		}
		break;
	}
}

void Surface::draw() {
	glPushMatrix();
	ctmMultiply();
	glScalef(s * 0.01, s * 0.01, s * 0.01);		// to shrink the object to size of viewable
	drawSurface();
	glPopMatrix();
}


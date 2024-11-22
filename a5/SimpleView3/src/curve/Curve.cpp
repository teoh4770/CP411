#include "Curve.hpp"

Curve::Curve() {
	nPts = 0;
}

Curve::~Curve() {
}

void Curve::reset() {
	nPts = 0;
}

void Curve::drawCurve() {
	// your code
	// draw the polyline of the curve by OpenGL
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < nPts; i++) {
		glVertex2f(Pts[i].x, Pts[i].y);
	}
	glEnd();
}

void Curve::set2DView(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top) {
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(left, right, bottom, top);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	  glColor3f(1.0, 0.0, 0.0);  // x-axis red
	  glVertex2f(left/2, 0.0);
	  glVertex2f(right/2, 0.0);

	  glColor3f(0.0, 1.0, 0.0); // x-axis green
	  glVertex2f(0.0, bottom/2);
	  glVertex2f(0.0, top/2);
	glEnd();
}

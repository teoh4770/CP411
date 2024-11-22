/*
 *  SimpleView : reference design
 *  Author: HBF
 *  Version: 2022-11-07 (update)
 */
#ifndef CURVE_H
#define CURVE_H

#include <GL/glut.h>
#include "../Point.hpp"
#include "../Vector.hpp"
#include <math.h>

#define MAXSIZE 100

class Curve  {
protected:
	Point Pts[MAXSIZE];       // array to hold sequence of points on curve
	Vector Tangent[MAXSIZE];  // array to hold sequence of tangents of the points
public:
	GLint nPts;   // number of points of the curve
	Curve();
    ~Curve();
	void reset();
	void drawCurve();
	void set2DView(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top);
};

#endif

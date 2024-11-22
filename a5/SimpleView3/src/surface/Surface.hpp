/*
 *  SimpleView : reference design
 *  Author: HBF
 *  Version: 2022-11-07 (update)
 */
#ifndef SURFACE_H
#define SURFACE_H

#include <GL/glut.h>
#include "../curve/Curve.hpp"
#include "../Shape.hpp"
#include "../Point.hpp"
#include "../Vector.hpp"
#include <stdio.h>

#define MAXROW 73
#define MAXCOL 26

class Surface : public Shape {
public:
	GLint row; // number of rows of mesh
	GLint col; // number of columns of mesh
	Point  Pts[MAXROW][MAXCOL];    // array of mesh vertex
	Vector Normal[MAXROW][MAXCOL]; 	// array of vertex normal
	Surface();
	void reset();
	void drawSurface();
	void draw();
};

#endif

/*
 *  SimpleView : reference design
 *  Author: HBF
 *  Version: 2022-11-07 (update)
 */
#ifndef SOLAR_H
#define SOLAR_H

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "Sphere.hpp"

class Solar : public Shape {
protected:

public:
	Sphere *sun;
	Sphere *earth;
	Sphere *moon;
	Solar();
	void draw();
	void reset();
};

#endif

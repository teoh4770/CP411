/*
 *  SimpleView : reference design
 *  Author: HBF
 *  Version: 2022-11-07 (update)
 */
#ifndef RBM_H
#define RBM_H

#include <GL/glut.h>
#include "../curve/Bezier.hpp"
#include "../Shape.hpp"
#include "../Point.hpp"
#include "../Vector.hpp"
#include "Surface.hpp"
#include "math.h"

class RBM: public Surface {
public:
	GLint R;      // degree of rotation
	GLint S;      // rotation step
	GLint T;      // number of steps of rotation curve
	Bezier *curve;//rotation curve

	RBM();
   ~RBM();
	void reset();
	void RotateCurve();
	void setRotationCurve(Bezier *curve);
};

#endif

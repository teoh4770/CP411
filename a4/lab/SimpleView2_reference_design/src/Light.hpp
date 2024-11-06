/*
 *  SimpleView : reference design
 *  Author: HBF
 *  Version: 2022-10-03 (update)
 */

#ifndef LIGHT_HPP_
#define LIGHT_HPP_

#include <GL/glut.h>
#include "Shape.hpp"


class Light : public Shape {
	public:
		GLfloat I, Rd;
		GLboolean on;
		GLfloat size;
		Light();
		void Reset();
		void draw();
		void LightReset();
		void Increment(GLfloat);

};
#endif /* LIGHT_HPP_ */

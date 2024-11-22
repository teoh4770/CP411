/*
 *  SimpleView : reference design
 *  Author: HBF
 *  Version: 2022-10-03 (update)
 */

#ifndef LIGHT_HPP_
#define LIGHT_HPP_

#include <GL/glut.h>
#include "Shape.hpp"


class Light:public Shape {
	public:
		// I = light intensity
		// Kd = surface diffusion rate
		GLfloat I, Kd;
		GLboolean on;
		GLfloat size;
		GLfloat position[4];
		// Missing type properties: set to point, directional, ambient
		// Add one point light object

		Light();
		void Reset();
		void draw();
		void LightReset();
		void Increment(GLfloat);

};
#endif /* LIGHT_HPP_ */

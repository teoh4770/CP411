/*
 *  SimpleView : reference design
 *  Author: HBF
 *  Version: 2022-10-03 (update)
 */
#include "Light.hpp"
#include "Matrix.hpp"
#include <stdio.h>


Light::Light(){
	// Initial position
	mc.matrix[0][3] = 2; mc.matrix[1][3] = 2; mc.matrix[2][3] = 2;
	// x, y, z position
	position[0] = 0.0; position[1] = 0.0; position[2] = 0.0;
	// fourth value indicates a positional light source(1.0) or a directional one(0.0)
	position[3] = 1.0;

	I = 1.0;
	Kd = 1.0;
	on = true;
	size = 0.2;
}

void Light::Reset(){
	I = 1.0;
	Kd = 1.0;
	on = true;
	size = 30;
}

// Change light intensity
void Light::Increment(GLfloat p){
	I += p;

	// Make sure that the range of light intensity is between 0.01 to 1
	if (I < 0.03) {
		I = 0.01;
	} else if (I > 0.97) {
		I = 1;
	}

}


// actually draw the light
void Light::draw(){
	if(on == true){
		glPushMatrix();
			this->ctmMultiply();
			glLightfv(GL_LIGHT0, GL_POSITION, position);
			glDisable(GL_LIGHTING);

			glColor3f(I, I, I);
			glutSolidSphere(size, 10, 10);
			glEnable(GL_LIGHTING);
		glPopMatrix();
	}
}

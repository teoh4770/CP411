/*
 *  SimpleView : reference design
 *  Author: HBF
 *  Version: 2022-10-03 (update)
 */
#include "Light.hpp"
#include "Matrix.hpp"
#include <stdio.h>


Light::Light(){
	mc.mat[0][3] = 2.0;
	mc.mat[1][3] = 2.0;
	mc.mat[2][3] = 2.0;

	I = 1.0;
	Rd = 1.0;
	on = true;
	size = 0.2;
}

void Light::Reset(){
	I = 1.0;
	Rd = 1.0;
	on = true;
	size = 30;
}

void Light::Increment(GLfloat p){
// change light intensity

}

void Light::draw(){
	if(on == true){
		glPushMatrix();
		this->ctmMultiply();
		glutSolidSphere(size, 10, 10);
		glPopMatrix();
	}
}

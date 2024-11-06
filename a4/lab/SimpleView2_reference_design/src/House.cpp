/*
 *  SimpleView : reference design
 *  Author: HBF
 *  Version: 2022-10-06
 */

#include "House.hpp"
#include <stdio.h>

House::House()
{
	cube =  new Cube();
	cube->setParentMC(&mc);
	pyramid = new Pyramid();
	pyramid->setParentMC(&mc);
	pyramid->translate(0, 0, 1);
}

House::~House()
{
	delete cube;
	delete pyramid;
}

void House::draw()
{
    glPushMatrix();
    this->ctmMultiply();
	glScalef(s, s, s);
	cube->draw();
	glPopMatrix();

	glPushMatrix();
	this->ctmMultiply();
	glScalef(s, s, s);
	pyramid->draw();
	glPopMatrix();
}

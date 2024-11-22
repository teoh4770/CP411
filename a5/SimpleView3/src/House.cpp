#include "House.hpp"

House::House() {
    // The Cube and Pyramid constructors will be called automatically,
    // so no need to initialize anything here for now.
	base = new Cube();
	base->setParentMC(&mc);
	roof = new Pyramid();
	roof->setParentMC(&mc);
	roof->translate(0, 0, 1);
}

House::~House()
{
	delete base;
	delete roof;
}

void House::draw() {
    // Draw the Cube (base of the house)
    glPushMatrix();
		this->ctmMultiply();
		glScalef(s, s, s);
		base->draw();
	glPopMatrix();


	// Draw the Pyramid (roof of the house) on top of the Cube
	glPushMatrix();
		this->ctmMultiply();
		glScalef(s, s, s);
		roof->draw();
		glPopMatrix();
	glPopMatrix();
}

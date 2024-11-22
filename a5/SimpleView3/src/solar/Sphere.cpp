#include "Sphere.hpp"

extern RenderMode renderMode;

Sphere::Sphere(GLdouble size) {
	radius = size;
	splices = 50;
	stacks = 50;
	textureID = 0;
	r=1;
	g=1;
	b=1;
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL); // Render as a filled sphere
	gluQuadricTexture(sphere, GL_TRUE); // Enable texture
	gluQuadricNormals(sphere, GLU_SMOOTH); // Specify normal for lighting
}

void Sphere::draw() {
	glPushMatrix();
	ctmMultiply();

	switch (renderMode) {
		case WIRE:
		case CONSTANT:
		case FLAT:
		case SMOOTH:
			glColor3f(r, g, b);
			glutSolidSphere(radius,splices,stacks);
			break;

		case TEXTURE:
			// your code
			glColor3f(r, g, b);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textureID);
			gluSphere(sphere, radius, splices, stacks);
			glDisable(GL_TEXTURE_2D);
			break;

		case PHONG:
			// your code
			break;
	}

	glPopMatrix();
}



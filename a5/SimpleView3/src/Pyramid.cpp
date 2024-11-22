#include "Pyramid.hpp"

extern Camera myCamera;
extern CullMode cullMode;
extern RenderMode renderMode;
extern Light myLight;

Pyramid::Pyramid()
{
	// Set coordinate values for all vertices
	// Make the pyramid point along the Z-axis
	vertex[0][0] = 0.0; vertex[0][1] = 0.0; vertex[0][2] = 1.0;  // Peak (tip) of the pyramid on the Z-axis
	vertex[1][0] = -1.0; vertex[1][1] = -1.0; vertex[1][2] = 0.0;  // Bottom left
	vertex[2][0] = 1.0;  vertex[2][1] = -1.0; vertex[2][2] = 0.0;  // Bottom right
	vertex[3][0] = 1.0;  vertex[3][1] = 1.0;  vertex[3][2] = 0.0;  // Top right
	vertex[4][0] = -1.0; vertex[4][1] = 1.0;  vertex[4][2] = 0.0;  // Top left

	// Set how face is defined
	// Faces are defined by the indices of the vertices forming each triangular face
	face[0][0] = 0; face[0][1] = 1; face[0][2] = 2;  // Side face 1
	face[1][0] = 0; face[1][1] = 2; face[1][2] = 3;  // Side face 2
	face[2][0] = 0; face[2][1] = 3; face[2][2] = 4;  // Side face 3
	face[3][0] = 0; face[3][1] = 4; face[3][2] = 1;  // Side face 4

	// Face color
	faceColor[0][0] = 1.0; faceColor[0][1] = 0.0; faceColor[0][2] = 0.0;
	faceColor[1][0] = 0.0; faceColor[1][1] = 1.0; faceColor[1][2] = 0.0;
	faceColor[2][0] = 0.0; faceColor[2][1] = 0.0; faceColor[2][2] = 1.0;
	faceColor[3][0] = 1.0; faceColor[3][1] = 0.0; faceColor[3][2] = 1.0;

	// Face normal
	// Compute face normal using vertices
	for (int i = 0 ; i < 4; i++) {
		Vector V1 = Vector(vertex[face[i][1]][0]-vertex[face[i][0]][0], vertex[face[i][1]][1]-vertex[face[i][0]][1], vertex[face[i][1]][2]-vertex[face[i][0]][2]);
		Vector V2 = Vector(vertex[face[i][2]][0]-vertex[face[i][1]][0], vertex[face[i][2]][1]-vertex[face[i][1]][1], vertex[face[i][2]][2]-vertex[face[i][1]][2]);
		Vector V3 =  V1.cross(V2);
		V3.normalize();
		faceNormal[i][0] = V3.x;
		faceNormal[i][1] = V3.y;
		faceNormal[i][2] = V3.z;
	}

	r = 1; g = 1; b = 0;
}

void Pyramid::drawFace(int i)
{
	GLfloat shade = 1;

	switch (renderMode) {
		case WIRE:
			glColor3f(r, g, b);

			glBegin(GL_LINE_LOOP);
				glVertex3fv(vertex[face[i][0]]);
				glVertex3fv(vertex[face[i][1]]);
				glVertex3fv(vertex[face[i][2]]);
			glEnd();
			break;
		case CONSTANT: // Note: should be name solid, but that's fine too
		    // if (myLight.on == true) shade = getFaceShade(i, myLight);
			// Set the color of the face
			glColor3f(faceColor[i][0], faceColor[i][1], faceColor[i][2]);

			// GL_POLYGON -> draw solid color (YES)
			// GL_LINE_LOOP -> draw line only (X)
			glBegin(GL_POLYGON);
				glVertex3fv(vertex[face[i][0]]);
				glVertex3fv(vertex[face[i][1]]);
				glVertex3fv(vertex[face[i][2]]);
			glEnd();
		   break;
		case FLAT:
			glShadeModel(GL_FLAT);
			// Add my code
			break;
		case SMOOTH:
			 glEnable(GL_NORMALIZE);
			 glShadeModel(GL_SMOOTH);

			break;
		case PHONG:
			break;
		case TEXTURE:
			// set texture color to white by default
			glColor3f(1, 1, 1);
			// enable 2d texture
			glEnable(GL_TEXTURE_2D);
			// bind texture to the texture set on each face
			glBindTexture(GL_TEXTURE_2D,i);

			// draw the
			glBegin(GL_POLYGON);
				// define how the texture wraps over the object
				// top
				glTexCoord2f(0.5, 1.0); glVertex3fv(vertex[face[i][0]]);
				// bottom-left
				glTexCoord2f(0.0, 0.0); glVertex3fv(vertex[face[i][1]]);
				// bottom-right
				glTexCoord2f(0.0, 1.0); glVertex3fv(vertex[face[i][2]]);
			glEnd();
			glDisable(GL_TEXTURE_2D);
			break;
	}
}

void Pyramid::draw()
{

    glPushMatrix();
		// Multiply the transformation matrix to ctm and scale the shape
		this->ctmMultiply();
		glScalef(s, s, s);

		for (int i = 0; i < 4; i++) {
			if  (cullMode == BACKFACE ) {
				if (isFrontface(i, myCamera)) {
					drawFace(i);
				}
			}
			else {
				drawFace(i);
			}
		}
    glPopMatrix();
}

// implement this -> backface detecting formula
bool Pyramid::isFrontface(int faceindex, Camera camera) {
	bool frontFace = false;

	// your implementation
	GLfloat v[4];

	// Get face normal in MCS
	v[0] = faceNormal[faceindex][0];
	v[1] = faceNormal[faceindex][1];
	v[2] = faceNormal[faceindex][2];
	v[3] = 0.0;
	// Compute faceNormal in WCS
	mc.multiplyVector(v);

	if (pmc != NULL) {
		pmc->multiplyVector(v);
		frontFace = ((pmc->matrix[0][3] - camera.eye.x) * v[0] +
					(pmc->matrix[1][3] - camera.eye.y) * v[1] +
					(pmc->matrix[2][3] - camera.eye.z) * v[2]) < 0;
	} else {
		frontFace = ((mc.matrix[0][3] - camera.eye.x) * v[0] +
					 (mc.matrix[1][3] - camera.eye.y) * v[1] +
					 (mc.matrix[2][3] - camera.eye.z) * v[2]) < 0;
	}

	return frontFace;
}

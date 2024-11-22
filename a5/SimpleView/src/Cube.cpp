#include "Cube.hpp"

extern Camera myCamera;
extern CullMode cullMode;
extern RenderMode renderMode;
extern Light myLight;

Cube::Cube()
{

	// Vertex to be drawn
	vertex[0][0] = -1.0; vertex[0][1] = -1.0; vertex[0][2] =  1.0;
	vertex[1][0] = -1.0; vertex[1][1] = -1.0; vertex[1][2] = -1.0;
	vertex[2][0] = -1.0; vertex[2][1] =  1.0; vertex[2][2] = -1.0;
	vertex[3][0] = -1.0; vertex[3][1] =  1.0; vertex[3][2] =  1.0;
	vertex[4][0] =  1.0; vertex[4][1] = -1.0; vertex[4][2] =  1.0;
	vertex[5][0] =  1.0; vertex[5][1] = -1.0; vertex[5][2] = -1.0;
	vertex[6][0] =  1.0; vertex[6][1] =  1.0; vertex[6][2] = -1.0;
	vertex[7][0] =  1.0; vertex[7][1] =  1.0; vertex[7][2] =  1.0;

	// Set how face is define
	face[0][0] = 0; face[0][1] = 3; face[0][2] = 2; face[0][3] = 1;
	face[1][0] = 2; face[1][1] = 3; face[1][2] = 7; face[1][3] = 6;
	face[2][0] = 4; face[2][1] = 5; face[2][2] = 6; face[2][3] = 7;
	face[3][0] = 0; face[3][1] = 1; face[3][2] = 5; face[3][3] = 4;
	face[4][0] = 1; face[4][1] = 2; face[4][2] = 6; face[4][3] = 5;
	face[5][0] = 3; face[5][1] = 0; face[5][2] = 4; face[5][3] = 7;

	// Set face color in this order
	// red, green, blue, yellow, magenda, cyan
	faceColor[0][0] = 1.0; faceColor[0][1] = 0.0; faceColor[0][2] = 0.0;
	faceColor[1][0] = 0.0; faceColor[1][1] = 1.0; faceColor[1][2] = 0.0;
	faceColor[2][0] = 0.0; faceColor[2][1] = 0.0; faceColor[2][2] = 1.0;
	faceColor[3][0] = 1.0; faceColor[3][1] = 1.0; faceColor[3][2] = 0.0;
	faceColor[4][0] = 1.0; faceColor[4][1] = 0.0; faceColor[4][2] = 1.0;
	faceColor[5][0] = 0.0; faceColor[5][1] = 1.0; faceColor[5][2] = 1.0;

	// Compute face normal using vertices
	for (int i = 0 ; i < 6; i++) {
		Vector V1 = Vector(vertex[face[i][1]][0]-vertex[face[i][0]][0], vertex[face[i][1]][1]-vertex[face[i][0]][1], vertex[face[i][1]][2]-vertex[face[i][0]][2]);
		Vector V2 = Vector(vertex[face[i][2]][0]-vertex[face[i][1]][0], vertex[face[i][2]][1]-vertex[face[i][1]][1], vertex[face[i][2]][2]-vertex[face[i][1]][2]);
		Vector V3 =  V1.cross(V2);
		V3.normalize();
		faceNormal[i][0] = V3.x;
		faceNormal[i][1] = V3.y;
		faceNormal[i][2] = V3.z;
	}

	// vertex color
	vertexColor[0][0] = 1.0; vertexColor[0][1] = 0.0; vertexColor[0][2] = 0.0;
	vertexColor[1][0] = 0.0; vertexColor[1][1] = 1.0; vertexColor[1][2] = 0.0;
	vertexColor[2][0] = 0.0; vertexColor[2][1] = 0.0; vertexColor[2][2] = 1.0;
	vertexColor[3][0] = 1.0; vertexColor[3][1] = 1.0; vertexColor[3][2] = 0.0;
	vertexColor[4][0] = 1.0; vertexColor[4][1] = 0.0; vertexColor[4][2] = 1.0;
	vertexColor[5][0] = 0.0; vertexColor[5][1] = 1.0; vertexColor[5][2] = 1.0;
	vertexColor[6][0] = 1.0; vertexColor[6][1] = 0.0; vertexColor[6][2] = 0.5;
	vertexColor[7][0] = 1.0; vertexColor[7][1] = 1.0; vertexColor[7][2] = 0.3;

	// vertex normal
	// find the normal for the vertex of i (i is a 2d/3d vector)
	// where i1 is the vertex after i and i2 is the vertex before i


	r = 1; g = 1; b = 1;
}

void Cube::drawFace(int i)
{
	GLfloat shade = 1;

	switch (renderMode) {
		case WIRE:
			glColor3f(r, g, b);

			glBegin(GL_LINE_LOOP);
				glVertex3fv(vertex[face[i][0]]);
				glVertex3fv(vertex[face[i][1]]);
				glVertex3fv(vertex[face[i][2]]);
				glVertex3fv(vertex[face[i][3]]);
			glEnd();
			break;
		case CONSTANT: // Note: should be name solid, but that's fine too
		   if (myLight.on == true) shade = getFaceShade(i, myLight);
			// Set the color of the face
			glColor3f(faceColor[i][0]*shade, faceColor[i][1]*shade, faceColor[i][2]*shade);

			// GL_POLYGON -> draw solid color (YES)
			// GL_LINE_LOOP -> draw line only (X)
			glBegin(GL_POLYGON);
				glVertex3fv(vertex[face[i][0]]);
				glVertex3fv(vertex[face[i][1]]);
				glVertex3fv(vertex[face[i][2]]);
				glVertex3fv(vertex[face[i][3]]);
			glEnd();
		   break;
		case FLAT:
			glShadeModel(GL_FLAT);

			// Add my code
			break;
		case SMOOTH:
			glBegin(GL_POLYGON);
			 for (int j=0; j<4; j++) {
				 if (myLight.on == true)
					 shade = getVertexShade(face[i][j], myLight);
					 glColor3f(
							 vertexColor[face[i][j]][0]*shade,
							 vertexColor[face[i][j]][1]*shade,
							 vertexColor[face[i][j]][2]*shade
					 );
					 glNormal3f(
							 vertexNormal[face[i][j]][0],
							 vertexNormal[face[i][j]][1],
							 vertexNormal[face[i][j]][2]
					 );
					 glVertex3fv(vertex[face[i][j]]);
			 }
			 glEnd();
			break;
		case PHONG:
			break;
		case TEXTURE:
			glColor3f(1, 1, 1);
			glEnable(GL_TEXTURE_2D);
			// bind texture to the specific texture with id i
			glBindTexture(GL_TEXTURE_2D,i);
			glBegin(GL_QUADS);
			// define how the texture wraps over the object
			// s range [0, 1] horizontal, t range [0, 1] vertical
			// (0, 0) bottom left to the first vertex of the face
			glTexCoord2f(0.0, 0.0); glVertex3fv(&vertex[face[i][0]][0]);
			// (1, 0) top left to the second vertex of the face
			glTexCoord2f(1.0, 0.0); glVertex3fv(&vertex[face[i][1]][0]);
			glTexCoord2f(1.0, 1.0); glVertex3fv(&vertex[face[i][2]][0]);
			glTexCoord2f(0.0, 1.0); glVertex3fv(&vertex[face[i][3]][0]);
			glEnd();
			glDisable(GL_TEXTURE_2D);
			break;
	}
}

void Cube::draw()
{
    glPushMatrix();
		// Multiply the transformation matrix to ctm and scale the shape
		this->ctmMultiply();
		glScalef(s, s, s);

		for (int i = 0; i < 6; i++) {
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
bool Cube::isFrontface(int faceindex, Camera camera) {
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

GLfloat Cube::getFaceShade(int faceindex, Light light) {
	GLfloat shade = 1;
	GLfloat v[4];
	GLfloat s[4];
	GLfloat temp;

	// your implementation
	// assign v the first vertex of face[faceindex][0]
	// compute the position of vertex face[faceindex][0] in WCS
	// compute the light vector s[] = lightposition - face[faceindex][0]
	// normalize vector s
	// compute the normal of  face[faceindex] in WCS
	// normalize face normal


	// compute v dot s

	temp = v[0]*s[0]+v[1]*s[1]+v[2]*s[2];

	// compute shade factor

	shade = light.I * light.Kd * temp;

	if (shade < 0.01) shade = 0.1;
	if (shade > 0.99 ) shade = 0.9;

	return shade;
}


GLfloat Cube::getVertexShade(int i, Light light) {
	GLfloat shade = 1, v[4], s[4], temp;
// your implementation
	return shade;
}



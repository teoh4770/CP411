/*
 * Description: Represents a Pyramid with vertices, faces, and color,
 *              providing methods to draw the Pyramid.
 * Author: HBF(main), Chee Kian Teoh
 * Version: 2024-10-19
 */

/*
 * Requirement
 *
 * - Defines the pyramid's vertices and faces.
 * - Includes a draw function to render the pyramid in yellow color
 *   within the world coordinate (WC).
 *
 */

#ifndef CPYRAMID_H
#define CPYRAMID_H

#include <GL/glut.h> 	// Include GLUT for drawing the pyramid
#include "Shape.hpp"
#include "Vector.hpp"
#include "Camera.hpp"
#include "Light.hpp"

// Represent a Pyramid shape with drawing capability in OpenGL
class Pyramid: public Shape {
protected:
	// Members
	// Array to store the coordinates of the pyramid's 5 vertices
	// 2D array to store pyramid vertices
	GLfloat vertex[5][3];
	// 2D Array to store faces ->
	// the indices of the 3 vertices of each of the 4 faces
	GLint face[4][3];

	// SimpleView2 properties
	GLfloat faceColor[4][3];
	GLfloat faceNormal[4][3];
	GLfloat r, g, b;
public:
	Pyramid();
	void draw();
	void drawFace(int);

	/* SimpleView2 properties */
	bool isFrontface(int faceindex, Camera camera);
};

#endif

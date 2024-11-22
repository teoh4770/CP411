/*
 * Description: Represents a Cube with vertices, faces, and color,
 *              providing methods to draw the cube.
 * Author: HBF(main), Chee Kian Teoh
 * Version: 2024-10-19
 */

/*
 * Requirement
 *
 * - Defines the cube's vertices and faces.
 * - Includes a draw function to render the cube in red color
 *   within the world coordinate (WC).
 *
 */

#ifndef CCUBE_H
#define CCUBE_H

#include <GL/glut.h> 	// Include GLUT for drawing the cube
#include "Shape.hpp"
#include "Vector.hpp"

#include "Camera.hpp"
#include "Light.hpp"

// An alias template for a two-dimensional std::array
// template <typename T, std::size_t Row, std::size_t Col>
// using Array2d = std::array<std::array<T, Col>, Row>;

// Represent a Cube shape with drawing capability in OpenGL
class Cube: public Shape {
protected:
	// Members
	// Array to store the coordinates of the cube's 8 vertices
	// 2D array to store cube vertices
	GLfloat vertex[8][3];
	// 2D Array to store faces ->
	// the indices of the 4 vertices of each of the 6 faces
	GLint face[6][4];

	/* SimpleView2 properties */
	GLfloat faceColor[6][3];
	GLfloat faceNormal[6][3];
	GLfloat vertexColor[8][3];
	GLfloat vertexNormal[8][3];
	GLfloat r, g, b;
public:
	Cube();
	void draw();
	void drawFace(int);

	/* SimpleView2 properties */
	bool isFrontface(int faceindex, Camera camera);
	GLfloat getFaceShade(int faceindex, Light light);
	GLfloat getVertexShade(int vertexindex, Light light);
};

#endif

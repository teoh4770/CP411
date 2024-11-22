/*
 * Description: Represent a transformation matrix for 3D graphics and provide various methods for matrix operations
 * Author: HBF(main), Chee Kian Teoh
 * Version: 2024-10-19
 */
#ifndef CMATRIX_H
#define CMATRIX_H

#include <GL/gl.h>     // Include OpenGL header for GL types
#include <iostream>    // Include iostream for input/output operations

using namespace std;

// Essential for 3D transformation in the graphic pipeline
// Represent a transformation matrix for Model Coordinates (MC)
// Note: 4 x 4 matrix
class Matrix {
 public:
	// Members
	GLfloat matrix[4][4];  // This transformation matrix is for Model Coordinates (MC)

	// Constructor (default)
	Matrix();
	// Destructor
	~Matrix() {}

	// "loadIdentity" initializes the matrix as an identity matrix
	void loadIdentity();

	// "matrixPreMultiply" pre-multiplies this matrix with another matrix
	// Resulting matrix is equivalent to m * this matrix
	void matrixPreMultiply(Matrix* m);

	// "transpose" transposes the matrix (flips rows and columns)
	void transpose();

	// "normalize" normalizes the model coordinates of the matrix
	void normalize();

	// "multiplyVector" multiplies this matrix by a vector
	// Updates the vector v with the result of the multiplication
	void multiplyVector(GLfloat* v);


	// "rotateMatrix" applies a rotation transformation to the matrix
	// Parameters:
	// - x: x-axis rotation (GLfloat)
	// - y: y-axis rotation (GLfloat)
	// - z: z-axis rotation (GLfloat)
	// - angle: rotation angle in degrees (GLfloat)
	// rotateMatrix(x = 1, y = 0, z = 0, angle = 45) means rotate 45 degree w.r.t x-axis
	void rotateMatrix(GLfloat x, GLfloat y, GLfloat z, GLfloat angle);
};

#endif // CMATRIX_H

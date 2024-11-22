/*
 * Description: Implementation of Matrix class
 * Author: HBF(main), Chee Kian Teoh
 * Version: 2024-10-19
 */

#include "Matrix.hpp"
#include <stdio.h>
#include <math.h>
#include <iostream>

using namespace std;

/*
 * Matrix constructor (default)
 * Initializes a Matrix object as an identity matrix
 * Parameters: none
 * Returns: none
 * Usage: Matrix m;
 */
Matrix::Matrix() {
	loadIdentity();
}

/*
 * loadIdentity
 * Initializes the matrix as an identity matrix
 * Parameters: none
 * Returns: none
 * Usage: m.loadIdentity();
 */
void Matrix::loadIdentity() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i == j)
                matrix[i][j] = 1; // Set diagonal to 1
            else
                matrix[i][j] = 0; // Set non-diagonal to 0
        }
    }
}

/*
 * matrixPreMultiply
 * Pre-multiplies this matrix with another matrix
 * Parameters:
 *     - m: pointer to another Matrix object (Matrix*)
 * Returns: none
 * Usage: m1.matrixPreMultiply(&m2);
 */
void Matrix::matrixPreMultiply(Matrix* m) {
	// add code here
	Matrix result;

	// i = row
	// j = col
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			result.matrix[row][col] = 0; // Initialize the matrix entries

			// Compute pre-multiply
			result.matrix[row][col] = m->matrix[row][0] * this->matrix[0][col] + m->matrix[row][1] * this->matrix[1][col]
							 + m->matrix[row][2] * this->matrix[2][col] + m->matrix[row][3] * this->matrix[3][col];
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			matrix[i][j] = result.matrix[i][j];
		}
	}
}

/*
 * transpose
 * Transposes the matrix (flips rows and columns)
 * Parameters: none
 * Returns: none
 * Usage: m.transpose();
 */
void Matrix::transpose() {
	// add code here
	Matrix result;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			// switching row and column of entries
			result.matrix[i][j] = this->matrix[j][i];
		}
	}

	*this = result;
}


/*
 * normalize
 * Normalizes the model coordinates(MC) of the matrix
 * Parameters: none
 * Returns: none
 * Usage: m.normalize();
 */
void Matrix::normalize() {
	// add code here
	// implementation is in the slides

	// 1. normalize 1st vector in the current matrix
	GLfloat first_vector_norm = sqrt(
		matrix[0][0]*matrix[0][0] +
		matrix[1][0]*matrix[1][0] +
		matrix[2][0]*matrix[2][0]
	);

	matrix[0][0] = matrix[0][0] / first_vector_norm;
	matrix[1][0] = matrix[1][0] / first_vector_norm;
	matrix[2][0] = matrix[2][0] / first_vector_norm;

	// 2. make 3rd vector the cross product of 1st and 2nd vectors
	matrix[0][2] = matrix[1][0]*matrix[2][1] - matrix[2][0]*matrix[1][1];
	matrix[1][2] = matrix[2][0]*matrix[0][1] - matrix[0][0]*matrix[2][1];
	matrix[2][2] = matrix[0][0]*matrix[1][1] - matrix[1][0]*matrix[0][1];

	// 3. normalize 3rd vector in the current matrix
	GLfloat third_vector_norm = sqrt(
		matrix[0][2]*matrix[0][2] +
		matrix[1][2]*matrix[1][2] +
		matrix[2][2]*matrix[2][2]
	);

	matrix[0][2] = matrix[0][2] / third_vector_norm;
	matrix[1][2] = matrix[1][2] / third_vector_norm;
	matrix[2][2] = matrix[2][2] / third_vector_norm;

	// 4. make 2nd vector the cross product of 1st and 3rd vector
	matrix[0][1] = matrix[1][2]*matrix[2][0] - matrix[2][2]*matrix[1][0];
	matrix[1][1] = matrix[2][2]*matrix[0][0] - matrix[0][2]*matrix[2][0];
	matrix[2][1] = matrix[0][2]*matrix[1][0] - matrix[1][2]*matrix[0][0];

	// 5. make it homogenous
	matrix[0][3] = 0;
	matrix[1][3] = 0;
	matrix[2][3] = 0;
	matrix[3][3] = 1;
}


/*
 * multiplyVector ( v  <- matrix * v )
 * Multiplies this matrix by a vector
 * Parameters:
 *     - v: pointer to an array representing the vector (GLfloat*) array size 4
 * Returns: none
 * Usage: m.multiplyVector(vectorArray);
 */
void Matrix::multiplyVector(GLfloat* v) {
	// add code here
	GLfloat sum;
	GLfloat temp[4];

	for (int row = 0; row < 4; row++) {
		sum = 0;
		for (int col = 0; col < 4; col++) {
			sum += matrix[row][col] * v[col];
		}
		temp[row] = sum;
	}

	for (int i = 0; i < 4; i++) {
		v[i] = temp[i];
	}
}

/*
 * rotateMatrix
 * Applies a rotation transformation to the matrix
 * Parameters:
 *     - rx: x-axis rotation (GLfloat)
 *     - ry: y-axis rotation (GLfloat)
 *     - rz: z-axis rotation (GLfloat)
 *     - angle: rotation angle in degrees (GLfloat)
 * Returns: none
 * Usage: m.rotateMatrix(1.0f, 0.0f, 0.0f, 90.0f);
 */
void Matrix::rotateMatrix(GLfloat rx, GLfloat ry, GLfloat rz, GLfloat angle) {
	// Quite complex, reference to slide 3d_view lecture 7 around page 12
	// add code here
	GLfloat radian = angle * 3.1415926/180;
	GLfloat vector_magnitude = sqrt(rx*rx + ry*ry + rz*rz);
	GLfloat cosA = cos(radian);
	GLfloat oneCos = 1 - cosA;
	GLfloat sinA = sin(radian);
	// compute unit vector
	GLfloat unit_vector_x = (rx) / vector_magnitude;
	GLfloat unit_vector_y = (ry) / vector_magnitude;
	GLfloat unit_vector_z = (rz) / vector_magnitude;

	// matrix = this->matrix
	matrix[0][0] = unit_vector_x*unit_vector_x*oneCos + cosA;
	matrix[0][1] = unit_vector_x*unit_vector_y*oneCos - unit_vector_z*sinA;
	matrix[0][2] = unit_vector_x*unit_vector_z*oneCos + unit_vector_y*sinA;
	matrix[0][3] = 0;

	matrix[1][0] = unit_vector_y*unit_vector_x*oneCos + unit_vector_z*sinA;
	matrix[1][1] = unit_vector_y*unit_vector_y*oneCos + cosA;
	matrix[1][2] = unit_vector_y*unit_vector_z*oneCos - unit_vector_x*sinA;
	matrix[1][3] = 0;

	matrix[2][0] = unit_vector_z*unit_vector_x*oneCos - unit_vector_y*sinA;
	matrix[2][1] = unit_vector_z*unit_vector_y*oneCos + unit_vector_x*sinA;
	matrix[2][2] = unit_vector_z*unit_vector_z*oneCos + cosA;
	matrix[2][3] = 0;

	matrix[3][0] = 0;
	matrix[3][1] = 0;
	matrix[3][2] = 0;
	matrix[3][3] = 1;
}




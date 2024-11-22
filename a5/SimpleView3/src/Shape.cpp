/*
 * Description: Implementation of Shape class for managing transformations in 3D graphics
 * Author: HBF(main), Chee Kian Teoh
 * Version: 2024-10-19
 */

#include "Shape.hpp"
#include <stdio.h>     // C++ standard library for input/output
#include <iostream>    // Use for debugging outputs

using namespace std;

/*
 * Shape constructor (default)
 * Initializes a Shape object with identity matrix and default scale
 * Parameters: none
 * Returns: none
 * Usage: Shape s;
 */
Shape::Shape() {
    reset();
}

/*
 * Shape destructor
 * Destroys the Shape object (no dynamic allocation used)
 * Parameters: none
 * Returns: none
 * Usage: Shape s;
 */
Shape::~Shape() { }

/*
 * getMC
 * Returns the model coordinate matrix (MC)
 * Parameters: none
 * Returns: Matrix (the model coordinate matrix)
 * Usage: Matrix mc = shape.getMC();
 */
Matrix Shape::getMC() {
    return mc;
}

/*
 * setParentMC
 * Sets the parent model coordinate matrix (PM)
 * Parameters:
 *     - pm: pointer to the parent model coordinate matrix (Matrix*)
 * Returns: none
 * Usage: shape.setParentMC(&parentMC);
 */
void Shape::setParentMC(Matrix *pm) {
    pmc = pm;
}

/*
 * setScale
 * Sets the scale factor for the shape
 * Parameters:
 *     - x: scale factor (GLfloat)
 * Returns: none
 * Usage: shape.setScale(1.5f);
 */
void Shape::setScale(GLfloat x) {
    s = x;
}

/*
 * scaleChange
 * Changes the current scale by a given factor
 * Parameters:
 *     - x: scale factor (GLfloat)
 * Returns: none
 * Usage: shape.scaleChange(0.5f);
 */
void Shape::scaleChange(GLfloat x) {
    s += x;
}

GLfloat Shape::getScale() {
	return s;
}

/*
 * setId
 * Sets the ID for the shape
 * Parameters:
 *     - i: ID (GLint)
 * Returns: none
 * Usage: shape.setId(101);
 */
void Shape::setId(GLint i) {
    id = i;
}

/*
 * getId
 * Returns the shape's ID
 * Parameters: none
 * Returns: GLint (the shape's ID)
 * Usage: GLint id = shape.getId();
 */
GLint Shape::getId() {
    return id;
}


/*
 * translate
 * Applies translation transformation to the shape's model coordinate matrix
 * Parameters:
 *     - tx: translation along the x-axis (GLfloat)
 *     - ty: translation along the y-axis (GLfloat)
 *     - tz: translation along the z-axis (GLfloat)
 * Returns: none
 * Usage: shape.translate(1.0f, 2.0f, 3.0f);
 */
void Shape::translate(GLfloat tx, GLfloat ty, GLfloat tz) {
	mc.matrix[0][3] += tx;
	mc.matrix[1][3] += ty;
	mc.matrix[2][3] += tz;
	mc.matrix[3][3] = 1;
}

/*
 * rotate
 * Premultiply a rotation matrix to mc
 * Parameters:
 *     - rx: x-axis rotation (GLfloat)
 *     - ry: y-axis rotation (GLfloat)
 *     - rz: z-axis rotation (GLfloat)
 *     - angle: rotation angle in degrees (GLfloat)
 * Returns: none
 * Usage: shape.rotate(1.0f, 0.0f, 0.0f, 90.0f);
 */
void Shape::rotate(GLfloat rx, GLfloat ry, GLfloat rz, GLfloat angle) {
	// refers to lecture 7 slides 10
    Matrix m;						    // create a plain matrix
    m.rotateMatrix(rx, ry, rz, angle);  // set transformation matrix as rotation matrix
    mc.matrixPreMultiply(&m);			// premultiply the current matrix with this transformation matrix
}

void Shape::rotate(GLfloat x0, GLfloat y0, GLfloat z0, GLfloat rx, GLfloat ry, GLfloat rz, GLfloat angle) {
    // Translate the model so its origin is at the world origin (0,0,0)
	translate(-x0, -y0, -z0);
	rotate(rx, ry, rz, angle);
	translate(x0, y0, z0);
}

/*
 * rotateOrigin (understand)
 * Rotate MCS origin w.r.t. axis (x0,y0,z0)+u(rx,ry,yz) in WCS
 * Parameters:
 *     - x0, y0, z0: the origin of rotation (GLfloat)
 *     - rx, ry, rz: axis of rotation (GLfloat)
 *     - angle: rotation angle in degrees (GLfloat)
 * Returns: none
 * Usage: shape.rotateOrigin(1.0f, 2.0f, 3.0f, 1.0f, 0.0f, 0.0f, 90.0f);
 */
void Shape::rotateOrigin(GLfloat x0, GLfloat y0, GLfloat z0, GLfloat rx, GLfloat ry, GLfloat rz, GLfloat angle) {
	Matrix m;
	m.rotateMatrix(rx, ry, rz, angle);
	GLfloat v[4];
	v[0] = mc.matrix[0][3] - x0;
	v[1] = mc.matrix[1][3] - y0;
	v[2] = mc.matrix[2][3] - z0;
	v[3] = mc.matrix[3][3];
	m.multiplyVector(v);
	mc.matrixPreMultiply(&m);
	mc.matrix[0][3] = v[0] + x0;
	mc.matrix[1][3] = v[1] + y0;
	mc.matrix[2][3] = v[2] + z0;
	mc.matrix[3][3] = v[3];
}

/*
 * ctmMultiply
 * Multiplies the current transformation matrix (CTM) by the shape's model coordinate matrix
 * Parameters: none
 * Returns: none
 * Usage: shape.ctmMultiply();
 */
void Shape::ctmMultiply() {
    GLfloat M[16];
    M[0] = mc.matrix[0][0];
    M[1] = mc.matrix[1][0];
    M[2] = mc.matrix[2][0];
    M[3] = 0;
    M[4] = mc.matrix[0][1];
    M[5] = mc.matrix[1][1];
    M[6] = mc.matrix[2][1];
    M[7] = 0;
    M[8] = mc.matrix[0][2];
    M[9] = mc.matrix[1][2];
    M[10] = mc.matrix[2][2];
    M[11] = 0;
    M[12] = mc.matrix[0][3];
    M[13] = mc.matrix[1][3];
    M[14] = mc.matrix[2][3];
    M[15] = 1;
    glMultMatrixf(M); // OpenGL function for multiplying CTM with M
}

/*
 * reset
 * Resets the shape's model coordinate matrix to identity, clears parent matrix, and sets scale to 1
 * Parameters: none
 * Returns: none
 * Usage: shape.reset();
 */
void Shape::reset() {
    mc.loadIdentity(); // reset the transformation matrix

    if (pmc != NULL) {
    	std::cout << "pmc is not null" << "\n";
    }

    s = 1;
}

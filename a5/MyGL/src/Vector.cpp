/*
 * Description: Implementation of Vector class
 * Author: HBF(main), Chee Kian Teoh
 * Version: 2024-10-19
 */
#include "Vector.hpp"
#include <math.h> 		// Use math functions such as sqrt()
#include <stdio.h>		// Print out things to console in C++
#include <iostream>

using namespace std;

/*
 * Vector constructor (default)
 * Initializes a Vector object with default coordinates (0,0,0)
 * Parameters: none
 * Returns: none
 * Usage: Vector v; / Vector *vectors = new Vector[num_of_vectors];
 */
Vector::Vector(){
	x = 0.0;
	y = 0.0;
	z = 0.0;
}

/*
 * Vector constructor
 * Initializes a Vector object with given coordinates
 * Parameters:
 *     - dx: x coordinate value (GLfloat)
 *     - dy: y coordinate value (GLfloat)
 *     - dz: z coordinate value (GLfloat)
 * Returns: none
 * Usage: Vector v(dx, dy, dz);
 */
Vector::Vector(GLfloat dx, GLfloat dy, GLfloat dz){
	x = dx;
	y = dy;
	z = dz;
}

/*
 * set
 * Sets the vector's coordinates with given values
 * Parameters:
 *     - dx: x coordinate value (GLfloat)
 *     - dy: y coordinate value (GLfloat)
 *     - dz: z coordinate value (GLfloat)
 * Returns: none
 * Usage: v.set(1.0, 2.0, 3.0);
 */
void Vector::set(GLfloat dx, GLfloat dy, GLfloat dz){
	x = dx;
	y = dy;
	z = dz;
}

/*
 * set
 * Sets the vector's coordinates using another Vector object
 * Parameters:
 *     - v: a Vector object (Vector)
 * Returns: none
 * Usage: v.set(v2);
 */
void Vector::set(Vector& v){
	x = v.x;
	y = v.y;
	z = v.z;
}

/*
 * setDiff
 * Sets the vector to the difference between two points (a - b)
 * Parameters:
 *     - a: the first point (Point)
 *     - b: the second point (Point)
 * Returns: none
 * Usage: v.setDiff(p1, p2);
 */
void Vector::setDiff(Point& a, Point& b){
	x = a.x - b.x;
	y = a.y - b.y;
	z = a.z - b.z;
}

/*
 * cross
 * Computes the cross product of this vector and another vector (b)
 * Parameters:
 *     - b: the other vector (Vector)
 * Returns: the resulting vector as a Vector object
 * Usage: Vector c = v.cross(v2);
 */
Vector Vector::cross(Vector b) {
	Vector c(
		y * b.z - z * b.y,
		z * b.x - x * b.z,
		x * b.y - y * b.x
	);
	return c;
}

/*
 * dot
 * Computes the dot product of this vector and another vector (b)
 * Parameters:
 *     - b: the other vector (Vector)
 * Returns: the dot product as a GLfloat
 * Usage: GLfloat result = v.dot(v2);
 */
GLfloat Vector::dot(Vector b) {
	return x * b.x + y * b.y + z * b.z;
}

/*
 * build4tuple
 * Builds a 4-tuple representation of the vector for homogeneous coordinates
 * Parameters:
 *     - v: an array to hold the 4-tuple values (GLfloat[])
 * Returns: none
 * Usage: v.build4tuple(array);
 */
void Vector::build4tuple(GLfloat v[]) {
	v[0] = x;
	v[1] = y;
	v[2] = z;
	v[3] = 0.0f;
}

/*
 * normalize
 * Adjusts this vector to have unit length
 * Parameters: none
 * Returns: none
 * Usage: v.normalize();
 */
void Vector::normalize() {
	GLdouble sqs = x * x + y * y + z * z;
	if (sqs < 0.0000001) {
		std::cerr << "\n" << "normalize() gets vector (0,0,0)!";
		return; // does nothing to zero vectors
	}

	// 1 / (magnitude)
	GLfloat scaleFactor = 1.0 / (GLfloat)sqrt(sqs);
	x *= scaleFactor;
	y *= scaleFactor;
	z *= scaleFactor;
}

/*
 * flip
 * Reverses the direction of this vector
 * Parameters: none
 * Returns: none
 * Usage: v.flip();
 */
void Vector::flip() {
	x = -x;
	y = -y;
	z = -z;
}

/*
 * printVector
 * Prints the vector's coordinates in the format (x, y, z)
 * Parameters: none
 * Returns: none
 * Usage: v.printVector();
 */
void Vector::printVector() {
	printf("(x:%f, y:%f, z:%f)\n", x, y, z);
}

/*
 * Description: Represent a vector in 3D space and provide various methods for vector operations
 * Author: HBF(main), Chee Kian Teoh
 * Version: 2024-10-19
 */
#ifndef CVECTOR_H
#define CVECTOR_H

#include <GL/glut.h>
#include "Point.hpp"

class Vector {
 public:
	// Members
	GLfloat x, y, z;  // the coordinates

	// Constructors
	// (default)
	Vector();
	// (parameterized)
	// Initializes a Vector object with given coordinates
	Vector(GLfloat dx, GLfloat dy, GLfloat dz);

	// Methods
	// Setter methods
	// Sets the vector's coordinates to the specified values
	void set(GLfloat dx, GLfloat dy, GLfloat dz);

	// Setter (overload)
	// Sets this vector's coordinates to another vector's coordinates
	void set(Vector& v);

	// "setDiff" sets this vector to the difference between two points (a and b)
	// Result is equivalent to vector b - vector a
	void setDiff(Point& a, Point& b);


	// Transformation Methods
	// "flip" reverses the direction of this vector
	void flip();


	// Math methods
	// "normalize" adjusts this vector to unit length
	// The result is a vector with the same direction but a length of 1
	void normalize();

	// "cross" computes the cross product of this vector and another vector (b)
	// Resulting vector is perpendicular to the plane formed by both vectors
	Vector cross(Vector b);

	// "dot" calculates the dot product between this vector and another vector (b)
	// Returns a scalar that represents the magnitude of projection of one vector onto the other
	GLfloat dot(Vector b);

	// Not sure what to use this
	// "diff" calculates the difference between two points (a and b)
	// and returns a vector pointing from a to b
	Vector diff(Point& a, Point& b);



	// Utility methods
	// "build4tuple" builds a homogeneous coordinate representation for the vector
	// Sets v[0] = x, v[1] = y, v[2] = z, and v[3] = 0 (homogeneous system)
	// For transformation matrix
	void build4tuple(GLfloat v[]);
	// Debugging purpose
	void printVector();
};

#endif

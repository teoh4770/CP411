/*
 * Description: Describe the shape that representing a point in 3D space and the methods that we can use
 * Author: HBF(main), Chee Kian Teoh
 * Version: 2024-10-19
 */
#ifndef CPOINT_H
#define CPOINT_H

#include <GL/glut.h>

// Represent a Point in 3D space
class Point {
 public:
	// Members
	GLfloat x,y,z; //the coordinates

	// Constructor (default)
	Point();

	// Setter
	// Sets this point's coordinates to the specified values
	void set(GLfloat x, GLfloat y, GLfloat z);

	// Setter (overload)
	// Sets this point's coordinates to another point's coordinates
	void set(Point p);

	// "Normalize" normalize the point’s coordinates,
	// essentially converting the point into a unit vector
	// by dividing each component by the vector's magnitude.
	void Normalize();

	// "CalcNormal" computes the normal vector for two points (p1 and p2)
	// relative to the current point (the point object invoking the method, i.e., this
	// Use in cross product calculation later or for transformation purposes?
	Point CalcNormal(Point, Point);

	// "CrossProduct" computes the cross product of two vectors (represented by points)
	// and the result will be perpendicular to the plane formed by the two input vectors.
	// Normal vector basically.
	void CrossProduct(Point, Point);

	// Debugging purpose
	void printPoint();
};

#endif

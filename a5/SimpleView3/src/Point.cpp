/*
 * Description: Implementation of Point class
 * Author: HBF(main), Chee Kian Teoh
 * Version: 2024-10-19
 */
#include "Point.hpp"
#include <math.h> 		// use math functions such as sqrt()
#include <stdio.h>		// print out things to console

/*
 * Point constructor
 * Initializes a Point object with default coordinate (0,0,0)
 * Parameters: none
 * Returns: none
 * Usage: Point p; / Point *points = new Point[num_of_points];
 */
Point::Point(){
	x = 0.0;
	y = 0.0;
	z = 0.0;
}

/*
 * set
 * Sets the point's coordinates with given values
 * Parameters:
 *     - x1: x coordinate value (GLfloat)
 *     - y1: y coordinate value (GLfloat)
 *     - z1: z coordinate value (GLfloat)
 * Returns: none
 * Usage: p.set(1.0, 2.0, 3.0);
 */
void Point::set(GLfloat x1, GLfloat y1, GLfloat z1){
	x = x1;
	y = y1;
	z = z1;
}

/*
 * set
 * Sets the point's coordinates using another Point object
 * Parameters:
 *     - p: a Point object (Point)
 * Returns: none
 * Usage: p.set(p2);
 */
void Point::set(Point p){
	x = p.x;
	y = p.y;
	z = p.z;
}


/*
 * Normalize
 * Normalizes the point to a unit vector
 * Parameters: none
 * Returns: none
 * Usage: p.Normalize();
 */
void Point::Normalize(){
	GLdouble length;
	length = sqrt(x * x + y * y + z * z);

	// divide each coordinate with its length
	if (length != 0) {
		x /= length;
		y /= length;
		z /= length;
	} else {
		x = 0;
		y = 0;
		z = 0;
	}
}

/*
 * CalcNormal
 * Takes two points as parameters, computes the normal vector for two points (p1 and p2)
   relative to the current point (the point object invoking the method, i.e., this
 * Parameters:
 *     - p1: the first point (Point)
 *     - p2: the second point (Point)
 * Returns: the normal vector as a Point object
 * Usage: Point n = p.CalcNormal(p1, p2);
 */
Point Point::CalcNormal(Point p1, Point p2){
	Point n,pa,pb;

	// Difference of 2 points get the vector basically
	pa.x = p1.x - this->x;
	pa.y = p1.y - this->y;
	pa.z = p1.z - this->z;
	pb.x = p2.x - this->x;
	pb.y = p2.y - this->y;
	pb.z = p2.z - this->z;
	pa.Normalize();
	pb.Normalize();

	// Cross product calculation
	n.x = pa.y * pb.z - pa.z * pb.y;
	n.y = pa.z * pb.x - pa.x * pb.z;
	n.z = pa.x * pb.y - pa.y * pb.x;
	n.Normalize();

	return(n);
}

/*
 * CrossProduct
 * Calculates the cross product of two points, representing as normal vector
 * Parameters:
 *     - p1: the first point (Point)
 *     - p2: the second point (Point)
 * Returns: none (modifies the current Point object)
 * Usage: p.CrossProduct(p1, p2);
 */
void Point::CrossProduct(Point p1, Point p2){
	this->x = p1.y*p2.z - p1.z*p2.y;
	this->y = p1.z*p2.x - p1.x*p2.z;
	this->z = p1.x*p2.y - p1.y*p2.x;
}

/*
 * printPoint
 * Prints the point's coordinates in the format (x, y, z)
 * Parameters: none
 * Returns: none
 * Usage: p.printPoint();
 */
void Point::printPoint(){
	printf("(%f, %f, %f)\n",x,y,z);
}


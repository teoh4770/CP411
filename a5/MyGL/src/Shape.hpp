/*
 * Description: Represent a base class for 3D shapes, supporting transformations and object management in 3D space
 * Author: HBF(main), Chee Kian Teoh
 * Version: 2024-10-19
 */

#ifndef CSHAPE_H
#define CSHAPE_H

#include <GL/glut.h>     // Include OpenGL header for GL types and utilities
#include <iostream>      // Include iostream for input/output operations
#include <cmath>         // Include cmath for mathematical operations
#include "Matrix.hpp"    // Include Matrix class for transformations

using namespace std;

/*
 *  enumeration for culling options
 */
enum CullMode {
  NONE = 0,
  BACKFACE,
  GLCULL,
  GLDEPTHBUFFER,
  GLCULLDEPTHBUFFER
};

/*
 *  enumeration for shading models
 */
enum RenderMode {
  WIRE = 0,
  CONSTANT,
  FLAT,
  SMOOTH,
  PHONG,   // will be used in A5
  TEXTURE  // will be sed in A5
};

// The Shape class contains
// a transformation matrix mc
// that converts from Model Coordinate (MC) to World Coordinate (WC)
// and a scale factor s.
/**
 * Shape
 * The common class that will be inherited by model object class
 */
class Shape {
protected:
    // Members
    Matrix mc;          // Transformation matrix mc converts from MC to WC
    Matrix* pmc;        // Pointer to parent model coordinate system, if any
    GLfloat s;          // Scale factor for the object
    GLint id;           // Identifier for the object

public:
    // Constructor and Destructor
    // Constructor (default)
    Shape();


    // Destructor (virtual)
    virtual ~Shape();


    // Getter and Setter
    // Get and set model coordinate, parent model coordinate, scale factor and id of the model

    // "getMC" retrieves the model coordinate matrix object
    Matrix getMC();

    // "setParentMC" sets the parent model coordinate system pointer, if any
    void setParentMC(Matrix* pm);

    // "setScale" sets the scale factor of the shape
    void setScale(GLfloat x);

    // "scaleChange" changes the scale factor of the shape
    void scaleChange(GLfloat x);

    // "getScale" retrieves the scale of the shape
    GLfloat getScale();

    // "setId" sets the identifier for the shape
    void setId(GLint id);

    // "getId" retrieves the identifier of the shape
    GLint getId();


    // Methods for current model transformation
    // Model Transformation: translate, rotate, how about scaling?

    // "translate" translates the model coordinate origin by (tx, ty, tz)
    void translate(GLfloat tx, GLfloat ty, GLfloat tz);

    // Rotation
    // Premultiply a rotation matrix to mc will cause
    // rotates around the global origin, but model's body remain fix
    // Since rotation is applied on
    void rotate(GLfloat rx, GLfloat ry, GLfloat rz, GLfloat angle);

    // axis(x0, y0, z0): point in WCS that serve as a base or origin for the rotation
    // a fixed point where the model rotate around
    // "rotate" rotates the shape w.r.t. axis (x0, y0, z0) + u(rx, ry, rz) in WCS
    // u(rx, ry, rz): direction of rotation axis, (1, 0, 0) rotation around x axis, (0, 1, 0) rotation around y axis
    void rotate(GLfloat x0, GLfloat y0, GLfloat z0, GLfloat rx, GLfloat ry, GLfloat rz, GLfloat angle);

    // "rotateOrigin" rotates the shape's model coordinate origin w.r.t. axis (x0, y0, z0) + u(rx, ry, rz) in WCS
    void rotateOrigin(GLfloat x0, GLfloat y0, GLfloat z0, GLfloat rx, GLfloat ry, GLfloat rz, GLfloat angle);

    // "ctmMultiply" multiplies the current transformation matrix (CTM) by the model coordinates (MC)
	// CTM * MC
	void ctmMultiply();


	// Utility Method

    // "reset"
	// Set the current shape transformation matrix to identity matrix
	// Set the parent model coordinate to null
	// Set the scale factor to 1
    void reset();


    // Pure virtual "draw" function to be implemented by derived classes
    virtual void draw() = 0;
};

#endif // CSHAPE_H

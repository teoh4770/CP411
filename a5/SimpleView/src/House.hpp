/*
 * Description: Represents a House object with a cube base and a pyramid top.
 * Author: HBF(main), Chee Kian Teoh
 * Version: 2024-10-19
 */

#ifndef CHOUSE_H
#define CHOUSE_H

#include <GL/glut.h>     // Include GLUT for rendering
#include "Shape.hpp"
#include "Cube.hpp"      // Include the Cube class for the base
#include "Pyramid.hpp"   // Include the Pyramid class for the roof

class House: public Shape {
private:
    Cube* base;      // Cube as the base (walls of the house)
    Pyramid* roof;   // Pyramid as the top (roof of the house)
public:
    House();        // Constructor
    ~House();
    void draw();    // Function to draw the house
};

#endif

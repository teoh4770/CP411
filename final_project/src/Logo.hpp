#ifndef CLOGO_H
#define CLOGO_H

#include <GL/glut.h> // Include GLUT for drawing the logo
#include "Score.hpp"

// structures
typedef struct {
	GLfloat r, g, b;
} Color;

typedef struct {
	GLfloat x, y;
} Position;

typedef struct {
	GLfloat x, y;
} Velocity;

typedef struct {
	GLfloat width, height;
} Dimension;


class Logo {

public:
	// Properties
	Position position;
	Velocity velocity;
	Dimension size;
	Color bgColor;

	Logo();

	void move();
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

	void detectCollision(GLsizei screenWidth, GLsizei screenHeight, Score &score);
	void changeRandomColor();
	void draw();
};

#endif

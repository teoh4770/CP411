#include <windows.h>
#include <mmsystem.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm> // For std::max

#include "Logo.hpp"
#include "Score.hpp"
#include "Font.hpp"

// Declare class instances
Logo logo;
Score score;

// Global variables configuration
// Constants
const GLfloat BG_COLOUR[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLint REFRESH_RATE_MS = 16; // 16ms = 60FPS (should change this to fps)


// Window size
GLsizei windowWidth = 1280, windowHeight = 800;

// Rendering text
char str[100];
void* fontType = GLUT_BITMAP_HELVETICA_18;

// Rendering text function
void message(char str[], GLsizei windowWidth, GLsizei windowHeight,
		GLfloat lineHeight, void* font) {
	Font myFont(font);  // Create font object

	int textWidth = myFont.calculateTextMaxWidth(str);	// Calculate text width
	GLfloat startX = (windowWidth - textWidth) / 2.0f;	// Center position x
	GLfloat startY = windowHeight;

	// Set color and raster position
	glColor3f(1.0, 1.0, 1.0);
	myFont.renderTextCenter(str, startX, startY, lineHeight);
}

void init() {
// Setup both the display mode and window
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("DVD Logo Challenge - Wen Tao & Chee Kian");
	glClearColor(BG_COLOUR[0], BG_COLOUR[1], BG_COLOUR[2], BG_COLOUR[3]);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, windowWidth, 0, windowHeight); // origin at bottom-left
}

void handleDisplay() {
// Render the DVD Logo and message
	glClear(GL_COLOR_BUFFER_BIT);

	logo.draw();

	char scoreMsg[200];
	char helpMsg[200] =
			"GOAL: HIT THE CORNERS!\nUSE ARROW KEYS TO GUIDE THE DVD LOGO\n";
	snprintf(scoreMsg, sizeof(scoreMsg), "SCORE: %d\n", score.getPoints());
	message(scoreMsg, windowWidth, windowHeight / 8, 30,
			GLUT_BITMAP_HELVETICA_18);
	message(helpMsg, windowWidth, (windowHeight / 8) - 30, 16,
			GLUT_BITMAP_HELVETICA_12);

	glFlush();
	glutSwapBuffers();
}

void handleResize(GLint newWidth, GLint newHeight) {
// Reset viewport and projection parameters
// Update display window size parameters
	glViewport(0, 0, newWidth, newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, windowWidth, 0, windowHeight); // origin at bottom-left

	windowWidth = newWidth;
	windowHeight = newHeight;
}

void handleSpecialKey(int key, int, int) {
// here's where I would update the velocity of the moving object
	switch (key) {
	case GLUT_KEY_UP:
		logo.moveUp();
		break;
	case GLUT_KEY_DOWN:
		logo.moveDown();
		break;
	case GLUT_KEY_LEFT:
		logo.moveLeft();
		break;
	case GLUT_KEY_RIGHT:
		logo.moveRight();
		break;
	default:
		puts("Invalid key, only arrow keys should be used!");
	}
}

void update(int value) {
// move the logo
	logo.move();

// detect logo collision
	logo.detectCollision(windowWidth, windowHeight, score);

	glutPostRedisplay();
	glutTimerFunc(REFRESH_RATE_MS, update, 0);
}

int main(int argc, char** argv) {
// Initialize the window
// Setup events and their handlers
	glutInit(&argc, argv);
	init();

	glutDisplayFunc(handleDisplay);
	glutReshapeFunc(handleResize);
	glutSpecialFunc(handleSpecialKey);
	glutTimerFunc(REFRESH_RATE_MS, update, 0);

	glutMainLoop();
	return 0;
}

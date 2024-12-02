#include <windows.h>
#include <mmsystem.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// screen size
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// DVD logo properties
float logoX = 100.0f, logoY = 100.0f; // original position
float logoRadius = 20.0f;             // logo radius? i want it to be rectangle
float velocityX = 2.0f, velocityY = 2.0f; // velocity

int score = 0; // scoring system

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // display dvd
    glColor3f(0.0f, 0.7f, 1.0f); // blue
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; ++i) {
        float angle = i * 3.14159f / 180.0f;
        glVertex2f(logoX + cos(angle) * logoRadius, logoY + sin(angle) * logoRadius);
    }
    glEnd();

    glutSwapBuffers();
}

void update(int value) {
    // update dvd velocity?
    logoX += velocityX;
    logoY += velocityY;

    // detection collision
    if (logoX - logoRadius <= 0 || logoX + logoRadius >= SCREEN_WIDTH) {
        velocityX = -velocityX; // horizontal speed reversal
        if (logoX - logoRadius <= 0 && logoY - logoRadius <= 0) ++score; // left top corner
        if (logoX + logoRadius >= SCREEN_WIDTH && logoY + logoRadius >= SCREEN_HEIGHT) ++score; // right bottom corner
    }
    if (logoY - logoRadius <= 0 || logoY + logoRadius >= SCREEN_HEIGHT) {
        velocityY = -velocityY; // vertical speed reversal
        if (logoX - logoRadius <= 0 && logoY - logoRadius <= 0) ++score; // let top corner
        if (logoX + logoRadius >= SCREEN_WIDTH && logoY + logoRadius >= SCREEN_HEIGHT) ++score; // right bottom corner
    }

    glutPostRedisplay(); // redisplay
    glutTimerFunc(16, update, 0); // update every 16ms
}

void handleResize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT); // setup 2d display
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutCreateWindow("DVD Logo Challenge - prototype");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // black background

    glutDisplayFunc(display);
    glutReshapeFunc(handleResize);
    glutTimerFunc(16, update, 0); // start the timer?

    glutMainLoop();
    return 0;
}

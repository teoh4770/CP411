#include <GL/glut.h>
#include <time.h>
#include <stdio.h>

// Animation using system time
// Note: oldTime must be initialized before the animation loop begins
// Note: If theta accumulates each frame (e.g., theta += rotation), glLoadIdentity()
//       will be necessary to reset the model-view matrix each frame before applying rotation.

// theta: angle of rotation for the cube
GLfloat theta;
// used to track time between frames
int oldTime, newTime;

// move(): responsible for updating the angle of rotation (theta) based on the time elapsed since the last frame
void move() {
    // 0.1 - 1 degrees per frame is a reasonable range for smooth rotation
    GLfloat speed = 0.05; // Speed factor for rotation
    newTime = clock(); // Set to the current time using clock()

    // Calculate the time difference between the current and previous frame
    // - The difference between oldTime and newTime gives us the amount of time passed since the last frame.
    // - This makes the rotation speed consistent, regardless of how fast or slow the system is running the loop.
    // - This approach makes the animation frame rate independent, so it runs at the same speed on different devices.

    // Update theta based on the elapsed time per frame to ensure smooth and stable rotation
    theta = (newTime - oldTime) * speed; // Calculate rotation angle based on time elapsed
    oldTime = newTime; // Update oldTime for the next frame
    glutPostRedisplay(); // Request a redraw, which calls the display function
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);	 // Clear the buffer every time it is display (refresh)
	// glLoadIdentity();			 // Uncomment if theta accumulates (e.g., theta += rotation) to reset the model-view matrix
	glRotatef(theta, 0.5, 1.0, 0.0); // Rotate around xy-axis
	glutWireCube(1);				 // Draw the cube
	glutSwapBuffers();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(300, 300);
	glutCreateWindow("Simple animation");
	oldTime = clock(); // Initiate oldTime
	glutDisplayFunc(display);
	glutIdleFunc(move); // Call move function when idle
	glutMainLoop();
	return 0;
}

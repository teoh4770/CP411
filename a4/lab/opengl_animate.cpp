#include <GL/glut.h>
#include <time.h>

GLfloat theta;
int oldTime = clock(), newTime;

void move() {
	GLfloat speed = 0.2;
	oldTime = clock();
	theta = (newTime - oldTime) * speed;
	oldTime = newTime;
	glutPostRedisplay();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glRotatef(0.1, 0.0, 0.0, theta);
	glutWireCube(1);
	glutSwapBuffers();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(300, 300);
	glutCreateWindow("Simple animation");
	glutDisplayFunc(display);
	glutIdleFunc(move);
	glutMainLoop();
	return 0;
}

/*
 *  SimpleView2 : reference design
 *  Author: HBF
 *  Version: 2022-10-06 (update)
 */
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Menu.hpp"
#include "World.hpp"
#include "Camera.hpp"
#include "Light.hpp"

GLint winWidth = 800, winHeight = 800;
GLint isInMove = 0,    /* flag for mouse motion */
	  xbegin = 0,      /* hold mouse down xMouse */
	  csType = 1,     /* coordinate system type: 1 for MCS, 2 for WCS, 3 for VCS */
	  transType = 4;  /* depends on csType  */

CullMode cullMode = NONE;          /* culling option */
RenderMode renderMode = CONSTANT;  /* shade option  */

World myWorld;
Camera myCamera;
Light myLight;
Shape *selectObj = NULL;  /* pointer to selected object */

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	selectObj = myWorld.searchById(1);
	myLight.on = false;
}


void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	myCamera.setProjectionMatrix();
	myWorld.draw();
	myLight.draw();
	glFlush();
	glutSwapBuffers();
}

void winReshapeFcn(GLint newWidth, GLint newHeight) {
	glViewport(0, 0, newWidth, newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	winWidth = newWidth;
	winHeight = newHeight;
}

void mouseActionFcn(int button, int state, int xMouse, int yMouse) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		isInMove = 1;
		xbegin = xMouse;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		isInMove = 0;
	}
}

void mouseMotionFcn(GLint xMouse, GLint yMouse) {
	if (isInMove) {
		if (csType == 1){
			MCSTransform(xMouse);
		}
		else if (csType == 2){
			WCSTransform(xMouse);
		}
		else if(csType == 3){
			VCSTransform(xMouse);
		}
		else if(csType == 4) {
			lightTransform(xMouse);
		}
		glutPostRedisplay();
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("SimpleView2 reference design (HBF)");
	init();
	menu();
	glutDisplayFunc(display);
	glutMotionFunc(mouseMotionFcn);
	glutMouseFunc(mouseActionFcn);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}

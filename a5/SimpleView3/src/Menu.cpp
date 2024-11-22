/*
 * Description: SimpleView reference design
 * Author: HBF
 * Version: 2022-10-03
 */
#include <time.h>
#include "Menu.hpp"
#include "World.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "solar/Solar.hpp"
#include "solar/Sphere.hpp"
#include "curve/Bezier.hpp"
#include "surface/RBM.hpp"
#include <stdio.h>

extern GLint csType;
extern Shape* selectObj;
extern GLint transType, xbegin;
extern World myWorld;
extern Camera myCamera;
extern Light myLight;
extern Solar mySolar;
extern Bezier myBezier;
extern RBM myRBM;

extern CullMode cullMode;
extern RenderMode renderMode;
extern int oldTime, newTime;

extern GLint displayOption;

void menu() {
	GLint Object_Menu = glutCreateMenu(ObjSubMenu);
	glutAddMenuEntry("Cube", 1);
	glutAddMenuEntry("Pyramid", 2);
	glutAddMenuEntry("House", 3);

	GLint MCTrans_Menu = glutCreateMenu(MCSTransMenu);
	glutAddMenuEntry("Rotate x", 1);
	glutAddMenuEntry("Rotate y", 2);
	glutAddMenuEntry("Rotate z", 3);
	glutAddMenuEntry("Scale", 4);

	GLint WCTrans_Menu = glutCreateMenu(WCSTransMenu);
	glutAddMenuEntry("Rotate x", 1);
	glutAddMenuEntry("Rotate y", 2);
	glutAddMenuEntry("Rotate z", 3);
	glutAddMenuEntry("Translate x", 4);
	glutAddMenuEntry("Translate y", 5);
	glutAddMenuEntry("Translate z", 6);

	GLint VCTrans_Menu = glutCreateMenu(VCSTransMenu);
	glutAddMenuEntry("Rotate x", 1);
	glutAddMenuEntry("Rotate y", 2);
	glutAddMenuEntry("Rotate z", 3);
	glutAddMenuEntry("Translate x", 4);
	glutAddMenuEntry("Translate y", 5);
	glutAddMenuEntry("Translate z", 6);
	glutAddMenuEntry("Clipping Near", 7);
	glutAddMenuEntry("Clipping Far", 8);

	// cull Menu
	GLint Cull_Menu = glutCreateMenu(cullMenu);
	glutAddMenuEntry("No culling", 1);
	glutAddMenuEntry("My back-face", 2);
	glutAddMenuEntry("OpenGL cull", 3);
	glutAddMenuEntry("OpenGL depth buffer", 4);
	glutAddMenuEntry("OpenGL back-face & depth buffer", 5);

	// light menu
	GLint Light_Menu = glutCreateMenu(lightMenu);
	glutAddMenuEntry("Turn on light", 8);
	glutAddMenuEntry("Turn off light", 9);
	glutAddMenuEntry("Change intensity", 7);
	glutAddMenuEntry("Rotate x ", 1);
	glutAddMenuEntry("Rotate y ", 2);
	glutAddMenuEntry("Rotate z", 3);
	glutAddMenuEntry("Translate x ", 4);
	glutAddMenuEntry("Translate y ", 5);
	glutAddMenuEntry("Translate z", 6);

	// shade menu
	GLint Shading_Menu = glutCreateMenu(shadeMenu);
	glutAddMenuEntry("No shading", 1);
	glutAddMenuEntry("My constant shading", 2);
	glutAddMenuEntry("OpenGL flat shading", 3);
	glutAddMenuEntry("OpenGL smooth shading", 4);

	// animate menu
	GLint Animate_Menu = glutCreateMenu(animateMenu);
	glutAddMenuEntry("Single object", 1);
	glutAddMenuEntry("Multiple object", 2);
	glutAddMenuEntry("Simple solar system", 3);  /* SimppleView3 feature */
	glutAddMenuEntry("Stop animation", 4);

	/* SimppleView3 features */
	GLint Curve_Surface_Menu = glutCreateMenu(curveSurfaceMenu);
	glutAddMenuEntry("Get control points", 1);
	glutAddMenuEntry("Bezier curve", 2);
	glutAddMenuEntry("Bezier curve rotation surface", 3);
//	glutAddMenuEntry("Cubic spline", 4);
//	glutAddMenuEntry("Cubic spline rotation surface", 5);

	glutCreateMenu(mainMenu);
	glutAddMenuEntry("Reset", 1);
	glutAddSubMenu("Select Object", Object_Menu);
	glutAddSubMenu("MCS Transformations", MCTrans_Menu);
	glutAddSubMenu("WCS Transformations", WCTrans_Menu);
	glutAddSubMenu("VCS Transformations", VCTrans_Menu);
	glutAddSubMenu("Culling", Cull_Menu);
	glutAddSubMenu("Light", Light_Menu);
	glutAddSubMenu("Shading", Shading_Menu);
	glutAddSubMenu("Animation", Animate_Menu);
	glutAddSubMenu("Curve & Surface", Curve_Surface_Menu); /* SimpleView3 feature */
	glutAddMenuEntry("Quit", 2);
}

void mainMenu(GLint option) {
	switch (option){
		case 1:
			myWorld.reset();
			myCamera.setDefaultCamera();
			break;
		case 2:
			exit(0);
			break;
	}
	glutPostRedisplay();
}

void ObjSubMenu(GLint objectOption)
{
	selectObj = myWorld.searchById(objectOption);
	glutPostRedisplay();
}


void MCSTransMenu(GLint transOption) {
	csType = 1;
	transType = transOption;
	glutPostRedisplay();
}


void WCSTransMenu(GLint transOption) {
	csType = 2;
	transType = transOption;
	glutPostRedisplay();
}

void VCSTransMenu(GLint transOption) {
	csType = 3;
	transType = transOption;
	glutPostRedisplay();
}

void MCSTransform(GLint x){
	GLfloat x0, y0, z0, rx, ry, rz, theta;
	theta = (xbegin - x > 0) ? 1 : -1;

	x0 = selectObj->getMC().matrix[0][3];
	y0 = selectObj->getMC().matrix[1][3];
	z0 = selectObj->getMC().matrix[2][3];

	if (transType == 1) { //model rotate x
		rx = selectObj->getMC().matrix[0][0];
		ry = selectObj->getMC().matrix[1][0];
		rz = selectObj->getMC().matrix[2][0];
		selectObj->rotate(x0, y0, z0, rx, ry, rz, theta * 0.5);
	}
	else if (transType == 2) { //model rotate y
		rx = selectObj->getMC().matrix[0][1];
		ry = selectObj->getMC().matrix[1][1];
		rz = selectObj->getMC().matrix[2][1];
		selectObj->rotate(x0, y0, z0, rx, ry, rz, theta * 0.5);
	}else if (transType == 3){  //model rotate z
		rx = selectObj->getMC().matrix[0][2];
		ry = selectObj->getMC().matrix[1][2];
		rz = selectObj->getMC().matrix[2][2];
		selectObj->rotate(x0, y0, z0, rx, ry, rz, theta * 0.5);
	}
	else if (transType == 4) { //model scale
		selectObj->scaleChange(theta * 0.02);
	}
}


void WCSTransform(GLint x){
	GLfloat theta = (xbegin - x > 0) ? 1 : -1;

	if (transType == 1) {
		selectObj->rotateOrigin(0, 0, 0, 1, 0, 0, theta * 0.5);
	}
	else if (transType == 2) {
		selectObj->rotateOrigin(0, 0, 0, 0, 1, 0, theta * 0.5);
	}
	else if(transType == 3){
		selectObj->rotateOrigin(0, 0, 0, 0, 0, 1, theta * 0.5);
	}
	else if (transType == 4) {
		selectObj->translate(theta * 0.02, 0, 0);
	}
	else if(transType == 5){ //WC translate y
		selectObj->translate(0, theta * 0.02, 0);
	}
	else if(transType == 6){ //WC translate z
		selectObj->translate(0, 0, theta * 0.02);
	}
}

void VCSTransform(GLint x){
	GLfloat theta = (xbegin - x > 0) ? 1 : -1;
	if (transType == 1) {  //eye rotate x
		myCamera.rotate(1.0, 0.0, 0.0, theta*0.5);
	}
	else if (transType == 2) { // eye rotate y
		myCamera.rotate(0.0, 1.0, 0.0, theta*0.5);
	}
	else if(transType == 3){ //eye rotate z
		myCamera.rotate(0.0, 0.0, 1.0, theta*0.5);
	}
	else if (transType == 4) { //eye translate x
		myCamera.translate(theta* 0.02, 0.0, 0.0);
	}
	else if(transType == 5){   // eye translate y
		myCamera.translate(0.0, theta* 0.02, 0.0);
	}
	else if(transType == 6){ // eye translate z
		myCamera.translate(0.0, 0.0, theta* 0.02);
	}
	else if(transType == 7){  // change dnear
		myCamera.dnear += theta * .1;
	}
	else if(transType == 8){  // change dfar
		myCamera.dfar += theta *.1;
	}
}

void cullMenu(GLint option) {
	switch (option){
	  case 1:
		cullMode = NONE;
		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
		break;
	  case 2:
		cullMode = BACKFACE;   // implementation of my back face
		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
		break;
	  case 3:
		cullMode = GLCULL;
		glEnable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
		break;
	  case 4:
		cullMode = GLDEPTHBUFFER;
		glDisable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		break;
	  case 5:
		cullMode = GLCULLDEPTHBUFFER;
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		break;
	}
	glutPostRedisplay();
}

void lightMenu(GLint option) {
	csType = 4;
	transType = option;

	switch (option) {
	   case 8:
	    glEnable(GL_LIGHTING);
	    glEnable(GL_LIGHT0);
	    glEnable(GL_DEPTH_TEST);

	    glShadeModel(GL_SMOOTH); // temporarily here
		myLight.on = true;
		break;
	  case 9:
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		glDisable(GL_DEPTH_TEST);
		myLight.on = false;
		break;
	}

	glutPostRedisplay();
}

void lightTransform(GLint x){
	GLfloat theta = (xbegin - x > 0) ? 1 : -1;
	if (transType == 1) {   // rotate x
		myLight.rotate(0, 0, 0, 1.0, 0.0, 0.0, theta*0.5);
	}
	else if (transType == 2) { // rotate y
		myLight.rotate(0, 0, 0, 0.0, 1.0, 0.0, theta*0.5);
	}
	else if(transType == 3){ // rotate z
		myLight.rotate(0, 0, 0, 0.0, 0.0, 1.0, theta*0.5);
	}
	else if (transType == 4) { // translate x
		myLight.translate(theta*0.1, 0.0, 0.0);
	}
	else if(transType == 5){   // eye translate y
		myLight.translate(0.0, theta*0.1, 0.0);
	}
	else if(transType == 6){ // eye translate z
		myLight.translate(0.0, 0.0, theta*0.1);
	}
	else if(transType == 7){  // change intensity
		myLight.I += theta *0.01;
	}

	glutPostRedisplay();
}

void shadeMenu(GLint option) {
	switch (option){
	  case 1:
		renderMode = WIRE;
		break;
	  case 2:
		renderMode = CONSTANT;
		break;
	  case 3:
		renderMode = FLAT;
		break;
	  case 4:
		renderMode = SMOOTH;
		break;
	}
	glutPostRedisplay();
}


// Animations
// move: animated a selected object by rotating it automatically wrt the z-axis of MCS
void move(void){
	//  your implementation
	GLfloat speed = 0.05;
	newTime = clock();
	GLfloat theta = (newTime - oldTime) * speed;
	oldTime = newTime;
	printf("time: %f\n", theta);

	selectObj->rotate(
			selectObj->getMC().matrix[0][3],
			selectObj->getMC().matrix[1][3],
			selectObj->getMC().matrix[2][3],
			0, 0, 1,
			theta
	);
	glutPostRedisplay();
}

void solar(void){
	//  your implementation
	GLfloat speed = 0.05;
	newTime = clock();
	GLfloat theta = (newTime - oldTime) * speed;
	oldTime = newTime;

	// id of
	// cube = 1; pyramid = 2; house = 3;
	Shape* cube = myWorld.searchById(1);
	Shape* pyramid = myWorld.searchById(2);
	Shape* house = myWorld.searchById(3);

	// House as sun rotating wrt the z-axis of WCS
	house->rotate(
			house->getMC().matrix[0][3],
			house->getMC().matrix[1][3],
			house->getMC().matrix[2][3],
			0, 0, 1,
			theta
	);

	// cube as earth rotating wrt its own z-axis and rotating wrt the sun's z-axis
	cube->rotate(
		cube->getMC().matrix[0][3],
		cube->getMC().matrix[1][3],
		cube->getMC().matrix[2][3],
		0, 0, 1,
		theta
	);
	cube->rotateOrigin(
		house->getMC().matrix[0][3],
		house->getMC().matrix[1][3],
		house->getMC().matrix[2][3],
		0, 0, 1,
		theta
	);


	// pyramid as moon rotating on its z-axis and rotating wrt the z-axis of the earth
	pyramid->rotate(
		pyramid->getMC().matrix[0][3],
		pyramid->getMC().matrix[1][3],
		pyramid->getMC().matrix[2][3],
		0, 0, 1,
		theta
	);

	// rotate around the sun then rotate around the earth...
	pyramid->rotateOrigin(
		house->getMC().matrix[0][3],
		house->getMC().matrix[1][3],
		house->getMC().matrix[2][3],
		0, 0, 1,
		theta
	);

	pyramid->rotateOrigin(
		cube->getMC().matrix[0][3],
		cube->getMC().matrix[1][3],
		cube->getMC().matrix[2][3],
		0, 0, 1,
		theta
	);
	glutPostRedisplay();
}

void solar2()
{
	GLfloat x1,y1,z1, x2,y2,z2, x3, y3, z3;
	GLfloat sunSpeed = 0.04, earthSpeed = 1, earthSunSpeed = 0.037, moonSpeed = 0.2, moonEarthSpeed = 0.034;

	Sphere *sun = mySolar.sun;
	Sphere *earth =  mySolar.earth;
	Sphere *moon = mySolar.moon;

	x1 = sun->getMC().matrix[0][3];
	y1 = sun->getMC().matrix[1][3];
	z1 = sun->getMC().matrix[2][3];

	x2 = earth->getMC().matrix[0][3];
	y2 = earth->getMC().matrix[1][3];
	z2 = earth->getMC().matrix[2][3];

	x3 = moon->getMC().matrix[0][3];
	y3 = moon->getMC().matrix[1][3];
	z3 = moon->getMC().matrix[2][3];

	// sun motion
	sun->rotate(x1, y1, z1, 0, 0, 1, sunSpeed);

	// earth motion
	earth->rotate(x2, y2, z2, 0, 0, 1, earthSpeed);
	earth->rotateOrigin(x1, y1, z1, 0, 0, 1, earthSunSpeed);

	// moon motion
	moon->rotate(x3, y3, z3,  0, 0, 1, moonSpeed);
	moon->rotateOrigin(x1, y1, z1, 0, 0, 1, earthSunSpeed);
	moon->rotateOrigin(x2, y2, z2,  0, 0, 1, moonEarthSpeed);

    glutPostRedisplay();
}


void animateMenu(GLint option) {
	switch (option){
	  case 1:
		glutIdleFunc(move);
		break;
	  case 2:
		myLight.on = false;
		displayOption = 0;
		glDisable(GL_LIGHTING);
		glutIdleFunc(solar);
		break;
	  case 3:
	    myLight.on = false;
	    displayOption = 1;
		//glDisable(GL_LIGHTING);
		glutIdleFunc(solar2);
		break;
	  case 4:
		glutIdleFunc(NULL);
		break;
	}
	glutPostRedisplay();
}

void curveSurfaceMenu(GLint option) {
	switch (option){
	  case 1:
	    displayOption = 2;
	    myBezier.displayCPts();
		break;
	  case 2:
		displayOption = 3;
		myBezier.computeBezCurvePts();
		break;
	  case 3:
		myRBM.RotateCurve();
		displayOption = 4;
		selectObj = &myRBM;
		break;
	}
	glutPostRedisplay();
}

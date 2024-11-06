/*
 *  SimpleView : reference design
 *  Author: HBF
 *  Version: 2022-10-03
 */
#include "Menu.hpp"
#include "World.hpp"
#include "Camera.hpp"
#include "Light.hpp"

extern GLint csType;
extern Shape* selectObj;
extern GLint transType, xbegin;
extern World myWorld;
extern Camera myCamera;
extern Light myLight;
extern CullMode cullMode;
extern RenderMode renderMode;


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

	GLint Cull_Menu = glutCreateMenu(cullMenu);
	glutAddMenuEntry("No culling", 1);
	glutAddMenuEntry("My back-face", 2);
	glutAddMenuEntry("OpenGL back-face & depth buffer", 3);

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

	GLint Shading_Menu = glutCreateMenu(shadeMenu);
	glutAddMenuEntry("No shading", 1);
	glutAddMenuEntry("My constant shading", 2);
	glutAddMenuEntry("OpenGL flat shading", 3);
	glutAddMenuEntry("OpenGL smooth shading", 4);

	GLint Animate_Menu = glutCreateMenu(animateMenu);
	glutAddMenuEntry("Single object", 1);
	glutAddMenuEntry("Multiple object", 2);
	glutAddMenuEntry("Stop animation", 3);


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
	Matrix mp = selectObj->getMC();
	myCamera.setRef(mp.mat[0][3], mp.mat[1][3], mp.mat[1][3]);
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

	x0 = selectObj->getMC().mat[0][3];
	y0 = selectObj->getMC().mat[1][3];
	z0 = selectObj->getMC().mat[2][3];

	if (transType == 1) { //model rotate x
		rx = selectObj->getMC().mat[0][0];
		ry = selectObj->getMC().mat[1][0];
		rz = selectObj->getMC().mat[2][0];
		selectObj->rotate(x0, y0, z0, rx, ry, rz, theta * 0.5);
	}
	else if (transType == 2) { //model rotate y
		rx = selectObj->getMC().mat[0][1];
		ry = selectObj->getMC().mat[1][1];
		rz = selectObj->getMC().mat[2][1];
		selectObj->rotate(x0, y0, z0, rx, ry, rz, theta * 0.5);
	}else if (transType == 3){  //model rotate z
		rx = selectObj->getMC().mat[0][2];
		ry = selectObj->getMC().mat[1][2];
		rz = selectObj->getMC().mat[2][2];
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
		cullMode = BACKFACE;
		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
		break;
	  case 3:
		cullMode = GLCULL;
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



void move(void){
//  your implementation
	glutPostRedisplay();
}

void solar(void){
//  your implementation

	glutPostRedisplay();
}

void animateMenu(GLint option) {
	switch (option){
	  case 1:
		glutIdleFunc(move);
		break;
	  case 2:
		myLight.on = false;
		glDisable(GL_LIGHTING);
		glutIdleFunc(solar);
		break;
	  case 3:
		glutIdleFunc(NULL);
		break;
	}
	glutPostRedisplay();
}


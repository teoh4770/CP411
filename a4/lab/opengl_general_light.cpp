/*
 * Description: testing on lighting and shading
 * compile: g++ opengl_general_light.cpp -lfreeglut -lopengl32 -lglu32
 * Run: a.exe  right clicking mouse to bring the menu
 * HBF
 */ 
 
#include <GL/glut.h>

GLint lightType = 1;

void init(void) {
	// Light model parameters for the entire scene
	// https://www.khronos.org/registry/OpenGL-Refpages/es1.1/xhtml/glLightModel.xml
	GLfloat lmKa[] = { 0.3, 0.3, 0.3, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmKa);
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 0.0);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);

//	 Material parameter for all faces
	GLfloat material_Ka[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat material_Kd[] = { 1.0f, 0.4f, 0.0f, 1.0f };
	GLfloat material_Ks[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat material_Ke[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat material_Se = 20.0f;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_Ka);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_Kd);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_Ks);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material_Ke);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material_Se);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSolidSphere(1.0, 20, 16);
	glFlush();
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-1.5, 1.5, -1.5 * (GLfloat) h / (GLfloat) w,
				1.5 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
	else
		glOrtho(-1.5 * (GLfloat) w / (GLfloat) h,
				1.5 * (GLfloat) w / (GLfloat) h, -1.5, 1.5, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void mainMenuFcn(GLint option) {
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT1);

	switch (option) {
	case 1:
		glDisable(GL_LIGHTING);
		break;
	case 2: {
		// Spotlight with attenuation
		GLfloat spot_direction[] = { 1.0, 1.0, 1.0, 0 };
		GLint spot_exponent = 30;
		GLint spot_cutoff = 180;
		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
		glLighti(GL_LIGHT0, GL_SPOT_EXPONENT, spot_exponent);
		glLighti(GL_LIGHT0, GL_SPOT_CUTOFF, spot_cutoff);
		GLfloat Kc = 1.0;
		GLfloat Kl = 0.0;
		GLfloat Kq = 0.0;
		glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, Kc);
		glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, Kl);
		glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, Kq);

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
	}

		break;

	case 3: {
		//	Set lighting parameters
		GLfloat pos[] = { 2.0, 2.0, 2.0, 1.0 };
		GLfloat Ka[] = { 1.0, 0.0, 0.0, 1.0 };
		GLfloat Kd[] = { 1.0, 1.0, 0.1, 1.0 };
		GLfloat Ks[] = { 0.0, 0.0, 1.0, 1.0 };
		glLightfv(GL_LIGHT1, GL_POSITION, pos);
		glLightfv(GL_LIGHT1, GL_AMBIENT, Ka);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, Kd);
		glLightfv(GL_LIGHT1, GL_SPECULAR, Ks);

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT1);
	}
		break;
	case 4:
		glShadeModel(GL_FLAT);
		break;

	case 5:
		glShadeModel(GL_SMOOTH);
		break;
	}

	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutCreateMenu(mainMenuFcn); /* Create main pop-up menu */
	glutAddMenuEntry("No light", 1);
	glutAddMenuEntry("Light0", 2);
	glutAddMenuEntry("Light1", 3);
	glutAddMenuEntry("GL_FLAT", 4);
	glutAddMenuEntry("GL_SMOOTH", 4);

	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
	return 0;
}

/*
 * Description: testing on configure overall light model material, spot light, ambient light, and spectacular.
 * compile: g++ opengl_general_light.cpp -lfreeglut -lopengl32 -lglu32
 * Run: a.exe  right clicking mouse to bring the menu
 * HBF
 */

#include <GL/glut.h>

GLint lightType = 1;

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);

	// Light model parameters for the entire scene
	// https://www.khronos.org/registry/OpenGL-Refpages/es1.1/xhtml/glLightModel.xml
	// Light Model: controls global lighting effects, such as the ambient lighting that impacts the entire scene.
	GLfloat lmKa[] = { 0.3, 0.3, 0.3, 1.0 }; // Sets a low-level ambient light
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmKa);    // Enable us to sets the global ambient light level for the scene.
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 0.0); // Determines whether lighting calculations consider the viewer's position, 0 treats viewer as infinitely far away, 1 treats viewer close to the object
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);	 // Controls lighting for the front and back faces of an object (0 means front only, 1 means both sides, useful for transparent or double-sided material)

	// Material parameter for all faces
	// Ambient: This color (a soft gray) sets the overall tone for the material in low-light conditions. Increasing these values will make the object appear brighter in the presence of ambient light.
	GLfloat material_Ka[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	// Diffuse: orange color will be visible when surface hit by direct light
	GLfloat material_Kd[] = { 1.0f, 0.4f, 0.0f, 1.0f };
	GLfloat material_Ks[] = { 0.5f, 0.5f, 0.5f, 1.0f }; // specular
	GLfloat material_Ke[] = { 0.5f, 0.5f, 0.5f, 1.0f }; // emission
	GLfloat material_Se = 20.0f; // fromt he scale 0 - 128

	// The object has 5 material properties added onto it, to give it a realistic look to 3D object
	// Which controls how it interacts with light sources in OpenGL
	// Determine the object appearance by affecting color, shininess, and self-illumination

	// Purpose: Sets the ambient reflectivity of the material, which determines how much ambient light the material reflects.
	// Effect: This property gives the material a baseline color even in shadowed areas or when there’s minimal direct light.
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_Ka);

	// Purpose: Defines the diffuse reflectivity, which controls the color that the material shows when directly illuminated.
	// Effect: Spreads light evenly across the surface, creating a matte finish
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_Kd);

	// Purpose: Sets the specular reflectivity, controlling the color and intensity of highlights (shiny spots) on the material
	// Effect: Specular reflection mimics the shiny, mirror-like properties of surfaces
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_Ks);

	// Purpose: Sets the emissive property of the material, making it look like it emits its own light
	// Effect: Emissive light does not rely on an external light source. Make object appears to glow (neon sign, glowing screens)
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material_Ke);

	// Purpose: Sets the shininess factor, affects the sharpness of the specular highlight on the material
	// Effect: controls how focused the highlight appears on the material.
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material_Se);
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
		// SPOTLIGHT: mimic a focused beam, like a theatre spotlight
		// Spotlight with attenuation
		GLfloat spot_direction[] = { 1.0, 1.0, 1.0, 0 };
		GLint spot_exponent = 30;
		GLint spot_cutoff = 180;
		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction); // Direction: Set the direction the spotlight points
		glLighti(GL_LIGHT0, GL_SPOT_EXPONENT, spot_exponent);	 // Intensity falloff: Controls how quickly the light fades as it moves away from the center of the cone. Higher means faster fading and more focused spotlight
		glLighti(GL_LIGHT0, GL_SPOT_CUTOFF, spot_cutoff);		 // Spread Angle: Defines the cone's angle(0 to 180 degrees). Larger values make a wider spotlight

		// Attenuation: adjusts the spotlight's brightness over distance, the constants control how light
		// weakens with distance, mimicking real-world light behavior.

		/*
		 High Kc, Kl, and Kq: Bright, soft light that remains relatively even over distances, creating a less defined beam.
		 Low Kc, high Kl: Sharp drop-off but brighter close up, resulting in a spotlight effect.
		 High Kq: If this is significantly higher than Kc and Kl, expect a very focused beam with a rapid fall-off, making it appear more like a true spotlight.
		*/
		GLfloat Kc = 1.0; // constant: determines the light intensity at the constant distance (set the base brightness level of the light)
		GLfloat Kl = 0.0; // linear: determines how light intensity decreases linearly with distance.
		GLfloat Kq = 0.0; // quadratic: ?
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

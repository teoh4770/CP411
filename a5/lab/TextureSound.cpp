/*
 * Description: testing texture mapping
 * compile: g++ TextureSound.cpp -lfreeglut -lopengl32 -lglu32 -lwinmm
 * Run: a.exe
 * HBF
 */

#include <windows.h>  // for playing sound
#include <mmsystem.h> //

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

GLfloat rotation = 0;
GLfloat Pi = 3.1415926;
GLint winWidth = 600, winHeight = 600;

GLuint texture[3];
GLUquadric *sphere = NULL;
GLint displayType = 1;

struct Image {
	unsigned long sizeX;
	unsigned long sizeY;
	char *data;
};

// Loading Texture
// Reads a BMP file and loads its data into an Image structure.
// Convert img for BGR (BMP format) to RGB for OpenGL compatibility
int ImageLoad(char *filename, Image *image) {
	FILE *file;
	unsigned long size; // size of the image in bytes.
	unsigned long i; // standard counter.
	unsigned short int planes; // number of planes in image (must be 1)
	unsigned short int bpp; // number of bits per pixel (must be 24)

	char temp; // temporary color storage for bgr-rgb conversion.

	// make sure the file is there.
	if ((file = fopen(filename, "rb")) == NULL) {
		printf("File Not Found : %s\n", filename);
		return 0;
	}

	// seek through the bmp header, up to the width/height:
	fseek(file, 18, SEEK_CUR);

	// read the width
	if ((i = fread(&image->sizeX, 4, 1, file)) != 1) {
		printf("Error reading width from %s.\n", filename);
		return 0;
	}

	// read the height
	if ((i = fread(&image->sizeY, 4, 1, file)) != 1) {
		printf("Error reading height from %s.\n", filename);
		return 0;
	}

	size = image->sizeX * image->sizeY * 3;

	if ((fread(&planes, 2, 1, file)) != 1) {
		printf("Error reading planes from %s.\n", filename);
		return 0;
	}

	if (planes != 1) {
		printf("Planes from %s is not 1: %u\n", filename, planes);
		return 0;
	}

	// read the bitsperpixel
	if ((i = fread(&bpp, 2, 1, file)) != 1) {
		printf("Error reading bpp from %s.\n", filename);
		return 0;
	}

	if (bpp != 24) {
		printf("Bpp from %s is not 24: %u\n", filename, bpp);
		return 0;
	}

	// seek past the rest of the bitmap header.
	fseek(file, 24, SEEK_CUR);

	image->data = (char *) malloc(size);
	if (image->data == NULL) {
		printf("Error allocating memory for color-corrected image data");
		return 0;
	}

	if ((i = fread(image->data, size, 1, file)) != 1) {
		printf("Error reading image data from %s.\n", filename);
		return 0;
	}

	for (i = 0; i < size; i += 3) { // reverse all of the colors. (bgr -> rgb)
		temp = image->data[i];
		image->data[i] = image->data[i + 2];
		image->data[i + 2] = temp;
	}
	return 1;
}

Image* loadTexture(char *filename) {
	Image *image = (Image *) malloc(sizeof(Image));
	if (image == NULL) {
		printf("Error allocating space for image");
		exit(0);
	}
	if (!ImageLoad(filename, image)) {
		exit(1);
	}
	return image;
}

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Create and load three textures
	// texture[0]: sun.bmp for square
	// texture[1]: earth for a sphere
	// texture[2]: moon for other object
	glGenTextures(3, texture);
	Image* image = loadTexture("sun.bmp");
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, image->sizeX, image->sizeY, 0, GL_RGB,
	GL_UNSIGNED_BYTE, image->data); // Bind the texture data to OpenGL (GL_TEXTURE_2D: specifies a 2d texture, texture dimension, format of the pixel data)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //scale linearly when image bigger than texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //scale linearly when image smalled than texture
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	image = loadTexture("earth.bmp");
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, image->sizeX, image->sizeY, 0, GL_RGB,
	GL_UNSIGNED_BYTE, image->data);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	image = loadTexture("moon.bmp");
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, image->sizeX, image->sizeY, 0, GL_RGB,
	GL_UNSIGNED_BYTE, image->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glEnable(GL_TEXTURE_2D);

	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, GL_TRUE);
	gluQuadricNormals(sphere, GLU_SMOOTH);
	glShadeModel(GL_FLAT);
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();


	GLint n = 36;
	GLfloat dt = 2 * Pi / n;
    GLfloat t = 0;

	switch (displayType) {
	case 1:
		glRotatef(rotation, 0.0, 1.0, 0.0);
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); // define how the texture wraps over the object, s[0, 1] horizontal, t[0, 1] vertical
		glVertex3f(0.0, -2.0, 0.0);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(2.0, -2.0, 0.0);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(2.0, 1.0, 0.0);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(0.0, 1.0, 0.0);
		glEnd();
		break;
	case 2:
		glRotatef(rotation, 0.0, 1.0, 0.0);
		glBindTexture(GL_TEXTURE_2D, texture[1]);
		gluSphere(sphere, 1.0, 20, 20);
		break;
	case 3:
		glRotatef(rotation, 0.0, 1.0, 0.0);
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		glutSolidTeapot(1.0);
		break;
	case 4:
		glRotatef(-20, 1.0, 0.0, 0.0);
		glTranslatef(0.0, 0.4, 0.0);
		glRotatef(rotation, 0.0, 1.0, 0.0);
		glPolygonMode(GL_BACK,GL_LINE);
		glPolygonMode(GL_FRONT,GL_FILL);
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		glBegin( GL_QUAD_STRIP);
		for (int j = 0; j <= n; ++j) {
			glTexCoord2f(t / (2 * Pi), 1);
			glVertex3f(cos(t), 1, -sin(t));
			glTexCoord2f(t / (2 * Pi), 0);
			glVertex3f(cos(t), -0.1, -sin(t));
			t = t + dt;
		}
		glEnd();
		break;

	case 5:
		glRotatef(-10, 1.0, 0.0, 0.0);
		glTranslatef(0.0, 0.2, 0.0);
		glRotatef(rotation, 0.0, 1.0, 0.0);

		glPolygonMode(GL_BACK, GL_LINE);
		glPolygonMode(GL_FRONT, GL_FILL);
		glBindTexture(GL_TEXTURE_2D, texture[2]);

		GLint m = 18;
		n = 36;
		GLfloat r = 1.5, a = 0, b = Pi/2, c=0, d = 2*Pi;
		GLfloat xs = (b-a)/m, ys=(d-c)/n, theta, phi, x, y, z;
		for (int i=0; i<m; i++) {   // m strips, ith strip
			glBegin( GL_QUAD_STRIP);
			for (int j=0; j<=n; j++) { // each strip,
				// compute the lower mesh point at (i, j)
				theta = a+i*xs;
				phi = c+j*ys;
				x = r * cos(theta) * cos(phi);
				y = r * cos(theta) * sin(phi);
			    z = r * sin(theta);
			    glTexCoord2f(theta /Pi, phi/(2*Pi));
			    glVertex3f(x, y, z);

			    // compute the upper mesh point at (i+1, j)
				theta = a+(i+1)*xs;
				phi = c+j*ys;
				x = r * cos(theta) * cos(phi);
				y = r * cos(theta) * sin(phi);
			    z = r * sin(theta);
			    glTexCoord2f(theta /Pi, phi/(2*Pi));
			    glVertex3f(x, y, z);
			}
			glEnd();
		}

		break;
	}

	glPopMatrix();
	glFlush();
	glutPostRedisplay();
	glutSwapBuffers();
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 1.0 * (GLfloat) w / (GLfloat) h, 1.0, 30.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -3.6);
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'L':
	case 'l':
		rotation += 20;
		break;
	case 'R':
	case 'r':
		rotation -= 20;
		break;
	default:
		break;
	}
}

void mainMenu(GLint option) {
	switch (option) {
	case 1:
		exit(0);
		break;
	case 2:
		displayType = 1;
		break;
	case 3:
		displayType = 2;
		break;
	case 4:
		displayType = 3;
		break;
	case 5:
		displayType = 4;
		break;
	case 6:
		displayType = 5;
		break;

	case 7:
		glDisable(GL_TEXTURE_2D);
		break;
	case 8:
		glEnable(GL_TEXTURE_2D);
		break;
	case 9:
		PlaySound((LPCSTR) "test.wav", NULL, SND_FILENAME | SND_ASYNC);
		break;
	case 10:
		PlaySound(NULL, NULL, NULL);
		break;

	}
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(winWidth, winHeight);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Texture Mapping (HBF)");
	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

	glutCreateMenu(mainMenu);
	glutAddMenuEntry("Quit", 1);
	glutAddMenuEntry("Square with texture", 2);
	glutAddMenuEntry("Sphere with texture", 3);
	glutAddMenuEntry("Teapot with texture", 4);
	glutAddMenuEntry("My cylinder with texture", 5);
	glutAddMenuEntry("My half sphere with texture", 6);
	glutAddMenuEntry("Disable texture", 7);
	glutAddMenuEntry("Enable texture", 8);
	glutAddMenuEntry("Play sound", 9);
	glutAddMenuEntry("Stop playing sound", 10);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
	return 0;
}

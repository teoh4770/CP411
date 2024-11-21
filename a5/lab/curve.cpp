#include <GL/glut.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

// Max number of points for precomputed curves
#define MAX 100
GLint m = MAX;  // Number of points on the curve

// Window and coordinate system settings
GLsizei winWidth = 800, winHeight = 800;
GLsizei cwleft = -2, cwright = 2, cwbottom = -2, cwtop = 2;  // Coordinate window for 2D view
GLfloat boxleft = -1.5, boxright = 1.5, boxbottom = -1.5, boxtop = 1.5;  // Box bounds for curves
GLint curveType = 1;  // Selected curve type

// Data structure for 2D points
struct POINT2 {
	GLfloat x, y;
};

// Draw a single line segment
void lineSegment(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2) {
	glBegin(GL_LINES);
	glVertex3f(x1, y1, z1);
	glVertex3f(x2, y2, z2);
	glEnd();
}

// Display a text message at a given position
void message(char str[], GLfloat x, GLfloat y) {
	glRasterPos2f(x, y);
	int i = 0;
	while (str[i]) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);  // Render each character
		i++;
	}
}

// Draw a line segment with labeled endpoints
void line_messae(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2) {
	char line[20];
	lineSegment(x1, y1, 0, x2, y2, 0);  // Draw the line
	sprintf(line, "(%.1f,%.1f)", x1, y1);  // Format the first point label
	message(line, x1, y1);  // Display the first point label
	sprintf(line, "(%.1f,%.1f)", x2, y2);  // Format the second point label
	message(line, x2, y2);  // Display the second point label
}

// Draw a bounding box around the curve
void drawBox() {
	glColor3f(1.0, 1.0, 1.0);  // White color for the box
	line_messae(boxleft, 0, boxright, 0);  // x-axis
	line_messae(0, boxbottom, 0, boxtop);  // y-axis
	line_messae(boxleft, boxbottom, boxright, boxbottom);  // Bottom edge
	line_messae(boxleft, boxtop, boxright, boxtop);        // Top edge
	line_messae(boxleft, boxbottom, boxleft, boxtop);      // Left edge
	line_messae(boxright, boxbottom, boxright, boxtop);    // Right edge
}

// Draw coordinate axes
void drawAxis() {
	glColor3f(1.0, 0.0, 0.0);  // Red x-axis
	lineSegment(boxleft, 0, 0, boxright, 0, 0);
	glColor3f(0.0, 1.0, 0.0);  // Green y-axis
	lineSegment(0, boxbottom, 0, 0, boxtop, 0);
	glColor3f(0.0, 0.0, 1.0);  // Blue z-axis
	lineSegment(0, 0, boxbottom, 0, 0, boxtop);
}

// Polynomial definition and evaluation
// n = degree of polynomial
// p[] = array of coefficients
int n = 3;  // Degree of the polynomial
GLfloat p[] = {1, 1, -1};  // Coefficients of the polynomial (x^2 + x - 1)

// Horner's algorithm to evaluate the polynomial
// x = value at which the polynomial is evaluated
GLfloat horner(int n, GLfloat p[], GLfloat x) {
	GLfloat r = 0;  // Initialize the result
	for (int i = 0; i < n; i++)
		r = r * x + p[i];  // Horner's method
	return r;
}

// Dynamically compute and draw polynomial curve
// need to has a high level understand of the formula
void drawPolynormial(int n, GLfloat p[]) {
	GLfloat a = -1.5, b = 1.5;  // Domain for x
	GLfloat s = (b - a) / m;  // Step size -> in here, m is already defined 100 (from -1.5 to 1.5 need 100 steps)
	GLfloat x, y;
	glBegin(GL_LINE_STRIP);  // Begin drawing connected line segments
	for (int i = 0; i < m; i++) {
		x = a + s * i;  // Compute x
		y = horner(n, p, x);  // Evaluate polynomial y value
		glVertex2f(x, y);  // Add vertex to the curve
	}
	glEnd();
}

// Precompute polynomial curve points
POINT2 polynomialPoints[MAX];
void computePolynormial(int n, GLfloat p[], POINT2 points[], int m) {
	GLfloat a = -1, b = 1;    // Domain for x
	GLfloat s = (b - a) / m;  // Step size
	GLfloat x, y;
	for (int i = 0; i < m; i++) {
		x = a + s * i;  // Compute x  (i = 0, x = -1; i = 1, x = -0.98)
		y = horner(n, p, x);  // Evaluate polynomial
		points[i].x = x;
		points[i].y = y;
	}
}

// Precompute circle points
#define Pi 3.1415
POINT2 circlePoints[MAX];
void computeCircle(GLfloat r, POINT2 points[], int m) {
	GLfloat a = 2 * Pi, b = 0;  // Full circle range (domain for x)
	GLfloat s = (b - a) / m;  // Step size (from 0 to 360 need m steps)
	GLfloat t;
	for (int i = 0; i < m; i++) {
		t = a + s * i;  // Compute angle
		points[i].x = r * cos(t);  // x-coordinate
		points[i].y = r * sin(t);  // y-coordinate
	}
}

// Dynamically draw curve using precomputed points
void drawCurveByPoints(POINT2 points[], int m, int isLoop) {
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < m; i++) {
		glVertex2f(points[i].x, points[i].y);  // Draw each vertex
	}
	glEnd();
	if (isLoop == 1) {  // Close the curve if needed
		glBegin(GL_LINE_LOOP);
		glVertex2f(points[m - 1].x, points[m - 1].y);
		glVertex2f(points[0].x, points[0].y);
		glEnd();
	}
}


void drawHelix() {
	int angle = 0, spcount = 2;
	GLfloat x, y, z=0;
	GLfloat r = 1,  b = 0.002;
	GLfloat radia= Pi/180, theta = 0;
	glBegin(GL_LINE_STRIP);
		for(angle = 0; angle < 360*spcount; angle += 1)
		{
			theta = angle*radia;
			x = r * cos(theta);
			y = r * sin(theta);
			glVertex3f(x,y,z);
			z+= b;
		}
	 glEnd();
}


// data structure to store 3D curve point
struct POINT3 {
	GLfloat x, y, z;
};


void computeHelix(POINT3 points[], int m) {
	int i = 0;
	GLfloat x, y, z=0;
	GLfloat r = 1, b = 0.002;
	GLfloat radia= Pi/180, theta = 0;
	for(i = 0; i < m; ++i)
	{
		theta = i*radia;
		x = r * cos(theta);
		y = r * sin(theta);
		points[i].x = x;
		points[i].y = y;
		points[i].z = z;
		z+= b;
	}
}

// compute curve point at rendering
void draw3DCurveByPoints(POINT3 points[], int m, int isLoop) {
	glBegin(GL_LINE_STRIP);
	for (int i=0; i<m; i++) {
		glVertex3f(points[i].x, points[i].y, points[i].z);
	}
	glEnd();

	if (isLoop == 1) {
		glBegin(GL_LINE_LOOP);
		glVertex3f(points[m-1].x, points[m-1].y, points[m-1].z);
		glVertex3f(points[0].x, points[0].y, points[m-1].z);
		glEnd();
	}

}

POINT3 helixPoints[720];

void init(void) {
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(cwleft,  cwright, cwbottom, cwtop);
	computePolynormial(n, p, polynomialPoints, 100);   // compute polynomial curve data
	computeCircle(1.0, circlePoints, 100);
	computeHelix(helixPoints, 720);
}


void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	//glClearColor(0.0, 0.0, 0.0, 1.0);

    switch (curveType) {
      // Compute and dynamically draw the polynomial curve
      case 1:
    	 drawBox();
    	 glColor3f(1.0, 0.0, 0.0);
    	 drawPolynormial(n, p);
    	 break;
      // Draw a precomputed polynomial curve from stored points
      case 2:
    	  drawBox();
    	  glColor3f(0.0, 1.0, 0.0);
    	  drawCurveByPoints(polynomialPoints, m, 0);
    	 break;
      // Draw a circle
      case 3:
    	 drawBox();
    	 glColor3f(0.0, 0.0, 1.0);
    	 drawCurveByPoints(circlePoints, m, 1);
    	 break;

      case 4:
    	drawAxis();
    	glColor3f(1.0, 1.0, 0.0);
    	drawHelix();
    	break;

      case 5:
    	drawAxis();
    	glColor3f(0.0, 1.0, 1.0);
    	draw3DCurveByPoints(helixPoints, 720, 0);
    	break;
    }
	glFlush();
	glutPostRedisplay();
	glutSwapBuffers();
}

void mainMenuFcn(GLint option) {
	curveType = option;
	switch (option) {
	case 1: case 2: case 3:
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(cwleft,  cwright, cwbottom, cwtop);
		break;

	case 4: case 5:
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(
		 40.0,  /* field of view in degree */
		 1.0,   /* aspect ratio */
		 1.0,   /* Z near */
		 30.0   /* Z far */
		);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(3.0, 3.0, 6.0, /* eye is at (0,0,5) */
		          0.0, 0.0, 0.0,  /* center is at (0,0,0) */
		          0.0, 0.0, 1.0   /* up is in positive Y direction */
	    );
		break;
	}

	display();
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	//setbuf(stdout, NULL);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("hand-on OpenGL curves");
    init();
	glutDisplayFunc(display);
	glutCreateMenu(mainMenuFcn);
	glutAddMenuEntry("Compute and draw polynomial curve", 1);
	glutAddMenuEntry("Draw stored polynomial curve", 2);
	glutAddMenuEntry("Draw stored circle", 3);
	glutAddMenuEntry("Draw 3D helix", 4);
	glutAddMenuEntry("Draw stored helix", 5);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
}

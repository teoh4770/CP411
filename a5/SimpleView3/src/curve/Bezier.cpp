#include "Bezier.hpp"
#include <stdio.h>

extern GLint winWidth, winHeight;

Bezier::Bezier() {
	reset();
}

void Bezier::reset() {
	nCtrlPts = 0;
	nPts = 26;
}

/*  Compute
 *  binomial coefficients C for given value of n, output in GLint C[]
 *  */
void Bezier::binomialCoeffs(GLint n, GLint B[]) {
	// your code
	// Using O(n) algorithm for C_{n, i), i = 0, 1, ..., n
	// compute the binomial coefficient C for given value of n
	// Iterative way to find i
	B[0] = 1; // C(n, 0) is always 1;

	for (int i = 1; i <= n; ++i) {
		B[i] = B[i - 1] * (n - i + 1) / i;
	}
}

/*  Compute Bezier point at u, and output in Point *bezPt */
void Bezier::computeBezPt(GLfloat u, GLint nCtrlPts, Point ctrlPts[], GLint B[], Point *bezPt)
{
	// we have the binomial coefficient define already
	double x = 0, y = 0, z = 0;

	if (u < 0.00001) {
		// starting point coordinate
		bezPt->x = ctrlPts[0].x;
		bezPt->y = ctrlPts[0].y;
		bezPt->z = ctrlPts[0].z;
	}
	else if (u > 0.99999) {
		// final point coordinate
		// Q: n - 1 or just n?
		bezPt->x = ctrlPts[nCtrlPts - 1].x;
		bezPt->y = ctrlPts[nCtrlPts - 1].y;
		bezPt->z = ctrlPts[nCtrlPts - 1].z;
	}
	else {
		// Compute Bezier point at parameter u
		// Using Bernstein polynomial
		for (int i = 0; i < nCtrlPts; ++i) {
			// Binomial coefficient * u ^ i * (1-u)^(n-i)
			GLfloat weight = B[i] * pow(u, i) * pow(1 - u, nCtrlPts - 1 - i);
		    printf("Control Point %d: Weight = %f, x = %f, y = %f\n", i, weight, ctrlPts[i].x, ctrlPts[i].y);
			x += weight * ctrlPts[i].x;
			y += weight * ctrlPts[i].y;
			z += weight * ctrlPts[i].z;
		}

		bezPt->x = x;
		bezPt->y = y;
		bezPt->z = z;
	}
}

/*  Compute both Bezier point and tangent at u, and output in Point bezPt and Vector bezTan respectively*/
void Bezier::computeBezPtTan(GLfloat u, GLint nCtrlPts, Point ctrlPts[], GLint B[], Point *bezPt, Vector *bezTan)
{
	int n = nCtrlPts - 1; // Degree of the curve
	GLfloat x = 0, y = 0, z = 0;	// components of the Bezier point
	GLfloat dx = 0, dy = 0, dz = 0; // components of tangent vector

	if (u < 0.00001) {
		// starting point coordinate
		bezPt->x = ctrlPts[0].x;
		bezPt->y = ctrlPts[0].y;
		bezPt->z = ctrlPts[0].z;

		// tangent
		bezTan->x = n * (ctrlPts[1].x - ctrlPts[0].x);
		bezTan->y = n * (ctrlPts[1].y - ctrlPts[0].y);
		bezTan->z = n * (ctrlPts[1].z - ctrlPts[0].z);
	}
	else if (u > 0.99999) {
		// final point coordinate
		// Q: n - 1 or just n?
		bezPt->x = ctrlPts[nCtrlPts - 1].x;
		bezPt->y = ctrlPts[nCtrlPts - 1].y;
		bezPt->z = ctrlPts[nCtrlPts - 1].z;


		// tangent
		bezTan->x = n * (ctrlPts[n].x - ctrlPts[n - 1].x);
		bezTan->y = n * (ctrlPts[n].y - ctrlPts[n - 1].y);
		bezTan->z = n * (ctrlPts[n].z - ctrlPts[n - 1].z);

	}
	else {
		// Compute Bezier point at parameter u
		for (int i = 0; i < nCtrlPts; ++i) {
			// Bernstein polynomial
			// Binomial coefficient * u ^ i * (1-u)^(n-i)
			GLfloat weight = B[i] * pow(u, i) * pow(1 - u, nCtrlPts - 1 - i);
			printf("Control Point %d: Weight = %f, x = %f, y = %f\n", i, weight, ctrlPts[i].x, ctrlPts[i].y);
			x += weight * ctrlPts[i].x;
			y += weight * ctrlPts[i].y;
			z += weight * ctrlPts[i].z;
		}
		bezPt->x = x;
		bezPt->y = y;
		bezPt->z = z;

		// Compute Bezier tangent at parameter u
		for (int i = 0; i < n; ++i) {
			GLfloat weight = n * B[i] * pow(u, i) * pow(1 - u, n - 1 - i);
			dx += weight * (ctrlPts[i + 1].x - ctrlPts[i].x);
			dy += weight * (ctrlPts[i + 1].y - ctrlPts[i].y);
			dz += weight * (ctrlPts[i + 1].z - ctrlPts[i].z);
		}
		bezTan->x = dx;
		bezTan->y = dy;
		bezTan->z = dz;
	}
}


/* call to compute the sequence of points on Bezier curve for drawing Bezier curve */
void Bezier::computeBezCurvePts() {
	GLfloat u = 0;
	GLint B[nCtrlPts];
	binomialCoeffs(nCtrlPts-1, B);

	for (int k = 0; k < nPts; k++) {
		u = GLfloat(k) / GLfloat(nPts-1); // Parameter u (0 to 1)
		computeBezPt(u, nCtrlPts, ctrlPts, B, &Pts[k]); // Compute Bezier point
	}
}


/* call to compute the sequence of points and tangents on Bezier curve for mesh of rotating Bezier curve */
void Bezier::computeBezPtTan(GLint npts, Point pts[], Vector tangents[]) {
	GLfloat u = 0;
	GLint B[npts];
	binomialCoeffs(npts-1, B);

	for (int k = 0; k < npts; k++) {
		u = GLfloat(k) / GLfloat(npts-1);
		computeBezPtTan(u, npts, ctrlPts, B, &pts[k], &tangents[k]);
	}
}


void Bezier::drawCPts() {
	glPointSize(3.0);
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POINTS);
	for (int i = 0; i < nCtrlPts; i++) {
		glVertex2f(ctrlPts[i].x, ctrlPts[i].y);
	}
	glEnd();
}

/* display Control points in 2D view */
void Bezier::displayCPts() {
	set2DView(-winWidth / 2, winWidth / 2, -winHeight / 2, winHeight / 2);
	drawCPts();
}

/* display Control points and curve in 2D view */
void Bezier::display() {
	set2DView(-winWidth / 2, winWidth / 2, -winHeight / 2, winHeight / 2);
	drawCPts();
	drawCurve();
}


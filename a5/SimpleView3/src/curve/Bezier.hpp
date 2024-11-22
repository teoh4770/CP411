/*
 *  SimpleView : reference design
 *  Author: HBF
 *  Version: 2022-11-07 (update)
 */

#ifndef BEZIER_H
#define BEZIER_H

#include <GL/glut.h>
#include "../Point.hpp"
#include "../Vector.hpp"
#include <math.h>
#include "../curve/Curve.hpp"

/*
 * Class `Bezier` defines a specialized type of `Curve` for rendering Bezier curves.
 * It provides methods to calculate and render Bezier curves and tangents.
 */
class Bezier : public Curve {
public:
	GLint nCtrlPts;       // number of Bezier curve control points
	Point ctrlPts[10];    // array to store control points, up to 10 points

	Bezier();

	// Reset control points and number of points
	void reset();

	/*
	 * Computes binomial coefficients for the Bezier curve formula.
	 * - `n`: Degree of the Bezier curve.
	 * - `B[]`: Array to store the computed binomial coefficients.
	 */
	void binomialCoeffs(GLint n, GLint B[]);

	/*
	 * Computes a coordinate of a single point on the Bezier curve at u.
	 * - `u`: Parameter (0 <= u <= 1) along the curve.
	 * - `nCtrlPts / ncp`: Number of control points.
	 * - `ctrlPts[]`: Array of control points.
	 * - `B[]`: Precomputed binomial coefficients.
	 * - `bezPt`: Pointer to the output Bezier point.
	 */
	void computeBezPt(GLfloat u, GLint nCtrlPts, Point ctrlPts[], GLint B[], Point *bezPt);

	/* Call to compute the sequence of points on Bezier curve for drawing Bezier curve */
	void computeBezCurvePts();

	/*
	 * Draws the control points of the Bezier curve as small points or markers.
	 */
	void drawCPts();

	/* display Control points in 2D view */
	void displayCPts();

	/* display Control points and curve in 2D view */
	void display();

	/* will be used be rotation */

	/*
	 * Computes a single point and its tangent on the Bezier curve at parameter `u`.
	 * - `u`: Parameter along the curve (0 <= u <= 1).
	 * - `nCtrlPts`: Number of control points.
	 * - `ctrlPts[]`: Array of control points.
	 * - `B[]`: Precomputed binomial coefficients.
	 * - `bezPt`: Pointer to the output Bezier point.
	 * - `bezTan`: Pointer to the output tangent vector at the Bezier point.
	 */
	void computeBezPtTan(GLfloat u, GLint nCtrlPts, Point ctrlPts[], GLint B[], Point *bezPt, Vector *bezTan);

	/*
	 * Computes points and tangents for all points on the Bezier curve.
	 * - `npts`: Number of points on the curve.
	 * - `pts[]`: Array of points on the curve (output of `computeBezCurvePts`).
	 * - `tangents[]`: Array to store the tangent vectors at each point.
	 */
	void computeBezPtTan(GLint npts, Point pts[], Vector tangents[]);
};

#endif

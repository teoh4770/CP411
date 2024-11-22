#include "RBM.hpp"
extern Bezier myBezier;

#define Pi 3.141592653589793238462643

RBM::RBM() {
	reset();
}

RBM::~RBM() {
}

void RBM::reset() {
	R = 360; // angle
	S = 5;
	T = 25;
	row = R / 5 + 1;
	col = T + 1;
}

// generate the mesh point and normal of rotation surface

void RBM::RotateCurve() {
	// 1. Generate points and tangents for the curve (fill up the pts [curve points] and tangent [derive vectors]
	Point pts[col]; // Points along the curve
	Vector tangents[col]; // Tangents along the curve
	curve->computeBezPtTan(col, pts, tangents); // Fill pts and tangents array

	// 2. Create the surface of rotation
	// Points and normals for the surface mesh
	Point surfacePts[row][col];
	Vector surfaceNormals[row][col];

    // Loop over each point on the curve and rotate it to generate the surface
	// rotate around x-axis
	for (int j = 0; j < col; j++) {
		for (int i = 0; i < row; i++) {
			float theta = (Pi / 180) * S * i;

			surfacePts[i][j].x = pts[j].x;
			surfacePts[i][j].y = pts[j].y * cos(theta);
			surfacePts[i][j].z = pts[j].y * sin(theta);

			surfaceNormals[i][j].x = 0; // Normals depend on tangent and rotation axis
			surfaceNormals[i][j].y = -pts[j].z * cos(theta);
			surfaceNormals[i][j].z = pts[j].y * sin(theta);
			surfaceNormals[i][j].normalize(); // Ensure unit normals
		}
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			printf("Point[%d][%d]: x=%f, y=%f, z=%f\n", i, j, surfacePts[i][j].x, surfacePts[i][j].y, surfacePts[i][j].z);
			printf("Normal[%d][%d]: x=%f, y=%f, z=%f\n", i, j, surfaceNormals[i][j].x, surfaceNormals[i][j].y, surfaceNormals[i][j].z);


			this->Pts[i][j] = surfacePts[i][j];
			this->Normal[i][j] = surfaceNormals[i][j];
		}
	}

}


void RBM::setRotationCurve(Bezier *curve1)
{
	curve = curve1;
}

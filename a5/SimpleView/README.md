## SimpleView3 Reference Design

Author: HBF

Date: 2022-11-02

## What's about

This is a reference design to A5Q3 SimpleView3 program. It is recommended that you develope your SimpleView3 project based on your SimpleView2 project referring this SimpleView3 reference design. However, you are allowed to design and implement your SimpleView3 based on or using part of this SimpleView3 reference design. 

SimpleView3 add the following features to SimpleView2. 

1. Curve objects and rendering: Bezier curves
2. Surface objects and rendering: rotation surface by Bezier curves
3. Texture mapping
4. GLSL GPU programming for Phong shading

Two third party program packages are used to reduced the amount the work.

- glsl : this folder contains program API and implemention for GLSL programming. 
- pixmap : this colder contains the programs for loading and handling bitmap images for texture mapping.


For better management of SimpleView3 programs, it is recommended to create the following folders for the objects to be added to SimpleView3.

- curve : contains the Curve class for gneral curve objects, and Bezier class for the Bezier curve. 
- surface: contains the Surface class for general surface objects, and RBM class for the mesh object rotating Bezier curve.  
- solar : contains the Sphere class for creating sun, earth and moon objects, Solar classes for the simple solar system. 



## Working plan

1. Try the provided execugtable sample SimpleView3 program, to see what SimpleView3 should look like at runtime. 

2. Import the SimpleView3_reference_design.zip into Eclipse to as existing archive project. Understand the program design by reading the SimpleView.cpp, *.hpp and *.cpp files. 

3. Create your SimpleView3 by coping your SimpleView2, then add folders SimpleView2_reference_desigs glsl, pixmap, solar, curve, and surface. Then copy the relevant programs from SimpleView3_reference_design. 
 
4. Add the new menu item  Curve & Surface menu and its sub-menus, and their callback functions by refering to SimpleView3_reference_design, so that your SimpleView3 program has the menu structure like the sample SimpleView3.exe. 

5. Add the following headers at top of SimpleView.cpp 
	
	#include <GL/glew.h>
	#include "pixmap/RGBpixmap.h"
	#include "solar/Solar.hpp"
	#include "curve/Bezier.hpp"
	#include "surface/RBM.hpp"
	#include "GL/glaux.h"
	#include "glsl/Angel.h"
	
	Add global variables to SimpleView.cpp
	
	RGBpixmap pix[6];      /* pixmaps for 6 textures */
	Solar mySolar;
	Bezier myBezier;       /* Bezier curve object */
	RBM myRBM;             /* rotation curve mesh object */
	GLuint ProgramObject;  /* GLSL program object */


Set the intitial value of renderMode to TEXTURE

	RenderMode renderMode = TEXTURE;  // this will show the texture on cube, pyramid when at start. 
		
Copy the the textues bitmaps to root folder. 
	

6. Add texture to cube, and/or pyramid

Load texture bitmaps in the init() in SimpleView.cpp, refer to the reference design. 

Add code to add texture in Cube::drawFace() in the TEXTURE case, like 


    case TEXTURE:
	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,i);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3fv(&vertex[face[i][0]][0]);
	glTexCoord2f(1.0, 0.0); glVertex3fv(&vertex[face[i][1]][0]);
	glTexCoord2f(1.0, 1.0); glVertex3fv(&vertex[face[i][2]][0]);
	glTexCoord2f(0.0, 1.0); glVertex3fv(&vertex[face[i][3]][0]);
	glEnd();
	glDisable(GL_TEXTURE_2D);
    break;

Test run to see the texture on the cube. 

Similarly you can apply tesxure to the triangle face of the pyramid by mapping three points of a texture map to the three vertices of the face. 


7. Working on solar system

Design and implement the Sphere class. Refer to the lab practices A5Q2.3 for texture maping on sphere, and use the code in the reference design. 

Design and implement the Solar class, which create three Sphheres, sun, earth, and moon, with your given size, and positions, and textures. 

Refer to the SimpleVieew3 reference design to add a sub-menu "Simple solar system" to Animation menu, and add motion control function solar2.cpp, and callback glutIdleFunc(solar2) in animateMenu function. 

Test run, choose Animation->Simple solar system, you shoud see your animated sun, earth and moon. 


8. Working Curve and Bezier curve

Warm up by designing and implementating Curve object. Specifically, implementing drawCurve() method of Curve object by drawing curve by stored curve ponts. 

void Curve::drawCurve() done

Next works on Bezier curve computing. We focus on the algorithms for the following computing. Refer to lecture note curve I for the algorithms. 

	/*  Compute binomial coefficients C for given value of n, output in GLint C[] */
	void Bezier::binomialCoeffs(GLint n, GLint C[]) {
		// your code
		// Using O(n) algorithm for C_{n, i), i = 0, 1, ..., n
	}
	
	/*  Compute Bezier point at u, and output in Point *bezPt */
	void Bezier::computeBezPt(GLfloat u, GLint nCtrlPts, Point ctrlPts[], GLint C[], Point *bezPt)
	{
	  // your code
	}
	
	/*  Compute both Bezier point and tangent at u, and output in Point bezPt and Vector bezTan respectively*/
	void Bezier::computeBezPtTan(GLfloat u, GLint nCtrlPts, Point ctrlPts[], GLint C[], Point *bezPt, Vector *bezTan)
	{
	// your code
	}


9. Working on roation surface

- Add code in the following method to draw surface 

	void Surface::drawSurface() {
	
	}

- Implement the following method to generate mesh data of rotation surface by the Bezier curve 

	void RBM::RotateCurve() {
		Point pts[col];
		Vector tangents[col];
		//1.  call curve->computeBezPtTan function to fill up pts and tangents
		//2.  rotate curve to generate surface mesh point and normal data and store in Pts and Normal.
	}

10. Working in Phong shading by GLSL programming

You can use provided vertex and fragment shader. Create GLSL programobject, and enable the programobject in the mode of phong shading option. Basically, it's about a few configuration setting. Refer to A5Q2.4 for examples of using GLSL. 

We need glew library for GLSL. Add the following statement to the main function after glutCreateWindow(...)

glewInit(); // this is for GSLS




## SimpleView2 Reference Design

Author: HBF

Date: 2022-10-25

## What's about

This is a reference design to A4Q3 SimpleView2 program. It is recommended that you develop your SimpleView2 project based on your SimpleView1 project. However, you are allowed to design and implement your SimpleView2 based on or using part of this SimpleView2 reference design. 

## Working plan

1. Try the provided executable sample SimpleView2 program, to see what SimpleView2 should look like at runtime. Import the SimpleView2_reference_design.zip into Eclipse to as existing archive project. Understand the program design by reading the SimpleView.cpp, *.hpp and *.cpp files.   

2. Create your SimpleView2 by coping your SimpleView1, then fixed the transformation problems if any by referring to SimpleView2_reference_design. 

3. Add the new menu items and their callback functions by referring to SimpleView2_reference_design, so that your SimpleView2 program has the menu structure like the sample solution SimpleView2.exe. 

Add the following to Shape.hpp for culling and rendering modes. 

/*
 *  enumeration for culling option
 */
enum CullMode {
  NONE = 0,
  BACKFACE,
  GLCULL,
  GLDEPTHBUFFER,
  GLCULLDEPTHBUFFER
};

/*
 *  enumeration for shading models
 */
enum RenderMode {
  WIRE = 0,
  CONSTANT,
  FLAT,
  SMOOTH,
  PHONG,   // will be used in A5
  TEXTURE  // will be sed in A5
};


Add global variables 

	CullMode cullMode = NONE;          /* culling option */
	RenderMode renderMode = CONSTANT;  /* shade option  */


to SimpleView.cpp  

and add 

	extern CullMode cullMode;
	extern RenderMode renderMode;
	
to programs that uses cullMode, and renderMode, i.e., menu.cpp, Cube.cpp, Pyramid.cpp, etc.	


4. Add faceColor data and faceNormal array to Cube.hpp

	GLfloat faceColor[6][3];
	faceNormal[6][3];


Add faceColor value to Cube constructor, 

    faceColor[0][0] = 1.0, faceColor[0][1] = 0.0; faceColor[0][2] = 0.0;
    ... 

To set faceNormal, you can hard code the normal based your cube design, like

	 faceNormal[0][0] =  0.0, faceNormal[0][1] =  0.0, faceNormal[0][2] = -1.0,
    ... 

However, it's better to compute face normal using the vertices, like

	for (int i = 0 ; i<6; i++) {
		Vector V1 = Vector(vertex[face[i][1]][0]-vertex[face[i][0]][0], vertex[face[i][1]][1]-vertex[face[i][0]][1], vertex[face[i][1]][2]-vertex[face[i][0]][2]);
		Vector V2 = Vector(vertex[face[i][2]][0]-vertex[face[i][1]][0], vertex[face[i][2]][1]-vertex[face[i][1]][1], vertex[face[i][2]][2]-vertex[face[i][1]][2]);
		Vector V3 =  V1.cross(V2);
		V3.normalize();
		faceNormal[i][0] = V3.x;
		faceNormal[i][1] = V3.y;
		faceNormal[i][2] = V3.z;
	}



Modify Cube::drawFace(int i) to 

	void Cube::drawFace(int i)
	{
		GLfloat shade = 1;

	switch (renderMode) {
	case WIRE:   // this case from SimpleView1
	   glColor3f(r, g, b);
	   glBegin(GL_LINE_LOOP);
	    glVertex3fv(vertex[face[i][0]]);
       glVertex3fv(vertex[face[i][1]]);
       glVertex3fv(vertex[face[i][2]]);
       glVertex3fv(vertex[face[i][3]]);
       glEnd();
	   break;
	case CONSTANT:
	   if (myLight.on == true) shade = getFaceShade(i, myLight);
	   glColor3f(faceColor[i][0]*shade, faceColor[i][1]*shade, faceColor[i][2]*shade);
	   glBegin(GL_POLYGON);
	   glVertex3fv(vertex[face[i][0]]);
	   glVertex3fv(vertex[face[i][1]]);
	   glVertex3fv(vertex[face[i][2]]);
	   glVertex3fv(vertex[face[i][3]]);
	   glEnd();
	  break;
	case FLAT:
	   glShadeModel(GL_FLAT);
       
	   // add your code
	   
	   break;
	
	case SMOOTH:

		glEnable(GL_NORMALIZE);
		glShadeModel(GL_SMOOTH);

....



	break;

	case PHONG:

	  break;
	  
	  case TEXTURE:
	  
	  break;
	}
}

Compile and run, you will see the cube with color faces, without hidden surface removal. 


5. Implement hidden surface removal by adding and implementing the following in Cube object.

    bool isFrontface(int faceindex, Camera camera);

Refer to lecture note slides 13, 14 for the back-face detecting formula. 

For accuracy, we can use the origin of an object to a reference point for testing front face. Specifially, it needs to compute the faceNormal N in WCS, and compute dot product (P-E)*N, where E is the eye, and P is the origin of parent MCS in WCS. The following code is an example of implementation.   
 
	GLfloat v[4];
	v[0] = faceNormal[faceindex][0];  // get faceNormal in MCS
	v[1] = faceNormal[faceindex][1];
	v[2] = faceNormal[faceindex][2];
	v[3] = 0.0;
	mc.multiplyVector(v);   // compute faceNormal in WCS
	   
	if (pmc != NULL) {  // if parent MCS exists, use the parent's origin as reference point. 
		pmc->multiplyVector(v);
		return (pmc->mat[0][3] - camera.eye.x) * v[0] + (pmc->mat[1][3] - camera.eye.y) * v[1] + (pmc->mat[2][3] - camera.eye.z) * v[2] < 0;
	} else {
		return (mc.mat[0][3] - camera.eye.x) * v[0] + (mc.mat[1][3] - camera.eye.y) * v[1] + (mc.mat[2][3] - camera.eye.z) * v[2] < 0;
	}


In Cube::draw() using the following to draw a faces


	for (int i = 0; i < 6; i++) {
		if  (cullMode == BACKFACE ) {
			if (isFrontface(i, myCamera)) {
				drawFace(i);
			}
		}
		else {
			drawFace(i);
		}
	}
	
Compile and run, 

choose Culling  > My back-face, to see the result of back-face method.

choose Culling  > OpenGL back-face & depth buffer, to see the result of OpenGL back-face and depth buffer. 
Note that it is enabled in void cullMenu(GLint option) as case 3. 


6. Create the light object in a similar way to create Pyramid object. 

Add the properties I (initial value 1) as light intensity, and Kd (initial value 1.0) as diffusion reflection rate. 

Use 

	glColor3f(I, I, I);
	glutSolidSphere(size, 10, 10);

to draw light. 

You can add a method to change the light intensity by mouse moving. 


	void Light::Increment(GLfloat p){
		I += p;
		if (I < 0.03) I = 0.01;
		else if (I > 0.97 ) I = 1;
	}

This setting allows you to transform light and change light intensity. 


7. Compute the shading

Add and implement a method, say getFaceShade, to compute face shade

	GLfloat getFaceShade(int faceindex, Light light);
	
Refer to lecture note for the formula to compute the reflection intensity. 	

We only compute diffusion reflection rate. Refer to lecture note about how compute the shade factor. For efficiency, you can add faceNormal for each face, just the first vertex of a face to compute the reflection rate at the point. Similar to isFrontface function, you can implement the 

	GLfloat Cube::getFaceShade(int faceindex, Light light) {
	GLfloat shade = 1, v[4], s[4], temp;

	// assign v the first vertex of face[faceindex][0]

	// compute the position of vertex face[faceindex][0] in WCS

	// compute the light vector s[] = lightposition - face[faceindex][0]

    // normalize vector s

    // compute the normal of  face[faceindex] in WCS

	 // normalize face normal

	 // compute v dot s
	
	temp = v[0]*s[0]+v[1]*s[1]+v[2]*s[2];

	// compute shade factor
	
	shade = light.I*light.Rd*temp; 

	if (shade < 0.01) shade = 0.1;
	if (shade > 0.99 ) shade = 0.9;

	return shade;
}


When this is done, add the following before the 

	  if (myLight.on == true) {
		 shade = getFaceShade(i, myLight);
	  }
	  
to drawFace method before

	 glColor3f(faceColor[i][0]*shade, faceColor[i][1]*shade, faceColor[i][2]*shade); 

Then you can see the effect of shading with menu option Shading->My constant shading. 

For the FLAT and SMOOTH render mode, you can just add glShadeModel(GL_FLAT); or glShadeModel(GL_SMOOTH); before rendering a face. 

For GL_SMOOTH mode, you can set different colors to different vertices. Doing so, you may introduce vertexColor properties to the Cube object. This will result in the colorful cube. 


8. Do the same for the Pyramid object. Then house object will be automatically done. 


9. Animations

For the single object animation, you can add a function move() function to menu.cpp 

	void move(void){
		selectObj->rotate(selectObj->getMC().mat[0][3], selectObj->getMC().mat[1][3], selectObj->getMC().mat[2][3], 0, 0, 1, 0.1);
		glutPostRedisplay();
	}

For multiple object animation, add a function say solar(). 

For example, to get house as sun: 

	GLfloat x1,y1,z1, x2,y2,z2, x3, y3, z3;
	GLfloat sunSpeed = 0.1, earthSpeed = 0.2, earthSunSpeed = 0.1, moonSpeed = 0.2, moonEarthSpeed = 0.2;
	
	Shape *sun = myWorld.searchById(3);
	Shape *earth = myWorld.searchById(1);
	Shape *moon = myWorld.searchById(2);

	x1 = sun->getMC().mat[0][3];
	y1 = sun->getMC().mat[1][3];
	z1 = sun->getMC().mat[2][3];

	x2 = earth->getMC().mat[0][3];
	y2 = earth->getMC().mat[1][3];
	z2 = earth->getMC().mat[2][3];

	x3 = moon->getMC().mat[0][3];
	y3 = moon->getMC().mat[1][3];
	z3 = moon->getMC().mat[2][3];

	// sun motion
    sun->rotate(x1, y1, z1, 0, 0, 1, sunSpeed);

    // earth motion
    earth->rotate(x2, y2, z2, 0, 0, 1, earthSpeed);
    earth->rotateOrigin(x1, y1, z1, 0, 0, 1, earthSunSpeed);

    // moon motion
    
    ....
    
10.  If time is allowed, you can try and add more features into your SimpleView2. For example, add vetex colors, vertex normals, and implement getVertexShade(int i, Light).  Use the following to draw cube face under renderMode=SMOOTH

	   glEnable(GL_NORMALIZE);
	   glShadeModel(GL_SMOOTH);
	   glBegin(GL_POLYGON);
	   for (int j=0; j<4; j++) {
		   if (myLight.on == true) shade = getVertexShade(face[i][j], myLight);
		   glColor3f(vertexColor[face[i][j]][0]*shade, vertexColor[face[i][j]][1]*shade, vertexColor[face[i][j]][2]*shade);
	       glNormal3f(vertexNormal[face[i][j]][0], vertexNormal[face[i][j]][1], vertexNormal[face[i][j]][2]);
	       glVertex3fv(vertex[face[i][j]]);
	   }
	   glEnd();  




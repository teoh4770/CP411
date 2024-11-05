# A4 Report

Author: Chee Kian Teoh

Date: 2024-11-04 

Check [readme.txt](readme.txt) for course work statement and self-evaluation. 
  
## Q1 Culling, Lighting, Shading (description)


### Q1.1 Concepts of culling

1. What is the difference between culling and clipping?

    Culling is a process of removing objects and primitives that cannot be visible; Clipping is a process of removing objects, polygons or fragments that are outside of the viewport.

    Culling does not modify the geometry, but simply remove it from the rendering process; Clipping can modify fragments and polygon shapes to fit within the viewport.

2. What is the difference between object precision and image precision hidden surface removal methods? Give an example of each method. 
    
    Object precision is used to determine visibility at the object level; Image precision is used to determine visibility at the pixel level.
    
    Example of object precision culling method is Back Face method; Example of image precision culling method is Scan Line algorithm.


### Q1.2 Culling computing

Given:

- Eye position at E(3, 2, 2), and
- Reference (look at) point at R(0, 0, 0).
1. Compute to determine if triangle P1(1,0,0), P2(0,1,0), P3(0, 0, 1) is a back face.
2. Compute the depth (z-value) of the above triangle.

Write your solution on paper, and take a picture using laptop camera, save it as a4q1.2.png to the images folder and link to the a4_report.md


### Q1.3 Concepts of lighting and shading

1. What does a color model do? Give the names of three color models.
    
    Color model uses color to classify, represent and create colours.

    Name of three color models: XYZ model, RGB model, CMY model.
    
2. What does a light source model determine? Give the names of three light source models.
    
    Light source model determines position or direction, color and intensity of the light source.

    Three light source models: point, directional, ambient
    
3. What does a reflection model determine? Give the names of three reflection models.
    
    Reflection model determines how light source is reflected by surface, more specifically, the reflection properties of the surface materials, such as colour, roughness, direction towards light source.

    Three reflection models: diffuse reflection, specular reflection, ambient reflection
    
4. What does a shading model determine? Give the names of three shading models.
    
    Shading model determines how a pixel color is calculated based on the light reflection models.
    
    Three shading models: constant shading, Gouraud Shading (smooth shading), Phong Shading


### Q1.4 Lighting computing

Given:

- Eye position at E(3, 2, 2), point light position at L(1, 2, 4) with light intensity 0.8,
- Triangle P1(1,0,0)P2(0,1,0)P3(0, 0, 1), and surface diffusion rate 0.4 for red color.

Compute the simple diffusion reflection intensity of red color at the center of the triangle. (Use the simple diffusion reflection formula in slide 11 of lecture 13 (lighting).

Write your solution on paper, and take a photo, save it as a4q1.4.png to the images folder and link to the a4_report.md



## Q2 OpenGL Culling, Lighting, Shading (lab practice)


### Q2.1 Hidden surface removal 

Complete? Yes or No 

<!--If you answer Yes, insert one or more screenshot images to show the completion.-->

![Image caption](images/demo.png){width=90%}

<!-- If No, add a short description to describe the issues encountered.-->

### Q2.2 Lighting and shading 

Complete? Yes or No 

<!--If you answer Yes, insert one or more screenshot images to show the completion.-->

![Image caption](images/demo.png){width=90%}

<!-- If No, add a short description to describe the issues encountered.-->

### Q2.3 Animation 

Complete? Yes or No 

<!--If you answer Yes, insert one or more screenshot images to show the completion.-->

![Image caption](images/demo.png){width=90%}

<!-- If No, add a short description to describe the issues encountered.-->


## Q3 SimpleView2 Culling, Lighting, Shading (programming)


### Q3.1 Culling

Complete? Yes or No 

<!--If you answer Yes, insert one or more screenshot images to show the completion. -->

![Image caption](images/demo.png){width=90%}

<!--If No, add a short description to describe the issues encountered.-->


### Q3.2 Lighting

Complete? Yes or No 

<!--If you answer Yes, insert one or more screenshot images to show the completion. -->

![Image caption](images/demo.png){width=90%}

<!--If No, add a short description to describe the issues encountered.-->


### Q3.3 Shading

Complete? Yes or No 

<!--If you answer Yes, insert one or more screenshot images to show the completion. -->

![Image caption](images/demo.png){width=90%}

<!--If No, add a short description to describe the issues encountered.-->


### Q3.4 Animations

Complete? Yes or No 

<!--If you answer Yes, insert one or more screenshot images to show the completion. -->

![Image caption](images/demo.png){width=90%}

<!--If No, add a short description to describe the issues encountered.-->




**References**

1. CP411 a4
2. Add your references if you used any. 

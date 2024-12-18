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

![a4q1 2](https://github.com/user-attachments/assets/3c0944e4-2bf5-42ce-9111-18a57d543a03)


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

![a4q1 4](https://github.com/user-attachments/assets/66bd86d1-0e0a-46b6-b27c-0051f264ef3d)


## Q2 OpenGL Culling, Lighting, Shading (lab practice)


### Q2.1 Hidden surface removal 

Complete? Yes

<!--If you answer Yes, insert one or more screenshot images to show the completion.-->
![Without culling](https://github.com/user-attachments/assets/12b81c6c-83d8-41dc-bc03-45987d741838)
![With culling](https://github.com/user-attachments/assets/5ed8bd61-139d-419c-95bc-1c0459594c3a)
![Animation](https://github.com/user-attachments/assets/4d59bce4-dd98-422a-a2ca-bd79fa7ec8c6)


<!-- If No, add a short description to describe the issues encountered.-->

### Q2.2 Lighting and shading 

Complete? Yes

<!--If you answer Yes, insert one or more screenshot images to show the completion.-->

**Drawing a Lit Sphere**

Purpose: learn how to do a dimple light setting to draw a lit sphere.

Note1: Try different values of light position, colors in mat_specular, to see the resulted effects.

Note2: change the color in mat_specular change the color of light being reflected

![white color light reflected](https://github.com/user-attachments/assets/f661ff7b-f34d-4025-94bb-f23ebf5b98a8)

![teal color light reflected](https://github.com/user-attachments/assets/236194a2-3118-4601-99b1-8650fd88df23)


**Move a Light with Modeling Transformation**

Purpose: to see how to transfer light positions

![light source at the back of the donut, front seems totally dark](https://github.com/user-attachments/assets/5f83dd6f-aacf-4a18-893c-2779518060b6)
![light source at the bottom of the donut, can see some light coming from the bottom of the object](https://github.com/user-attachments/assets/58b567a5-5058-46e5-9164-6ade746e0c70)

**Programming material reflection properties**

Purpose: to learn how to program material reflection properties

Note: diffuse = matte surface; specular = reflective surface like glass or metal

![Increment the red component of diffuse material to make it appear more red when reflected by light](https://github.com/user-attachments/assets/446fb976-65a6-4fc6-8a0d-215fa351433a)

**General lighting and shading**

Purpose: see how to use OpenGL API to configure overall light model material, spot light, ambient light and spectacular

Note: seems like different light have different light setting.

![Light 0](https://github.com/user-attachments/assets/36ce5d62-a1bf-42f5-b99a-9fa82e2ce162)

![Light 1](https://github.com/user-attachments/assets/dab523b5-5273-4061-9429-ebdc10b291b8)




<!-- If No, add a short description to describe the issues encountered.-->

### Q2.3 Animation 

Complete? Yes

<!--If you answer Yes, insert one or more screenshot images to show the completion.-->
![A spinning cube that rotates at xy-axis](https://github.com/user-attachments/assets/c24f2a65-b120-413b-922a-bc398ffdd7a8)


<!-- If No, add a short description to describe the issues encountered.-->


## Q3 SimpleView2 Culling, Lighting, Shading (programming)


### Q3.1 Culling

Complete? Yes

<!--If you answer Yes, insert one or more screenshot images to show the completion. -->
**No culling**

<img width="696" alt="no_culling" src="https://github.com/user-attachments/assets/2cace9e7-935d-4035-a5f3-c3dfe454aa0a">
<hr />

**Custom backface culling**

<img width="696" alt="my_back_culling" src="https://github.com/user-attachments/assets/e636a7c5-f05e-4c9a-9714-2cca1cf84463">
<hr />

**Built-in backface & depth buffer**

<img width="696" alt="built-in-culling" src="https://github.com/user-attachments/assets/3a44c322-f9e7-4363-94f5-224e66cf5d6c">


<!--If No, add a short description to describe the issues encountered.-->


### Q3.2 Lighting

Complete? No, I complete the lighting effect, but I kinda make the lighting not align with the cube that represent the lighting position.

<!--If you answer Yes, insert one or more screenshot images to show the completion. -->

![Screenshot 2024-11-07 at 11 19 31 AM](https://github.com/user-attachments/assets/32b97227-c2bb-4365-b024-9482ca9b2c17)


<!--If No, add a short description to describe the issues encountered.-->


### Q3.3 Shading

Complete? No, only finish no shading and my constant shading

<!--If you answer Yes, insert one or more screenshot images to show the completion. -->

**No shading**

![No shading](https://github.com/user-attachments/assets/2a2fd90a-2117-441b-a53b-e132d4a510a8)
<hr />

**My constant shading**

![Constant shading](https://github.com/user-attachments/assets/ed89f090-dc54-40ea-b6b4-bbfa9c27c41a)
<hr />

<!--If No, add a short description to describe the issues encountered.-->
<!--Can't figure out how shading work for flat shading and smooth shading.-->


### Q3.4 Animations

Complete? Yes

<!--If you answer Yes, insert one or more screenshot images to show the completion. -->

**Single object animation**

![single_animation](https://github.com/user-attachments/assets/6881df5e-f835-4440-a6ae-1c81da13f7bb)
<hr/>

**Multiple object animation**

![multiple_animation](https://github.com/user-attachments/assets/0c25cac2-5a99-4843-9995-93c571dac338)


<!--If No, add a short description to describe the issues encountered.-->


**References**

1. CP411 a4
2. CP411 a4 slides
3. SimpleView2_reference_design

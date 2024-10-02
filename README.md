# A2 Report

Author: Chee Kian Teoh

Date: 2024-09-19

Check [readme.txt](readme.txt) for course work statement and self-evaluation. 
  
## Q1 Graphics pipeline (description)


### Q1.1 Graphics primitives

What are graphic primitives, and their relations to graphics objects?

Write your answer here:
Graphics primitives, or primitives, are the fundamental elements that display on the screen, which are used to construct more complex graphical objects. Examples of primitives are points, lines, triangles and polygon.


### Q1.2 Graphics pipeline operations

What are the major operations/computings in graphic pipelines?

Write your answer here:
Graphic pipeline describes a process where we convert a 3D scene description into a 2D image that we can view. Processes of graphics pipeline involves transformations between scenes (3D scene to 2D scene), projection and rasterisation.


### Q1.3 Coordinate systems & transformations

What coordinate systems and transformations are involved in graphics pipeline?

Write your answer here.
Coordinate systems that involved in graphics pipeline are:
a. Modelling Coordinate System (MCS): local coordinate to represent object model
b. World Coordinate System (WCS): global coordinate to represent all object instances in 3D world
c. Viewer Coordinate System (VCS): local coordinate of viewer
d. Normalised Device Coordinate System (NDCS): 
e. Device Coordinate System or Screen Coordinate System (DCS or SCS):

Transformations that involved in graphics pipeline are:
a. Modelling transformations: what I need to know in high level?
b. Viewing transformations
c. Projection transformations
d. Display transformations



### Q1.4 Scan conversion

What does a scan conversion algorithm do?

Write your answer here.
Scan conversion, or rasterisation algorithms are implemented at the last step of graphics pipeline, which convert primitives to pixels, which then store to framebuffer to be rendered.


### Q1.5 Hand-on Midpoint algorithm

Apply Midpoint algorithm to determine the pixel positions (0<=x<=y) of circle centered at (0, 0) and radius 10.

Write you answer on paper, write your name on the paper, take a picture and save it in the image folder, and link as follows.  

![Midpoint-algorithm-question](https://github.com/user-attachments/assets/dc557584-21a8-480b-9b37-afbce00c52ed)


## Q2 OpenGL and Glut (lab practice)


### Q2.1 OpenGL primitives 

Complete? Yes or No 

<!--If you answer Yes, insert a screenshot image to show the completion.-->
Yes

![Image caption](images/demo.png){width=90%}

<!-- If No, add a short description to describe the issues encountered.-->

### Q2.2 Interactive graphics 

Complete? Yes or No 

<!--If you answer Yes, insert a screenshot image to show the completion.-->

![Image caption](images/demo.png){width=90%}

<!-- If No, add a short description to describe the issues encountered.-->

### Q2.3 Bitmap file I/O 

Complete? Yes or No 

<!--If you answer Yes, insert a screenshot image to show the completion.-->

![Image caption](images/demo.png){width=90%}

<!-- If No, add a short description to describe the issues encountered.-->


## Q3 SimpleDraw (programming)


### Q3.1 Display window and menu

Complete? Yes or No 

<!--If you answer Yes, insert a screenshot image to show the completion. -->

![Image caption](images/demo.png){width=90%}

<!--If No, add a short description to describe the issues encountered.-->


### Q3.2 Data structures

Complete? Yes or No 

<!--If you answer Yes, insert a screenshot image to show the completion. -->

![Image caption](images/demo.png){width=90%}

<!--If No, add a short description to describe the issues encountered.-->


### Q3.3 Draw rectangles

Complete? Yes or No 

<!--If you answer Yes, insert a screenshot image to show the completion. -->

![Image caption](images/demo.png){width=90%}

<!--If No, add a short description to describe the issues encountered.-->


### Q3.4 Draw circles

Complete? Yes or No 

<!--If you answer Yes, insert a screenshot image to show the completion. -->

![Image caption](images/demo.png){width=90%}

<!--If No, add a short description to describe the issues encountered.-->


### Q3.5 Edit features

Complete? Yes or No 

<!--If you answer Yes, insert a screenshot image to show the completion. -->

![Image caption](images/demo.png){width=90%}

<!--If No, add a short description to describe the issues encountered.-->


### Q3.6 Save/Open SVG files

Complete? Yes or No

If you answer Yes, link the image
![output.bmp](images/output.svg).


### Q3.7 Export to bitmap

Complete? Yes or No

If you answer Yes, link the image
![ouput.bmp](images/output.bmp).


### Q3.8 Circle&Square artwork

Complete? Yes or No

If you answer Yes, link the images
[C&S artwork in SVG](images/c&s.svg)
![C&S artwork in bitmap](images/c&s.bmp).




**References**

1. CP411 a2
2. Add your references if you used any. 


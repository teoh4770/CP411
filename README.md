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

![Q2 1](https://github.com/user-attachments/assets/ebdc5062-8a58-478f-9502-c79886fe5c2c)


<!-- If No, add a short description to describe the issues encountered.-->

### Q2.2 Interactive graphics 

Complete? Yes or No 

<!--If you answer Yes, insert a screenshot image to show the completion.-->
Yes

![Q2 2](https://github.com/user-attachments/assets/f7518b43-e64b-4d55-8085-b60c49fd37c2)


<!-- If No, add a short description to describe the issues encountered.-->

### Q2.3 Bitmap file I/O 

Complete? Yes or No 

<!--If you answer Yes, insert a screenshot image to show the completion.-->

<!-- If No, add a short description to describe the issues encountered.-->
No. I couldn't see the downloaded bitmap file in my folder. I am able to reload it back to the screen though...


## Q3 SimpleDraw (programming)


### Q3.1 Display window and menu

Complete? Yes or No 

<!--If you answer Yes, insert a screenshot image to show the completion. -->
Yes

![Screenshot 2024-10-01 234807](https://github.com/user-attachments/assets/f4add10b-7c1d-4545-b651-66215140f423)


### Q3.2 Data structures

Complete? Yes or No 

Yes, this is a small snippet of the codes regarding that.

![Screenshot 2024-10-01 235030](https://github.com/user-attachments/assets/8ca5da8a-5be6-48f4-a723-6644241481eb)


### Q3.3 Draw rectangles

Complete? Yes or No

<!--If you answer Yes, insert a screenshot image to show the completion. -->
Yes and No. I'm only able to show one rectangle one at a time. Also no move and edit feature.

![Screenshot 2024-10-01 235156](https://github.com/user-attachments/assets/6ecbb422-2a89-4b06-b8f9-8077f60a29ae)


<!--If No, add a short description to describe the issues encountered.-->

### Q3.4 Draw circles

Complete? Yes or No 

Yes and No. I'm only able to show a circle one at a time. Also no move and edit feature.

![Screenshot 2024-10-01 235305](https://github.com/user-attachments/assets/01845869-2d2b-42b3-bf62-5a2c07b35b60)


<!--If No, add a short description to describe the issues encountered.-->


### Q3.5 Edit features

Complete? Yes or No 

No. Didn't do

<!--If No, add a short description to describe the issues encountered.-->


### Q3.6 Save/Open SVG files

Complete? Yes or No

No. Didn't do


### Q3.7 Export to bitmap

No. Didn't do


### Q3.8 Circle&Square artwork

No. Didn't do


**References**

1. CP411 a2


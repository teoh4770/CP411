# Project Report

Author: Wen Tao, Chee Kian Teoh  

Date: 2024-12-03 

Check [readme.txt](readme.txt) for course work statement and self-evaluation. 
  

## R1 Proposal (proposal)

### R1.1 Application problem description
 
Complete? (Yes) 

The project involves implementing the iconic DVD Logo Challenge, where the player controls the direction of a bouncing logo to make it hit the screen's corners for points. The primary goal is to combine animation, user interaction, and graphics techniques to create a nostalgic yet engaging experience. 
	

### R1.2 Creativity/new features
 
Complete? (Yes) 

Highlighted features:

1. Dynamic color changes upon collision.
2. Corner collision detection for scoring.
3. User-controlled direction via arrow keys.
4. Real-time rendering with visual and functional feedback.

<a href="proposal.md">Proposal</a>

### R1.3 Design consideration
 
Complete? (Yes)

The design incorporates:

1. Accurate collision detection for walls and corners.
2. User interaction with smooth response to keyboard inputs.
3. Realistic physics for bouncing effects.
4. A simple yet visually pleasing graphics rendering system.

<a href="proposal.md">Proposal</a>

### R1.4 Milestones and schedule
 
Complete? (Yes) 

| Task ID | Description   |  Due date | Lead   |  
| :----:  | :------------ | :-----:   | :------: |  
|  1      | Project research & team up | Nov 25 | Wen Tao | 
|  2      | Project proposal | Nov 26 | Chee Kian |
|  3      | Programming milestones  | Nov 28 | Both  |
|  4      | Final testing & demo prep  | Dec 1  | Both  |
|  5      | Project demonstration | Dec 5 | Both  |
|  6      | Project submission | Dec 3 | Both   |


### R1.5 References
 

Complete? (Yes) 

<a href="proposal.md">Proposal</a>


### R1.6 Writing of the proposal
 
Complete? (Yes) 

<a href="proposal.md">Proposal</a>


## R2 Design & implementation (programming)

### R2.1 Problem solving and algorithms
 
Complete? (Yes) 

Collision detection is implemented to detect wall and corner hits. The logo's trajectory and velocity are adjusted based on these collisions, and colors change dynamically.

[collision algorithm at Logo.cpp](images/collision.png)


### R2.2 Completion of the project
 
Complete? (Yes) 

[Running Program](images/program.png)


### R2.3 New features
 
Complete? (Yes) 

- Dynamic color changes when the logo collides with wall.

[Color changes when the logo collides with wall](images/color.png)

- Corner detection and scoring.

[Score updates after the logo hits the corner](images/score.png)

- Interactive controls for logo direction.

[Keyboard control logic in main.cpp](images/control.png)


### R2.4 Program design and organization
 
Complete? (Yes) 

Modular Design And MVC Design:

Logo Class: Handles animation, movement, and collision detection.
Score Class: Manages scoring logic.
Font Class: Renders text for messages and score display.
Main Application: Coordinates user inputs, rendering, and game logic.

[Generic MVC Diagram Sketch for DVD Logo Challenge](images/mvc.png)

## R3 Delivery (document)

### R3.1 Presentation & demonstration
 

Complete? (Yes) 

If not presented in class, include media file, and add link to the medial file.


### R3.2 Documentation
 
Complete? (Yes) 

Add the hyperlinks to the documents. 

<a href="project_report.md">Project Report</a>

### R3.3 Submission packaging


Complete? (Yes) 

This package.


**References**

1. CP411 project
2. LearnOpenGL. (n.d.). Collision detection. Retrieved from https://learnopengl.com/In-Practice/2D-Game/Collisions/Collision-detection
3. opengl-tutorial.org. (n.d.). Tutorial 6: Keyboard and mouse. Retrieved from https://www.opengl-tutorial.org/beginners-tutorials/tutorial-6-keyboard-and-mouse/
4. MDN Web Docs. (n.d.). 3D collision detection - Game development techniques. Retrieved from https://developer.mozilla.org/en-US/docs/Games/Techniques/3D_collision_detection
5. YouTube. (n.d.). OpenGL video tutorial - Collision detection. Retrieved from https://www.youtube.com/watch?v=Lg0kOoiCI80
6. GitHub. (n.d.). jojoth/OpenTK-Course: Learn OpenTK and OpenGL game development. Retrieved from https://github.com/jojoth/OpenTK-Course
7. DVD Game inspiration, DesignList. Retrieved from https://www.designslist.com/dvd
8. Model-View-Controller, Wikipedia. Retrieved from https://en.wikipedia.org/wiki/Model%E2%80%93view%E2%80%93controller

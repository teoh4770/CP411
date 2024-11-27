# CP411 Project: DVD Logo Challenge 

Author(s): Wen Tao, Chee Kian Teoh

Date: 2024-11-25

## Introduction  

Remember the iconic DVD logo bouncing around a dark screen? This simple yet captivating animation sparked excitement as viewers eagerly awaited the moment it perfectly hit the corner of the screen. Inspired by this nostalgic memory, we present DVD Logo Challenge, an interactive 2D game that brings this iconic moment to life.

In this game, players control the movement of the bouncing DVD logo using arrow keys, aiming to make it hit the exact corners of the screen to score points. The game combines the simplicity of the original animation with interactive gameplay, challenging players to plan ahead and react quickly to the logo's changing position.

The project aims to revive the joy of watching the DVD logo bounce while introducing a new layer of engagement through interactivity. It will also serve as a hands-on exercise in implementing key computer graphics concepts, such as collision detection, real-time rendering, and input handling.

## Problem Solving and Algorithms  

To create the DVD Logo Challenge, several technical challenges must be addressed:

- **Collision Detection**: The game requires accurate detection of when the DVD logo reaches the edges of the screen, particularly the corners, to ensure correct scoring and movement mechanics.

- **Player-Controlled Movement**: Smooth and intuitive player control of the DVD logo's movement direction using arrow keys, without breaking the bouncing physics of the logo.

- **Realistic Bouncing Physics**: Maintaining a natural bounce behavior when the logo collides with edges while preserving the exact angles of reflection.

- **Dynamic Color Changes**: Implementing color transitions when the logo bounces to visually signal collisions.

<br />

**Notes on collision detection algirithm**

Collision detection algorithm is implemented to determine whether the logo has hit the edges or corners of the screen. The algorithm comprises:

**Boundary Detection**: Check if the logo's center position exceeds the screen's boundaries.

> Assuming the screen dimensions are width and height, and the logo's center is (x, y) with a radius r:
> 
> Left boundary: x - r <= 0
> 
> Right boundary: x + r >= width
> 
> Top boundary: y - r <= 0
> 
> Bottom boundary: y + r >= height

**Corner Detection**: If the logo meets both a horizontal and vertical boundary condition, it is considered to have hit a corner.

> For example:
> 
> Top-left corner: x - r <= 0 && y - r <= 0
> 
> Bottom-right corner: x + r >= width && y + r >= height

**Pseudocode Example**:

    def detect_collision(x, y, vx, vy, r, width, height):
        if x - r <= 0 or x + r >= width:
            vx = -vx  # Invert horizontal velocity
            if y - r <= 0 or y + r >= height:
                score += 1  # Corner hit
        if y - r <= 0 or y + r >= height:
            vy = -vy  # Invert vertical velocity
        return vx, vy, score

## Design consideration of our CG project

**Components and their roles**

- Edges of the Screen: Define boundaries for collision detection and scoring.
- Logo: Represents the moving object, interacting with walls and edges.
- Keyboard Inputs: Allows players to control the logo's moving direction through keyboard in real time.
- Score Tracker: Keeps a real-time record of the user’s score when corners are hit.
- Rendering System: Ensures a smooth visual experience for the player.

**How these components come together**

The logo starts by bouncing off from the corner of the edge of the screen. When the player presses an arrow key, it updates the moving direction of the logo. The collision detection system checks if the logo has hit an edge or corner. The logo bounces and change color, indicate that a collision is detected. The score tracker updates the player's score if the collision happens at a corner. The rendering system continously updates the screen to reflect these changes in real time.

**User Stories**

1. As a player, I want to use keyboard inputs to control the direction of the moving logo so I can aim for the screen corners.
2. As a player, I want the logo bounces off walls at the correct angle.
3. As a player, I want to see the logo changes color when bouncing to visually confirm the collision.
4. As a player, I want to control the logo to hit the corner of the screen to score.
5. As a player, I want the game to render in real time so I can see instant feedback on my action.

<br />

We will adopt an **MVC (Model, View, Controller)** design pattern.

**Model (Game Logic)**, Handles the data and logic:

- Keeps track of the logo’s position, velocity, and color.
- Detects collisions and updates the score when the logo hits a corner.
- Manages the player's score and resets the game state if needed.
  
**View (Rendering)**, manages what the user sees:

- Draws the DVD logo, edges, and score on the screen.
- Updates the visuals dynamically (e.g., changes the logo color after collisions).
  
**Controller (Input)**, handles player input:

- Processes arrow key presses to move the DVD logo.
- Communicates these actions to the Model to update the logo’s position.

## Milestones & schedule

List of tasks/milestones/check points of your project with time schedule. For group project, it needs to provide the roles and tasks of each member.


| Task ID | Description   |  Due date | Lead   |  
| :----:  | :------------ | :-----:   | :------: |  
|  1      | Project research & team up | Nov 25 | Wen Tao | 
|  2      | Project proposal | Nov 26 | Chee Kian |
|  3      | Project check point  | Nov 28 | -  |
|  4      | Project check point  | Nov 1  | -  |
|  5      | Project demonstration | Dec 5 | -  |
|  6      | Project submission | Dec 3 | -   |



## References

1. LearnOpenGL. (n.d.). Collision detection. Retrieved from https://learnopengl.com/In-Practice/2D-Game/Collisions/Collision-detection

2. opengl-tutorial.org. (n.d.). Tutorial 6: Keyboard and mouse. Retrieved from https://www.opengl-tutorial.org/beginners-tutorials/tutorial-6-keyboard-and-mouse/

3. MDN Web Docs. (n.d.). 3D collision detection - Game development techniques. Retrieved from https://developer.mozilla.org/en-US/docs/Games/Techniques/3D_collision_detection

4. YouTube. (n.d.). OpenGL video tutorial - Collision detection. Retrieved from https://www.youtube.com/watch?v=Lg0kOoiCI80

5. GitHub. (n.d.). jojoth/OpenTK-Course: Learn OpenTK and OpenGL game development. Retrieved from https://github.com/jojoth/OpenTK-Course

6. DVD Game inspiration, DesignList. Retrieved from https://www.designslist.com/dvd

7. Model-View-Controller, Wikipedia. Retrieved from https://en.wikipedia.org/wiki/Model%E2%80%93view%E2%80%93controller


**Comments**

1. Check the project [readme.txt](readme.txt) for detailed requirements and evaluation. You need to describe and claim new features in your project, so it is good (not required) to mention some new features in the proposal. 
2. You may use HTML elements and CSS for better presentation of your proposal. For example, this HTML document is generated by using [proposal_template.md](proposal_template.md) and  [proposal.css](proposal.css) and the following pandoc command   

~~~
pandoc -s -i proposal_template.md -o proposal_template.html --css=proposal.css --metadata pagetitle="proposal
~~~

3. You can submit your proposal in PDF file format for proposal submission. 

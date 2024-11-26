# CP411 Project: Your Project Title

Author(s): Wen Tao, Chee Kian Teoh

Date: 2024-11-25


## Introduction

General description and rationals of your project. 

The main problem to be solved, and algorithms. For example, how to pick up a 3D object by mouse in 3D view system.  
 
## Problem solving and algorithms

Briefly describe the major computing problem and possible solutions.  

## Design consideration 

### System design of our CG project

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


### The architecture

We will adopt an **MVC (Model, View, Controller)** design pattern:  

- **Model:** Handles the game's logic, including position updates, collision detection, and scoring.  
- **View:** Renders the DVD logo, window edges, and color transitions.  
- **Controller:** Processes player input and communicates with the Model to update the game state.  


## Milestones & schedule

List of tasks/milestones/check points of your project with time schedule. For group project, it needs to provide the roles and tasks of each member.


| Task ID | Description   |  Due date | Lead   |  
| :----:  | :------------ | :-----:   | :------: |  
|  1      | Project research & team up | Day 7 of week 10 | who | 
|  2      | Project proposal | Day 6 of week 11 | who |
|  3      | Project check point  | date | who  |
|  4      | Project check point  | date  | who  |
|  5      | Project demonstration | Day 6 of week 12 | who  |
|  6      | Project submission | Day 7 of week 12 | who   |



## References

A list of references you read for your project, such as papers, articles, data sources. 


**Comments**

1. Check the project [readme.txt](readme.txt) for detailed requirements and evaluation. You need to describe and claim new features in your project, so it is good (not required) to mention some new features in the proposal. 
2. You may use HTML elements and CSS for better presentation of your proposal. For example, this HTML document is generated by using [proposal_template.md](proposal_template.md) and  [proposal.css](proposal.css) and the following pandoc command   

~~~
pandoc -s -i proposal_template.md -o proposal_template.html --css=proposal.css --metadata pagetitle="proposal
~~~

3. You can submit your proposal in PDF file format for proposal submission. 
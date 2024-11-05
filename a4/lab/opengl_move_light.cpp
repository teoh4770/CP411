/*
 * Example from OpenGL red book demos how to move a light source in an OpenGL 3D scene
 * https://www.glprogramming.com/red/chapter05.html
 * compile: g++ opengl_move_light.cpp -lfreeglut -lopengl32 -lglu32
 * Run: a.exe  left clicking mouse to move light position
*/

#include <GL/glut.h>

// When you click the left mouse button, the light rotates around the scene, making objects appear differently lit as the light position changes.
// Key elements include:
// 1. setting up light source
// 2. configuring lighting properties
// 3. using mouse input to update the light position
static int spin = 0;


void init(void)
{
	// Setup the background color to black
	// Enable smooth shading (what is smooth shading?)
	// Enable lighting
	// Enable specific lighting (needed)
	// Enable depth testing so that objects closer to the viewer appear in front of those that are further back
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);
}

/*  Here is where the light position is reset after the modeling
 *  transformation (glRotated) is called.
 *  - This places the light at a new position in world coordinates.
 *  - The cube represents the position of the light.
 *  - When GL_LIGHT0 position is updated with each left-click, the light effectively rotates around the torus
 *  - The rotation simulates a movement of light source around the object, which (important) change the shade and reflections on the torus
 */
// Knowledge point:
// GL_LIGHT0: first light source in OpenGL (from 0 to 7), must be enabled to create lighting effects in this scene
// 	glLightfv(GL_LIGHT0, GL_POSITION, position); -> set the light source based on the coordinate in position
//
void display(void)
{
   // Define the light initial position at glLightFv
   // fourth value (1.0) indicates a positional light source (as opposed to a directional one)
   GLfloat position[] = { 0.0, 0.0, 1.5, 1.0 };

   // Scene is cleared
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   // Transformation are applied to both light and torus
   // Note1: both lighting and cube are at the same position, 1.5 units along the z-axis
   // Note2: both lighting and cube undergo the same transformations (rotation)
   // E.g. cube translated to match the position of lighting, 1.5 units along the z-axis
   // E.g. lighting and cube getting the rotating transformation
   // E.g. cube will be translated, then rotated
   glPushMatrix ();
	   glTranslatef (0.0, 0.0, -5.0);

	   glPushMatrix ();
		   // Moving the light around the x-axis by the angle store in spin
		   // setting the light position for GL_LIGHT0 after rotation
		   glRotated ((GLdouble) spin, 1.0, 0.0, 0.0);
		   glLightfv (GL_LIGHT0, GL_POSITION, position);

		   // Disable lighting to draw the cube in a fixed color without shading
		   glDisable(GL_LIGHTING);

	       // Translate the cube to 1.5 units along the z-axis to match light's position
		   glTranslated (0.0, 0.0, 1.5);
		   glColor3f (0.0, 1.0, 1.0);
		   glutWireCube (0.1);
		   glEnable (GL_LIGHTING); // Restore the lighting after drawing the cube
	   glPopMatrix ();

	   // Draw the torus object(donut) which will receive lighting effect based on the current position of GL_LIGHT0
	   glutSolidTorus (0.275, 0.85, 8, 15);
   glPopMatrix ();
   glFlush ();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(40.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void mouse(int button, int state, int x, int y)
{
   switch (button) {
      case GLUT_LEFT_BUTTON:
         if (state == GLUT_DOWN) {
            spin = (spin + 30) % 360;
            // trigger the display function to refresh the scene
            glutPostRedisplay();
         }
         break;
      default:
         break;
   }
}
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (500, 500);
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutMouseFunc(mouse);
   glutMainLoop();
   return 0;
}

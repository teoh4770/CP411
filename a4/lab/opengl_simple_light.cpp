/*
 * Example from OpenGL red book, testing on simple OpenGL light and material
 * compile: g++ opengl_simple_light.cpp -lfreeglut -lopengl32 -lglu32
 * Run: a.exe
*/

#include <GL/glut.h>

// Note about glMaterialfv
// glMaterialfv:
// sets material properties for the object being rendered
// which define how they interact with light sources
// glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
// -> sets the specular reflection properties for the front facing side of object
// -> mat_specular is set to {1.0, 1.0, 1.0, 1.0},
//    meaning the material reflects light at full intensity in
//    all color channels (red, green, and blue) and is fully opaque (alpha is 1.0).
// glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
// -> sets the shininess property, control how shiny the material appears
// -> mat_shininess is 50, lower values create smaller, sharper highlights,
//    while higher values make highlights broader and softer
void init(void)
{

   glClearColor (0.0, 0.0, 0.0, 0.0);
   // Enable lights
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);
   glShadeModel (GL_SMOOTH);

   GLfloat light_position[] = { 2.0, 2.0, 2.0, 0.0 };
   GLfloat mat_specular[] = { 0.0, 1.0, 1.0, 1.0 };
   GLfloat mat_shininess[] = { 50.0 };
   // General form
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);
   // Set the materials
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   // sphere with radius 1.0, 20 slices (from left to right), 16 stacks(from top to bottom)
   glutSolidSphere (1.0, 20, 16);
   glFlush ();
}

void reshape (int w, int h)
{
   // ensure sphere remains centered and maintains its shape
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   // Remove any prior transformation
   glLoadIdentity();
   // setup orthogonal projection
   // adjust based on window's aspect ratio to prevent sphere from stretching
   // when window is resized
   // If the width w is less than or equal to the height h, the x-axis is set to [-1.5, 1.5] and the y-axis is scaled proportionally.
   // Otherwise, if the window is wider than it is tall, the y-axis is set to [-1.5, 1.5] and the x-axis is scaled proportionally.
   if (w <= h)
      glOrtho (-1.5, 1.5, -1.5*(GLfloat)h/(GLfloat)w,
         1.5*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
   else
      glOrtho (-1.5*(GLfloat)w/(GLfloat)h,
         1.5*(GLfloat)w/(GLfloat)h, -1.5, 1.5, -10.0, 10.0);
   // Reset the matrix model to modelview matrix, enable translations
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
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
   glutMainLoop();
   return 0;
}

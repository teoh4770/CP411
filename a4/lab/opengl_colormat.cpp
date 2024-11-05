/*  adopted from
 * https://www.glprogramming.com/red/chapter05.html
*/

/*
 * Description: testing OpenGL color material features, diffuse material specifically
 * compile: g++ opengl_colormat.cpp -lfreeglut -lopengl32 -lglu32
 * Run: a.exe  clicking different mouse buttons to see the changes.
 * HBF
 */

#include <GL/glut.h>

// diffuse reflection represents how a material reflects light in all directions from its surface.
// means that sphere will appear brightest on the side facing the light source
// and gradually darken on other sides, create a smooth transition of light across the surface

// gray color initially
// dynamically updated based on user interaction to change the color component
// controls how sphere reflects light from GL_LIGHT0, change how sphere looks like under lighting
// increasing red component makes sphere reflects more red light
GLfloat diffuseMaterial[4] = { 0.5, 0.5, 0.5, 1.0 };

void init(void)
{
   GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);
   glEnable(GL_DEPTH_TEST);

   glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial); // create matte surface that don't create sharp highlights, but still showing shading based on direction of light
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); // ideal for materials like metal, glass, that reflect light in a focused manner (hightlight)
   glMaterialf(GL_FRONT, GL_SHININESS, 25.0);

   glLightfv(GL_LIGHT0, GL_POSITION, light_position);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);

   // If disabled, then no diffuse
   // To update the color, glColor4fv(updated diffuse material color);
   glColorMaterial(GL_FRONT, GL_DIFFUSE);
   // to allow the use of glColor to update the diffuse material
   // so that when glColor4fv(updatedColor); is called, it directly update the diffuse color, which affects how the sphere is shaded.
   glEnable(GL_COLOR_MATERIAL);
}

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glutSolidSphere(1.0, 20, 16);
   glFlush ();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   if (w <= h)
      glOrtho (-1.5, 1.5, -1.5*(GLfloat)h/(GLfloat)w,
         1.5*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
   else
      glOrtho (-1.5*(GLfloat)w/(GLfloat)h,
         1.5*(GLfloat)w/(GLfloat)h, -1.5, 1.5, -10.0, 10.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void mouse(int button, int state, int x, int y)
{
   switch (button) {
      case GLUT_LEFT_BUTTON:
         if (state == GLUT_DOWN) {       /*  change red  */
            diffuseMaterial[0] += 0.1;
            if (diffuseMaterial[0] > 1.0)
               diffuseMaterial[0] = 0.0;
            glColor4fv(diffuseMaterial);
            glutPostRedisplay();
         }
         break;
      case GLUT_MIDDLE_BUTTON:
         if (state == GLUT_DOWN) {       /*  change green  */
            diffuseMaterial[1] += 0.1;
            if (diffuseMaterial[1] > 1.0)
               diffuseMaterial[1] = 0.0;
            glColor4fv(diffuseMaterial);
            glutPostRedisplay();
         }
         break;
      case GLUT_RIGHT_BUTTON:
         if (state == GLUT_DOWN) {      /*  change blue  */
            diffuseMaterial[2] += 0.1;
            if (diffuseMaterial[2] > 1.0)
               diffuseMaterial[2] = 0.0;
            glColor4fv(diffuseMaterial);
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

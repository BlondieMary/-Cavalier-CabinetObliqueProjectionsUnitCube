#include <windows.h> 
#include <GL/glut.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <math.h> 
#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <fstream>
#define _USE_MATH_DEFINES

using namespace std;
static GLint axis = 2;
static GLfloat theta[3] = { 0.0, 0.0, 0.0 };
int window_1, window_2, window_3;
static int view_state = 0, light_state = 0;
int spin;
	GLfloat xRotated, yRotated, zRotated;
	GLfloat xScale = 1, yScale = 1, zScale = 1;
	GLfloat xTranslate = 0, yTranslate = 0, zTranslate = 02;	
int shape;
class Renderer {
public:
  int mode;
  double azimouthio;

public:
  Renderer() : mode(1), azimouthio(-45.0) {}
  public:
  // Draw our world
void display_1(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    float m[16]; // identity
    glGetFloatv(GL_MODELVIEW_MATRIX, m);
    float angle = (M_PI / 180.0f) * float(azimouthio);
    if(mode == 1) { // cavalier
      m[2*4+0] = -cos(angle);
      m[2*4+1] = sin(angle);
    }
    if(mode == 2) { // cabinet
      m[2*4+0] = -cos(angle)/2.0f;
      m[2*4+1] = sin(angle)/2.0f;
    }
    glMultMatrixf(m);

    glColor3f(0.0f, 0.0f, 1.0f);
    drawCoordinateAxisZ();
    glColor3f(0.0f, 1.0f, 0.0f);
    drawCoordinateAxisY();
    glColor3f(1.0f, 0.0f, 0.0f);
    drawCoordinateAxisX();

    drawUnitCube();
}
void init(void)
{
glClearColor (0.0, 0.0, 0.0, 0.0); // When screen cleared, use black.
glShadeModel (GL_SMOOTH); // How the object color will be rendered smooth or flat
glEnable(GL_DEPTH_TEST); // Check depth when rendering
}
// This is called when the window has been resized.
void reshape_1 (int w, int h)
{
double aspect = double(w)/double(h);
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0*aspect, 2.0*aspect, -2.0, 2.0, -5.0, 5.0);
}

void drawCoordinateAxisZ() {
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f); // z-axis
    glVertex3f(0.0f, 0.0f, 2.0f);
    glEnd();
    glLineWidth(1);
    // z-axis tip
    glBegin(GL_TRIANGLES);
    glVertex3f( 0.0f, 0.0f, 2.0f);
    glVertex3f(-0.05f, 0.05f, 1.9f);
    glVertex3f( 0.05f, 0.05f, 1.9f);
    glVertex3f( 0.0f,  0.0f, 2.0f);
    glVertex3f( 0.05f, -0.05f, 1.9f);
    glVertex3f(-0.05f, -0.05f, 1.9f);
    glVertex3f( 0.0f,  0.0f, 2.0f);
    glVertex3f( 0.05f,  0.05f, 1.9f);
    glVertex3f( 0.05f, -0.05f, 1.9f);
    glVertex3f( 0.0f,  0.0f, 2.0f);
    glVertex3f(-0.05f, -0.05f, 1.9f);
    glVertex3f(-0.05f,  0.05f, 1.9f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f( 0.05f, -0.05f, 1.9f);
    glVertex3f( 0.05f,  0.05f, 1.9f);
    glVertex3f(-0.05f,  0.05f, 1.9f);
    glVertex3f(-0.05f, -0.05f, 1.9f);
    glEnd();
  }

  void drawCoordinateAxisX() {
      glPushMatrix();
      glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
      drawCoordinateAxisZ();
      glPopMatrix();
  }

  void drawCoordinateAxisY() {
      glPushMatrix();
      glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
      drawCoordinateAxisZ();
      glPopMatrix();
  }

  void drawUnitCube(void) {
    glColor3f(0.0f,1.0f,0.0f); //blue
    glBegin(GL_LINE_LOOP);
    glVertex3f(0.0f, 1.0f, 1.0f);
    glVertex3f(0.0f,0.0f, 1.0f);
    glVertex3f( 1.0f,0.0f, 1.0f);
    glVertex3f( 1.0f, 1.0f, 1.0f);
    glEnd();
    glColor3f(1.0f,0.5f,0.0f);    // Color Orange
    glBegin(GL_LINE_LOOP);
    glVertex3f( 1.0f, 1.0f,0.0f);
    glVertex3f( 1.0f,0.0f,0.0f);
    glVertex3f(0.0f,0.0f,0.0f);
    glVertex3f(0.0f, 1.0f,0.0f);
    glEnd();
    glColor3f(1.0f,0.0f,0.0f);    // Color Red
    glBegin(GL_LINE_LOOP);
    glVertex3f( 1.0f, 1.0f, 1.0f);
    glVertex3f( 1.0f,0.0f, 1.0f);
    glVertex3f( 1.0f,0.0f,0.0f);
    glVertex3f( 1.0f, 1.0f,0.0f);
    glEnd();
    glColor3f(1.0f,1.0f,0.0f);    // Color Yellow
    glBegin(GL_LINE_LOOP);
    glVertex3f(0.0f, 1.0f,0.0f);
    glVertex3f(0.0f,0.0f,0.0f);
    glVertex3f(0.0f,0.0f, 1.0f);
    glVertex3f(0.0f, 1.0f, 1.0f);
    glEnd();
    glColor3f(0.0f,0.0f,1.0f);    // Color Blue
    glBegin(GL_LINE_LOOP);
    glVertex3f( 1.0f, 1.0f,0.0f);
    glVertex3f(0.0f, 1.0f,0.0f);
    glVertex3f(0.0f, 1.0f, 1.0f);
    glVertex3f( 1.0f, 1.0f, 1.0f);
    glEnd();
    glColor3f(1.0f,0.0f,1.0f);    // Color Violet
    glBegin(GL_LINE_LOOP);
    glVertex3f( 1.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f,0.0f);
    glVertex3f( 1.0f, 0.0f,0.0f);
    glEnd();
  glFlush();
  }
};

// This creates the spinning of the cube.
static void TimeEvent(int te)
{
spin++;  // increase cube rotation by 1
if (spin > 360) spin = 0; // if over 360 degress, start back at zero.
glutSetWindow( window_1 );
glutPostRedisplay(); // Update screen with new rotation data

glutSetWindow( window_2 );
glutPostRedisplay(); // Update screen with new rotation data

glutSetWindow( window_3 );
glutPostRedisplay(); // Update screen with new rotation data

glutTimerFunc( 100, TimeEvent, 1); // Reset our timmer.
}

void init(void)
{
glClearColor (0.0, 0.0, 0.0, 0.0); // When screen cleared, use black.
glShadeModel (GL_SMOOTH); // How the object color will be rendered smooth or flat
glEnable(GL_DEPTH_TEST); // Check depth when rendering
}
static Renderer *renderer;

void colorcube ( )
{
renderer->drawUnitCube();
  return;
}
void display_2(void)
{
 glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glLoadIdentity ( );
  glRotatef ( theta[0], 1.0, 0.0, 0.0 );
  glRotatef ( theta[1], 0.0, 1.0, 0.0 );
  glRotatef ( theta[2], 0.0, 0.0, 1.0 );

  colorcube ( );
  glFlush ( );
  glutSwapBuffers ( );
  return;
}

void mouse ( int btn, int state, int x, int y )
{
  if ( btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
  {
    axis = axis + 1;
  }
  if ( btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN )
  {
    axis = axis + 1;
  }
  if ( btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN )
  {
    axis = axis + 1;
  }
  axis = axis % 3;
  return;
}

// This is called when the window has been resized.
void reshape_2 (int w, int h)
{
glViewport ( 0, 0, w, h );
  glMatrixMode ( GL_PROJECTION );
  glLoadIdentity ( );
  if ( w <= h )
  {
    glOrtho ( 
      -2.0, 2.0, 
      -2.0 * ( GLfloat ) h / ( GLfloat ) w, 2.0 * ( GLfloat ) h / ( GLfloat ) w, 
      -10.0, 10.0 );
  }
  else
  {
    glOrtho ( 
      -2.0 * ( GLfloat ) h / ( GLfloat ) w, 2.0 * ( GLfloat ) h / ( GLfloat ) w,  
      -2.0, 2.0, 
      -10.0, 10.0 );
  }
  glMatrixMode ( GL_MODELVIEW );
  return;
}

static void display_3(){
	  glMatrixMode(GL_MODELVIEW);
	    // clear the drawing buffer.
	    glClear(GL_COLOR_BUFFER_BIT);
	    glLoadIdentity();
	    glTranslatef(0.0,0.0,-10.5);

	    glPushMatrix();
glRotatef(xRotated,1.0,0.0,0.0); // rotation about Y axis
	    glRotatef(yRotated,0.0,1.0,0.0); // rotation about Z axis

	   glTranslatef(xTranslate, yTranslate, zTranslate);

	    glScalef(xScale, yScale, zScale);
		glRotatef(zRotated,0.0,0.0,1.0);
	glColor3f(0.0f,1.0f,0.0f);    // Color Blue
	glBegin(GL_LINE_LOOP);
	        glVertex3f( 1.0f, 1.0f,-1.0f);    // Top Right Of The Quad (Top)
	        glVertex3f(-1.0f, 1.0f,-1.0f);    // Top Left Of The Quad (Top)
	        glVertex3f(-1, 1, 1);    // Bottom Left Of The Quad (Top)
	        glVertex3f( 1.0f, 1.0f, 1.0f);    // Bottom Right Of The Quad (Top)
	    glEnd();
		glColor3f(1.0f,0.5f,0.0f);    // Color Orange
	    glBegin(GL_LINE_LOOP);
	        glVertex3f( 1.0f,-1.0f, 1.0f);    // Top Right Of The Quad (Bottom)
	        glVertex3f(-1.0f,-1.0f, 1.0f);    // Top Left Of The Quad (Bottom)
	        glVertex3f(-1.0f,-1.0f,-1.0f);    // Bottom Left Of The Quad (Bottom)
	        glVertex3f( 1.0f,-1.0f,-1.0f);    // Bottom Right Of The Quad (Bottom)
	    glEnd();
		glColor3f(1.0f,0.0f,0.0f);    // Color Red
	    glBegin(GL_LINE_LOOP);
	        glVertex3f( 1.0f, 1.0f, 1.0f);    // Top Right Of The Quad (Front)
	        glVertex3f(-1.0f, 1.0f, 1.0f);    // Top Left Of The Quad (Front)
	        glVertex3f(-1.0f,-1.0f, 1.0f);    // Bottom Left Of The Quad (Front)
	        glVertex3f( 1.0f,-1.0f, 1.0f);    // Bottom Right Of The Quad (Front)
	   glEnd();
	    glColor3f(1.0f,1.0f,0.0f);    // Color Yellow
	    glBegin(GL_LINE_LOOP);
	        glVertex3f( 1.0f,-1.0f,-1.0f);    // Top Right Of The Quad (Back)
	        glVertex3f(-1.0f,-1.0f,-1.0f);    // Top Left Of The Quad (Back)
	        glVertex3f(-1.0f, 1.0f,-1.0f);    // Bottom Left Of The Quad (Back)
	        glVertex3f( 1.0f, 1.0f,-1.0f);    // Bottom Right Of The Quad (Back)
	    glEnd();
		glColor3f(0.0f,0.0f,1.0f);    // Color Blue
	    glBegin(GL_LINE_LOOP);
	        glVertex3f(-1.0f, 1.0f, 1.0f);    // Top Right Of The Quad (Left)
	        glVertex3f(-1.0f, 1.0f,-1.0f);    // Top Left Of The Quad (Left)
	        glVertex3f(-1.0f,-1.0f,-1.0f);    // Bottom Left Of The Quad (Left)
	        glVertex3f(-1.0f,-1.0f, 1.0f);    // Bottom Right Of The Quad (Left)
	    glEnd();
		glColor3f(1.0f,0.0f,1.0f);    // Color Violet
	    glBegin(GL_LINE_LOOP);
	        glVertex3f( 1.0f, 1.0f,-1.0f);    // Top Right Of The Quad (Right)
	        glVertex3f( 1.0f, 1.0f, 1.0f);    // Top Left Of The Quad (Right)
	        glVertex3f( 1.0f,-1.0f, 1.0f);    // Bottom Left Of The Quad (Right)
	        glVertex3f( 1.0f,-1.0f,-1.0f);    // Bottom Right Of The Quad (Right)
	    glEnd();            // End Drawing The Cube
	    glFlush();
	    glutSwapBuffers ( );
	    return;
}
void reshape_3(int x, int y){
	if (x == 0 || y == 0) return;  //Nothing is visible then, so return
	    //Set a new projection matrix
	    glMatrixMode(GL_PROJECTION);
	    glLoadIdentity();
	    
	    gluPerspective(40.0,(GLdouble)x/(GLdouble)y,0.5,20.0);
	    glMatrixMode(GL_MODELVIEW);
	    glViewport(0,0,x,y);  //Use the whole window for rendering
	    return;
}

static void glutreshape_1(int w, int h) 
{
  renderer->reshape_1(w,h);
}

static void glutdisplay_1() 
{
  renderer->display_1();
  glutSwapBuffers();
  glutReportErrors(); 
}


// Read the keyboard
void keyboard (unsigned char key, int x, int y)
{
bool redraw = false;
  std::string modeStr;
  std::stringstream ss;
  switch(key) {
    case '1':	
      renderer->mode = 1;
      redraw = true;
      modeStr = string("cavalier");
      break;
    case '2':
      renderer->mode = 2;
      redraw = true;
      modeStr = string("cabinet");
      break;
    case '3':
      renderer->azimouthio += 2.0f;
      if(renderer->azimouthio > 360.0f) renderer->azimouthio = 0.0f;
      redraw = true;
	  ss << "azimouthio: " <<  renderer->azimouthio;
      modeStr = ss.str();
      break;
    case '0':
      renderer->azimouthio = -45.0f;
      glutReshapeFunc(glutreshape_1);
      redraw = true;
	  ss << "azimouthio: " <<  renderer->azimouthio;
      modeStr = ss.str();
      break;
}
if(redraw) {
      glutdisplay_1();
	  cout << modeStr << endl;
      glutSetWindowTitle(modeStr.c_str());
    }
}

void spinCube ( )
//    SPINCUBE adjusts the angle of rotation and redisplays the picture.
{
  theta[axis] = theta[axis] + 0.020;
  if ( 360.0 < theta[axis] ) 
  {
    theta[axis] = theta[axis] - 360.0;
  }
  glutPostRedisplay ( );
  return;
}
// Main program
int main(int argc, char** argv)
{
glutInit(&argc, argv);
glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
glutInitWindowSize (500, 500);
glutInitWindowPosition (100, 100);
glutTimerFunc( 10, TimeEvent, 1);

window_1 = glutCreateWindow ("press: 1-cavalier, 2-cabinet, 3-azimouthios");
glutDisplayFunc(glutdisplay_1);
glutReshapeFunc(glutreshape_1);
glutKeyboardFunc(keyboard); 
  renderer = new Renderer;
  renderer->init();

glutInitWindowPosition (150, 150);
window_2 = glutCreateWindow ("spinning cube");
glutDisplayFunc(display_2);
glutReshapeFunc(reshape_2); 
glutIdleFunc ( spinCube );
glutMouseFunc ( mouse );
  
glutInitWindowPosition (170,170);
window_3 = glutCreateWindow ("perspective view");
glutDisplayFunc(display_3);
glutReshapeFunc(reshape_3); 
glutMainLoop();
}

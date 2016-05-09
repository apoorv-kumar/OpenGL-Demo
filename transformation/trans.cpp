#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <vector>
#include <iostream>

using namespace std;
static float zoomFactor = 1.0; /* Global, if you want. Modified by user input. Initially 1.0 */

float w, h, tip = 0, turn = 0;

/* Function to translate a cube having bottom-left front face coordinates as (x,y,z) and width w to (Tx, Ty, Tz) */
/* Point vector is the definition of cube i.e. 8 vertex. t_Pt is translation vector. This function updates
coordinates values in Point vector. */

void trans_func(vector<vector<float> > &vertex, float t_x, float t_y, float t_z, vector<vector<float> > &vertex1)
{
   /* construct translate matrix. */
   /* Translate vertex. */
   int i;
   for(i = 0; i<8; i++)
   {
     vertex1[i][0] = vertex[i][0] + t_x;
     vertex1[i][1] = vertex[i][1] + t_y;
     vertex1[i][2] = vertex[i][2] + t_z;
   }

}

/* this function scales input vertex and updates values in vertex vector. */
void scale(vector<vector<float> > &vertex , float s_x, float s_y, float s_z, vector<vector<float> > &vertex1)
{
   int i=0;
   for(i=0; i<8; i++)
   {
      vertex1[i][0] = vertex[i][0] * s_x;
      vertex1[i][1] = vertex[i][1] * s_y;
      vertex1[i][2] = vertex[i][2] * s_z;
   }
}

/* shear function for xy. Input is sh_x, sh_y */
void shear_xy(vector<vector<float> > &vertex, float sh_x, float sh_y, vector<vector<float> > &vertex1)
{
   float i, x, y, z;
   for(i=0; i<8; i++)
   {
      x = vertex[i][0];
      y = vertex[i][1];
      z = vertex[i][2];

      vertex1[i][0] = vertex[i][0] + sh_x*z;
      vertex1[i][1] = vertex[i][1] + sh_y*z;
      vertex1[i][2] = vertex[i][2];
   }
}

/* shear function for xz. Input is sh_x, sh_z */
void shear_xz(vector<vector<float> > &vertex, float sh_x, float sh_z, vector<vector<float> > &vertex1)
{
   float i, x, y, z;
   for(i=0; i<8; i++)
   {
      x = vertex[i][0];
      y = vertex[i][1];
      z = vertex[i][2];

      vertex1[i][0] = vertex[i][0] + sh_x*y;
      vertex1[i][1] = vertex[i][1];
      vertex1[i][2] = vertex[i][2] + sh_z*y;
   }
}

/* shear function for yz. Input is sh_y, sh_z */
void shear_yz(vector<vector<float> > &vertex, float sh_y, float sh_z, vector<vector<float> > &vertex1)
{
   float i, x, y, z;
   for(i=0; i<8; i++)
   {
      x = vertex[i][0];
      y = vertex[i][1];
      z = vertex[i][2];

      vertex1[i][0] = vertex[i][0];
      vertex1[i][1] = vertex[i][1] + sh_y*x;
      vertex1[i][2] = vertex[i][2] + sh_z*x;
   }
}

/* Rotate vertex about x axis. Pass the angle and vertex values. */
void rotate_x(vector<vector<float> > &vertex, float angle, vector<vector<float> > &vertex1)
{
   float i, x, y, z;
   for(i = 0; i < 8; i++)
   {
      x = vertex[i][0];
      y = vertex[i][1];
      z = vertex[i][2];

      vertex1[i][0] = x;
      vertex1[i][1] = y*cos(angle) - z*sin(angle);
      vertex1[i][2] = y*sin(angle) + z*cos(angle);
   }
}

/* Rotate vertex about y axis. Pass the angle and vertex values. */
void rotate_y(vector<vector<float> > &vertex, float angle, vector<vector<float> > &vertex3)
{
   float i, x, y, z;
   for(i = 0; i < 8; i++)
   {
      x = vertex[i][0];
      y = vertex[i][1];
      z = vertex[i][2];
      vertex3[i][0] = x*cos(angle) + z*sin(angle);
      vertex3[i][1] = y;
      vertex3[i][2] = -x*sin(angle) + z*cos(angle);
   }

}

/* Rotate vertex about z axis. Pass the angle and vertex values. */
void rotate_z(vector<vector<float> > &vertex, float angle, vector<vector<float> > &vertex1)
{
   float i, x, y, z;
   for(i = 0; i < 8; i++)
   {
      x = vertex[i][0];
      y = vertex[i][1];
      z = vertex[i][2];
      vertex1[i][0] = x*cos(angle) - y*sin(angle);
      vertex1[i][1] = x*sin(angle) + y*cos(angle);
      vertex1[i][2] = z;
   }
}

void draw_cube(vector<vector<float> > &vertex, vector<float> &color_t)
{

  glBegin(GL_QUADS);

  /* front face. */
  glColor3f(color_t[0], color_t[1], color_t[2]);
//  glColor3f(0.547, 0.16, 0.06);
  glVertex3f(vertex[0][0], vertex[0][1], vertex[0][2]);
  glVertex3f(vertex[1][0], vertex[1][1], vertex[1][2]);
  glVertex3f(vertex[2][0], vertex[2][1], vertex[2][2]);
  glVertex3f(vertex[3][0], vertex[3][1], vertex[3][2]);

  /* right side face. */
  glColor3f(0.656, 0.2372, 0.2372);
  glVertex3f(vertex[1][0], vertex[1][1], vertex[1][2]);
  glVertex3f(vertex[2][0], vertex[2][1], vertex[2][2]);
  glColor3f(1,1,1);
  glVertex3f(vertex[6][0], vertex[6][1], vertex[6][2]);
  glVertex3f(vertex[5][0], vertex[5][1], vertex[5][2]);

  /* bottom face. */
  glColor3f(0.184, 0.309, 0.184);
  glVertex3f(vertex[5][0], vertex[5][1], vertex[5][2]);
  glVertex3f(vertex[6][0], vertex[6][1], vertex[6][2]);
  glVertex3f(vertex[7][0], vertex[7][1], vertex[7][2]);
//  glColor3f(1, 1, 1);
  glVertex3f(vertex[4][0], vertex[4][1], vertex[4][2]);


  /* top face. */
  glColor3f(0.656, 0.2372, 0.2372);
  glVertex3f(vertex[7][0], vertex[7][1], vertex[7][2]);
  glVertex3f(vertex[4][0], vertex[4][1], vertex[4][2]);
  glVertex3f(vertex[0][0], vertex[0][1], vertex[0][2]);
  glColor3f(1.0, 1.0, 1);
  glVertex3f(vertex[3][0], vertex[3][1], vertex[3][2]);


  /* top face */
  glColor3f(1, 1, 0);
  glVertex3f(vertex[3][0], vertex[3][1], vertex[3][2]);
  glVertex3f(vertex[2][0], vertex[2][1], vertex[2][2]);
  glVertex3f(vertex[6][0], vertex[6][1], vertex[6][2]);
  glColor3f(1, 0, 0);
  glVertex3f(vertex[7][0], vertex[7][1], vertex[7][2]);


  /* bottom face. */
  glColor3f(0, 1, 0);
  glVertex3f(vertex[0][0], vertex[0][1], vertex[0][2]);
  glVertex3f(vertex[1][0], vertex[1][1], vertex[1][2]);
  glVertex3f(vertex[5][0], vertex[5][1], vertex[5][2]);
  glColor3f(1, 1, 1);
  glVertex3f(vertex[4][0], vertex[4][1], vertex[4][2]);
  /* No more quads */
  glEnd();
}


/* Function called to update rendering */
void DisplayFunc(void)
{
  static float alpha = 0;
  static float position_offset = 0 ;

  /* Clear the buffer, clear the matrix */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glRotatef(tip , 1,0,0);
  glRotatef(turn, 0, 1, 0);
  //glRotatef (alpha, 0,1,0);

//  glTranslatef(0, 0, -10);

/* handle lighting here. */
//  glMaterialfv(GL_FRONT, GL_SPECULAR, cyan);

//  glRotatef(30, 1, 0, 0);
//   glRotatef(alpha, 0, 1, 0);

  /* call function to rotate, translate etc.*/

  float matrix[8][3] = { {0, 0, 0}, {0.5, 0, 0}, {0.5, 0.5, 0}, {0, 0.5, 0}, {0, 0, -0.5}, {0.5, 0, -0.5}, {0.5, 0.5, -0.5}, {0, 0.5, -0.5}};
  vector<vector<float> > vertex(8, vector<float >(2, 0));
  vector<vector<float> > vertex1(8, vector<float >(2, 0));
  vector<vector<float> > vertex2(8, vector<float >(2, 0));
  vector<float > color_t;
  for(int i=0; i<8; i++)
  {
    for(int j=0; j<3; j++)
    {
        vertex[i][j] = matrix[i][j];
    }
  }

//   glTranslatef(0, 0, -10);

   gluLookAt(1, 6, -3, 0, 0, -10, 0, 1, 0);
   /* left side roof.*/
   glPushMatrix();
   scale(vertex, 0.2, 2.5, 2, vertex1);
   rotate_z(vertex1, -0.8, vertex1);
   trans_func(vertex1, -1.8, -0.2, -10, vertex1);
   //gluLookAt(4, 5, -4, 0, 0, -10, 0, 1, 0);
   color_t.clear();
   color_t.push_back(0.547);
   color_t.push_back(0.16);
   color_t.push_back(0.06);
   draw_cube(vertex1, color_t);
   glPopMatrix();

   /* right side roof.*/
   glPushMatrix();
   scale(vertex, 0.2, 2.5, 2, vertex2);
   rotate_z(vertex2, 0.8, vertex2);
   trans_func(vertex2, 0, -0.2, -10, vertex2);
   draw_cube(vertex2, color_t);
   glPopMatrix();

   /*left side pillar.*/
   glPushMatrix();
   scale(vertex, 0.2, 2.2, 2, vertex2);
   trans_func(vertex2, -1.6, -1.2, -10, vertex2);
   draw_cube(vertex2, color_t);
   glPopMatrix();


   /* right side pillar.*/
   glPushMatrix();
   scale(vertex, 0.2, 2.2, 2, vertex2);
   trans_func(vertex2, -0.2, -1.2, -10, vertex2);
   draw_cube(vertex2, color_t);
   glPopMatrix();


   /* Base ground green colored. */
   glPushMatrix();
   scale(vertex, 10.5, 0.05, 30, vertex2);
   rotate_z(vertex2, 3.14, vertex2);
   trans_func(vertex2, 0.2, -1.4, -9, vertex2);
   draw_cube(vertex2, color_t);
   glPopMatrix();

   glPushMatrix();
   scale(vertex, 6.5, 0.05, 14, vertex2);
   rotate_z(vertex2, 3.14, vertex2);
   trans_func(vertex2, 4.5, -1.2, -9, vertex2);
   draw_cube(vertex2, color_t);
   glPopMatrix();

  /* road path.*/
   glPushMatrix();
   scale(vertex, 2.2, 14, 0.1, vertex2);
   rotate_x(vertex2, -1.57, vertex2);
   color_t[0] = 0.75294;
   color_t[1] = 0.75294;
   color_t[2] = 0.75294;
   trans_func(vertex2, 0.2, -1.4, -9, vertex2);
   draw_cube(vertex2, color_t);
   glPopMatrix();


   glPushMatrix();
   scale(vertex, 2.6, 2.2, 2, vertex2);
   //rotate_y(vertex2, -1.57, vertex2);
   trans_func(vertex2, -1.5, -1.2, -10, vertex2);
   color_t[0] = 1;
   color_t[1] = 1;
   color_t[2] = 0;
   draw_cube(vertex2, color_t);
   glPopMatrix();

   glPushMatrix();
   scale(vertex, 0.4, 0.4, 2, vertex2);
   //rotate_y(vertex2, -1.57, vertex2);
   trans_func(vertex2, -1.3, -0.5, -9.95, vertex2);
   color_t[0] = 1;
   color_t[1] = 0;
   color_t[2] = 0;
   draw_cube(vertex2, color_t);
   scale(vertex, 0.4, 0.4, 2, vertex2);
   trans_func(vertex2, -0.5, -0.5, -9.95, vertex2);
   draw_cube(vertex2, color_t);

   /*draw door.*/
   scale(vertex, 0.6, 1, 2, vertex2);
   trans_func(vertex2, -1, -1.15, -9.95, vertex2);
   color_t[0] = 0;
   color_t[1] = 0;
   color_t[2] = 1;
   draw_cube(vertex2, color_t);

   glPopMatrix();



   /* tree definition starts here.*/
   color_t[0] = 0.547;
   color_t[1] = 0.15;
   color_t[2] = 0.06;

   /*trunk definition starts here*/
   glPushMatrix();
   scale(vertex, 0.2, 1.5, 0.1, vertex2);
   trans_func(vertex2, 1.4, 0.2, -9, vertex2);
   draw_cube(vertex2, color_t);
   glPopMatrix();
   /*trunk definition ends here*/

   glPushMatrix();
   scale(vertex, 0.2, 1.5, 0.0, vertex2);
   rotate_z(vertex2, 0.5, vertex2);
   trans_func(vertex2, 1.8, 0.9, -9, vertex2);
   color_t[0] = 0.1843;
   color_t[1] = 0.309;
   color_t[2] = 0.184;
   draw_cube(vertex2, color_t);
   glPopMatrix();
   glPushMatrix();
   scale(vertex, 0.2, 1.5, 0.0, vertex2);
   rotate_z(vertex2, -0.5, vertex2);
   trans_func(vertex2, 1.1, 0.9, -9, vertex2);
   draw_cube(vertex2, color_t);

   scale(vertex, 0.15, 1.5, 0.0, vertex2);
   rotate_z(vertex2, -1.57, vertex2);
   trans_func(vertex2, 1.1, 1, -9, vertex2);
   draw_cube(vertex2, color_t);

   scale(vertex, 0.9, 0.5, 0.0, vertex2);
   trans_func(vertex2, 1.28, 1, -9, vertex2);
   draw_cube(vertex2, color_t);

   scale(vertex, 0.4, 0.2, 0.0, vertex2);
   trans_func(vertex2, 1.4, 1.2, -9, vertex2);
   draw_cube(vertex2, color_t);

   scale(vertex, 0.4, 0.3, 0.0, vertex2);
   //rotate_z(vertex2, -1.57, vertex2);
   trans_func(vertex2, 1.4, 1.3, -9, vertex2);
   draw_cube(vertex2, color_t);

   glPopMatrix();

/* tree definition complete. */

  /* character definition start. */
   glPushMatrix();
   scale(vertex, 0.5, 0.85, 0.001, vertex2);
   trans_func(vertex2, 0.7, 0.3, -9-position_offset, vertex2);
   color_t[0] = 0;
   color_t[1] = 0;
   color_t[2] = 0.47;
   draw_cube(vertex2, color_t);

   /* head */
   scale(vertex, 0.2, 0.2, 0.05, vertex2);
   rotate_x(vertex2, 0, vertex2);
   trans_func(vertex2, 0.78, 0.75, -9-position_offset, vertex2);
   color_t[0] = 1;
   color_t[1] = 0;
   color_t[2] = 0;
   draw_cube(vertex2, color_t);

   /* left leg*/
   scale(vertex, 0.12, 0.7, 0.05, vertex2);
   rotate_z(vertex2, -0.1, vertex2);
   //rotate_x(vertex2, -1.5, vertex2);
   trans_func(vertex2, 0.72, -0.06, -9-position_offset, vertex2);
   color_t[0] = 1;
   color_t[1] = 0.2;
   color_t[2] = 0;
   draw_cube(vertex2, color_t);

   /*right leg*/
   scale(vertex, 0.12, 0.7, 0.05, vertex2);
   rotate_z(vertex2, 0.1, vertex2);
   trans_func(vertex2, 0.85, -0.06, -9-position_offset, vertex2);
   color_t[0] = 1;
   color_t[1] = 0.2;
   color_t[2] = 0;
   draw_cube(vertex2, color_t);

   /*right hand*/
   scale(vertex, 0.12, 0.28, 0.05, vertex2);
   rotate_z(vertex2, 0.8, vertex2);
   trans_func(vertex2, 1.04, 0.56, -9-position_offset, vertex2);
   color_t[0] = 1;
   color_t[1] = 0.2;
   color_t[2] = 0;
   draw_cube(vertex2, color_t);

   scale(vertex, 0.12, 0.32, 0.05, vertex2);
   rotate_z(vertex2, -0.8, vertex2);
   trans_func(vertex2, 0.9, 0.46, -9-position_offset, vertex2);
   draw_cube(vertex2, color_t);
   /* right hand drawn*/

   /*left hand*/
   scale(vertex, 0.12, 0.68, 0.05, vertex2);
   rotate_z(vertex2, -0.15, vertex2);
   trans_func(vertex2, 0.6, 0.35, -9-position_offset, vertex2);
   color_t[0] = 1;
   color_t[1] = 0.2;
   color_t[2] = 0;
   draw_cube(vertex2, color_t);

   glPopMatrix();

float char2xoffset = .4;
float position_offset2 = position_offset/2;

  /* character2 definition start. */
   glPushMatrix();
   scale(vertex, 0.5, 0.85, 0.001, vertex2);
   trans_func(vertex2, 0.7+char2xoffset, 0.3, -9-position_offset2, vertex2);
   color_t[0] = 0;
   color_t[1] = 0;
   color_t[2] = 0.47;
   draw_cube(vertex2, color_t);

   /* head */
   scale(vertex, 0.2, 0.2, 0.05, vertex2);
   rotate_x(vertex2, 0, vertex2);
   trans_func(vertex2, 0.78+char2xoffset, 0.75, -9-position_offset2, vertex2);
   color_t[0] = 1;
   color_t[1] = 0;
   color_t[2] = 0;
   draw_cube(vertex2, color_t);

   /* left leg*/
   scale(vertex, 0.12, 0.7, 0.05, vertex2);
   rotate_z(vertex2, -0.1, vertex2);
   //rotate_x(vertex2, -1.5, vertex2);
   trans_func(vertex2, 0.72+char2xoffset, -0.06, -9-position_offset2, vertex2);
   color_t[0] = 1;
   color_t[1] = 0.2;
   color_t[2] = 0;
   draw_cube(vertex2, color_t);

   /*right leg*/
   scale(vertex, 0.12, 0.7, 0.05, vertex2);
   rotate_z(vertex2, 0.1, vertex2);
   trans_func(vertex2, 0.85+char2xoffset, -0.06, -9-position_offset2, vertex2);
   color_t[0] = 1;
   color_t[1] = 0.2;
   color_t[2] = 0;
   draw_cube(vertex2, color_t);

   /*right hand*/
   scale(vertex, 0.12, 0.28, 0.05, vertex2);
   rotate_z(vertex2, 0.8, vertex2);
   trans_func(vertex2, 1.04+char2xoffset, 0.56, -9-position_offset2, vertex2);
   color_t[0] = 1;
   color_t[1] = 0.2;
   color_t[2] = 0;
   draw_cube(vertex2, color_t);

   scale(vertex, 0.12, 0.32, 0.05, vertex2);
   rotate_z(vertex2, -0.8, vertex2);
   trans_func(vertex2, 0.9+char2xoffset, 0.46, -9-position_offset2, vertex2);
   draw_cube(vertex2, color_t);
   /* right hand drawn*/

   /*left hand*/
   scale(vertex, 0.12, 0.68, 0.05, vertex2);
   rotate_z(vertex2, -0.15, vertex2);
   trans_func(vertex2, 0.6+char2xoffset, 0.35, -9-position_offset2, vertex2);
   color_t[0] = 1;
   color_t[1] = 0.2;
   color_t[2] = 0;
   draw_cube(vertex2, color_t);

   glPopMatrix();



   /* set rotation speed here. */
   alpha = alpha + 0.1;

   position_offset += .01;

   if(position_offset > 8) position_offset = -2;

   /* End */
   glFlush();
   glutSwapBuffers();

  /* Update again and again */
  glutPostRedisplay();
}

/*
** Function called when the window is created or resized
*/
void ReshapeFunc(int width, int height)
{
  glMatrixMode(GL_PROJECTION);

  glLoadIdentity();
  gluPerspective(20, width / (float) height, 5, 15);
  glViewport(0, 0, width, height);

  glMatrixMode(GL_MODELVIEW);
  glutPostRedisplay();
}

/* Function called when a key is hit */
void KeyboardFunc(unsigned char key, int x, int y)
{
  int foo;

  foo = x + y; /* Has no effect: just to avoid a warning */
  if ('q' == key || 'Q' == key || 27 == key)
      exit(0);

}

void init1( void )
{

  glEnable(GL_DEPTH_TEST);              // so the renderer considers depth
}


void Turn(int key, int x, int y)
{
   switch (key)
  {
     case GLUT_KEY_RIGHT: turn += 2; break;
     case GLUT_KEY_LEFT : turn -= 2; break;
     case GLUT_KEY_UP : tip -= 2; break;
     case GLUT_KEY_DOWN : tip += 2; break;
  }



}

int main(int argc, char **argv)
{
  /* Creation of the window */
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(800, 600);
  glutCreateWindow("Scene made from transformed cubes");

  /* OpenGL settings */
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glEnable(GL_DEPTH_TEST);
  /* Declaration of the callbacks */
  glutDisplayFunc(&DisplayFunc);
  glutReshapeFunc(&ReshapeFunc);
  glutKeyboardFunc(&KeyboardFunc);
  glutSpecialFunc(Turn);

  init1();
  /* Loop */
  glutMainLoop();

  /* Never reached */
  return 0;
}



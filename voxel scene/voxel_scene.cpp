#include <iostream>
#include <GL/glut.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <list>
using namespace std;

vector< vector< vector<bool> > >  main_cube;


// THESE SET THE DIMENSIONS OF OBJECTS DRAWN IN THE SCENE
const int cube_size = 100;
static float a = 0;

const int floor_ht = 3;
const int well_height = 4;
const int xwell_center = 3*cube_size/4;
const int zwell_center = 3*cube_size/4;
const int xtree = cube_size/6;
const int ztree = 3*cube_size/4;
const int tree_radius = 8;
const int upper_tree_height = cube_size/1.5;
const int trunk_height = cube_size/4;

const int xhome = cube_size/7;
const int zhome = cube_size/7;
const int home_size_x = cube_size/2;
const int home_size_z = cube_size/3;
const int home_ht = cube_size/5;



const int wall_thickness = 3;


/* THIS FUNCTION CONTAINS THE DESIGN OF THE SCENE
IT TELLS WHETHER A POINT SHOULD BE PAINTED WITH A VOXEL
OR LEFT EMPTY

DRAWS:
1. A HOUSE
2. A TREE
3. A WELL


*/

bool is_point_valid( int x , int y , int z ) // pass spl_radius
{
//the trunk of tree
if(y > floor_ht && y <= trunk_height && x > xtree-2 && x < xtree+2 && z > ztree-2 && z < ztree+2) 
{
  return true;
}
//the upper tree
else if ( ( (upper_tree_height*upper_tree_height)*( (x-xtree)*(x-xtree) + (z-ztree)*(z-ztree) ) < tree_radius*tree_radius*(upper_tree_height-y + trunk_height)*(upper_tree_height-y + trunk_height)  )  &&  (y < trunk_height+ upper_tree_height&& y > trunk_height ) ) return true; 

// the ground
else if ( y < floor_ht && y >0 && !(x > xhome + 3*wall_thickness && x < xhome + 9*wall_thickness && z > zhome+home_size_z && y < floor_ht && y >1) ) return true; 

// the well
else if ( y > floor_ht && y < well_height+floor_ht && (x-xwell_center)*(x-xwell_center) + (z-zwell_center)*(z-zwell_center) > 16 && (x-xwell_center)*(x-xwell_center) + (z-zwell_center)*(z-zwell_center) < 36 ) return true; 

// lower part of house
else if ( (x > xhome && z > zhome && x < xhome+home_size_x && z < zhome+home_size_z && y < home_ht) && !(  x > xhome+wall_thickness && z > zhome +wall_thickness && x < xhome+home_size_x-wall_thickness && z < zhome+home_size_z-wall_thickness && y < home_ht-wall_thickness) && !(x > xhome + 4*wall_thickness && z > zhome + wall_thickness && x < xhome + 8*wall_thickness && z < zhome+home_size_z +wall_thickness && y < home_ht/2)  ) return true; 


else return false;




}



void init() // pass spr_radius and mainj_cube
{
    for( int i = 0 ; i < cube_size ; i++)
    {
        vector< vector<bool> > plane;
        main_cube.push_back(plane);
        for( int j = 0 ; j < cube_size ; j++)
        {
            vector< bool > row;
            main_cube[i].push_back(row);
            for( int k = 0 ; k < cube_size ; k++)
            {
                bool cell = false;
                main_cube[i][j].push_back(cell);
            }
        }
    }

}


void fill_pattern() // pass main cube and center
{
    for( int i = 0 ; i < cube_size ; i++)
        for( int j = 0 ; j < cube_size ; j++)
            for( int k = 0 ; k < cube_size ; k++)
            {
                main_cube[i][j][k] = is_point_valid(i , j , k);
            }

}



void draw_cube(float x, float y, float z, float w)
{

  glBegin(GL_QUADS);

  /* left side face. */
  glColor3f(1, 0, 0);
  glVertex3f(x, y, z);
  glVertex3f(x, y + w,  z);
  glVertex3f(x, y + w,  z - w);
  glVertex3f(x, y, z - w);

  /* right side face. */
  glColor3f(0.5, 0.5, 0);
  glVertex3f(x + w, y, z);
  glVertex3f(x + w, y + w,  z);
  glVertex3f(x + w, y + w,  z - w);
  glColor3f(0.9, 0.9, 0.9);
  glVertex3f(x + w, y, z - w);

  /* bottom face. */
  glColor3f(0, 0, 0);
  glVertex3f(x, y, z);
  glVertex3f(x, y, z - w);
  glVertex3f(x + w, y,  z - w);
  glVertex3f(x + w, y, z);

  /* top face. */
  glColor3f(0.0, 1.0, 0);
  glVertex3f(x, y + w, z);
  glVertex3f(x + w, y + w, z);
  glVertex3f(x + w, y + w, z - w);
//  glColor3f(0, 1, 1);
  glVertex3f(x, y + w, z - w);

  /* back face */
  glColor3f(0, 0, 0);
  glVertex3f(x, y, z - w);
  glColor3f(0, 1, 0);
  glVertex3f(x + w, y, z - w);
  glColor3f(1, 1, 0);
  glVertex3f(x + w,  y + w, z - w);
  glColor3f(1, 0, 0);
  glVertex3f(x, y + w, z - w);

  /* front face. */
  glColor3f(0, 0, 0.5);
  glVertex3f(x, y, z);
  glVertex3f(x + w, y, z);
  glVertex3f(x + w, y + w, z);
  glColor3f(1, 1, 1);
  glVertex3f(x, y + w, z);

  /* No more quads */
  glEnd();


}

void DisplayFunc(void)
{
    a -= 0.01;
  static float alpha = 0;
    static float look_at_z_delta = 0;
  /* Clear the buffer, clear the matrix */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  /* A step backward, then spin the cube */
  glTranslatef(0, -0, -3);
  gluLookAt(1,1, -3, xhome/float(cube_size), 0.5, zhome/float(cube_size), 0, 1, 0);

  /* rotate function calls. */
//glRotatef(30, 1, 0, 0);
  glRotatef(alpha, 0, 1, 0);

  /* Call draw_cube function here. */



    for( int i = 0 ; i < cube_size ; i++)
    {
        for( int j = 0 ; j < cube_size; j++)
        {
            for( int k = 0 ; k < cube_size ; k++)
            {
                if( main_cube[i][j][k] ) draw_cube(float(i)/cube_size , float(j)/cube_size , float(k)/cube_size , float(1)/cube_size );
            }
        }
    }





  /* Rotate a bit more */
  alpha = alpha + 1.5;

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
  gluPerspective(30-a , width / (float) height, 5, 15);
  glViewport(0, 0, width, height);

  glMatrixMode(GL_MODELVIEW);
  glutPostRedisplay();
}

/*
** Function called when a key is hit
*/
void KeyboardFunc(unsigned char key, int x, int y)
{
  int foo;

  foo = x + y; /* Has no effect: just to avoid a warning */
  if ('q' == key || 'Q' == key || 27 == key)
      exit(0);
}






int main(int argc, char **argv)
{


    init();
    fill_pattern();
  /* Creation of the window */
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(800, 800);
  glutCreateWindow("VOXEL SCENE");

  /* OpenGL settings */
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glEnable(GL_DEPTH_TEST);

  /* Declaration of the callbacks */
  glutDisplayFunc(&DisplayFunc);
  glutReshapeFunc(&ReshapeFunc);
  glutKeyboardFunc(&KeyboardFunc);

  /* Loop */
  glutMainLoop();

  /* Never reached */
  return 0;
}




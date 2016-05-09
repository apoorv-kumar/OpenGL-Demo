#include <stdlib.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#define MAXZ 8.0
#define MINZ -8.0
#define ZINC 0.4

using namespace std;


const bool auto_trigger = false;


static float solidZ = MAXZ;
static float transparentZ = MINZ;
static GLuint sphereList, cubeList;

float movingCubeY = 2.0;
int movingBlockId = 0;// 2- red , 1 - blue , 0- green

float z_distance = -0.0;
float x_distance = -0.0;
float y_distance = -0.0;
float rot_angle_x = 0;
float rot_angle_y = 15;
float rot_angle_z = 0;
float rot_angle_xz = 15;

//color of the three animated blocks
GLfloat mat_solid_red[] = { 1.0, 0.0, 0.0, 1.0 };
GLfloat mat_solid_blue[] = { 0.0, 0.0, 1.0, 1.0 };
GLfloat mat_solid_green[] = { 0.0, 1.0, 0.0, 1.0 };
GLfloat mat_solid_gray[] = { 0.2, 0.2, 0.2, 1.0 };
GLfloat mat_solid[] = { 1.0, 1.0, 0.2, 1.0 }; //yellow 


float cube_size = 0.25;

float move_distance = 2*cube_size;
const float green_cube_start_y = 3*cube_size;
const float blue_cube_start_y = green_cube_start_y+cube_size;
const float red_cube_start_y = blue_cube_start_y+cube_size;

float green_cube_current_y = green_cube_start_y;
float blue_cube_current_y = blue_cube_start_y;
float red_cube_current_y = red_cube_start_y;

static void
drawBox(GLfloat size, GLenum type = GL_QUADS , int gray_face_id=-1 , bool construction_block = false)
{
	static GLfloat n[6][3] =
	{
		{-1.0, 0.0, 0.0},
		{0.0, 1.0, 0.0},
		{1.0, 0.0, 0.0},
		{0.0, -1.0, 0.0},
		{0.0, 0.0, 1.0},
		{0.0, 0.0, -1.0}
	};
	static GLint faces[6][4] =
	{
		{0, 1, 2, 3},
		{3, 2, 6, 7},
		{7, 6, 5, 4},
		{4, 5, 1, 0},
		{5, 6, 2, 1},
		{7, 4, 0, 3}
	};
	GLfloat v[8][3];
	GLint i;
	
	v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
	v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
	v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
	v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
	v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
	v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;


	for (i = 5; i >= 0; i--) {
		//change color if face is inner one
		if(construction_block) // if it is one of the construction blocks
		{
		if(i == gray_face_id) {

			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_solid_gray);
			glBegin(type);
			glNormal3fv(&n[i][0]);
			glVertex3fv(&v[faces[i][0]][0]);
			glVertex3fv(&v[faces[i][1]][0]);
			glVertex3fv(&v[faces[i][2]][0]); 
			glVertex3fv(&v[faces[i][3]][0]);
			glEnd();

		}
		else
		{
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_solid);
			glBegin(type);
			glNormal3fv(&n[i][0]);
			glVertex3fv(&v[faces[i][0]][0]);
			glVertex3fv(&v[faces[i][1]][0]);
			glVertex3fv(&v[faces[i][2]][0]); 
			glVertex3fv(&v[faces[i][3]][0]);
			glEnd();
		}

		}
		else
		{
			glBegin(type);
			glNormal3fv(&n[i][0]);
			glVertex3fv(&v[faces[i][0]][0]);
			glVertex3fv(&v[faces[i][1]][0]);
			glVertex3fv(&v[faces[i][2]][0]); 
			glVertex3fv(&v[faces[i][3]][0]);
			glEnd();
		}
	}

}



static void init(void)
{
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 0.15 };
	GLfloat mat_shininess[] = { 100.0 };
	GLfloat position[] = { 0.5, 0.5, 1.0, 0.0 };
	
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}

void display(void)
{
	
	
	//SET PERSPECTIVE
	
	//glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(50.0, 0.0,0.0,15.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	/*gluLookAt(0.0, 0.0, 10.0,
		  0.0, 0.0, 0.0,
		  0.0, 0.0, 0.0);*/
	
	//\PERSPECTIVE
	

	GLfloat mat_zero[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat mat_emission[] = { 0.0, 0.3, 0.3, 0.6 };
	

	
	
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	
	//shift back
	glTranslatef(0.0f, -0.0f, z_distance);
	
	//draw 8 cubes that make the enclosure
	
	//cube 1
	glPushMatrix ();      glRotatef (rot_angle_xz, 1.0, 1.0, 0.0);glTranslatef(x_distance , y_distance , z_distance);
      glRotatef( rot_angle_y, 0.0, 1.0, 0.0);glRotatef( rot_angle_x, 1.0, 0.0, 0.0);glRotatef( rot_angle_z, 0.0, 0.0, 1.0);

	glTranslatef(0.0f, 0.0f, cube_size);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_zero);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_solid);
	drawBox(cube_size , GL_QUADS ,5 , true);
	glDepthMask (GL_TRUE);
	glDisable (GL_BLEND);
	glPopMatrix ();
	
	//cube 2	
	glPushMatrix ();      glRotatef (rot_angle_xz, 1.0, 1.0, 0.0);glTranslatef(x_distance , y_distance , z_distance);
      glRotatef( rot_angle_y, 0.0, 1.0, 0.0);glRotatef( rot_angle_x, 1.0, 0.0, 0.0);glRotatef( rot_angle_z, 0.0, 0.0, 1.0);

	glTranslatef(cube_size, 0.0f, cube_size);
      glMaterialfv(GL_FRONT, GL_EMISSION, mat_zero);
      glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_solid);
	drawBox(cube_size , GL_QUADS);
	glDepthMask (GL_TRUE);
	glDisable (GL_BLEND);
	glPopMatrix ();
	
	//cube 3	
	glPushMatrix ();      glRotatef (rot_angle_xz, 1.0, 1.0, 0.0);glTranslatef(x_distance , y_distance , z_distance);
      glRotatef( rot_angle_y, 0.0, 1.0, 0.0);glRotatef( rot_angle_x, 1.0, 0.0, 0.0);glRotatef( rot_angle_z, 0.0, 0.0, 1.0);

	glTranslatef(-cube_size, 0.0f, cube_size);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_zero);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_solid);
	drawBox(cube_size , GL_QUADS);
	glDepthMask (GL_TRUE);
	glDisable (GL_BLEND);
	glPopMatrix ();
	
	
	//cube 4
	glPushMatrix ();      glRotatef (rot_angle_xz, 1.0, 1.0, 0.0);glTranslatef(x_distance , y_distance , z_distance);
      glRotatef( rot_angle_y, 0.0, 1.0, 0.0);glRotatef( rot_angle_x, 1.0, 0.0, 0.0);glRotatef( rot_angle_z, 0.0, 0.0, 1.0);

	glTranslatef(-cube_size, 0.0f, 0.0f);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_zero);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_solid);
	drawBox(cube_size , GL_QUADS , 2 , true);
	glDepthMask (GL_TRUE);
	glDisable (GL_BLEND);
	glPopMatrix ();
	
	
	//cube 5	
	glPushMatrix ();      glRotatef (rot_angle_xz, 1.0, 1.0, 0.0);glTranslatef(x_distance , y_distance , z_distance);
      glRotatef( rot_angle_y, 0.0, 1.0, 0.0);glRotatef( rot_angle_x, 1.0, 0.0, 0.0);glRotatef( rot_angle_z, 0.0, 0.0, 1.0);

	glTranslatef(-cube_size, 0.0f, -cube_size);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_zero);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_solid);
	drawBox(cube_size , GL_QUADS);
	glDepthMask (GL_TRUE);
	glDisable (GL_BLEND);
	glPopMatrix ();
	
	
	//cube 6	
	glPushMatrix ();      glRotatef (rot_angle_xz, 1.0, 1.0, 0.0);glTranslatef(x_distance , y_distance , z_distance);
      glRotatef( rot_angle_y, 0.0, 1.0, 0.0);glRotatef( rot_angle_x, 1.0, 0.0, 0.0);glRotatef( rot_angle_z, 0.0, 0.0, 1.0);

	glTranslatef(0.0f, 0.0f, -cube_size);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_zero);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_solid);
	drawBox(cube_size , GL_QUADS , 4 , true);
	glDepthMask (GL_TRUE);
	glDisable (GL_BLEND);
	glPopMatrix ();
	
	
	//cube 7	
	glPushMatrix ();      glRotatef (rot_angle_xz, 1.0, 1.0, 0.0);glTranslatef(x_distance , y_distance , z_distance);
      glRotatef( rot_angle_y, 0.0, 1.0, 0.0);glRotatef( rot_angle_x, 1.0, 0.0, 0.0);glRotatef( rot_angle_z, 0.0, 0.0, 1.0);

	glTranslatef(cube_size, 0.0f, -cube_size);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_zero);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_solid);
	drawBox(cube_size , GL_QUADS);
	glDepthMask (GL_TRUE);
	glDisable (GL_BLEND);
	glPopMatrix ();
	
	//cube 8
	glPushMatrix ();      glRotatef (rot_angle_xz, 1.0, 1.0, 0.0);glTranslatef(x_distance , y_distance , z_distance);
      glRotatef( rot_angle_y, 0.0, 1.0, 0.0);glRotatef( rot_angle_x, 1.0, 0.0, 0.0);glRotatef( rot_angle_z, 0.0, 0.0, 1.0);

	glTranslatef(cube_size, 0.0f, 0.0f);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_zero);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_solid);
	drawBox(cube_size , GL_QUADS , 0 , true); 
	glDepthMask (GL_TRUE); 
	glDisable (GL_BLEND);
	glPopMatrix ();
	
	
	
	//cube 9 - the moving cube
	//can be red green or blue one
	if(true)//hack to make them move together//(movingBlockId == 0)//green one
{
	
	if(green_cube_current_y < green_cube_start_y-move_distance) 
	{
		
		if(auto_trigger)movingBlockId++;//auto trigger
	}
	else
	{

	  green_cube_current_y -= .001;
	}
	
}

if(true)//hack to make them move together //(movingBlockId ==1)//blue
{
	
	if(blue_cube_current_y < blue_cube_start_y-move_distance) 
	{
		if(auto_trigger)movingBlockId++;//auto trigger
	}
	else
	{
	  blue_cube_current_y -= .001;
	}
	
}

if(true)//hack to make them move together //(movingBlockId == 2)//red one
{
	
	if(red_cube_current_y < red_cube_start_y-move_distance) 
	{

		movingBlockId=-1;//don't move any block now
	}
	else
	{
	  red_cube_current_y -= .001;
	}
	
}

	//green cube
	glPushMatrix ();      glRotatef (rot_angle_xz, 1.0, 1.0, 0.0);glTranslatef(x_distance , y_distance , z_distance);
	glRotatef( rot_angle_y, 0.0, 1.0, 0.0);glRotatef( rot_angle_x, 1.0, 0.0, 0.0);glRotatef( rot_angle_z, 0.0, 0.0, 1.0);
	glTranslatef(0.0f,green_cube_current_y, 0.0f);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_zero);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_solid_green);
	drawBox(cube_size , GL_QUADS);
	glDepthMask (GL_TRUE);
	glDisable (GL_BLEND);
	glPopMatrix ();
	
	//blue cube
	glPushMatrix ();      glRotatef (rot_angle_xz, 1.0, 1.0, 0.0);glTranslatef(x_distance , y_distance , z_distance);
	glRotatef( rot_angle_y, 0.0, 1.0, 0.0);glRotatef( rot_angle_x, 1.0, 0.0, 0.0);glRotatef( rot_angle_z, 0.0, 0.0, 1.0);
	glTranslatef(0.0f,blue_cube_current_y, 0.0f);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_zero);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_solid_blue);
	drawBox(cube_size , GL_QUADS);
	glDepthMask (GL_TRUE);
	glDisable (GL_BLEND);
	glPopMatrix ();
	
	//red cube
	glPushMatrix ();      glRotatef (rot_angle_xz, 1.0, 1.0, 0.0);glTranslatef(x_distance , y_distance , z_distance);
	glRotatef( rot_angle_y, 0.0, 1.0, 0.0);glRotatef( rot_angle_x, 1.0, 0.0, 0.0);glRotatef( rot_angle_z, 0.0, 0.0, 1.0);
	glTranslatef(0.0f,red_cube_current_y, 0.0f);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_zero);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_solid_red);
	drawBox(cube_size , GL_QUADS);
	glDepthMask (GL_TRUE);
	glDisable (GL_BLEND);
	glPopMatrix ();



glFlush();
}
	


void reshape(int w, int h)
{	drawBox(cube_size , GL_QUADS);


	glViewport(0, 0, (GLint) w, (GLint) h);
	glMatrixMode(GL_PROJECTION);
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

void animate(void)
{
	if (solidZ <= MINZ || transparentZ >= MAXZ)
		glutIdleFunc(NULL);
	else {
		solidZ -= ZINC;
		transparentZ += ZINC;
		glutPostRedisplay();
	}
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
		case ' ':move_distance+= cube_size;break;
		//case 'f':cube_size/=2;break;
		//case 'c':cube_size *=2;break;
		case 'x':
			rot_angle_x -=15;
			if(rot_angle_x< 0) rot_angle_x += 360;
			;
		case 'z':
			rot_angle_z -=15;
			if(rot_angle_z< 0) rot_angle_z += 360;
			;
		case 'l':
			rot_angle_y -=15;
			if(rot_angle_y< 0) rot_angle_y += 360;
			;
			break;
		case 'r':
			rot_angle_y +=15;
			if(rot_angle_y> 360) rot_angle_y -= 360;
			break;
		case 'u':
			rot_angle_xz -=15;
			if(rot_angle_xz< 0) rot_angle_xz += 360;
			;
			break;
		case 'd':
			rot_angle_xz +=15;
			if(rot_angle_xz> 360) rot_angle_xz -= 360;
			break;
		case 27:
			exit(0);
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow(argv[0]);

	init();
	glutDisplayFunc(display); // Tell GLUT to use the method "display" for rendering
	glutIdleFunc(display); // Tell GLUT to use the method "display" as our idle method as well
	glutReshapeFunc(reshape); // Tell GLUT to use the method "reshape" for reshaping
	glutKeyboardFunc (keyboard);
	
	glutMainLoop();
	return 0;
}

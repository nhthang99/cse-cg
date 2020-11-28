#include <math.h>
#include <iostream>

#include "supportClass.h"
#include "Mesh.h"

#define PI 3.1415926

using namespace std;

// Screen size
int		screenWidth = 1200;
int		screenHeight = 600;

// Camera parameter
float camera_angle;
float camera_height;
float camera_dis;

float lookAt_X, lookAt_Y, lookAt_Z;

// Boolean feature
bool isView = false;
bool isFrame = false;
bool isLight = true;

Mesh	base;
Mesh 	shape1;
Mesh 	shape2;
Mesh 	shape3;
Mesh 	shape4;
Mesh	shape5;

// Base size
float fSizeXBase = 2;
float fSizeYBase = 0.25;
float fSizeZBase = 6;

void drawAxis()
{
	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(4, 0, 0);

	glVertex3f(0, 0, 0);
	glVertex3f(0, 4, 0);

	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 4);
	glEnd();
}

void drawBackground()
{

}

void drawBase()
{
	glPushMatrix();

	//glTranslated(0, 0, 0);
	//glRotatef(0, 0, 2, 0);

	// Dark violet material
	GLfloat ambient[] = { 0.0, 1.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 0.8, 0.5, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	base.SetupMaterial(ambient, diffuse, specular, shininess);

	if (isFrame)
		base.DrawWireframe();
	else
		base.DrawColor();

	glPopMatrix();
}

void drawShape1()
{
	glPushMatrix();

	//glTranslated(0, 0, 0);
	glRotatef(0, 0, 2, 0);

	// Blue material
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 0.2, 0.2, 1.0, 1.0 };
	GLfloat specular[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat shininess = 100.0;
	shape1.SetupMaterial(ambient, diffuse, specular, shininess);

	if (isFrame)
		shape1.DrawWireframe();
	else
		shape1.DrawColor();

	glPopMatrix();
}

void drawShape2()
{
	glPushMatrix();

	glTranslated(0, 10, 0);
	//glRotatef(0, 0, 1, 0);

	// Red material
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat shininess = 100.0;
	shape2.SetupMaterial(ambient, diffuse, specular, shininess);

	if (isFrame)
		shape2.DrawWireframe();
	else
		shape2.Draw();

	glPopMatrix();
}

void drawShape3()
{
	glPushMatrix();

	glTranslated(0, 10, 0);
	//glRotatef(0, 0, 1, 0);

	// Green material
	GLfloat diffuse[] = { 0.0, 1.0, 0.0, 1.0 };
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat shininess = 100.0;
	shape3.SetupMaterial(ambient, diffuse, specular, shininess);

	if (isFrame)
		shape3.DrawWireframe();
	else
		shape3.Draw();

	glPopMatrix();
}

void drawShape4()
{
	glPushMatrix();

	glTranslated(0, 10, 0);
	//glRotatef(0, 0, 1, 0);

	// Green material
	GLfloat diffuse[] = { 0.0, 1.0, 0.0, 1.0 };
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat shininess = 100.0;
	shape3.SetupMaterial(ambient, diffuse, specular, shininess);

	if (isFrame)
		shape4.DrawWireframe();
	else
		shape4.Draw();

	glPopMatrix();
}

void drawShape5()
{
	glPushMatrix();

	glTranslated(0, 10, 0);
	//glRotatef(0, 0, 1, 0);

	// Gold material
	GLfloat diffuse[] = { 1.0, 0.5, 0.5, 1.0 };
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	shape5.SetupMaterial(ambient, diffuse, specular, shininess);

	if (isFrame)
		shape5.DrawWireframe();
	else
		shape5.Draw();

	glPopMatrix();
}

void drawAllItems()
{
	drawAxis();
	drawBase();
	drawShape1();
	drawShape2();
	drawShape3();
	drawShape4();
	drawShape5();
}

void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	GLfloat light_position0[] = { 10.0, 10.0, 10.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);

	if (isLight)
	{
		glEnable(GL_LIGHT1);
		GLfloat diffuse1[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat specular1[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat ambient1[] = { 0.0, 0.0, 0.0, 1.0 };
		GLfloat position1[] = { -10.0, 10.0, -10.0, 0.0 };

		glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
		glLightfv(GL_LIGHT1, GL_AMBIENT, ambient1);
		glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);
		glLightfv(GL_LIGHT1, GL_POSITION, position1);
	}
	else
		glDisable(GL_LIGHT1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	float camera_X = camera_dis * sinf(camera_angle * PI / 180);
	float camera_Y = camera_height;
	float camera_Z = camera_dis * cosf(camera_angle * PI / 180);

	if (isView)
		gluLookAt(0, 10, 0, 0, 0, 0, 0, 0, -1);
	else if (camera_dis == 0)
		gluLookAt(camera_X, camera_Y, camera_Z, lookAt_X, lookAt_Y, lookAt_Z, sinf(camera_angle * PI / 180), 0, cosf(camera_angle * PI / 180));
	else
		gluLookAt(camera_X, camera_Y, camera_Z, lookAt_X, lookAt_Y, lookAt_Z, 0, 1, 0);

	glViewport(0, 0, screenWidth, screenHeight);

	// Clear the stencil buffers
	glClearStencil(0);
	// Clear depth
	glClearDepth(1.0f);
	// Draw
	drawAllItems();
	/* Don't update color or depth. */
	glDisable(GL_DEPTH_TEST);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	/* Draw 1 into the stencil buffer. */
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	//drawNen(1.0f);
	/* Re-enable update of color and depth. */
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glEnable(GL_DEPTH_TEST);
	/* Now, only render where stencil is set to 1. */
	glStencilFunc(GL_EQUAL, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	//Draw the cube, reflected vertically, at all PIxels where the stencil
	//buffer is 1
	glPushMatrix();
	glScalef(1, -1, 1);
	drawAllItems();
	glPopMatrix();
	glDisable(GL_STENCIL_TEST);
	// // Blend the floor onto the screen
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//drawNen(0.7f);
	glDisable(GL_BLEND);

	glFlush();
	glutSwapBuffers();
}

void myInit()
{
	camera_angle = -30;  // Góc quay camera xung quanh trục Oy
	camera_height = 5.5; // Chiều cao camera so với mặt phẳng xOz
	camera_dis = 6.5;	// Khoảng cách đến trục Oy

	lookAt_X = 0;
	lookAt_Y = 1;
	lookAt_Z = 0;

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);

	//glutTimerFunc(25, processTimer, 0);

	const float ar = (float)screenWidth / (float)screenHeight;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-ar, ar, -1.0, 1.0, 1.5, 50.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	glDepthFunc(GL_LEQUAL);
	//glEnable(GL_COLOR_MATERIAL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat lmodel_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	GLfloat light_ambient0[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse0[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular0[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular0);
}

void createItem()
{
	base.CreateCuboid(fSizeXBase, fSizeYBase, fSizeZBase);
	base.SetColor(0);
	base.CalculateFacesNorm();

	float fSizeX = 3, fSizeY = 0.2, fSizeZ = 0.8, fRadius = 1;
	int nSegment = 16;

	// Shape 1
	shape1.CreateShape1(fSizeX, fSizeY, fSizeZ, fRadius, nSegment);
	shape1.SetColor(0);
	shape1.CalculateFacesNorm();

	// Shape 2
	shape2.CreateShape2(fSizeX, fSizeY, fSizeZ, nSegment);
	shape2.SetColor(1);
	shape2.CalculateFacesNorm();

	// Shape 3
	fSizeX = 5, fSizeZ = 1; fRadius = 0.4;
	shape3.CreateShape3(fSizeX, fSizeY, fSizeZ, fRadius, nSegment);
	shape3.SetColor(2);
	shape3.CalculateFacesNorm();

	// Shape 4
	fSizeX = 4, fSizeZ = 2, fRadius = 0.4;
	shape4.CreateShape4(fSizeX, fSizeY, fSizeZ, fRadius, nSegment);
	shape4.SetColor(3);
	shape4.CalculateFacesNorm();

	// Shape 5
	shape5.CreateShape5(fSizeX, fSizeY, fSizeZ, nSegment);
	shape5.SetColor(4);
	shape5.CalculateFacesNorm();
}

void printInstruction()
{
	cout << "1, 2: Xoay can dao" << endl
		<< "W, w : Chuyen doi qua lai giua che do khung day va to mau" << endl
		<< "V, v : Chuyen doi qua lai giua hai che do nhin khac nhau" << endl
		<< "+ : Tang khoang cach camera" << endl
		<< "- : Giam khoang cach camera" << endl
		<< "up arrow : Tang chieu cao camera" << endl
		<< "down arrow : Giam chieu cao camera" << endl
		<< "< -: Quay camera theo chieu kim dong ho" << endl
		<< "-> : Quay camera nguoc chieu kim dong ho" << endl
		<< "D, d : Bat / tat nguon sang thu 2" << endl;
}

void mySpecialKeyboard(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		camera_height += 0.25;
		break;
	case GLUT_KEY_DOWN:
		camera_height -= 0.25;
		/*if (camera_height < 0)
			camera_height = 0;*/
		break;
	case GLUT_KEY_RIGHT:
		camera_angle += 1;
		break;
	case GLUT_KEY_LEFT:
		camera_angle -= 1;
		break;
	}
	glutPostRedisplay();
}

void myKeyboard(unsigned char key, int x, int y)
{

	switch (key)
	{
	/*case '1':
		base.rotateY += baseRotateStep;
		if (base.rotateY > 360)
			base.rotateY -= 360;
		break;
	case '2':
		base.rotateY -= baseRotateStep;
		if (base.rotateY < 0)
			base.rotateY += 360;
		break;*/
	case 'w':
	case 'W':
		isFrame = !isFrame;
		break;
	case 'v':
	case 'V':
		isView = !isView;
	case 'd':
	case 'D':
		isLight = !isLight;
		break;
	case '+':
		camera_dis += 0.25;
		break;
	case '-':
		camera_dis -= 0.25;
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv); //initialize the tool kit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //set the display mode
	glutInitWindowSize(screenWidth, screenHeight); //set window size
	glutInitWindowPosition(100, 100); //set window position on screen
	glutCreateWindow("Nguyen Huu Thang - 1713239"); //open the screen window

	printInstruction();

	createItem();
	myInit();

	glutDisplayFunc(myDisplay);
	glutSpecialFunc(mySpecialKeyboard);
	glutKeyboardFunc(myKeyboard);

	glutMainLoop();
	return 0;
}


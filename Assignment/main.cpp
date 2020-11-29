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
Mesh	chot1;
Mesh	chot2;
Mesh	chot3;
Mesh	chot4;

int nSegment = 32;
float distanceLeftXBase = 1.0;
float distanceRightXBase = 1.5;

// Base size
float fSizeXBase = 7.0;
float fSizeYBase = 0.25;
float fSizeZBase = 1.6;

// Shape 1 size
float fSizeXShape1 = fSizeXBase / 2.0 - distanceLeftXBase / 2.0;
float fSizeYShape1 = fSizeYBase * 1.5;
float fSizeZShape1 = 0.65;
float fRadiusShape1 = 0.9;

// Shape 2 size
float fSizeXShape2 = 3.5;
float fSizeYShape2 = fSizeYBase * 1.5;
float fSizeZShape2 = 0.6;

// Shape 3 size
float fSizeXShape3 = fSizeXBase - distanceLeftXBase * 2;
float fSizeYShape3 = fSizeYBase * 1.5;
float fSizeZShape3 = 1.0;
float fSizeX2Shape3 = fSizeXShape3 / 1.5;
float fRadiusShape3 = 0.4;

// Shape 4 size
float fSizeXShape4 = 4.0;
float fSizeYShape4 = fSizeYBase * 1.5;
float fSizeZShape4 = 2.4;
float fRadiusShape4 = 0.6;

// Shape 5 size
float fSizeXShape5 = 1.8;
float fSizeYShape5 = fSizeYBase * 1.5;
float fSizeZShape5 = 2.0;
float fRadiusShape5 = fSizeXShape5 / 3.2;

// Chot size
float fHeightChot = fSizeYBase * 6 + 0.2;
float fRadiusChot = 0.2;

void drawAxis()
{
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(4, 0, 0);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 4, 0);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 4);
	glEnd();
}

void drawLucGiac(float x, float y, float z, float R, float alpha)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_QUADS);
	glColor4f(0.3, 1.0, 1.0, alpha);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x + R * cos(-60 * PI / 180), y, z + R * sin(-60 * PI / 180));
	glVertex3f(x + R * cos(0), y, z + R * sin(0));
	glVertex3f(x + R * cos(60 * PI / 180), y, z + R * sin(60 * PI / 180));
	glVertex3f(x, y, z);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(77.0 / 255.0, 166.0 / 255.0, 210.0 / 255.0, alpha);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x + R * cos(60 * PI / 180), y, z + R * sin(60 * PI / 180));
	glVertex3f(x + R * cos(120 * PI / 180), y, z + R * sin(120 * PI / 180));
	glVertex3f(x + R * cos(180 * PI / 180), y, z + R * sin(180 * PI / 180));
	glVertex3f(x, y, z);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0, 1.0, 1.0, alpha);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x + R * cos(180 * PI / 180), y, z + R * sin(180 * PI / 180));
	glVertex3f(x + R * cos(240 * PI / 180), y, z + R * sin(240 * PI / 180));
	glVertex3f(x + R * cos(300 * PI / 180), y, z + R * sin(300 * PI / 180));
	glVertex3f(x, y, z);
	glEnd();
}

void drawNen(float alpha)
{
	float y = 0;
	glDisable(GL_LIGHTING);
	glColor3f(1.0f, 1.0f, 1.0f);
	float d = 0.7, R = d / cos(PI / 6);
	int i = 0;
	for (float x = -30; x < 30; x += R + R * cos(PI / 3))
	{
		float z = (i % 2 == 0) ? -20 : (-20 - d);
		for (; z < 20; z += 2 * d)
			drawLucGiac(x, y, z, R, alpha);
		i++;
	}
	glEnable(GL_LIGHTING);
}

void drawBase()
{
	glPushMatrix();

	glTranslated(0, fSizeYBase, 0);

	// Red material
	GLfloat diffuse[] = { 0.5, 0.0, 0.0, 1.0 };
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	base.SetupMaterial(ambient, diffuse, specular, shininess);

	if (isFrame)
		base.DrawWireframe();
	else
		base.Draw();

	glPopMatrix();
}

void drawShape1()
{
	glPushMatrix();

	float distXShape3 = fSizeXShape3 - fSizeX2Shape3;
	float halfXShape1 = (fSizeXShape1 * 2 + fRadiusShape1) / 2;

	float translateXright = fSizeXShape1 + fRadiusShape1;
	float translateXleft = distanceLeftXBase + distXShape3 / 2 + halfXShape1;

	glTranslated(translateXright - translateXleft, fSizeYBase * 2 + fSizeZShape1 + fSizeZShape3, -fSizeYShape1);
	glRotatef(90, 1, 0, 0);

	// Pink material
	GLfloat diffuse[] = { 1.0, 0.5, 0.5, 1.0 };
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	shape1.SetupMaterial(ambient, diffuse, specular, shininess);

	if (isFrame)
		shape1.DrawWireframe();
	else
		shape1.Draw();

	glPopMatrix();
}

void drawShape2()
{
	glPushMatrix();

	float distBaseY = 2 * fSizeYBase + fSizeZShape2;
	float fRadiusShape2 = 4 * fSizeZShape2 / 5;
	float fSizeX2Shape2 = 3 * fSizeXShape2 / 2;
	float fSizeZ3Shape2 = fSizeZShape2 / 2;

	float halfDistXShape3 = (fSizeXShape3 - fSizeX2Shape3) / 2;
	float halfXShape1 = (fSizeXShape1 * 2 + fRadiusShape1) / 2;

	float distX = halfXShape1 - (halfDistXShape3 + distanceLeftXBase) - fRadiusShape5 * 2;

	float lengthX = fRadiusShape2 + fSizeXShape2 + fSizeX2Shape2 + fSizeZ3Shape2;
	float centerX = lengthX / 2;

	float fRotateAngle = -15;
	float fTranslateAfterRotate = centerX * sin(-fRotateAngle / 180) + fRadiusShape2;

	glTranslated(fSizeXShape2 + fRadiusShape2 + distX, distBaseY + fSizeZShape3 + fSizeXShape5 + fTranslateAfterRotate, -fSizeYShape2);
	glRotatef(-90, 1, 0, 0);
	glRotatef(fRotateAngle, 0, 1, 0);

	// Pink material
	GLfloat diffuse[] = { 1.0, 0.5, 0.5, 1.0 };
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
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

	glTranslated(-(fSizeXShape3 + distanceLeftXBase), 2 * fSizeYBase, fSizeYShape3);
	glRotatef(180, 0, 1, 0);
	glRotatef(-90, 1, 0, 0);

	// Green material
	GLfloat diffuse[] = { 0.0, 1.0, 0.0, 1.0 };
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
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

	glTranslated(fSizeXBase - distanceRightXBase, 2 * fSizeYBase, fSizeYShape4);
	glRotatef(-90, 0, 0, 1);
	glRotatef(90, 1, 0, 0);

	// Green material
	GLfloat diffuse[] = { 0.0, 1.0, 0.0, 1.0 };
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	shape4.SetupMaterial(ambient, diffuse, specular, shininess);

	if (isFrame)
		shape4.DrawWireframe();
	else
		shape4.Draw();

	glPopMatrix();
}

void drawShape5()
{
	glPushMatrix();

	float halfDistXShape3 = (fSizeXShape3 - fSizeX2Shape3) / 2;
	float halfXShape1 = (fSizeXShape1 * 2 + fRadiusShape1) / 2;
	float Z = halfXShape1 - (halfDistXShape3 + distanceLeftXBase);

	glTranslated(-fRadiusShape5 + Z, fSizeYBase * 2 + fRadiusShape5 + fSizeZShape3, fSizeYShape5);
	glRotatef(-90, 0, 0, 1);
	glRotatef(-90, 1, 0, 0);

	// Gold material
	GLfloat diffuse[] = { 0.780392, 0.568627, 0.113725, 1.0 };
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

void drawChot1()
{
	glPushMatrix();

	float halfDistXShape3 = (fSizeXShape3 - fSizeX2Shape3) / 2;
	float distZ = 1.5 * fSizeZShape3;

	glTranslated(-(halfDistXShape3 + distanceLeftXBase), 2 * fSizeYBase + distZ, 0);
	glRotatef(-90, 1, 0, 0);

	// Gold material
	GLfloat diffuse[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	chot1.SetupMaterial(ambient, diffuse, specular, shininess);

	if (isFrame)
		chot1.DrawWireframe();
	else
		chot1.Draw();

	glPopMatrix();
}

void drawChot2()
{
	glPushMatrix();

	float halfDistXShape3 = (fSizeXShape3 - fSizeX2Shape3) / 2;
	float halfXShape1 = (fSizeXShape1 * 2 + fRadiusShape1) / 2;
	float Z = halfXShape1 - (halfDistXShape3 + distanceLeftXBase);

	glTranslated(Z - fRadiusShape5, 2 * fSizeYBase + fSizeZShape3 + fRadiusShape5, 0);
	glRotatef(-90, 1, 0, 0);

	// Gold material
	GLfloat diffuse[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	chot2.SetupMaterial(ambient, diffuse, specular, shininess);

	if (isFrame)
		chot2.DrawWireframe();
	else
		chot2.Draw();

	glPopMatrix();
}

void drawChot3()
{
	glPushMatrix();

	float halfDistXShape3 = (fSizeXShape3 - fSizeX2Shape3) / 2;
	float halfXShape1 = (fSizeXShape1 * 2 + fRadiusShape1) / 2;
	float Z = halfXShape1 - (halfDistXShape3 + distanceLeftXBase);

	glTranslated(Z - fRadiusShape5, 2 * fSizeYBase + fSizeZShape3 + fRadiusShape5 + fSizeXShape5, 0);
	glRotatef(-90, 1, 0, 0);

	// Gold material
	GLfloat diffuse[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	chot3.SetupMaterial(ambient, diffuse, specular, shininess);

	if (isFrame)
		chot3.DrawWireframe();
	else
		chot3.Draw();

	glPopMatrix();
}

void drawChot4()
{
	glPushMatrix();

	float fSizeX2 = fSizeXShape4 / 1.5;
	float fHeightX = fSizeX2 + fSizeX2 / 2;

	float fSizeZ2 = fSizeZShape4 / 1.6;
	float distZ = (fSizeZShape4 - fSizeZ2) / 7;
	float fZ = fSizeZ2 + 6 * distZ;

	glTranslated((fSizeXBase - distanceRightXBase) - fZ, 2 * fSizeYBase + fHeightX, 0);
	glRotatef(-90, 1, 0, 0);

	// Gold material
	GLfloat diffuse[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	chot4.SetupMaterial(ambient, diffuse, specular, shininess);

	if (isFrame)
		chot4.DrawWireframe();
	else
		chot4.Draw();

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
	drawChot1();
	drawChot2();
	drawChot3();
	drawChot4();
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
	drawNen(1.0f);

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

	drawNen(0.7f);
	glDisable(GL_BLEND);

	glFlush();
	glutSwapBuffers();
}

void myInit()
{
	camera_angle = -10.0;  // Góc quay camera xung quanh trục Oy
	camera_height = 6.0; // Chiều cao camera so với mặt phẳng xOz
	camera_dis = 15.0;	// Khoảng cách đến trục Oy

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
	// Base
	base.CreateCuboid(fSizeXBase, fSizeYBase, fSizeZBase);
	base.SetColor(7);
	base.CalculateFacesNorm();

	// Shape 1
	shape1.CreateShape1(fSizeXShape1, fSizeYShape1, fSizeZShape1, fRadiusShape1, nSegment);
	shape1.SetColor(1);
	shape1.CalculateFacesNorm();

	// Shape 2
	shape2.CreateShape2(fSizeXShape2, fSizeYShape2, fSizeZShape2, nSegment);
	shape2.SetColor(2);
	shape2.CalculateFacesNorm();

	// Shape 3
	shape3.CreateShape3(fSizeXShape3, fSizeYShape3, fSizeZShape3, fSizeX2Shape3, fRadiusShape3, nSegment);
	shape3.SetColor(3);
	shape3.CalculateFacesNorm();

	// Shape 4
	shape4.CreateShape4(fSizeXShape4, fSizeYShape4, fSizeZShape4, fRadiusShape4, nSegment);
	shape4.SetColor(4);
	shape4.CalculateFacesNorm();

	// Shape 5
	shape5.CreateShape5(fSizeXShape5, fSizeYShape5, fSizeZShape5, fRadiusShape5, nSegment);
	shape5.SetColor(5);
	shape5.CalculateFacesNorm();

	// Chot 1
	chot1.CreateCylinder(nSegment, fHeightChot, fRadiusChot);
	chot1.SetColor(6);
	chot1.CalculateFacesNorm();

	// Chot 2
	chot2.CreateCylinder(nSegment, fHeightChot, fRadiusChot);
	chot2.SetColor(7);
	chot2.CalculateFacesNorm();

	// Chot 3
	chot3.CreateCylinder(nSegment, fHeightChot, fRadiusChot);
	chot3.SetColor(8);
	chot3.CalculateFacesNorm();

	// Chot 4
	chot4.CreateCylinder(nSegment, fHeightChot, fRadiusChot);
	chot4.SetColor(9);
	chot4.CalculateFacesNorm();
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
		if (camera_height < 0)
			camera_height = 0;
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


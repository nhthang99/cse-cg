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
float fRadiusShape3 = 0.45;

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

// Chot 2 translation
float fSizeX2 = fSizeXShape4 / 1.5;
float fHeightX = fSizeX2 + fSizeX2 / 2;

float fSizeZ2 = fSizeZShape4 / 1.6;
float distZ = (fSizeZShape4 - fSizeZ2) / 7;
float fZ = fSizeZ2 + 6 * distZ;
float fXTranslateChot2 = (fSizeXBase - distanceRightXBase) - fZ;

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

void makeBackground(float fSizeX, float fSizeZ, float fRadius, float fSizeY=0, float alpha=0.7) {
	int mode = GL_QUADS;
	if (isFrame) {
		mode = GL_LINE_LOOP;
	}
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glBegin(mode);
		glColor4f(0.6f, 0.6f, 0.6f, alpha);
		glNormal3f(0.0f, 1.0f, 0.0f);

		glVertex3f(fSizeX + fRadius, fSizeY, fSizeZ + 2 * fRadius / 3);
		glVertex3f(fSizeX + fRadius, fSizeY, fSizeZ + fRadius / 3);
		glVertex3f(fSizeX + fRadius / 2, fSizeY, fSizeZ + fRadius / 2);
		glVertex3f(fSizeX + 1.8 * fRadius / 3, fSizeY, fSizeZ + 2.4 * fRadius / 3);
	glEnd();

	glBegin(mode);
		glColor4f(0.6f, 0.6f, 0.6f, alpha);
		glNormal3f(0.0f, 1.0f, 0.0f);

		glVertex3f(fSizeX + fRadius, fSizeY, fSizeZ + 2 * fRadius / 3);
		glVertex3f(fSizeX + fRadius, fSizeY, fSizeZ + fRadius / 3);
		glVertex3f(fSizeX + fRadius / 2, fSizeY, fSizeZ + fRadius / 2);
		glVertex3f(fSizeX + 1.8 * fRadius / 3, fSizeY, fSizeZ + 2.4 * fRadius / 3);
	glEnd();

	glBegin(mode);
		glColor4f(0.6f, 0.6f, 0.6f, alpha);
		glNormal3f(0.0f, 1.0f, 0.0f);

		glVertex3f(fSizeX + fRadius / 2, fSizeY, fSizeZ + fRadius / 2);
		glVertex3f(fSizeX + 2 * fRadius / 3, fSizeY, fSizeZ);
		glVertex3f(fSizeX + fRadius / 3, fSizeY, fSizeZ);
		glVertex3f(fSizeX + 0.6 * fRadius / 3, fSizeY, fSizeZ + 1.2 * fRadius / 3);
	glEnd();

	glBegin(mode);
		glColor4f(0.6f, 0.6f, 0.6f, alpha);
		glNormal3f(0.0f, 1.0f, 0.0f);

		glVertex3f(fSizeX, fSizeY, fSizeZ + fRadius / 3);
		glVertex3f(fSizeX + 0.6 * fRadius / 3, fSizeY, fSizeZ + 1.2 * fRadius / 3);
		glVertex3f(fSizeX + 0.3 * fRadius / 3, fSizeY, fSizeZ + 2.1 * fRadius / 3);
		glVertex3f(fSizeX, fSizeY, fSizeZ + 2 * fRadius / 3);
	glEnd();

	glBegin(mode);
		glColor4f(0.6f, 0.6f, 0.6f, alpha);
		glNormal3f(0.0f, 1.0f, 0.0f);

		glVertex3f(fSizeX + 0.3 * fRadius / 3, fSizeY, fSizeZ + 2.1 * fRadius / 3);
		glVertex3f(fSizeX + 0.6 * fRadius / 3, fSizeY, fSizeZ + 1.2 * fRadius / 3);
		glVertex3f(fSizeX, fSizeY, fSizeZ + fRadius / 3);
		glVertex3f(fSizeX, fSizeY, fSizeZ + 2 * fRadius / 3);
	glEnd();

	glBegin(mode);
		glColor4f(0.6f, 0.6f, 0.6f, alpha);
		glNormal3f(0.0f, 1.0f, 0.0f);

		glVertex3f(fSizeX + 2 * fRadius / 3, fSizeY, fSizeZ + fRadius);
		glVertex3f(fSizeX + 1.8 * fRadius / 3, fSizeY, fSizeZ + 2.4 * fRadius / 3);
		glVertex3f(fSizeX + 0.9 * fRadius / 3, fSizeY, fSizeZ + 2.7 * fRadius / 3);
		glVertex3f(fSizeX + fRadius / 3, fSizeY, fSizeZ + fRadius);
	glEnd();

	glBegin(mode);
		glColor4f(0.6f, 0.6f, 0.6f, alpha);
		glNormal3f(0.0f, 1.0f, 0.0f);

		glVertex3f(fSizeX + 0.9 * fRadius / 3, fSizeY, fSizeZ + 2.7 * fRadius / 3);
		glVertex3f(fSizeX + 0.75 * fRadius / 3, fSizeY, fSizeZ + 2.25 * fRadius / 3);
		glVertex3f(fSizeX + 0.3 * fRadius / 3, fSizeY, fSizeZ + 2.1 * fRadius / 3);
		glVertex3f(fSizeX, fSizeY, fSizeZ + fRadius);
	glEnd();

}

void drawSmallPart(int fRadius)
{
	for (int fX = 0; fX < 2; fX += fRadius) {
		for (int fZ = 0; fZ < 2; fZ += fRadius) {
			glTranslatef(-fRadius / 2, 0, -fRadius / 2);
			glRotatef((fX % 2) * 180 + (fZ % 2) * 90, 0, 1, 0);
			glTranslatef(fRadius / 2, 0, fRadius / 2);
			makeBackground(fZ / 2, fX / 2, fRadius, 0);
			//makeBackground(fZ / 2, fX / 2, fRadius, -0.01);
		}
	}
}

void drawBackground(float alpha, float fSizeY=-0.005, int fRadius=1) {
	glDisable(GL_LIGHTING);
	glColor3f(1.0f, 1.0f, 1.0f);

	/*glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glBegin(GL_QUADS);
	glColor4f(1.0, 1.0, 1.0, alpha);
	glNormal3f(0.0f, 1.0f, 0.0f);

	glVertex3f(-200, fSizeY, -200);
	glVertex3f(-200, fSizeY, 200);
	glVertex3f(200, fSizeY, 200);
	glVertex3f(200, fSizeY, -200);

	glEnd();*/

	for (int idx_i = 0; idx_i < 3; idx_i++) {
		glTranslatef(0, 0, 20 * idx_i);
		for (int idx_k = -10; idx_k < 10; idx_k++) {
			glTranslatef(0, 0, 2 * idx_k);
			for (int idx_j = -5; idx_j < 12; idx_j++) {
				glTranslatef(2 * idx_j, 0, 0);
				drawSmallPart(fRadius);
			}
		}
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
	float fRadiusShape2 = 7 * fSizeZShape2 / 8;
	float fSizeX2Shape2 = 3 * fSizeXShape2 / 2;
	float fSizeZ3Shape2 = fSizeZShape2 / 2;

	float halfDistXShape3 = (fSizeXShape3 - fSizeX2Shape3) / 2;
	float halfXShape1 = (fSizeXShape1 * 2 + fRadiusShape1) / 2;

	float distX = halfXShape1 - (halfDistXShape3 + distanceLeftXBase) - fRadiusShape5 * 2;

	float lengthX = fRadiusShape2 + fSizeXShape2 + fSizeX2Shape2 + fSizeZ3Shape2 * 2;
	float centerX = lengthX / 2;

	float fRotateAngle = -15;
	float fTranslateAfterRotate = centerX * sin(-fRotateAngle / 180) + fRadiusShape2;

	glTranslated(fSizeXShape2 + fRadiusShape2 + distX, distBaseY + fSizeZShape3 + fSizeXShape5 + fTranslateAfterRotate, -fSizeYShape2);
	glRotatef(-90, 1, 0, 0);
	glRotatef(fRotateAngle, 0, 1, 0);

	//glTranslatef(-distX - centerX + fXTranslateChot2, 0, 0);
	glRotatef(chot2.rotateY, 0, 1, 0);
	//glTranslatef(-(-distX - centerX + fXTranslateChot2), 0, 0);

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

	// Black material
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

	glTranslated(fXTranslateChot2, 2 * fSizeYBase + fHeightX, 0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(chot2.rotateY, 0, 1, 0);

	// Black material
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

	// Black material
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

	float halfDistXShape3 = (fSizeXShape3 - fSizeX2Shape3) / 2;
	float halfXShape1 = (fSizeXShape1 * 2 + fRadiusShape1) / 2;
	float Z = halfXShape1 - (halfDistXShape3 + distanceLeftXBase);

	glTranslated(Z - fRadiusShape5, 2 * fSizeYBase + fSizeZShape3 + fRadiusShape5, 0);
	glRotatef(-90, 1, 0, 0);

	// Black material
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
	//drawAxis();
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
	// Clear parameter
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	GLfloat light_position0[] = { 10.0, 10.0, 10.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);

	// Turn on/off light mode
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

	float camera_X = camera_dis * sinf(camera_angle * PI / 180); // camera respect to X-dimentional
	float camera_Y = camera_height; // camera respect to Y-dimentional
	float camera_Z = camera_dis * cosf(camera_angle * PI / 180); // // camera respect to Z-dimentional

	// Change view mode
	if (isView) {
		gluLookAt(0, 1, 15, lookAt_X, lookAt_Y, lookAt_Z, 0, 1, 1);
	}
	else if (camera_dis == 0)
		gluLookAt(camera_X, camera_Y, camera_Z, lookAt_X, lookAt_Y, lookAt_Z, sin(camera_angle * PI / 180), 0, cos(camera_angle * PI / 180));
	else
		gluLookAt(camera_X, camera_Y, camera_Z, lookAt_X, lookAt_Y, lookAt_Z, 0, 1, 0);

	// Setup view port
	glViewport(0, 0, screenWidth, screenHeight);

	// Clear the stencil buffers
	glClearStencil(0);
	// Clear depth
	glClearDepth(1.0f);

	// Draw all items
	drawAllItems();

	// No update color and depth
	glDisable(GL_DEPTH_TEST);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	/* Draw 1 into the stencil buffer. */
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	// Draw background
	drawBackground(1.0f);

	// Update of color and depth
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glEnable(GL_DEPTH_TEST);
	
	// Only render where stencil is set to 1
	glStencilFunc(GL_EQUAL, 1, 2);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

	// Draw the cube, reflected vertically, at all pixels where the stencil
	glPushMatrix();
	glScalef(1, -1, 1);
	drawAllItems();
	glPopMatrix();
	glDisable(GL_STENCIL_TEST);
	// Blend the floor onto the screen
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Draw reflected background
	drawBackground(0.7f);

	glDisable(GL_BLEND);

	glFlush();
	glutSwapBuffers();
}

void myInit()
{
	isLight = true;

	camera_angle = -10.0;  // Góc quay camera xung quanh trục Oy
	camera_height = 6.0; // Chiều cao camera so với mặt phẳng xOz
	camera_dis = 15.0;	// Khoảng cách đến trục Oy

	// Look parameter
	lookAt_X = 0;
	lookAt_Y = 1;
	lookAt_Z = 0;

	// Clear color
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);

	const float ar = (float)screenWidth / (float)screenHeight;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-ar, ar, -1.0, 1.0, 1.5, 50.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	glDepthFunc(GL_LEQUAL);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// Light model
	GLfloat lmodel_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	// Light parameter
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
		break;
	case GLUT_KEY_LEFT:
		camera_angle += 2;
		break;
	case GLUT_KEY_RIGHT:
		camera_angle -= 2;
		break;
	}
	glutPostRedisplay();
}

void myKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1':
		chot2.rotateY -= 1;
		break;
	case '2':
		chot2.rotateY += 1;
		break;
	case 'w':
	case 'W':
		isFrame = !isFrame;
		break;
	case 'v':
	case 'V':
		isView = !isView;
		if (isView)
		{
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(-16, 16, -8, 8, -1000, 1000);
			break;
		}
		else
		{
			myInit();
			break;
		}
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


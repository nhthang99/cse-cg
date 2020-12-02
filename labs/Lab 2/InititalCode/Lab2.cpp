// Bai3.cpp : Defines the entry point for the console application.
//

#include <math.h>
#include <iostream>
#include "supportClass.h"
#include "Mesh.h"

using namespace std;

int		screenWidth = 600;
int		screenHeight= 300;

Mesh	tetrahedron;
Mesh	cube;
Mesh	cuboid;
Mesh 	cylinder;
Mesh 	shape1;
Mesh 	shape2;
Mesh 	shape3;
Mesh 	shape4;

int		nChoice = 1;

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
void myDisplay()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(4.5, 4, 2, 0, 0, 0, 0, 1, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glViewport(0, 0, screenWidth/2, screenHeight);
	
	drawAxis();

	glColor3f(0, 0, 0);
	if(nChoice == 1)
		tetrahedron.DrawWireframe();
	else if(nChoice == 2)
		cube.DrawWireframe();
	else if(nChoice == 3)
		cuboid.DrawWireframe();
	else if(nChoice == 4)
		cylinder.DrawWireframe();
	else if(nChoice == 5)
		shape1.DrawWireframe();
	else if(nChoice == 6)
		shape2.DrawWireframe();
	else if(nChoice == 7)
		shape3.DrawWireframe();
	else if(nChoice == 8)
		shape4.DrawWireframe();

	glViewport(screenWidth/2, 0, screenWidth/2, screenHeight);

	drawAxis();
	if(nChoice == 1)
		tetrahedron.DrawColor();
	else if(nChoice == 2)
		cube.DrawColor();
	else if (nChoice == 3)
		cuboid.DrawColor();
	else if (nChoice == 4)
		cylinder.DrawColor();
	else if (nChoice == 5)
		shape1.DrawColor();
	else if (nChoice == 6)
		shape2.DrawColor();
	else if (nChoice == 7)
		shape3.DrawColor();
	else if (nChoice == 8)
		shape4.DrawColor();

	glFlush();
    glutSwapBuffers();
}

void myInit()
{
	float	fHalfSize = 4;

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-fHalfSize, fHalfSize, -fHalfSize, fHalfSize, -1000, 1000);
}

int main(int argc, char* argv[])
{
	cout << "1. Tetrahedron" << endl;
	cout << "2. Cube" << endl;
	cout << "3. Cuboid" << endl;
	cout << "4. Cylinder" << endl;
	cout << "5. Shape1" << endl;
	cout << "6. Shape2" << endl;
	cout << "7. Shape3" << endl;
	cout << "8. Shape4" << endl;
	cout << "Input the choice: " << endl;
	cin  >> nChoice;

	glutInit(&argc, (char**)argv); //initialize the tool kit
	glutInitDisplayMode(GLUT_DOUBLE |GLUT_RGB | GLUT_DEPTH);//set the display mode
	glutInitWindowSize(screenWidth, screenHeight); //set window size
	glutInitWindowPosition(100, 100); // set window position on screen
	glutCreateWindow("Lab 2"); // open the screen window

	tetrahedron.CreateTetrahedron();
	cube.CreateCube(1);
	cuboid.CreateCuboid(3, 1, 1);
	cylinder.CreateCylinder(20, 5, 1);
	shape1.CreateShape1(3, 0.5, 0.8, 1.1, 16);
	shape2.CreateShape2(3, 1.5, 0.2, 0.5, 0.5, 0.4, 8);
	shape3.CreateShape3(3, 0.2, 1, 0.5, 0.7, 8);
	shape4.CreateShape4(-2, 1.2, 2.5, 0.2, 1, 0.7, 0.2, 0.5, 6);

	myInit();
    glutDisplayFunc(myDisplay);
	  
	glutMainLoop();
	return 0;
}


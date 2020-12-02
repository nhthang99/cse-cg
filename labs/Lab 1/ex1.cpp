#include <GL/glut.h>
#include <math.h>
#include <stdio.h>


void drawing_circle()
{
    float x = 0;
    float y = 0;
    int r = 5;
    float alpha = 10;

    glPointSize(5);
    glBegin(GL_POINTS);
    for (int i = 0; i <= 360 / alpha; ++i){
        x = sin(alpha*i/2/M_PI) * r;
        // y += theta_y;
        y = cos(alpha*i/2/M_PI) * r;
        // x += theta_x;
        // printf("%f %f", x, y);
        glVertex2f(10, 10);
    }
    glEnd();
    
    glFlush();
}


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(640, 640);
    gluOrtho2D(-20, 20, -20, 20);
	glutCreateWindow("Randomly generated points");
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	glutDisplayFunc(drawing_circle);
    glutMainLoop();
    return 0;
}

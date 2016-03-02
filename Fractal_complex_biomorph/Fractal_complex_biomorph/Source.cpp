
#include<iostream>
#include<cmath>
#include<cstdlib>
#include<complex>
#include <glut.h>

using namespace std;

int n = 0;

double WinWidth = 800.0;
double WinHeight = 600.0;
double x = 0, y = 0;



void Draw()
{
	glLoadIdentity();
	glClear(GLUT_DOUBLE | GLUT_RGB);
	glBegin(GL_POINTS);
	for (y = -2.5; y < 2.5; y += 0.005)
	{
		for (x = -2.5; x < 2.5; x += 0.005)
		{
			complex <double> z(x, y);
			int i = 0;
			complex <double> c(0.75669, 0);

			while (i < 100)
			{
				z = pow(z, 5) + c;
				i++;
				if (abs(real(z)) > 10 || abs(imag(z)) > 10 || pow(real(z), 2) + pow(imag(z), 2) >= 100)
					i = 100;
			}
			double Scale = 150;
			if (abs(real(z)) < 10 && abs(imag(z)) < 10)
			{
				glColor3d(1, 1, 0.01);
				glVertex2d(x*Scale, y*Scale);
			}
			if (abs(real(z)) >= 10 && abs(imag(z)) < 10)
			{
				glColor3d(1, 0, 0);
				glVertex2d(x*Scale, y*Scale);
			}
			if (abs(real(z)) < 10 && abs(imag(z)) >= 10)
			{
				glColor3d(0, 1, 0);
				glVertex2d(x*Scale, y*Scale);
			}
			if (abs(real(z)) >= 10 && abs(imag(z)) >= 10)
			{
				glColor3d(0, 0, 0);
				glVertex2d(x*Scale, y*Scale);
			}
		}
	}
	glEnd();
	glutSwapBuffers();
}

void Initialize()
{
	glClearColor(0, 0, 0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-WinWidth / 2, WinWidth / 2, -WinHeight / 2, WinHeight / 2, -200.0, 200.0);
	glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WinWidth, WinHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Biomorph fractal");
	Initialize();
	glutDisplayFunc(Draw);
	glutMainLoop();
	return 0;
}
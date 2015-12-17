#include<glut.h>
#include<iostream>
#include<cmath>
#include<cstdlib>
#define pi = 3.14

int n = 0;
const float a = -0.1;
float WinWidth = 600.0;
float WinHeight = 600.0;
float Xk1 = -200;
float Yk1 = -200;
float Xk2 = 200;
float Yk2 = -200;
float Xk3 = 200;
float Yk3 = 200;
float Xk4 = -200;
float Yk4 = 200;

class Point 
{
	public:
	float x, y;
	Point()
	{
		x = 0;
		y = 0;
	}
	Point(float _x, float _y)
	{
		x = _x;
		y = _y;
	}
	Point(const Point &p)
	{
		x = p.x;
		y = p.y;
	}
};

class Quadrant 
{
	public:
	Point pt1, pt2, pt3, pt4;
	Quadrant(Point p1, Point p2, Point p3, Point p4)
	{
		pt1.x = p1.x;
		pt1.y = p1.y;
		pt2.x = p2.x;
		pt2.y = p2.y;
		pt3.x = p3.x;
		pt3.y = p3.y;
		pt4.x = p4.x;
		pt4.y = p4.y;
	}
	void drawQuadrant(int n)
	{
		glBegin(GL_LINE_LOOP);
		glColor3f(0, 0, 1);
		glVertex2f(pt1.x, pt1.y);
		glVertex2f(pt2.x, pt2.y);
		glVertex2f(pt3.x, pt3.y);
		glVertex2f(pt4.x, pt4.y);
		glEnd();
	}
	Point internalCoords(Point p,  int n)
	{
		float A = 1 / (sqrt(2)* sin(0.785 - a));
		float xt = A*(p.x * cos(a) - p.y*sin(a));
		float yt = A*(p.x * sin(a) + p.y*cos(a));
		p.x = xt;
		p.y = yt;
		return p;
	}
	void SetCoords(int n)
	{
		pt1 = internalCoords(pt1, n);
		pt2 = internalCoords(pt2, n);
		pt3 = internalCoords(pt3, n);
		pt4 = internalCoords(pt4, n);

		drawQuadrant(n);
		if (n <= 100)
		{
			drawQuadrant(n);
			n++;
			SetCoords(n);
		}
	}
};


void Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Point p1(Xk1, Yk1);
	Point p2(Xk2, Yk2);
	Point p3(Xk3, Yk3);
	Point p4(Xk4, Yk4);
	Quadrant Q(p1, p2, p3, p4);
	Q.drawQuadrant(n);
	Q.SetCoords(n);
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
using namespace std;

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WinWidth, WinHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Quadrant");
	glutDisplayFunc(Draw);
	Initialize();
	glutMainLoop();
	return 0;
}


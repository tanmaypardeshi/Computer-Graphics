
#include<iostream>
#include<GL/glut.h>
#include<cmath>

using namespace std;

float r;

void plot(int x,int y)
{
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
}

void init(void)
{
	glClearColor(0.0,0.0,0.0,0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-780,780,-420,420);
}

void drawMidpoint(float r1)
{
	float x, y, p;
	
	p = 5/4 - r1;
	x = 0;
	y = r1;
	plot(x,y);
	
	while(x <= y)
	{
		if(p<0)
		{
			p += 2*x+3;
			x += 1;
		}
		else if(p >=0)
		{
			p += 2*(x-y)+5;
			x += 1;
			y -= 1;
		}
		plot(x,y);
		plot(x,-y);
		plot(-x,y);
		plot(-x,-y);
		plot(y,x);
		plot(-y,x);
		plot(y,-x);
		plot(-y,-x);
	}
	
}

void displayMidpoint()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(1.0);
	glColor3f(1.0,1.0,1.0);
	drawMidpoint(r);
	glFlush();
}

int main(int argc,char **argv)
{
	int choice;
	
	cout<<"Enter the radius of the circle :\n"<<endl;
	cin>>r;
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1366, 768);
	glutInitWindowPosition(100,100);
	
	glutCreateWindow("Midpoint Circle");
	init();
	glutDisplayFunc(displayMidpoint);
	glutMainLoop();
	return 0;
}


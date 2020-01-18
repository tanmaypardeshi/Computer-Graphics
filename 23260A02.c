#include<iostream>
#include<GL/glut.h>
#include<cmath>
using namespace std;

void plot(int,int);
void midpoint(float,float,float);
void dda(float,float,float,float);
void display();

float cx=0,cy=0,r1;

int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1366, 768);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Assignment 2");
	cout<<"Enter radius of circle:- ";
	cin>>r1;
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}


void plot(int x,int y)
{
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
}

void midpoint(float cx, float cy, float r1)
{	
	float x, y, p;
	p = 5/4 - r1;
	x = 0;
	y = r1;
	
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
		
		plot(x+cx, y+cy);
		plot(x+cx,-y+cy);
		plot(-x+cx,y+cy);
		plot(-x+cx,-y+cy);
		plot(y+cx,x+cy);
		plot(-y+cx,x+cy);
		plot(y+cx,-x+cy);
		plot(-y+cx,-x+cy);
	}
	
}

void dda(float x1,float y1,float x2,float y2)
{
	float x,y,Xin,Yin,dy,dx,length;
	int i;	
	dx=x2-x1;
	dy=y2-y1;
	
	if(abs(dx)>=abs(dy))
		length=abs(dx);
	else
		length=abs(dy);
		
	Xin=dx/length;
	Yin=dy/length;
	x=x1;
	y=y1;
	plot(round(x),round(y));
	
	for(i=0;i<length;i++)
	{
		x=x+Xin;
		y=y+Yin;
		plot(round(x),round(y));
	}
	glFlush();
}


void display()
{
	glClearColor(0.0,0.0,0.0,0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-780,780,-420,420);
	glClear(GL_COLOR_BUFFER_BIT);	
	glPointSize(1.0);
	
	//Outer circle
	glColor3f(1.0,0.0,0.0);
	midpoint(cx,cy,2*r1);
	
	//Inner circle
	glColor3f(0.0,1.0,0.0);
	midpoint(cx,cy,r1);
	
     //Triangle
     glColor3f(1.0,1.0,0.0);
     dda(0,2*r1,2*r1*0.866,-r1);
     dda(2*r1*0.866,-r1,-2*r1*0.866,-r1);
     dda(-2*r1*0.866,-r1,0,2*r1);
          
     //coordinates
     glColor3f(0.3,0.3,0.3);
     glPointSize(1.0);
     dda(-780,0,780,0);
     dda(0,420,0,-420);
     
   	glFlush();
}



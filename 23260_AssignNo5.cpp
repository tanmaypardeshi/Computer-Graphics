/*
===========================================================
Roll number:- 23260
Batch:- H 10
Problem Definition:- Implement Cohen Sutherland algorithm 
to clip an given line/polygon. Provide the vertices of the 
line/polygon to be clipped and the pattern of clipping 
interactively. 
===========================================================
*/

#include<iostream>
#include<cmath>
#include<GL/glut.h>
#define PI 3.1415926535
using namespace std;

void plot(int, int , int , int);
void lineClipping(int, int,int, int);
void init();
void display();

int n;
float wx1, wy1, wx2, wy2;
float x[20], y[20];


int main(int argc, char **argv)
{
	int choice;
	
	cout<<"\nEnter the diagonally opposite co-ordinates of the clipping window:- "<<endl;
	cout<<"\nBottom point:- "<<endl;
	cout<<"Enter x coorinate:- ";
	cin>>wx1;
	cout<<"Enter y coordinate:- ";
	cin>>wy1;
	cout<<"\nTop point:- "<<endl;
	cout<<"Enter x coorinate:- ";
	cin>>wx2;
	cout<<"Enter y coordinate:- ";
	cin>>wy2;
	

	cout<<"\nEnter the number of vertices of the polygon:- ";
	cin>>n;
	cout<<"\nEnter their coordinates:- "<<endl;
	for(int i=0; i<n; i++)
	{
		cout<<"\nPoint "<<i+1<<":- "<<endl;
		cout<<"Enter x coorinate:- ";
		cin>>x[i];
		cout<<"Enter y coordinate:- ";
		cin>>y[i];
		
	}

	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1366,768);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Assignment 5");
	
	glClearColor(0.0,0.0,0.0,0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-780,780,-420,420);

	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(wx1,wy1);
	glVertex2f(wx2,wy1);
	glVertex2f(wx2,wy2);
	glVertex2f(wx1,wy2);
	glEnd();
	
	glPointSize(2.0);
	glColor3f(1.0,1.0,0.0);
	
	if(n == 2)
		lineClipping(x[0],y[0],x[1],y[1]);
	else
	{
		for(int i=0; i<n; i++)
			lineClipping(x[i],y[i],x[i+1],y[i+1]);
		lineClipping(x[n-1],y[n-1],x[0],y[0]);
	}
	
	glFlush();
}

void plot(int x1, int y1, int x2, int y2)
{
	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
}

void lineClipping(int x1, int y1,int x2, int y2)
{
	int a[4], b[4], c[4];
	int xa, ya, xb, yb;
	xa = x1;
	ya = y1;
	xb = x2;
	yb = y2;
	for(int i=0; i<4; i++)
	{
		a[i] = 0;
		b[i] = 0;
	}
	
	if(x1 < wx1)
		a[3] = 1;
	if(x1 > wx2)
		a[2] = 1;
	if(y1 < wy1)
		a[1] = 1;
	if(y1 > wy2)
		a[0] = 1;
		
	if(x2 < wx1)
		b[3] = 1;
	if(x2 > wx2)
		b[2] = 1;
	if(y2 < wy1)
		b[1] = 1;
	if(y2 > wy2)
		b[0] = 1;
		
	if(a[0] == 0 && a[1] == 0 && a[2] == 0 && a[3] == 0 && b[0] == 0 && b[1] == 0 && b[2] == 0 && b[3] == 0)
		plot(xa, ya, xb, yb);
		
	else
	{
		c[0] = a[0] && b[0];
		c[1] = a[1] && b[1];
		c[2] = a[2] && b[2];
		c[3] = a[3] && b[3];
		
		if(c[0] == 0 && c[1] == 0 && c[2] == 0 && c[3] == 0)
		{
			if(a[0] == 0 && a[1] == 0 && a[2] == 0 && a[3] == 1)
			{
				xa = wx1;
				ya = (xa-x1)*(y1-y2)/(x1-x2) + y1;
			}
			else if(a[0] == 0 && a[1] == 0 && a[2] == 1 && a[3] == 0)
			{
				xa = wx2;
				ya = (xa-x1)*(y1-y2)/(x1-x2) + y1;
			}
			else if(a[0] == 0 && a[1] == 1 && a[2] == 0 && a[3] == 0)
			{
				ya = wy1;
				xa = (ya-y1)*(x1-x2)/(y1-y2) + x1;
			}
			else if(a[0] == 1 && a[1] == 0 && a[2] == 0 && a[3] == 0)
			{
				ya = wy2;
				xa = (ya-y1)*(x1-x2)/(y1-y2) + x1;
			}
			else if(a[0] == 1 && a[1] == 0 && a[2] == 0 && a[3] == 1)
			{
				ya = wy2;
				xa = (ya-y1)*(x1-x2)/(y1-y2) + x1;
				
				if((xa-x1)*(y1-y2) - (ya-y1)*(y1-y2) != 0)
				{
					xa = wx1;
					ya = (xa-x1)*(y1-y2)/(x1-x2) + y1;
				}
			}
			else if(a[0] == 1 && a[1] == 0 && a[2] == 1 && a[3] == 0)
			{
				ya = wy2;
				xa = (ya-y1)*(x1-x2)/(y1-y2) + x1;
				
				if((xa-x1)*(y1-y2) - (ya-y1)*(y1-y2) != 0)
				{
					xa = wx2;
					ya = (xa-x1)*(y1-y2)/(x1-x2) + y1;
				}
			}
			else if(a[0] == 0 && a[1] == 1 && a[2] == 0 && a[3] == 1)
			{
				ya = wy1;
				xa = (ya-y1)*(x1-x2)/(y1-y2) + x1;
				
				if((xa-x1)*(y1-y2) - (ya-y1)*(y1-y2) != 0)
				{
					xa = wx1;
					ya = (xa-x1)*(y1-y2)/(x1-x2) + y1;
				}
			}
			else if(a[0] == 0 && a[1] == 1 && a[2] == 1 && a[3] == 0)
			{
				ya = wy1;
				xa = (ya-y1)*(x1-x2)/(y1-y2) + x1;
				
				if((xa-x1)*(y1-y2) - (ya-y1)*(y1-y2) != 0)
				{
					xa = wx2;
					ya = (xa-x1)*(y1-y2)/(x1-x2) + y1;
				}
			}
			
			if(b[0] == 0 && b[1] == 0 && b[2] == 0 && b[3] == 1)
			{
				xb = wx1;
				yb = (xb-x1)*(y1-y2)/(x1-x2) + y1;
			}
			else if(b[0] == 0 && b[1] == 0 && b[2] == 1 && b[3] == 0)
			{
				xb = wx2;
				yb = (xb-x1)*(y1-y2)/(x1-x2) + y1;
			}
			else if(b[0] == 0 && b[1] == 1 && b[2] == 0 && b[3] == 0)
			{
				yb = wy1;
				xb = (yb-y1)*(x1-x2)/(y1-y2) + x1;
			}
			else if(b[0] == 1 && b[1] == 0 && b[2] == 0 && b[3] == 0)
			{
				yb = wy2;
				xb = (yb-y1)*(x1-x2)/(y1-y2) + x1;
			}
			else if(b[0] == 1 && b[1] == 0 && b[2] == 0 && b[3] == 1)
			{
				yb = wy2;
				xb = (yb-y1)*(x1-x2)/(y1-y2) + x1;
				
				if((xb-x1)*(y1-y2) - (yb-y1)*(y1-y2) != 0)
				{
					xb = wx1;
					yb = (xb-x1)*(y1-y2)/(x1-x2) + y1;
				}
			}
			else if(b[0] == 1 && b[1] == 0 && b[2] == 1 && b[3] == 0)
			{
				yb = wy2;
				xb = (yb-y1)*(x1-x2)/(y1-y2) + x1;
				
				if((xb-x1)*(y1-y2) - (yb-y1)*(y1-y2) != 0)
				{
					xb = wx2;
					yb = (xb-x1)*(y1-y2)/(x1-x2) + y1;
				}
			}
			else if(b[0] == 0 && b[1] == 1 && b[2] == 0 && b[3] == 1)
			{
				yb = wy1;
				xb = (yb-y1)*(x1-x2)/(y1-y2) + x1;
				
				if((xb-x1)*(y1-y2) - (yb-y1)*(y1-y2) != 0)
				{
					xb = wx1;
					yb = (xb-x1)*(y1-y2)/(x1-x2) + y1;
				}
			}
			else if(b[0] == 0 && b[1] == 1 && b[2] == 1 && b[3] == 0)
			{
				yb = wy1;
				xb = (yb-y1)*(x1-x2)/(y1-y2) + x1;
				
				if((xb-x1)*(y1-y2) - (yb-y1)*(y1-y2) != 0)
				{
					xb = wx2;
					yb = (xb-x1)*(y1-y2)/(x1-x2) + y1;
				}
			}
			
			plot(xa,ya,xb,yb);
		}
	}
}

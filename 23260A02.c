#include<GL/glut.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>

void plot(int,int);
void midpoint(float,float,float);
void bresnham(float,float,float);
void dda(float,float,float,float);
void display1();
void display2();

float r1=0;

int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1366, 768);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Assignment 2");

	int choice;
	printf("\nCircle Drawing Algorithm\n");
	printf("1. Midpoint Circle Algorithm\n");
	printf("2. Breshnham Circle Algorithm\n");
	printf("3. Exit program\n");
	printf("\nEnter your choice:- ");
	scanf("%d", &choice);

	switch(choice)
	{
		case 1:
			printf("Enter radius of circle:- ");
			scanf("%f", &r1);
			glutDisplayFunc(display1);
			glutMainLoop();	
			break;
		case 2:
			printf("Enter radius of circle:- ");
			scanf("%f", &r1);
			glutDisplayFunc(display2);
			glutMainLoop();	
			break;
		case 3:
			return 0;
		default:
			printf("\nError in choice, try again\n");
	
	}
	
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
		
		plot(x, y);
		plot(x,-y);
		plot(-x,y);
		plot(-x,-y);
		plot(y,x);
		plot(-y,x);
		plot(y,-x);
		plot(-y,-x);
	}
	
}

void bresnham(float cx,float cy,float r)
{
	float x,y,p,delta,delta_dash;

	x=0;
	y=r;
	p= 2*(1-r);

	while(x<=y)
	{
		if(p<0)
		{
			delta = 2*p + 2*y -1;
			if( delta <= 0)
			{
				x += 1;
				p = p + 2*x +1;
			}
			else
			{
				p = p + 2*x -2*y +2;
				x += 1;
				y -= 1;
			}
		}
		else if(p>0)
		{
			delta_dash = 2*p - 2*x - 1;
			if(delta_dash<=0)
			{
				x+=1;
				y-=1;
				p=p + 2*x - 2*y +2;
			}
			else
				y-=1;
		}
		else
		{
			x+=1;
			y-=1;
			p=p + 2*x -2*y+2;
		}

		plot(x, y);
		plot(x,-y);
		plot(-x,y);
		plot(-x,-y);
		plot(y,x);
		plot(-y,x);
		plot(y,-x);
		plot(-y,-x);
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


void display1()
{
	glClearColor(0.0,0.0,0.0,0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-780,780,-420,420);
	glClear(GL_COLOR_BUFFER_BIT);	
	glPointSize(1.0);
	
	//Outer circle
	glColor3f(1.0,0.0,0.0);
	midpoint(0,0,2*r1);
	
	//Inner circle
	glColor3f(0.0,1.0,0.0);
	midpoint(0,0,r1);
	
     //Triangle
     glColor3f(1.0,1.0,0.0);
     dda(0,2*r1,2*r1*0.866,-r1);
     dda(2*r1*0.866,-r1,-2*r1*0.866,-r1);
     dda(-2*r1*0.866,-r1,0,2*r1);
          
     //coordinate axes
     glColor3f(0.3,0.3,0.3);
     glPointSize(1.0);
     dda(-780,0,780,0);
     dda(0,420,0,-420);
     
   	glFlush();
}

void display2()
{
	glClearColor(0.0,0.0,0.0,0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-780,780,-420,420);
	glClear(GL_COLOR_BUFFER_BIT);	
	glPointSize(1.0);
	
	//Outer circle
	glColor3f(1.0,0.0,0.0);
	bresnham(0,0,2*r1);
	
	//Inner circle
	glColor3f(0.0,1.0,0.0);
	bresnham(0,0,r1);
	
     //Triangle
     glColor3f(1.0,1.0,0.0);
     dda(0,2*r1,2*r1*0.866,-r1);
     dda(2*r1*0.866,-r1,-2*r1*0.866,-r1);
     dda(-2*r1*0.866,-r1,0,2*r1);
          
     //coordinate axes
     glColor3f(0.3,0.3,0.3);
     glPointSize(1.0);
     dda(-780,0,780,0);
     dda(0,420,0,-420);
     
   	glFlush();
}


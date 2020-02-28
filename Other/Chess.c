#include<iostream>
#include<GL/gl.h>
#include<GL/freeglut.h>
#include<stdio.h>
#include<math.h> 
#include <GL/glut.h>
using namespace std;

#define sin45 (1/sqrt(2))

void bound_it(int x, int y, float* fillColor, float* bc);
int X1,Y1,X2,Y2,X3,Y3,x, y,size;

void setPixel (GLint xCoord, GLint yCoord)
{
	glBegin (GL_POINTS);
	glVertex2i (xCoord, yCoord);
	glEnd ( );
}

void bresenham_line(int x1, int y1, int x2, int y2) 
{
	int dx, dy, i, p;
	int incx, incy, inc1, inc2;
	int x,y;
	dx = x2-x1;
	dy = y2-y1;
	if (dx < 0) 
	{
		dx = -dx;
	}	
	if (dy < 0) 
	{
		dy = -dy;
	}
	incx = 1;
	if (x2 < x1) 
	{
		incx = -1;
	}	
	incy = 1;
	if (y2 < y1) 
	{
		incy = -1;
	}	
	x = x1; y = y1;
	if (dx > dy) 
	{
		setPixel(x, y);
		p = 2 * dy-dx;
		inc1 = 2*(dy-dx);
		inc2 = 2*dy;
		for (i=0; i<dx; i++) 
		{
			if (p > 0) 
			{
				y += incy;
				p += inc1;
			}
			else
			{
				p += inc2;
			}
			x += incx;
			setPixel(x, y);
		}
	} 
	else 
	{
		setPixel(x, y);
		p = 2*dx-dy;
		inc1 = 2*(dx-dy);
		inc2 = 2*dx;
		for (i=0; i<dy; i++) 
		{
			if (p > 0) 
			{
				x += incx;
				p += inc1;
			}
			else
			{
				p += inc2;
			}	
			y += incy;
			setPixel(x, y);
		}
	}
}

void init (void)
{
	glClearColor (1.0, 1.0, 1.0, 0.0);		// Set display-window color to white.
	glMatrixMode (GL_PROJECTION);		// Set projection parameters.
	gluOrtho2D (0.0, 1024, 0.0, 768);
}

void lineSegment ()
{
	int i, X=0, Y=0;
	glLineWidth(3);
    glPointSize(2);
	glClear (GL_COLOR_BUFFER_BIT);
	glColor3f (0, 0, 0);
	for(i=0;i<5;i++)
	{
		bresenham_line(X1+X, Y1+Y, X2+X, Y2+Y);	
		//X-=size;
		Y+=size;
	}
	X=0;
	Y=0;
	for(i=0;i<5;i++)
	{
		bresenham_line(X3+X, Y3+Y, X1+X, Y1+Y);
		X+=size;
		//Y+=size;
	}	
	float bCol[] = {0,0,0};
    float color[] = {0,0,0};
    //glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,intCol);
    X1=500;
    Y1=0;
    bound_it(X1+2,Y1+2,color,bCol);
    bound_it(X1+2+(2*size),Y1+2,color,bCol);

    bound_it(X1+2+size,Y1+2+size,color,bCol);
    bound_it(X1+2+(3*size),Y1+2+size,color,bCol);

	bound_it(X1+2,Y1+2+(2*size),color,bCol);
    bound_it(X1+2+(2*size),Y1+2+(2*size),color,bCol);

    bound_it(X1+2+size,Y1+2+(3*size),color,bCol);
    bound_it(X1+2+(3*size),Y1+2+(3*size),color,bCol);
                	glFlush ( );
	// Clear display window.
	// Set line segment color to green.
	// Specify line-segment geometry.
	// Process all OpenGL routines as quickly as possible.
}

void bound_it(int x, int y, float* fillColor, float* bc)
{
    float color[3];
    glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,color);
    if((color[0]!=bc[0] || color[1]!=bc[1] || color[2]!=bc[2])&&(
     color[0]!=fillColor[0] || color[1]!=fillColor[1] || color[2]!=fillColor[2]))
     {
        glColor3f(fillColor[0],fillColor[1],fillColor[2]);
        glBegin(GL_POINTS);
            glVertex2i(x,y);
        glEnd();
        glFlush();
        bound_it(x+1,y,fillColor,bc);
        bound_it(x-2,y,fillColor,bc);
        bound_it(x,y+2,fillColor,bc);
        bound_it(x,y-2,fillColor,bc);
    }
}

int main(int argc,char **argv)  
{ 
	float temp;
	
	cout<<"\nEnter the size of small square: ";
	cin>>size;
	X1=500;
	Y1=0;
	X2=500+(size*4);
	Y2=0;
	X3=500;
	Y3=size*4;
			
	glutInit (&argc, argv);							// Initialize GLUT.
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);	// Set display mode.
	glutInitWindowPosition (50, 50);					// Set top-left display-window position.
	glutInitWindowSize (1024, 768);						// Set display-window width and height.
	glutCreateWindow ("Assignment 4: Chess Board"); // Create display window.
	init ( );
	glutDisplayFunc (lineSegment);	
	glutMainLoop ( );
	return 0; 
}


/*
===========================================================
Roll number:- 23211
Batch:- E 10
Problem Definition:- Draw a 4x4 chessboard rotated 45 
degrees with horizontal axis. Use bresenham algorithm
to draw all the lines. Use seed fill algorithm to fill
black spaces of chessboard.
===========================================================
*/

#include<stdio.h>
#include<math.h>
#include<GL/gl.h>
#include<stdlib.h>
#include<GL/glu.h>
#include<GL/glut.h>

float trans[3][3],ans[20][3],mat[20][3];
int tx,ty;
float X,Y;

typedef struct pixel
{
	GLubyte r;
	GLubyte g;
	GLubyte b;
}pixel;
pixel b_clr,f_clr;

void initialize()
{
	float X1,Y1;
	printf("Enter x coordinate:- ");
	scanf("%f",&X);
	printf("Enter y coordinate:- ");
	scanf("%f",&Y);
	X1=X;
	Y1=Y;
	for(int i=0;i<10;i+=2)
	{
		mat[i][0]=X;
		mat[i][1]=Y;
		mat[i][2]=1;
		
		mat[i+1][0]=X+120;
		mat[i+1][1]=Y;
		mat[i+1][2]=1;
		
		Y+=30;
	}
	Y=Y1;
	for(int i=10;i<20;i+=2)
	{
		mat[i][0]=X;
		mat[i][1]=Y;
		mat[i][2]=1;
		
		mat[i+1][0]=X;
		mat[i+1][1]=Y+120;
		mat[i+1][2]=1;
		
		X+=30;
	} 
	
	float root2 = 1/(sqrt(2));
	trans[0][0]=trans[0][1]=trans[1][1]=root2;
	trans[1][0]=-root2;
	trans[0][2]=trans[1][2]=0;

	tx=mat[0][0];
	ty=mat[0][1];

	trans[2][0]=((ty-tx)*root2) + tx;
	trans[2][1]=((-ty-tx)*root2) + ty;
	trans[2][2]=1;

	for(int i=0;i<20;i++)
	{
		for(int j=0;j<3;j++)
		{
			ans[i][j]=0;
		
			for(int k=0;k<3;k++)
				ans[i][j]+=mat[i][k] * trans[k][j];
		}
	}
	X=X1;
	Y=Y1;
}

void plot(int x,int y)                                 //FUNCTION TO PLOT A POINT
{
	glBegin(GL_POINTS);
    	glVertex2i(x,y);
    glEnd();  
    glFlush();
}

void  Brezenham(int x1,int y1,int x2,int y2)
{
	
    int incx,incy,inc1,inc2,p,x,y;                    //INITIALIZATION
	int dy=y2-y1;
    int dx=x2-x1;
    if(dx<0)
    	dx=-dx;
    if(dy<0)
    	dy=-dy;
    incx=1;
    incy=1;
    if(x2<x1)                                        //IF FINAL CO-ORDINATE IS LESS THAN INITIAL THE INCREMENT ID NEGATIVE   
    	incx=-1;
    if(y2<y1)
    	incy=-1;
    x=x1;
    y=y1;
    if(dx>dy)                                         //TOTAL NUMBER OF STEPS IS DX IF IT IS GREATER THAN DY
    {
    	plot(x,y);
    	p=2*dy-dx;
    	inc1=2*(dy-dx);
    	inc2=2*dy;
    	for(int i=0;i<dx;i++)
    	{
    		if(p>0)
    		{
    			y+=incy;
    			p+=inc1;
    		}
    		else
    			p+=inc2;
    		x+=incx;
    		plot(x,y);
    	}
    }
    else	                                          //TOTAL NUMBER OF STEPS IS DY IF IT IS GREATER THAN DX
    {
	 	plot(x,y);
	 	p=2*dx-dy;
	 	inc1=2*(dx-dy);
	 	inc2=2*dx;
	 	for(int i=0;i<dy;i++)
	 	{
	 		if(p>0)
	 		{
				x+=incx;
				p+=inc1;
			}
			else
			{
				p+=inc2;
			}
			y+=incy;
			plot(x,y);
		}
	}
}

void boundary_fill(float x,float y)
{
	pixel c;
	glReadPixels(x,y,1,1,GL_RGB,GL_UNSIGNED_BYTE,&c);
	
	if((c.r!=b_clr.r || c.g!=b_clr.g ||  c.b!=b_clr.b) && (c.r!=f_clr.r || c.g!=f_clr.g || c.b!=f_clr.b))
	{
		glBegin(GL_POINTS);
     		glVertex2d(x,y);
     		glColor3ub(f_clr.r,f_clr.g,f_clr.b);
     		glEnd();
     		glFlush();
     		boundary_fill(x,y+1);
     		boundary_fill(x-1,y);
     		boundary_fill(x,y-1);
     		boundary_fill(x+1,y);
    }
}

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3i(0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
   	gluOrtho2D(0,750,0,750);
}

void draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	int i;
	for(i=0;i<20;i+=2)
		Brezenham(ans[i][0],ans[i][1],ans[i+1][0],ans[i+1][1]);
		
	float factor=60/(sqrt(2));
	float add=30/sqrt(2);
	Y=Y+add;
	
	boundary_fill(X,Y);
	
	for(int i=2;i<=6;i++)
		boundary_fill(X,Y+i*add);
		
	Y=Y+factor;
	boundary_fill(X+factor,Y);
	boundary_fill(X+factor,Y+factor);
	boundary_fill(X-factor,Y);
	boundary_fill(X-factor,Y+factor);
	
	glEnd();
	glFlush();
}
	
int main(int argc,char **argv)
{
	initialize();
	
	b_clr.r=0;
	b_clr.g=0;
	b_clr.b=0;
	
	f_clr.r=150;
	f_clr.g=150;
	f_clr.b=150;
	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(750,750);
    glutCreateWindow("Assignment 4");
	init();
	glutDisplayFunc(draw);
	glutMainLoop();
}

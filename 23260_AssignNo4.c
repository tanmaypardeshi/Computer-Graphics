/*
==============================================================

Roll number:- 23260
Batch:- H 10

Problem Definition:- Draw a 4X4 chessboard rotated PI/4 degrees
with the horizontal axis. Use Bresenham algorithm to draw all 
the lines. Use seed fill algorithm to fill black squares of 
the rotated chessboard

==============================================================
*/

#include<GL/glut.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#define PI 3.141


void bresenham(float,float,float,float);
void plot(int ,int );
void render();

float xx1,yy1,length;
     
int main(int argc, char** argv) 
{
	
     glutInit(&argc, argv);
     glutInitDisplayMode (GLUT_SINGLE);
     glutInitWindowSize (700, 700);
     glutInitWindowPosition (500,0);
     glutCreateWindow ("Assignment 4");
     
     printf("Enter the coordinates of left vertex:- \n");
     printf("Enter the x coordinte:- ");
     scanf("%f",&xx1);
     printf("Enter the y coordinate:- ");
     scanf("%f",&yy1);
     printf("Enter the length of the square:- ");
     scanf("%f",&length);
   
     glutDisplayFunc(render);
     glutMainLoop();
     return 0;
} 

     
void  bresenham(float x1,float y1,float x2,float y2)
{
     int i;
     float dx,dy,xinc,yinc,inc1,inc2,p,x,y;                  
     dx=x2-x1;
     dy=y2-y1;
    
     if(dx<0)
          dx=-dx;
     if(dy<0)
          dy=-dy;
    
     xinc=1;
     yinc=1;
    
     if(x2<x1)                                    
          xinc=-1;
     if(y2<y1)
          yinc=-1;
    
     x=x1;
     y=y1;

     if(dx>dy)
     {
    		plot((x-y)*cos(PI/4),(x+y)*cos(PI/4));
          
          p=2*dy-dx;          
          inc1=2*(dy-dx);
          inc2=2*dy;
          for(i=0;i<dx;i++)
          {
	          if(p>0)
         		{
		          y+=yinc;
         			p+=inc1;
         		}
	          else
		          p+=inc2;
         		x+=xinc;
	    		plot((x-y)*cos(PI/4),(x+y)*cos(PI/4));
         	
          }
     }
     else	                                          
     {
  		plot((x-y)*cos(PI/4),(x+y)*cos(PI/4));
      	
      	p=2*dx-dy;
      	inc1=2*(dx-dy);
      	inc2=2*dx;
      	for(i=0;i<dy;i++)
      	{
      		if(p>0)
      		{
			     x+=xinc;
			     p+=inc1;
		     }
		     else
			     p+=inc2;
		     y+=yinc;
         		plot((x-y)*cos(PI/4),(x+y)*cos(PI/4));
	     }
     }
}

     
void plot(int x,int y)
{
     glBegin(GL_POINTS);
     glVertex2i(x,y);
     glEnd();
     glFlush();
}
	     
void render()
{
	int temp;
     glClearColor(0.0, 0.0, 0.0, 0.0);
     glPointSize(3.0);
     glClear(GL_COLOR_BUFFER_BIT);
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     gluOrtho2D(-780,780,-420,420);
     

     //coordinates
     glPointSize(2.0);
     glColor3f(1.0,1.0,1.0);
     
     for(temp=0;temp<=length;temp+=length/4)
     {
          bresenham(xx1+temp,yy1,xx1+temp,yy1+length);
          bresenham(xx1,yy1+temp,xx1+length,yy1+temp);
     }

}

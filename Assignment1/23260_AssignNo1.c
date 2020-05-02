/*
===========================================================
Roll number:- 23260
Batch:- H 10
Problem Definition:- Draw the given pattern using
line drawing algorithm
===========================================================
*/

#include<GL/glut.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>

void dda(float,float,float,float);
void bresnham(float,float,float,float);
void plot(int ,int );
void render1();
void render2();


float xx1,yy1,xx2,yy2;

int main(int argc, char** argv) 
{
	
     glutInit(&argc, argv);
     glutInitDisplayMode(GLUT_SINGLE);
     glutInitWindowSize (700, 700);
     glutInitWindowPosition (500,0);
     glutCreateWindow ("Assignment 1");
     
     int choice;
     printf("\n1. DDA algorithm\n");
     printf("2. Bresnham's algorithm\n");
     printf("\nEnter your choice:- ");
     scanf("%d" ,&choice);
     switch(choice)
     {
          case 1: 
               printf("Enter x1:- ");
               scanf("%f",&xx1);   
               printf("Enter y1:- ");
               scanf("%f",&yy1);
               printf("Enter x2:- ");
               scanf("%f",&xx2);
               printf("Enter y2:- ");
               scanf("%f",&yy2);   
               glutDisplayFunc(render1);
               glutMainLoop();
               break;
          case 2:
               printf("Enter x1:- ");
               scanf("%f",&xx1);   
               printf("Enter y1:- ");
               scanf("%f",&yy1);
               printf("Enter x2:- ");
               scanf("%f",&xx2);
               printf("Enter y2:- ");
               scanf("%f",&yy2);   
               glutDisplayFunc(render2);
               glutMainLoop();
               break;
             
     }
     return 0;
} 

void dda(float x1,float y1,float x2,float y2)
{

     float dy,dx,diff,x,y,i,xinc,yinc;
     dx=x2-x1;
     dy=y2-y1;

     if(abs(dx)> abs(dy))
          diff = abs(dx);
     else
          diff = abs(dy);

     xinc = dx/diff;
     yinc = dy/diff;
	      	
     x=x1;
     y=y1;

     plot(round(x),round(y));

     for (i=1 ;i<=diff;i++)
     {
          x= x + xinc;
          y= y + yinc;
          plot(round(x),round(y));
     }	

     glFlush();
}

void  bresnham(float x1,float y1,float x2,float y2)
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
          plot(x,y);
          
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
         		plot(x,y);
         	
          }
     }
     else	                                          
     {
	 	plot(x,y);
	 	
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
			plot(x,y);
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

void render1()
{
	
     glClearColor(0.0, 0.0, 0.0, 0.0);
     glPointSize(3.0);
     glClear(GL_COLOR_BUFFER_BIT);
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     gluOrtho2D(-120,120,-120,120);

     //outer sqaure
     glPointSize(3.0);
     glColor3f(1.0,1.0,0.0);
     dda(xx1,yy1,xx1,yy2);
     dda(xx1,yy2,xx2,yy2);
     dda(xx2,yy2,xx2,yy1);
     dda(xx2,yy1,xx1,yy1);

     //diamond
     glColor3f(0,1.0,0);
     dda((xx1+xx2)/2,yy1,xx2,(yy1+yy2)/2);
     dda(xx2,(yy1+yy2)/2,(xx1+xx2)/2,yy2);
     dda((xx1+xx2)/2,yy2,xx1,(yy1+yy2)/2);
     dda(xx1,(yy1+yy2)/2,(xx1+xx2)/2,yy1);

     //inner sqaure
     glColor3f(1.0,0.0,0.0);
     dda((3*xx1+xx2)/4,(3*yy1+yy2)/4,(xx1+3*xx2)/4,(3*yy1+yy2)/4);
     dda((xx1+3*xx2)/4,(3*yy1+yy2)/4,(xx1+3*xx2)/4,(yy1+3*yy2)/4);
     dda((xx1+3*xx2)/4,(yy1+3*yy2)/4,(3*xx1+xx2)/4,(yy1+3*yy2)/4);
     dda((3*xx1+xx2)/4,(yy1+3*yy2)/4,(3*xx1+xx2)/4,(3*yy1+yy2)/4);
     glFlush();

     //coordinates
     glPointSize(1.0);
     glColor3f(0.0,0.0,1.0);
     dda(-120,0,120,0);
     dda(0,-120,0,120);

     //vertex points
     glPointSize(12.0);
     glColor3f(1.0,0.0,0.0);
     dda(xx1,yy1,xx1,yy1);
     dda(xx2,yy2,xx2,yy2);	
}

void render2()
{
	
     glClearColor(0.0, 0.0, 0.0, 0.0);
     glPointSize(3.0);
     glClear(GL_COLOR_BUFFER_BIT);
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     gluOrtho2D(-120,120,-120,120);
     
     //outer sqaure
     glPointSize(3.0);
     glColor3f(1.0,1.0,0.0);
     bresnham(xx1,yy1,xx1,yy2);
     bresnham(xx1,yy2,xx2,yy2);
     bresnham(xx2,yy2,xx2,yy1);
     bresnham(xx2,yy1,xx1,yy1);

     //diamond
     glColor3f(0,1.0,0);
     bresnham((xx1+xx2)/2,yy1,xx2,(yy1+yy2)/2);
     bresnham(xx2,(yy1+yy2)/2,(xx1+xx2)/2,yy2);
     bresnham((xx1+xx2)/2,yy2,xx1,(yy1+yy2)/2);
     bresnham(xx1,(yy1+yy2)/2,(xx1+xx2)/2,yy1);

     //inner sqaure
     glColor3f(1.0,0.0,0.0);
     bresnham((3*xx1+xx2)/4,(3*yy1+yy2)/4,(xx1+3*xx2)/4,(3*yy1+yy2)/4);
     bresnham((xx1+3*xx2)/4,(3*yy1+yy2)/4,(xx1+3*xx2)/4,(yy1+3*yy2)/4);
     bresnham((xx1+3*xx2)/4,(yy1+3*yy2)/4,(3*xx1+xx2)/4,(yy1+3*yy2)/4);
     bresnham((3*xx1+xx2)/4,(yy1+3*yy2)/4,(3*xx1+xx2)/4,(3*yy1+yy2)/4);
     glFlush();

     //coordinates
     glPointSize(1.0);
     glColor3f(0.0,0.0,1.0);
     bresnham(-120,0,120,0);
     bresnham(0,-120,0,120);

     //vertex points
     glPointSize(12.0);
     glColor3f(1.0,0.0,0.0);
     bresnham(xx1,yy1,xx1,yy1);
     bresnham(xx2,yy2,xx2,yy2);
}

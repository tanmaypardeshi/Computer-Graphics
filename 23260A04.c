/*
==============================================================

Roll number:- 23260
Batch:- H 10

Problem Definition:- Draw a 4X4 chessboard rotated 45 degrees
with the horizontal axis. Use Bresenham algorithm to draw all 
the lines. Use seed fill algorithm to fill black squares of 
the rotated chessboard

==============================================================
*/

#include<GL/glut.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>

void bresenham(float,float,float,float);
void plot(int ,int );
void render();

int main(int argc, char** argv) 
{
	
     glutInit(&argc, argv);
     glutInitDisplayMode (GLUT_SINGLE);
     glutInitWindowSize (700, 700);
     glutInitWindowPosition (500,0);
     glutCreateWindow ("Assignment 4");
     
     glutDisplayFunc(render);
     glutMainLoop();
     return 0;
} 

     
void plot(int x,int y)
{
     glBegin(GL_POINTS);
     glVertex2i(x,y);
     glEnd();
     glFlush();
}


void  bresenham(float x1,float y1,float x2,float y2)
{
     float x0,y0,dx,dy,dk;
     int i;
     
     x0 = x1;
     y0 = y1;
     
     plot(x0,y0);
     
     dx = abs(x2-x1);
     dy = abs(y2-y1);
     
     dk = 2*dy - dx;
     
     for(i=0;i<round(4*dx);i++)
     { 
          if(dk<0)
          {
               x0+=1;
               plot(x0,y0);
               dk = dk + 2*dy;
         }
         else
         {
               x0+=1;
               y0+=1;
               plot(x0,y0);
               dk = dk + 2*dy - 2*dx;
         }
     }  
     
}
void render()
{
	
     float xx1,yy1,length;
     float box;
     
     printf("Enter the coordinates of left vertex:- \n");
     printf("Enter the x coordinte:- ");
     scanf("%f",&xx1);
     printf("Enter the y coordinate:- ");
     scanf("%f",&yy1);
     printf("Enter the length of the square:- ");
     scanf("%f",&length);
      
     
     glClearColor(0.0, 0.0, 0.0, 0.0);
     glPointSize(3.0);
     glClear(GL_COLOR_BUFFER_BIT);
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     gluOrtho2D(-120,120,-120,120);
     

     //coordinates
     glPointSize(1.0);
     glColor3f(1.0,1.0,1.0);
     bresenham(xx1,yy1,xx1+length,yy1+length);


}

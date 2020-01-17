#include <GL/freeglut.h>
#include <GL/gl.h>
#include<stdio.h>

void render1();
void plot(int ,int);
void bresnham();

float xc,yc,r;

int main(int argc, char** argv)
{
     glutInit(&argc, argv);
     glutInitDisplayMode (GLUT_SINGLE);
     glutInitWindowSize (700, 700);
     glutInitWindowPosition (500,0);
     glutCreateWindow ("DDA Assignment 2");

     int choice;
     printf("\n1. \n");
     printf("2. Bresnham's algorithm\n");
     printf("\nEnter your choice:- ");
     scanf("%d" ,&choice);
     switch(choice)
     {
          case 1:            
               break;
          case 2:
               print("Enter the x coordinate of centre:- ");
               scanf("%f", &xc);
               print("Enter the y coordinate of centre:- ");
               scanf("%f", &yc);
               printf("Enter the radius of circle:- ");
               scanf("%f", &r);
               glutDisplayFunc(render1);
               glutMainLoop();
               break;
             
     }
     return 0;
} 


void render1()
{
     glClearColor(0.0, 0.0, 0.0, 0.0);
     glPointSize(3.0);
     glClear(GL_COLOR_BUFFER_BIT);
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     gluOrtho2D(-120,120,-120,120);
     bresnham();
}

void plot(int x,int y)
{
     glBegin(GL_POINTS);
     glVertex2i(x,y);
     glEnd();
     glFlush();
}


void bresnham(float xc,float yc,float r)
{
     float x,y,dk,delta,delta_dash;
     
     x=0;
     y=r;
     dk=2(1-r);
     
     while(y>=x)
     {
          if(dk<0)
          {
               delta = 2*dk + 2*y -1;
               if(delta<=0)
               {
                    x=x+1;
                    dk = dk + 2x +1
               }
               else
               {
                    x=x+1;
                    y=y-1;
                    dk = dk + 2*x - 2*y +2;
               }
         }
         else if(dk>0)
         {
               delta_dash = 2*dk - 2*x -1;
               if(delta_dash <=0)
               {
                    x=x+1;
                    y=y-1;
                    dk = dk + 2*x - 2*y +2;
               }
               else
               {
                    y=y-1;
                    dk = dk -2y + 1;
               }
          }
          
          else if(dk==0)
          {
               x=x+1;
               y=y-1;
               dk=dk + 2*x -2*y +2;
          }
     }
}
                
                 

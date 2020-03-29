#include <stdio.h>
#include <GL/glut.h>
//#include <GL/freeglut.h>
#define inf 1000000


 double x1;
 double x2;
 double y;
 double y2;
 double dashsize;
 double dashgaps;


void init1() {
 glOrtho(-200, 200, -200, 200, -200, 200);
 x1 = 0;
 x2 = 100;
 y = 0;
 y2 = 100;
 dashsize = 10;
 dashgaps = 10;
}

void func1() {
 glClearColor(0, 0, 0, 0);
 glClear(GL_COLOR_BUFFER_BIT);
 glColor3f(1, 1, 1);
 glBegin(GL_POINTS);
 double k1 = 0;
 double k2 = 0;
 int istrue = 1;

 while (x1 <= x2) {
  if (istrue) {
   glVertex2f(x1, y);
   x1++;
   y++;
   k1++;
  }
  else {
   x1++;
   y++;
   k2++;
  }
  if (k1 >= dashsize) {
   k1 = 0;
   istrue = 0;
  }
  if (k2 >= dashgaps) {
   istrue = 1;
   k2 = 0;
  }
 }
 glEnd();
 glFlush();
}

int main(int argc, char **argv) {
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_SINGLE);
 glutInitWindowSize(500, 500);
 glutInitWindowPosition(50, 50);
 glutCreateWindow("hello world");
 glutDisplayFunc(func1);
 init1();
 glutMainLoop();
 return 0;
}

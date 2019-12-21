#include<GL/glut.h>
#include"draw.hpp"

vp2D vec2D;
vp2D v;

void displayPoint(void){
  glColor3f (1.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_POLYGON);
    for(auto &p : v)
      glVertex2fv(p.get().data());
  glEnd();
  glColor3f (0.0, 0.0, 0.0);
  glBegin(GL_POINTS);
    glVertex2i(25,25);
  glEnd();
  glBegin(GL_LINE_LOOP);
    for(auto &p : vec2D)
      glVertex2fv(p.get().data());
  glEnd();
  glFlush();
}

int main(int argc, char** argv){
  glutInit (&argc,argv);
  glutInitWindowPosition (600, 300);
  glutInitDisplayMode (GLUT_SINGLE);
  glutInitWindowSize(640, 640);
  glutCreateWindow ("Ejemplo de OpenGL");
  glClearColor (1.0, 1.0, 1.0, 0.0);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluOrtho2D (-320,320,-320,320);
  Point2D p1(0,0);
  Point2D p2(50,0);
  Point2D p3(50,50);
  Point2D p4(0,50);
  vec2D.push_back(p1);
  vec2D.push_back(p2);
  //vec2D.push_back(p3);
  //vec2D.push_back(p4);
  v = vec2D;
  //traslation(vec2D,50,-50);
  //rotation(vec2D,30);
  //traslation(vec2D,200,100);
  rotation(v,45,Point2D(0,0));
  glutDisplayFunc(displayPoint);
  glutMainLoop ();
  return 0;
}

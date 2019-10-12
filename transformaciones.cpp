#include<GL/glut.h>
#include"draw.hpp"

vp2D vec2D;

void displayPoint(void){
  glColor3f (1.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_LINE_LOOP);
    for(auto &p : vec2D) {
      glVertex2iv(p.get().data());
    }
  glEnd();
  glFlush();
}

int main(int argc, char** argv){
  glutInit (&argc,argv);
  glutInitWindowPosition (400, 300);
  glutInitDisplayMode (GLUT_SINGLE);
  glutInitWindowSize(640, 480);
  glutCreateWindow ("Ejemplo de OpenGL");
  glClearColor (1.0, 1.0, 1.0, 0.0);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluOrtho2D (0,300,0,400);
  Point2D p1(100,100);
  Point2D p2(150,100);
  Point2D p3(150,150);
  Point2D p4(100,150);
  vec2D.push_back(p1);
  vec2D.push_back(p2);
  vec2D.push_back(p3);
  vec2D.push_back(p4);
  //traslation(vec2D,50,-50);
  //rotation(vec2D,30);
  rotation(vec2D,30,Point2D(125,125));
  glutDisplayFunc(displayPoint);
  glutMainLoop ();
  return 0;
}

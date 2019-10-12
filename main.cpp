#include<GL/glut.h>
#include<iostream>
#include"draw.hpp"

vp2D vec2D;
vp3D vec3D;

void displayPoint(void){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glutWireTeapot(100);
  glBegin(GL_POINTS);
    for(auto &p : vec3D) {
      glVertex3iv(p.get().data());
    }
    //glVertex2i(25,17);
  glEnd();
  glFlush();
  glutSwapBuffers();
}

int main(int argc, char** argv){
  glutInit (&argc,argv);
  glutInitWindowPosition (400, 300);
  glutInitWindowSize(640, 480);
  glutInitDisplayMode(GLUT_DOUBLE);
  glutCreateWindow ("Ejemplo de OpenGL");
  //glMatrixMode (GL_PROJECTION);
  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity ();
  //gluOrtho2D (0,50,0,100);
  Point2D p1(1,1);
  Point2D p2(20,15);
  bresenham(1,1,1,10,30,20,vec3D);
  for(auto c:vec3D)
    cout<<c<<endl;
  //lineDDA(1,1,20,15,vec);
  glutDisplayFunc(displayPoint);
    glEnable(GL_DEPTH_TEST);
  glutMainLoop ();
  return 0;
}

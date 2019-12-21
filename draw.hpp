#include<GL/glut.h>
#include<iostream>
#include<cmath>
#include<vector>
#include<array>
#define PI 3.14159265

#define STATIC_ASSERT( e ) static_assert( e, "!(" #e ")" )

using namespace std;

template<typename T, int n>
class Point{
private:
  array<T,n> elements_;
public:
  Point(T x, T y) {
    STATIC_ASSERT( n == 2 );
    elements_[0] = x;
      elements_[1] = y;
  }
  Point(T x, T y, T z) {
    STATIC_ASSERT( n == 3 );
    elements_[0] = x;
    elements_[1] = y;
    elements_[2] = z;
  }
  ~Point() {}
  array<T,n>& get() {return this->elements_;}
  T& operator[](T const i) { return elements_[i];}
  T const& operator[](T const i) const { return elements_[i];}
};

typedef Point<float,2> Point2D;
typedef Point<float,3> Point3D;
typedef vector<Point2D> vp2D;
typedef vector<Point3D> vp3D;

ostream& operator<<(ostream& stream, Point2D const& point) {
  return (stream << "(" << point[0] << ", " << point[1] << ")");
}

ostream& operator<<(ostream& stream, Point3D const& point) {
  return (stream << "(" << point[0] << ", " << point[1] << ", " << point[2] << ")");
}

inline int Round(const float p) { return int (p + 0.5); }

void lineDDA(int x0, int y0, int xEnd, int yEnd, vp2D &line){
  int dx = xEnd - x0, dy = yEnd - y0, k, steps;
  float incX, incY, x = x0, y = y0;

  if( dx > dy )
    steps = dx;
  else
    steps = dy;
  incX = float (dx) / float (steps);
  incY = float (dy) / float (steps);

  line.push_back(Point2D(x,y));
  for( k = 0; k < steps; ++k) {
    x += incX;
    y += incY;
    line.push_back(Point2D(x,y));
  }
}

void bresenham(int x0, int y0, int xEnd, int yEnd, vp2D &line){
  int dx = fabs(xEnd - x0), dy = fabs(yEnd - y0);
  int p = 2*dy-dx;
  int twody = 2*dy, f = 2*(dy-dx);
  int x,y;

  if(x0 > xEnd) {
    x = xEnd;
    y = yEnd;
    xEnd = x0;
  } else {
    x = x0;
    y = y0;
  }

  line.push_back(Point2D(x,y));

  while(x < xEnd) {
    x++;
    if (p < 0)
      p += twody;
    else {
      y++;
      p += f;
    }
    line.push_back(Point2D(x,y));
  }
}

void bresenham(int x0, int y0, int z0, int xEnd, int yEnd, int zEnd, vp3D &line){
  int dx = fabs(xEnd - x0), dy = fabs(yEnd - y0), dz = fabs(zEnd - z0);
  int py = 2*dy - dx;
  int pz = 2*dz - dx;
  int twody = 2*dy, fy = 2*(dy-dx);
  int twodz = 2*dz, fz = 2*(dz-dx);
  int x,y,z;

  if(x0 > xEnd) {
    x = xEnd;
    y = yEnd;
    z = zEnd;
    xEnd = x0;
  } else {
    x = x0;
    y = y0;
    z = z0;
  }

  line.push_back(Point3D(x,y,z));

  while(x < xEnd) {
    x++;
    if (py < 0 && pz < 0) {
      py += twody;
      pz += twodz;
    } else if(py > 0 && pz < 0){
      y++;
      py += fy;
      pz += twodz;
    } else if(py < 0 && pz > 0) {
      z++;
      pz += fz;
      py += twody;
    } else {
      y++;
      z++;
      py += fy;
      pz += fz;
    }
    line.push_back(Point3D(x,y,z));
  }
}

void traslation(vp2D &vertexs, float s1, float s2){
  for(auto &point: vertexs) {
    point[0] += s1;
    point[1] += s2;
  }
}

void rotation(vp2D &vertexs, float angle){
  for(auto &point: vertexs) {
    float x,y;
    x = point[0];
    y = point[1];
    point[0] = x*cos(angle) - y*sin(angle);
    point[1] = x*sin(angle) - x*cos(angle);
  }
}

void rotation(vp2D &vertexs, float angle, const Point2D p){
  for(auto &pts: vertexs){
    float dx = pts[0] - p[0];
    float dy = pts[1] - p[1];
    pts[0] = p[0] + (dx*cos(angle) - dy*sin(angle));
    pts[1] = p[0] + (dx*sin(angle) - dy*cos(angle));
  }
}

void scale(vp2D &vertexs, float sx = 1, float sy = 1){
  for(auto &point: vertexs){
    point[0] *= sx;
    point[1] *= sy;
  }
}

void scale(vp2D &vertexs, Point2D p, float sx = 1, float sy = 1){
  int xc = p[0],yc = p[1];
  for(auto &point: vertexs){
    int x,y;
    x = point[0] - xc;
    y = point[1] - yc;
    point[0] = xc + sx*x;
    point[1] = yc + sy*y;
  }
}

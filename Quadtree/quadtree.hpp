typedef int coordinates;
class Point{
  public:
    coordinates x;
    coordinates y;
    Point(): x(0), y(0) {}
    Point(coordinates _x, coordinates _y): x(_x), y(_y) {}
    void setPoint(coordinates a, coordinates b);
    coordinates getX();
    coordinates getY();
};
void Point::setPoint(coordinates a, coordinates b){
  x = a;
  y = b;
}
coordinates Point::getX() {return x;}
coordinates Point::getY() {return y;}

////////////////////////////////////////////////////////////////////////
#include<iostream>
using namespace std;

typedef double intensity;

class rgb{
public:
  intensity r;
  intensity g;
  intensity b;
  rgb(intensity R, intensity G, intensity B): r(R),g(G),b(B){}
  rgb() {}
  rgb(rgb& o): r(o.r), g(o.g), b(o.b) {}
  friend rgb operator+(rgb& o, rgb &p){
    rgb aux;
    aux.r = o.r + p.r;
    aux.g = o.r + p.g;
    aux.b = o.r + p.b;
    return aux;
  }
  friend rgb operator*(rgb& o, rgb &p){
    rgb aux;
    aux.r = o.r * p.r;
    aux.g = o.r * p.g;
    aux.b = o.r * p.b;
    return aux;
  }
  friend rgb operator/(rgb& o, double p){
    rgb aux;
    aux.r = o.r / p;
    aux.g = o.r / p;
    aux.b = o.r / p;
    return aux;
  }
};

static double threshold = 2.50;

template<class Data>
class qNode{
  public:
    int full;
    qNode<Data>* m_child[4];
    qNode<Data>* father;
    Data *m_data;
    Point pointA;
    Point pointB;
    // PointA in this case is the leftmost upper point in that rectangule
    // PointB in this case thus is the rightmost most down point in that rectangule
    qNode(Point a, Point b): father(0), full(0), m_data(0), pointA(a), pointB(b) {for(int i = 0; i< 4; ++i) this->m_child[i] = 0;}
    qNode(Data d, Point a, Point b): full(0), m_data(new Data(d)), pointA(a), pointB(b) {for(int i = 0; i< 4; ++i) this->m_child[i] = 0;}
    qNode(Data d, Point a, Point b, qNode<Data>* f): father(f), full(0), m_data(new Data(d)), pointA(a), pointB(b) {for(int i = 0; i< 4; ++i) this->m_child[i] = 0;}
    void setData(Data d) {m_data = new Data(d);}
    ~qNode(){
      for(int i = 0; i < 4; ++i)
        delete m_child[i];
    }
    void insert(Point p, Data pixel){
      if (abs(pointA.x - pointB.x) <= 1 && abs(pointA.y - pointB.y) <= 1){
        if (m_data == NULL){
          m_data = new Data(pixel);
          this->father->full++;
          qNode<Data>* n = this->father;
          while(n && n->full == 4){
            if(variance(n) > threshold)
              reduction(n);
            n = n->father;
          }
        }
        return;
      }
      if ((pointA.x + pointB.x) / 2 >= p.x){
        if ((pointA.y + pointB.y) / 2 >= p.y){
          if (m_child[0] == NULL)
            m_child[0]  = new qNode(Point(pointA.x, pointA.y),Point((pointA.x + pointB.x)/2,(pointA.y + pointB.y)/2),this);
          m_child[0]->insert(p,pixel);
        }
        else{
          if (m_child[2] == NULL)
            m_child[2] = new qNode(Point(pointA.x,(pointA.y + pointB.y)/2),Point((pointA.x + pointB.x)/2, pointB.y),this);
          m_child[2]->insert(p,pixel);
        }
      }
      else{
        if ((pointA.y + pointB.y) / 2 >= p.y){
          if (m_child[1] == NULL)
            m_child[1] = new qNode(Point((pointA.x + pointB.x)/2, pointA.y),Point(pointB.x,(pointA.y + pointB.y)/2),this);
          m_child[1]->insert(p,pixel);
        }
        else{
          if (m_child[3] == NULL)
            m_child[3] = new qNode(Point((pointA.x + pointB.x)/2,(pointA.y + pointB.y)/2),Point(pointB.x, pointB.y),this);
          m_child[3]->insert(p,pixel);
        }
      }
    }
    bool search(Point p, Data& d){
      if (this->m_data != NULL){
        cout<<"Found!"<<endl;
        return true;
      }
      if ((pointA.x + pointB.x)/2 >= p.x){
        if ((pointA.y + pointB.y)/2 >= p.y){
          if (m_child[0] == NULL)
            return false;
          return m_child[0]>search(p);
        }
        else{
          if (m_child[2] == NULL)
            return false;
          return m_child[2]->search(p);
        }
      }
      else{
        if ((pointA.y + pointB.y) / 2 >= p.y){
          if (m_child[1] == NULL)
            return false;
          return m_child[1]->search(p);
        }
        else{
          if (m_child[3] == NULL)
            return false;
          return m_child[3]->search(p);
        }
      }
    }
    bool limit(Point p){
      return (p.x >= pointA.x && p.x <= pointB.x && p.y >= pointA.y && p.y <= pointB.y);
    }
    bool isfull(){ return (full >= 4) ? true : false;}
  private:
    void reduction(qNode<Data>* p){
      rgb aux;
      for(auto &c : p->m_child)
        aux += c.m_data;
      p->father->m_data = aux/4;
      if(p->father)
        p->father->full++;
      return;
    }
    double variance(qNode<Data>* p){
      Data expc;
      for(auto c : p->m_child){
        expc += c->m_data;
      }
      double varz_r=expc.r,varz_g=expc.r,varz_b=expc.b;
      double r=0,g=0,b=0;
      for(int i = 1; i <= 4; ++i){
        double auxr = i - varz_r;
        double auxg = i - varz_g;
        double auxb = i - varz_b;
        r += auxr*auxr;
        g += auxg*auxg;
        b += auxb*auxb;
      }
      return (r+g+b)/12;
    }
};

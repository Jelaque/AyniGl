#include"CImg.h"
#include"quadtree.hpp"
#include<iostream>
using namespace std;
typedef unsigned char uchar;
using namespace cimg_library;

int main(){
  CImg<uchar> src("lena.png");
  int width = src.width();
  int height = src.height();
  cout << width << "x" << height << endl;
  qNode<rgb>* root = new qNode<rgb>(Point(0,height),Point(width,0));
  for (int r = 0; r < height; r++){
    for (int c = 0; c < width; c++){
      rgb color((int)src(c,r,0,0),(int)src(c,r,0,1),(int)src(c,r,0,2));
      root->insert(Point(c,r), color);
      cout << "(" << r << "," << c << ") =" << " R" << (int)src(c,r,0,0) << " G" << (int)src(c,r,0,1) << " B" << (int)src(c,r,0,2) << endl;
    }
  }
  CImg<uchar> src2 = src;
  //CImgDisplay display(src,"Lena");
  //while(!display.is_closed()) display.wait();

  return 0;
}

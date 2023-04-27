#include "Image.hpp"
#include <vector>
using namespace std;

namespace prog{
  
  //constructor -> image with width w, height h and all pixels set to color fill
  Image::Image(int w, int h, const Color &fill){
    
    width_ = w;
    height_ = h;
    for (int y = 0; y < height_; y ++){ //range of values of y needed
      vector< Color > new_line;
      for (int x = 0; x < width_; x++){ //range of values of x needed
        new_line.push_back(fill);       //default value alocated in position (x,y) (line y)
      }
      pixels_.push_back(new_line);      //line created previously is alocated in the matrix
    }
  }

  //destructor -> not needed in this case (no dynamically allocated memory used explicitly)
  Image::~Image(){
  }

  //getters' implementation (width and heigth)
  int Image::width() const{
    return width_;
  }
  int Image::height() const{
    return height_;
  }

  //mutable reference to the values of pixel (x,y)
  Color& Image::at(int x, int y){
    return pixels_[y][x];
  }

  //read-only reference to the value of pixel (x,y)
  const Color& Image::at(int x, int y) const{
    return pixels_[y][x];
  }
}

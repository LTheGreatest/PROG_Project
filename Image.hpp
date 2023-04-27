#ifndef __prog_Image_hpp__
#define __prog_Image_hpp__
#include "Color.hpp"
#include <vector>

namespace prog{
  
  class Image{
    
    private:
      int width_, height_;
      std::vector<std::vector<Color>> pixels_;  //2d vector represents the pixels in the image
    public:
      Image(int w, int h, const Color &fill = {255, 255, 255});
      ~Image(); //destructor
      //getters
      int width() const;
      int height() const;
      Color &at(int x, int y);
      const Color &at(int x, int y) const;
  };
}

#endif

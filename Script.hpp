#ifndef __prog_Script_hpp__
#define __prog_Script_hpp__
#include <string>
#include <fstream>
#include "Image.hpp"

namespace prog{
  
  class Script{
    
    public: 
      Script(const std::string &filename);
      ~Script(); //destructor
      void run();

      //image manipulations (dimensions are not altered)
      void invert();
      void to_gray_scale();
      void replace(const Color &rgb1, const Color &rgb2);
      void fill(int x, int y, int w, int h, const Color &other);
      void h_mirror();
      void v_mirror();
      void add(const std::string &filename, const Color &other, int x, int y);
      //dimension-changing operations
      void crop(int x, int y, int w, int h);
      void rotate_left();
      void rotate_right();
    private:
      Image *image; //current image
      std::ifstream input; //input stream for reading script commands
    private:
      // Private functions
      void clear_image_if_any();
      void open();
      void blank();
      void save();
  };
}

#endif

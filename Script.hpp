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
      //commands for simple image manipulations (image dimensions are not altered)
      void invert();
      void to_gray_scale();
      void replace(const Color &rgb1, const Color &rgb2);
      void fill(int x, int y, int w, int h, const Color &other);
      void h_mirror();
      void v_mirror();
      void add(const std::string &filename, const Color &other, int x, int y);
      //commands for dimension-changing operations
      void crop(int x, int y, int w, int h);
      void rotate_left();
      void rotate_right();
      //Advanced functionality
      void median_filter(int ws);
    private:
      Image *image; //current image
      std::ifstream input; //input stream for reading script commands
    private:
      //private functions
      void clear_image_if_any();
      //commands for initialization and I/O
      void open();
      void blank();
      void save();
  };
}

#endif

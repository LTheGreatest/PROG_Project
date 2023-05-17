#ifndef __prog_Color_hpp__
#define __prog_Color_hpp__

namespace prog{
  
  typedef unsigned char rgb_value;
  class Color{
    friend bool operator<(const Color& a, const Color& b);
    private:
      rgb_value green_, blue_, red_;
    public:
      Color(); 
      Color(const Color& c);
      Color(rgb_value r, rgb_value g, rgb_value b);
      //getters for individual RGB color channels + mutable references for individual RGB color channels
      rgb_value red() const;
      rgb_value& red();
      rgb_value green() const;
      rgb_value& green();
      rgb_value blue() const;
      rgb_value& blue();
  };
}

#endif

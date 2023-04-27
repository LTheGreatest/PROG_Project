#include "Color.hpp"

namespace prog {

    //default contructor (default color is black)
    Color::Color() {
        red_ = blue_ = green_ = 0;
    }

    //copy constructor
    Color::Color(const Color& other) {
        this->red_ = other.red_;
        this->blue_ = other.blue_;
        this->green_ = other.green_;
    }

    //constructor using supplied values
    Color::Color(rgb_value red, rgb_value green, rgb_value blue) {
        red_ = red;
        green_ = green;
        blue_ = blue;
    }

    //getters implementantion (red, green and blue)
    rgb_value Color::red() const {
        return red_;
    }
    rgb_value Color::green() const {
        return green_;
    }
    rgb_value Color::blue() const {
        return blue_;
    }

    //mutable references to individual RGB color channels
    rgb_value& Color::red()  {
        return red_;
    }
    rgb_value& Color::green()  {
      return green_;
    }
    rgb_value& Color::blue()  {
      return blue_;
    }


    //auxiliary variables 
    const Color Color::RED (255,0, 0);
    const Color Color::GREEN(0, 255, 0);
    const Color Color::BLUE(0, 0, 255);
    const Color Color::WHITE(255, 255, 255);
    const Color Color::BLACK(0, 0, 0);
}

#ifndef __prog_XPM2_hpp__
#define __prog_XPM2_hpp__
#include <string>
#include "Image.hpp"

namespace prog {
    unsigned long value(const char c1);
    Color hexatocolor(const std::string& hexadecimal);
    std::string colortohexa(const Color& rgb);
    Image* loadFromXPM2(const std::string& file);
    void saveToXPM2(const std::string& file, const Image* img);
}
#endif

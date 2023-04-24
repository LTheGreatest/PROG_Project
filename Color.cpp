Color::Color(unsigned char red, unsigned char green, unsigned char blue){
        red_ = red;
        green_ = green;
        blue_ = blue;
}
Color::Color(const Color& c) : red_(c.red_), green_(c.green_), blue_(c.blue_){}
const Color Color::RED(255,0,0);
const Color Color::GREEN(0,255,0);
const Color Color::BLUE(0,0,255);
const Color Color::BLACK(0,0,0);
const Color Color::WHITE(255,255,255);
unsigned char Color::red() const{
    return red_;
}
unsigned char Color::green() const{
    return green_;
}
unsigned char Color::blue() const{
    return blue_;
}

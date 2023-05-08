#include "XPM2.hpp"
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;
namespace prog {
    unsigned long value(const char c1){
        unsigned long v;
        if (c1 >= '0' && c1 <= '9') {
            v = c1 - '0';
        } 
        else if (c1 >= 'A' && c1 <= 'F') {
            v = c1 + 10 - 'A';
        }
        else {
            v = c1 + 10 - 'a';
        }
        return v;
    }
    Color hexatocolor(const string& hexadecimal){
        unsigned long r,g,b;
        istringstream in(hexadecimal);
        char c1,c2,c3,c4,c5,c6;
        in >> c1; // "#""
        in >> c1 >> c2 >> c3 >> c4 >> c5;
        if (in >> c6)in >> c6;
        else c6 = '0';
        r = value(c1)*16 + value(c2); //pass them to int values
        g = value(c3)*16 + value(c4);
        b = value(c5)*16 + value(c6);
        return Color(r,g,b);  //create a color with them
    }
    Image* loadFromXPM2(const string& file){
        int w,h,n,c;
        char character,dummy;
        string hexa;
        ifstream in(file);
        string line;
        getline(in,line);   // "! XPM2"
        getline(in,line);   // line with the width, height, number of colors and char per color = 1
        istringstream iss(line);
        iss >> w >> h >> n >> c;
        Image* image = new Image(w, h);  //Image at full white
        std::map<char,Color> colordict;  //create a map for each character what color to use
        while (n>0){    
            getline(in,line);       //fill the map
            istringstream iss(line);
            iss>>character>>dummy>>hexa;
            colordict[character] = hexatocolor(hexa);
            n--;
        }
        int y=0;
        while (getline(in,line) and y<h){
            int x = 0;
            for (char c : line){
                if (x==w) break;
                image->at(x,y) = colordict[c];
                x++;
            }
            y++;
        }
        return image;
    }

    void saveToXPM2(const std::string& file, const Image* image) {

    }
}

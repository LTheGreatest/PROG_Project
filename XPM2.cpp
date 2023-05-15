#include "XPM2.hpp"
#include <iostream>
#include <iomanip>
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
        char c1, c2, c3, c4, c5, c6;
        in >> c1; // "#""
        in >> c1 >> c2 >> c3 >> c4 >> c5 >> c6;
        r = value(c1) * 16 + value(c2); //pass them to int values
        g = value(c3) * 16 + value(c4);
        b = value(c5) * 16 + value(c6);
        return Color(r, g, b);  //create a color with them
    }

    string colortohexa(const Color& rgb){
        string hexa;
        hexa.push_back('#'); //insert "#" at the begining
        string s1, s2, s3;
        int red = rgb.red();
        int green = rgb.green();
        int blue = rgb.blue();
        //convert red
        ostringstream out1;
        out1 << setfill('0') << setw(2) << hex << red;
        s1 = out1.str();
        //convert green
        ostringstream out2;
        out2 << setfill('0') << setw(2) << hex << green;
        s2 = out2.str();
        //convert blue
        ostringstream out3;
        out3 << setfill('0') << setw(2) << hex << blue;
        s3 = out3.str();
        //append the values
        hexa.append(s1);
        hexa.append(s2);
        hexa.append(s3);
        return hexa;
    }
    
    Image* loadFromXPM2(const string& file){
        int w, h, n, c;
        char character, dummy;
        string hexa;
        ifstream in(file);
        string line;
        getline(in, line);   //"! XPM2"
        getline(in, line);   //line with the width, height, number of colors and char per color = 1
        istringstream iss(line);
        iss >> w >> h >> n >> c;
        Image* image = new Image(w, h);  //image at full white
        std::map<char,Color> colordict;  //create a map for each character what color to use
        while (n > 0){    
            getline(in, line);       //fill the map
            istringstream iss(line);
            iss >> character >> dummy >> hexa;
            colordict[character] = hexatocolor(hexa);
            n--;
        }
        int y = 0;
        while(getline(in, line) and y < h){
            int x = 0;
            for (char c : line){
                if (x == w) break;
                image->at(x, y) = colordict[c];
                x++;
            }
            y++;
        }
        return image;
    }

    void saveToXPM2(const std::string& file, const Image* image){
        ofstream out(file);
        out << "! XMP2" << "\n";
        int w, h, n, c = 1;
        w = image->width();
        h = image->height();
        //characters used to encode colors (16 colors) 
        vector<char> color_char {
            'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 
            'i', 'j', 'k', 'l', 'm','n', 'o', 'p'
        };
       map <Color,char> colordict; //operator< implemented for Color (more info Color.cpp)
        //find number of different colors
        int idx = 0; //auxiliary value used to acess color_char and store number of colors used
        for (int y = 0; y < h; y++){
            for (int x = 0; x < w; x++){
                auto search = colordict.find(image->at(x,y));
                if(search == colordict.end()){
                    colordict.insert({image->at(x,y), color_char[idx]});
                    idx++;
                }
            }
        }
        n = idx; //idx has the number of colors used
        out << w << ' '<< h << ' ' << n << ' ' << c <<'\n';
        // fill lines with char/color encoding
        for (auto i = colordict.begin(); i != colordict.end(); i++){
            char character = i->second;
            string hexa = colortohexa(i->first); 
            out << character << ' ' << 'c' << ' ' << hexa << '\n';
        }
        // fill lines with characters
        for(int y = 0; y < h; y++){
            for(int x = 0; x < w; x++){
                out << colordict[image->at(x,y)];
            }
            out << '\n';
        }
    }
}

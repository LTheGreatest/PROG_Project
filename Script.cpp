#include <iostream>
#include <fstream>
#include "Script.hpp"
#include "PNG.hpp"
#include "XPM2.hpp"
using namespace std;

namespace prog{
    //used to read color values from a script file
    istream& operator>>(istream& input, Color& c){
        int r, g, b;
        input >> r >> g >> b;
        c.red() = r;
        c.green() = g;
        c.blue() = b;
        return input;
    }

    Script::Script(const string& filename) :
            image(nullptr), input(filename){
    }
    void Script::clear_image_if_any(){
        if (image != nullptr){
            delete image;
            image = nullptr;
        }
    }
    Script::~Script(){
        clear_image_if_any();
    }

    void Script::run(){
        string command;
        while (input >> command){
            cout << "Executing command '" << command << "' ..." << endl;
            if (command == "open"){
                open();
                continue;
            }
            if (command == "blank"){
                blank();
                continue;
            }
            //other commands require an image to be previously loaded
            if (command == "save"){
                save();
                continue;
            }
            //commands for simple image manipulations 
            if (command == "invert"){
                invert();
                continue;
            }
            if(command == "to_gray_scale"){
                to_gray_scale();
                continue;
            }
            if (command == "fill"){
                int x, y, h, w;
                Color other;
                input >> x >> y >> w >> h >> other;
                fill(x, y, w, h, other);
                continue;
            }
            if (command == "add"){
                string filename;
                Color other;
                int x,y;
                input >> filename >> other >> x >> y;
                add(filename, other, x,  y);
                continue;
            }
            //commands for dimension-changing operations
            if(command == "crop"){
                int x, y, w, h;
                input >> x >> y >> w >> h;
                crop(x, y, w, h);
                continue;
            }
            if(command == "rotate_left"){
                rotate_left();
                continue;
            }
            if(command == "rotate_right"){
                rotate_right();
                continue;
            }
        }
    }
    void Script::open(){
        //replace current image (if any) with image read from PNG file
        clear_image_if_any();
        string filename;
        input >> filename;
        image = loadFromPNG(filename);
    }
    void Script::blank(){
        //replace current image (if any) with blank image
        clear_image_if_any();
        int w, h;
        Color fill;
        input >> w >> h >> fill;
        image = new Image(w, h, fill);
    }
    void Script::save(){
        //save current image to PNG file
        string filename;
        input >> filename;
        saveToPNG(filename, image);
    }

    //simple image manipulations (image dimensions are not altered): -----------

    void Script::invert(){
        //transforms each individual pixel (r, g, b) to (255 - r, 255 - g, 255 - b)
        int height = image->height();
        int width = image->width();
        for (int y = 0; y < height; y++){
            for (int x = 0; x < width; x++){
                Color new_pixel = image->at(x, y);
                new_pixel.blue() = 255 - new_pixel.blue();
                new_pixel.red() = 255 - new_pixel.red();
                new_pixel.green() = 255 - new_pixel.green();
                image->at(x, y) = new_pixel;
            }
        }
    }

    void Script::to_gray_scale(){
        //transforms each individual pixel (r, g, b) to (v, v, v)
        //v = (r + g + b) / 3
        int height = image->height();
        int width = image->width();
        for (int y = 0; y < height; y++){
            for (int x = 0; x < width; x++){
                int blue = image->at(x, y).blue();
                int red = image->at(x, y).red();
                int green = image->at(x, y).green();
                int v = (blue + green + red) / 3;
                image->at(x, y).blue() = v;
                image->at(x, y).red() = v;
                image->at(x, y).green() = v;
            }
        }
    }
    
    void Script::replace(const Color &rgb1, const Color &rgb2){
        //replaces all (r1, g1, b1) pixels by (r2,  g2, b2)
        if (image->at(x, y) == rgb1){
            int height = image->height();
            int width = image->width();
            for (int yy = y; yy < height; yy++){
                for (int xx = x; xx < width; xx++){
                    image->at(xx, yy).blue() = rgb2.blue();
                    image->at(xx, yy).green() = rgb2.green();
                    image->at(xx, yy).red() = rgb2.red();
                }    
            }
        }
    }
        
    void Script::fill(int x, int y, int w, int h, const Color &other){
        //for each pixel in the rectangle switch to the "other" Color"
        for (int line = y; line < y + h; line++){
            for(int col = x; col < x + w; col++){
                image->at(col, line).blue() = other.blue();
                image->at(col, line).red() = other.red();
                image->at(col, line).green() = other.green();
            }
        }
    }
    
    void Script::h_mirror{
        //mirror image horizontally
        int height = image->height();
        int width = image->width();
        for (int y = 0; y < height; y++){
            for (int x = 0; x < width / 2; x++){
                image->at(x, y) = image->at(width() - 1 - x, y);
            }
        }
    }
        
    void Script::v_miror{
        //mirror image vertically
        int height = image->height();
        int width = image->width();
        for (int y = 0; y < height / 2; y++){
            for (int x = 0; x < width; x++){
                image->at(x, y) = image->at(x, height() - 1 - y);
            }
        }
    }
    
    void Script::add(const std::string &filename, const Color &other, int x, int y){
        //get the image inside of the file
        Image *copy;
        copy = loadFromPNG(filename);
        //only get the pixels that are not "neutral"
        for (int line = 0 ; line < copy->height(); line++){    
            for (int col = 0 ; col < copy->width(); col++){
                if (copy->at(col, line).red() == other.red() and copy->at(col, line).blue() == other.blue() and copy->at(col, line).green() == other.green());
                else  image->at(x + col, y + line) = copy->at(col, line);
            }
        }
        //delete the created image from the file to avoid memory leaks
        delete copy;
    }

    //dimension-changing operations: -----------

    void Script::crop(int x, int y, int w, int h){
        //reduce the image to all pixels contained in the rectangle
        //define by top-left corner (x, y), width w and height h
         Image new_image(w ,h);
         for(int yy = y; yy < y + h; yy++){
             for(int xx = x; xx < x + w; xx++){
              new_image.at(xx - x,yy - y) = image->at(xx, yy);
            }
        }
        *image = new_image;
    }

    void Script::rotate_left(){
        //rotate image right by 90 degrees
        Image new_image(image->height(), image->width()); //height = current image width | width = curret image height
        int h = new_image.height();
        int w = new_image.width();
        for(int x = 0; x < w; x++){
            for(int y = 0; y < h; y++){
                new_image.at(x, y) = image->at(h - y - 1, x); 
            }
        }
        *image = new_image;
    }

    void Script::rotate_right(){
        //rotate image right by 90 degrees
        Image new_image(image->height(), image->width()); //height = current image width | width = curret image height
        int h = new_image.height();
        int w = new_image.width();
        for(int x = 0; x < w; x++){
            for(int y = 0; y < h; y++){
                new_image.at(x, y) = image->at(y, w - x - 1);
            }
        }
        *image = new_image;
    }  
}

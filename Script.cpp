#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
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
            if(command == "replace"){
                Color a, b;
                input >> a >> b;
                replace(a, b);
                continue;
            }
            if (command == "fill"){
                int x, y, h, w;
                Color other;
                input >> x >> y >> w >> h >> other;
                fill(x, y, w, h, other);
                continue;
            }
            if(command == "h_mirror"){
                h_mirror();
                continue;
            }
            if(command == "v_mirror"){
                v_mirror();
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
            //commands for advanced functionality
            if(command == "median_filter"){
                int ws;
                input >> ws;
                median_filter(ws);
                continue;
            }
            if (command == "xpm2_open"){
                xpm2_open();
                continue;
            }
            if(command == "xpm2_save"){
                xpm2_save();
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

    //simple image manipulations (image dimensions are not altered): ---------------------

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
        int height = image->height();
        int width = image->width();
        for (int y = 0; y < height; y++){
            for (int x = 0; x < width; x++){
                if(image->at(x, y).blue() == rgb1.blue() && image->at(x, y).green() == rgb1.green() && image->at(x, y).red() == rgb1.red()){
                    image->at(x, y).blue() = rgb2.blue();
                    image->at(x, y).green() = rgb2.green();
                    image->at(x, y).red() = rgb2.red();
                }
            }    
        }
    }
        
    void Script::fill(int x, int y, int w, int h, const Color &other){
        //for each pixel in the rectangle switch to the "other" Color
        for (int line = y; line < y + h; line++){
            for(int col = x; col < x + w; col++){
                image->at(col, line).blue() = other.blue();
                image->at(col, line).red() = other.red();
                image->at(col, line).green() = other.green();
            }
        }
    }
    
    void Script::h_mirror(){
        //mirror image horizontally
        Color aux;
        int height = image->height();
        int width = image->width();
        for (int y = 0; y < height; y++){
            for (int x = 0; x < width / 2; x++){
                aux = image->at(width - 1 - x, y);
                image->at(width - 1 - x, y) = image->at(x, y);
                image->at(x, y) = aux;
            }
        }
    }
        
    void Script::v_mirror(){
        //mirror image vertically
        Color aux;
        int height = image->height();
        int width = image->width();
        for (int y = 0; y < height / 2; y++){
            for (int x = 0; x < width; x++){
                aux = image->at(x, height - 1 - y);
                image->at(x,height - 1 - y) = image->at(x,y);
                image->at(x,y) = aux;
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
                if (copy->at(col, line).red() == other.red() and copy->at(col, line).blue() == other.blue() and copy->at(col, line).green() == other.green())
                    continue;
                else  image->at(x + col, y + line) = copy->at(col, line);
            }
        }
        //delete the created image from the file to avoid memory leaks
        delete copy;
    }

    //dimension-changing operations: ---------------------

    void Script::crop(int x, int y, int w, int h){
        //reduce the image to all pixels contained in the rectangle
        //define by top-left corner (x, y), width w and height h
         Image new_image(w ,h);
         for(int yy = y; yy < y + h; yy++){
             for(int xx = x; xx < x + w; xx++){
              new_image.at(xx - x, yy - y) = image->at(xx, yy);
            }
        }
        *image = new_image;
    }

    void Script::rotate_left(){
        //rotate image left by 90 degrees
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

    //advanced functionality: ---------------------

    void Script::median_filter(int ws){
        //apply a median filter with window size ws >= 3 to the current image
        int dist = ws / 2;    //neighbours max distance (auxiliary value)
        Image* new_image = new Image(image->width(), image->height());
        //loop through each pixel in the image
        for (int y = 0, len_y = image->height(); y < len_y; y++){
            for (int x = 0, len_x = image->width(); x < len_x; x++){
                //RGB vectors
                vector<rgb_value> red_neighbours;
                vector<rgb_value> blue_neighbours;
                vector<rgb_value> green_neighbours;
                //obtain the neighbouring pixels
                for(int ny = y - dist; ny <= y + dist; ny ++ ){
                    //y bounds
                    if ((ny < 0) || (ny >= len_y))
                        continue;
                    for(int nx = x - dist; nx <= x + dist; nx++){
                        //x bounds
                        if((nx < 0) || (nx >= len_x))
                            continue;
                        //add the RGB values of the neighbor pixels to their respective vectors
                        red_neighbours.push_back(image->at(nx, ny).red());
                        blue_neighbours.push_back(image->at(nx, ny).blue());
                        green_neighbours.push_back(image->at(nx, ny).green());
                    }
                }
                //sort neighboring pixels RGB values
                sort(red_neighbours.begin(), red_neighbours.end());
                sort(blue_neighbours.begin(), blue_neighbours.end());
                sort(green_neighbours.begin(), green_neighbours.end());
                if (red_neighbours.size() % 2 == 0){
                    //median pixels when number of neighbours is even
                    int red = (red_neighbours[red_neighbours.size() / 2] +  red_neighbours[red_neighbours.size() / 2 - 1]) / 2;
                    int blue = (blue_neighbours[blue_neighbours.size() / 2] +  blue_neighbours[blue_neighbours.size() / 2 - 1]) / 2;
                    int green = (green_neighbours[green_neighbours.size() / 2] +  green_neighbours[green_neighbours.size() / 2 - 1]) / 2;
                    new_image->at(x, y).red() = red;
                    new_image->at(x, y).blue() = blue;
                    new_image->at(x, y).green() = green;
                }
                else{
                    //median pixels when number of neighbours is odd
                    new_image->at(x, y).red() = red_neighbours[red_neighbours.size() / 2];
                    new_image->at(x, y).blue() = blue_neighbours[blue_neighbours.size() / 2];
                    new_image->at(x, y).green() = green_neighbours[green_neighbours.size() / 2];
                }
            }
        }
        //replace the original image with the new image
        *image = *new_image;
        delete new_image;
    }
    
    void Script::xpm2_open(){
        //read image stored in the XPM2 file format
        //calls Image *loadFromXPM2
        clear_image_if_any();
        string filename;
        input >> filename;
        image = loadFromXPM2(filename);
    }
    
    void Script::xpm2_save(){
        //save image to XPM2 file format
        //calls void saveToXPM2
        string filename;
        input >> filename;
        saveToXPM2(filename, image);
    } 
}

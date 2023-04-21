#include <iostream>
#include <fstream>
#include <sstream>
#include "Script.hpp"
#include "PNG.hpp"
#include "XPM2.hpp"

using namespace std;

namespace prog {
    // Use to read color values from a script file.
    istream& operator>>(istream& input, Color& c) {
        int r, g, b;
        input >> r >> g >> b;
        c.red() = r;
        c.green() = g;
        c.blue() = b;
        return input;
    }

    Script::Script(const string& filename) :
            image(nullptr), input(filename) {

    }
    void Script::clear_image_if_any() {
        if (image != nullptr) {
            delete image;
            image = nullptr;
        }
    }

    Script::~Script() {
        clear_image_if_any();
    }

    unsigned char convertToUChar(string s){ // auxiliar function that converts string to unsigned char
        return static_cast<unsigned char>(stoi(s));
    }

    void Script::run() {
        string command;
        while (input >> command) {
            cout << "Executing command '" << command << "' ..." << endl;
            if (command == "open") {
                open();
                continue;
            }
            if (command == "blank") {
                blank();
                continue;
            }
            // Other commands require an image to be previously loaded.
            if (command == "save") {
                save();
                continue;
            } 

            if (command == "invert"){
                invert();
                continue;
            }

            if (command == "to_gray_scale"){
                to_gray_scale();
                continue;
            }

            if(command == "replace"){
                // need to use strings because we are getting the values from the .txt file
                string s_r1, s_g1, s_b1, s_r2, s_g2, s_b2;
                input >> s_r1 >> s_g1 >> s_b1 >> s_r2 >> s_g2 >> s_b2;

                // convert strings to unsigned char's
                rgb_value r1, g1, b1, r2, g2, b2;
                r1 = convertToUChar(s_r1);
                g1 = convertToUChar(s_g1);
                b1 = convertToUChar(s_b1);
                r2 = convertToUChar(s_r2);
                g2 = convertToUChar(s_g2);
                b2 = convertToUChar(s_b2);
                
                replace(r1, g1, b1, r2, g2, b2);
                continue;
            }

            // TODO por aqui o nome das funções que é para dar run
        }
    }
    void Script::open() {
        // Replace current image (if any) with image read from PNG file.
        clear_image_if_any();
        string filename;
        input >> filename;
        image = loadFromPNG(filename);
    }
    void Script::blank() {
        // Replace current image (if any) with blank image.
        clear_image_if_any();
        int w, h;
        Color fill;
        input >> w >> h >> fill;
        image = new Image(w, h, fill);
    }
    void Script::save() {
        // Save current image to PNG file.
        string filename;
        input >> filename;
        saveToPNG(filename, image);
    }

    void Script::invert(){ // calls to invert function with image object
        image->invert();
    }

    void Script::to_gray_scale(){ // calls to to_gray_scale function with image object
        image->to_gray_scale();
    }

    void Script::replace(rgb_value r1, rgb_value g1, rgb_value b1, rgb_value r2, rgb_value g2, rgb_value b2){
        image->replace(r1, g1, b1, r2, g2, b2);
    }
}

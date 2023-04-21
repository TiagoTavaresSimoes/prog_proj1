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
                // need to use ints because with unsigned chars each of these variables would be a single char in the .txt instead of the 
                // whole number
                int i_r1, i_g1, i_b1, i_r2, i_g2, i_b2;
                input >> i_r1 >> i_g1 >> i_b1 >> i_r2 >> i_g2 >> i_b2;

                // convert integers to unsigned chars
                rgb_value r1, g1, b1, r2, g2, b2;
                r1 = static_cast<unsigned char>(i_r1);
                g1 = static_cast<unsigned char>(i_g1);
                b1 = static_cast<unsigned char>(i_b1);
                r2 = static_cast<unsigned char>(i_r2);
                g2 = static_cast<unsigned char>(i_g2);
                b2 = static_cast<unsigned char>(i_b2);
                
                replace(r1, g1, b1, r2, g2, b2);
                continue;
            }

            if(command == "fill"){
                int x, y, w, h, i_r1, i_g1, i_b1;
                input >> x >> y >> w >> h >> i_r1 >> i_g1 >> i_b1;

                rgb_value r1, g1, b1;
                r1 = static_cast<unsigned char>(i_r1);
                g1 = static_cast<unsigned char>(i_g1);
                b1 = static_cast<unsigned char>(i_b1);

                fill(x, y, w, h, r1, g1, b1);
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

    void Script::replace(rgb_value r1, rgb_value g1, rgb_value b1, rgb_value r2, rgb_value g2, rgb_value b2){ // calls to replace function with image object
        image->replace(r1, g1, b1, r2, g2, b2);
    }

    void Script::fill(int x, int y, int w, int h, rgb_value r, rgb_value g, rgb_value b){
        image->fill(x, y, w, h, r, g, b);
    }
}

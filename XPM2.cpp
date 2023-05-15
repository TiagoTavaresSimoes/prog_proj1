#include "XPM2.hpp"
#include "Color.hpp"
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <iostream>
#include <iomanip>
#include <stdlib.h>

using namespace std;

namespace prog {
    Image* loadFromXPM2(const std::string& file) {
        string line;
        ifstream in(file);
        getline(in, line); // to skip the first line with the xpm header

        getline(in, line); // get the line with width, height and num of colors (char per color can be ignored because it is always 1)
        istringstream iss(line);
        int width, height, n;
        iss >> width >> height >> n;

        map<char, Color> mapCharToColor; // created a map that will map a character to a color
        for(int i = 0; i < n; i++){ // iterate through all the colors
            getline(in, line);
            char symbol, c;
            string hexaColor;
            istringstream iss(line);
            iss >> symbol >> c >> hexaColor;
            vector<int> rgb; // will store red, green, blue values as rgb[0], rgb[1] and rgb[2]

            for(size_t j = 1; j < hexaColor.length() - 1; j += 2){ // ignore first char in hexaColor because it is the '#'
                int tmp = 0;

                if(tolower(hexaColor[j]) >= 'a' && tolower(hexaColor[j]) <= 'f') tmp += (tolower(hexaColor[j]) - 'a' + 10) * 16;
                else tmp += (hexaColor[j] - '0') * 16;

                if(tolower(hexaColor[j + 1]) >= 'a' && tolower(hexaColor[j + 1]) <= 'f') tmp += (tolower(hexaColor[j + 1]) - 'a' + 10);
                else tmp += (hexaColor[j + 1] - '0');

                rgb.push_back(tmp);
            }

            mapCharToColor.insert({symbol, {(rgb_value) rgb[0], (rgb_value) rgb[1], (rgb_value) rgb[2]}});
        }

        Image* xpmImage = new Image(width, height); // create the new image with the xpm width and height
        for(int h = 0; h < height; h++){
            getline(in, line);
            istringstream iss(line);
            char symbol;
            for(int w = 0; w < width; w++){
                iss >> symbol;
                for(auto m : mapCharToColor){
                    if(m.first == symbol){
                        xpmImage->at(w, h) = m.second;
                    }
                }
            }
        }

        return xpmImage;
    }

    

void saveToXPM2(const std::string& file, const Image* image) {
        ofstream save_file(file);

        save_file<< "! XPM2" << endl;//Write the first line in the file
        int height =image->height();//get the height of the image
        int width = image->width();//get the width of the image
        vector<Color> colors;//create a vector to put all the colors that exist in the image
        map<char, string> mapColortoChar; // created a map that will map a char to a hexadecimal color


    for(int w = 0; w < width; w++){ //iterates through all the pixels in the image and save their color
      for(int h = 0; h < height; h++){
        rgb_value r = image->at(w,h).red();
        rgb_value g = image->at(w,h).green();
        rgb_value b = image->at(w,h).blue();
        Color new_color(r,g,b);
        bool found = false;
        if(w==0 && h==0)colors.push_back(new_color);

        for(auto i :colors){
            if(new_color.red()==i.red() && new_color.green()==i.green() && new_color.blue()==i.blue()){found = true; break;}  //if the color already exists in the vector ignores the color
        }
        if(!found) colors.push_back(new_color);//if it reaches the final of the vector and doesn't exist that color pushes it into the vector

      }
    }   

    int total_of_colors=colors.size();//the total of colors that exist in the image is the size of the vector colors

save_file<< width <<' ' << height <<' '<< total_of_colors <<' ' << 1 << endl;//print the second line into the file (w:width ,h:height , total_of_colors: colors existent in the image, 1 = number of chars per color)
    

 for(int i = 0;i<total_of_colors;i++){//for every color transform it in a hexadecimal color form and maps it with the char
    stringstream ss;
    char symbol;
    symbol= i+'a';
    ss << '#'<< setw(2) << setfill('0')<< hex << colors[i].red() << setw(2) << setfill('0')<< hex <<colors[i].green()<< setw(2) << setfill('0')<< hex << colors[i].blue();
    string hexaColor(ss.str());
    mapColortoChar.insert({symbol, hexaColor});

}


 for(int i = 0;i<total_of_colors;i++){//for every color print the respective line
 char used_char;
 used_char=i+'a';
     for(auto m : mapColortoChar){  if(m.first==used_char){
    save_file<<m.first<<' '<<'c' <<' '<<m.second << endl;  
    }      
}
 }
        
for(int w = 0; w < width; w++){// Transforms all the pixels in text
    for(int h = 0; h < height; h++){;
    Color pixel = image->at(w,h);//iterate trough all the pixels int the image
    stringstream ss;

    ss << '#'<< setw(2) << setfill('0')<<  hex << pixel.red() <<  setw(2) << setfill('0')<< hex <<pixel.green()<<  setw(2) << setfill('0')<< hex << pixel.blue();// transfrom the color of the pixel in hexadecimal color
    string pixel_hexaColor(ss.str());
        for(auto m : mapColortoChar){
            if(m.second == pixel_hexaColor){
                    save_file<<m.first;
            }
                }
            }
            save_file << endl;
        }

save_file.close();
}
} 
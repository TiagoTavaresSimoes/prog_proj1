#include "XPM2.hpp"
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

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
            vector<rgb_value> rgb; // will store red, green, blue values as rgb[0], rgb[1] and rgb[2]

            for(size_t j = 1; j < hexaColor.length() - 1; j += 2){ // ignore first char in hexaColor because it is the '#'
                rgb_value tmp = 0;

                if(hexaColor[j] >= 'a' && hexaColor[j] <= 'z') tmp += (hexaColor[j] - 'a');
                else tmp += hexaColor[j];

                if(hexaColor[j + 1] >= 'a' && hexaColor[j + 1] <= 'z') tmp += (hexaColor[j + 1] - 'a');
                else tmp += hexaColor[j + 1];

                rgb.push_back(tmp);
            }

            mapCharToColor.insert({symbol, {rgb[0], rgb[1], rgb[2]}});
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

    }
}

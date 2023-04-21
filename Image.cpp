#include "Image.hpp"

namespace prog
{
  // constructor

  Image::Image(int w, int h, const Color &fill)
  {
    width_ = w;
    height_ = h;
    pixels = new Color*[width_]; // allocate array of width_ size
    for(int i = 0; i < width_; i++){
      pixels[i] = new Color[height_]; // allocate array of height_ size
      for(int j = 0; j < height_; j++){
        pixels[i][j] = fill;
      }
    }
  }

  // destructor

  Image::~Image()
  {
    for(int i = 0; i < width_; i++){
      delete [] pixels[i]; // free/release memory of each array inside the main array
    }
    delete [] pixels; // free/release memory of the main array
  }

  // accessors

  int Image::width() const
  {
    return width_;
  }

  int Image::height() const
  {
    return height_;
  }

  const Color& Image::at(int x, int y) const
  {
    return pixels[x][y];
  }

  // mutator

  Color& Image::at(int x, int y)
  {
    return pixels[x][y];
  }

  void Image::invert(){
    for(int i = 0; i < width_; i++){
      for(int j = 0; j < height_; j++){
        pixels[i][j].invert();
      }
    }
  }

  void Image::to_gray_scale(){
    for(int i = 0; i < width_; i++){
      for(int j = 0; j < height_; j++){
        pixels[i][j].to_gray_scale();
      }
    }
  }
}

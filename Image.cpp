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

  void Image::invert(){ // iterates through all the pixels in the image and calls the invert function for each pixel
    for(int i = 0; i < width_; i++){
      for(int j = 0; j < height_; j++){
        pixels[i][j].invert();
      }
    }
  }

  void Image::to_gray_scale(){ // iterates through all the pixels in the image and calls the to_gray_scale function for each pixel
    for(int i = 0; i < width_; i++){
      for(int j = 0; j < height_; j++){
        pixels[i][j].to_gray_scale();
      }
    }
  }

  void Image::replace(rgb_value r1, rgb_value g1, rgb_value b1, rgb_value r2, rgb_value g2, rgb_value b2){ // iterates through all the pixels in the image and calls the replace function for each pixel
    for(int i = 0; i < width_; i++){
      for(int j = 0; j < height_; j++){
        pixels[i][j].replace(r1, g1, b1, r2, g2, b2);
      }
    }
  }

  void Image::fill(int x, int y, int w, int h, rgb_value r, rgb_value g, rgb_value b){
    for(int i = x; i < x + w; i++){
      for(int j = y; j < y + h; j++){
        pixels[i][j] = Color(r, g, b);
      }
    }
  }
  void Image::v_mirror(){ // iterate through all pixels within the range of 0 <= x < width_ and 0 <= y < height_ / 2 and change the pixel in (x, y) with the pixel in (x, height_ - 1 - y)
    for(int i=0;i<width_;i++){
      for(int j=0;j<height_/2;j++){
        Color tmpPixel = pixels[i][j];
        pixels[i][j]=pixels[i][height_-1-j];
        pixels[i][height_-1-j]=tmpPixel;

        
      }
    }
    
  }

  //TODO replace function will operate in color.cpp here it will only iterate
}

#ifndef __prog_Image_hpp__
#define __prog_Image_hpp__
#include "Color.hpp"

namespace prog
{
  class Image
  {
  private:
    int width_, height_;
    Color **pixels;
  public:
    Image(int w, int h, const Color &fill = {255, 255, 255}); // constructor
    ~Image(); // destructor
    int width() const; // accessor
    int height() const; // accessor
    Color &at(int x, int y); // mutator
    const Color &at(int x, int y) const; // accessor
    void invert();
    void to_gray_scale();
  };
}
#endif

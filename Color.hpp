#ifndef __prog_Color_hpp__
#define __prog_Color_hpp__

namespace prog
{
  typedef unsigned char rgb_value;
  class Color
  {
    private:
      rgb_value red_, green_, blue_;
    public:
      Color(); // default constructor
      Color(const Color& c); // copy constructor
      Color(rgb_value r, rgb_value g, rgb_value b); // constructor using supplied (r, g, b) values
      rgb_value red() const; // accessor
      rgb_value& red(); // mutator
      rgb_value green() const; // accessor
      rgb_value& green(); // mutator
      rgb_value blue() const; // accessor
      rgb_value& blue(); // mutator
      void invert();
  };
}
#endif

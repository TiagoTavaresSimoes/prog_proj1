#include "Color.hpp"

namespace prog {
    // constructors

    Color::Color() {
        red_ = 0;
        green_ = 0;
        blue_ = 0;
    }

    Color::Color(const Color& other) {
        red_ = other.red_;
        green_ = other.green_;
        blue_ = other.blue_;
    }

    Color::Color(rgb_value red, rgb_value green, rgb_value blue) {
        red_ = red;
        green_ = green;
        blue_ = blue;
    }

    // accessors

    rgb_value Color::red() const {
        return red_;
    }

    rgb_value Color::green() const {
        return green_;
    }

    rgb_value Color::blue() const {
        return blue_;
    }

    // mutators

    rgb_value& Color::red()  {
        return red_;
    }

    rgb_value& Color::green()  {
        return green_;
    }

    rgb_value& Color::blue()  {
        return blue_;
    }

    void Color::invert(){
        red_ = 255 - red_;
        green_ = 255 - green_;
        blue_ = 255 - blue_;
    }

    void Color::to_gray_scale(){
        rgb_value v = (red_ + green_ + blue_) / 3;
        red_ = v;
        green_ = v;
        blue_ = v;
    }
}

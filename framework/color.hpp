#ifndef BUW_COLOR_HPP
#define BUW_COLOR_HPP

#include <iostream>

struct Color
{
  Color(float red, float green, float blue) : r(red), g(green), b(blue) {}
  float r;
  float g;
  float b;

  friend std::ostream& operator<<(std::ostream& os, Color const& c)
  {
    os << "(" << c.r << "," << c.g << "," << c.b << ")\n";
    return os;
  }

  Color& operator+=(Color const& other)
  {
    r += other.r;
    g += other.g;
    b += other.b;
    return *this;
  }

  Color& operator-=(Color const& other)
  {
    r -= other.r;
    g -= other.g;
    b -= other.b;
    return *this;
  }

  friend Color operator+(Color const& a, Color const& b)
  {
    auto tmp(a);
    tmp += b;
    return tmp;
  }

  friend Color operator-(Color const& a, Color const& b)
  {
    auto tmp(a);
    tmp -= b;
    return tmp;
  }

  friend bool operator==(const Color& a, const Color& b)
  {
    return (a.r == b.r and a.g == b.g and a.g == b.g);
  }

  friend Color operator*( Color a, float factor) {
    a.r *= factor;
    a.g *= factor;
    a.b *= factor;
    return a;
}

  friend Color operator*(float factor, Color a) {
    a.r *= factor;
    a.g *= factor;
    a.b *= factor;
    return a;
}
};



#endif //#define BUW_COLOR_HPP

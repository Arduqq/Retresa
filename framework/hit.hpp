#ifndef MY_HIT
#define MY_HIT

#include <glm/glm.hpp>

class Shape;

struct Hit
{
  Hit():
    impact{false},
    point{glm::vec3{0,0,0}},
    normal{glm::vec3{1,0,0}},
    shape{nullptr}
  {}

  Hit(bool i, glm::vec3 const& p, glm::vec3 const& n, Shape* s):
    impact{i},
    point{p},
    normal{n},
    shape{s}
  {}

  bool impact;
  glm::vec3 point;
  glm::vec3 normal;
  Shape* shape;
};

#endif
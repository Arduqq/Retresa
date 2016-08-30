#ifndef MY_HIT
#define MY_HIT

#include <glm/glm.hpp>

class Shape;

struct Hit
{
  Hit():
    impact{false},
    distance{1000000.0},
    point{glm::vec3{0,0,0}},
    normal{glm::vec3{1,0,0}},
    shape{nullptr}
  {}

  Hit(bool i, float d, glm::vec3 const& p, glm::vec3 const& n, Shape* s):
    impact{i},
    distance{d},
    point{p},
    normal{n},
    shape{s}
  {}

  bool impact = false;
  float distance = 10000000.0;
  glm::vec3 point{0,0,0};
  glm::vec3 normal{0,0,1};
  Shape* shape{nullptr};
};

#endif
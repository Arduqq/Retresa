#ifndef MY_HIT
#define MY_HIT

#include "scene.hpp"

struct Hit
{
Hit(bool i, glm::vec3 p, Ray n, Shape* s):
impact{i},
point{p},
normal{n},
Shape*{s}{}

bool impact;
glm::vec3 point;
Ray normal;
Shape* shape;
};

#endif
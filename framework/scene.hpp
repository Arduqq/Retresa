#ifndef SCENE_RT_HPP
#define SCENE_RT_HPP

#include <vector>
#include <memory>
#include "shape.hpp"
#include "hit.hpp"

struct Scene
{
std::vector<shared_ptr<Shape>> shapes;
//std::vector<shared_ptr<Light>> lights;
};

#endif
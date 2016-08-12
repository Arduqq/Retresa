#ifndef SCENE_RT_HPP
#define SCENE_RT_HPP

#include <vector>
#include <memory>
#include "shape.hpp"
#include "hit.hpp"
#include "light.hpp"
#include "camera.hpp"
#include "material.hpp"

struct Scene
{
	unsigned int sizeShape;
	unsigned int sizeLight;
	unsigned int width;
	unsigned int height;
	std::vector<std::shared_ptr<Shape>> shapes;
	std::vector<std::shared_ptr<Light>> lights;
	std::vector<std::shared_ptr<Material>> materials;
	std::shared_ptr <Camera> cam;

	void loadscene(std::string const& input);
};

#endif
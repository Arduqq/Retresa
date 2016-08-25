#ifndef RAY_HPP
#define RAY_HPP

#include <glm/vec3.hpp>
struct Ray
{
	Ray():
	origin{0.0f,0.0f,0.0f},
	direction{0.0f,0.0f,0.0f}
	{}

	Ray(glm::vec3 const& ori, glm::vec3 const& dir):
	origin{ori},
	direction{dir}
	{}

	glm::vec3 origin;
	glm::vec3 direction;
};

#endif
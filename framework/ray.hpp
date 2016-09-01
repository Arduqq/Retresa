#ifndef RAY_HPP
#define RAY_HPP

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/glm.hpp>

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

	Ray transformRay(glm::mat4 const& mat)
	{
		glm::vec4 origino{origin,1.0f};
		glm::vec4 directiono{direction,0.0f};

		glm::vec4 origin_homogen = mat * origino;
		glm::vec4 direction_homogen = mat * directiono;

		glm::vec3 origini(origin_homogen);
		glm::vec3 directini(direction_homogen); 

		return Ray {origini, directini};
	}
};

#endif
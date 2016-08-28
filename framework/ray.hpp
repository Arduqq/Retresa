#ifndef RAY_HPP
#define RAY_HPP

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
struct Ray
{
	Ray();

	Ray(glm::vec3 const& ori, glm::vec3 const& dir):
	origin{ori},
	direction{dir}
	{}

	/*Ray(glm::vec4 const& transori, glm::vec4 const& transdir):
	transorigin{transori},
	transdirection{transdir}
	{}

	Ray(glm::vec4 const& scalori, glm::vec4 const& scaldir):
	scaorigin{scalori},
	scadirection{scaldir}
	{}*/

	glm::vec3 origin;
	glm::vec3 direction;
	/*glm::vec4 transorigin;
	glm::vec4 transdirection;
	glm::vec4 scaorigin;
	glm::vec4 scadirection;*/
};

#endif
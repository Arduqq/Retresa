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

	Ray transformRay(glm::mat4 const& mat)
{


    /*glm::vec4 origin4{origin, 1.0f};
    glm::vec4 direction4{direction, 0.0f};
    glm::vec4 origin_trans = mat * origin4;
    glm::vec4 direction_trans = mat * direction4;

    glm::vec3 origin3(origin_trans);
    glm::vec3 direction3(direction_trans);

    Ray ray{origin3, direction3};

    return ray;*/


	glm::vec4 origino{origin,1.0f};
	glm::vec4 directiono{direction,0.0f};

  //world_transformation_inv = glm::inverse(world_transformation);
  //world_transformation_inv_tp = glm::transpose(world_transformation_inv);

  //glm::vec4 newOrigin   {origin    * world_transformation_inv};
  //glm::vec4 newDirection{direction * world_transformation_inv};

	glm::vec4 origin_homogen = mat * origino;
	glm::vec4 direction_homogen = mat * directiono;

	glm::vec3 origini(origin_homogen);
	glm::vec3 directini(direction_homogen); 

	Ray ray{origini, directini};

	//return Ray{glm::vec3{newOrigin.x, newOrigin.y, newOrigin.z }, glm::vec3{newDirection.x, newDirection.y, newDirection.z}};
	return ray; 
}
};

#endif
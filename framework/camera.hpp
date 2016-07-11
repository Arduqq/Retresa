#ifndef CAMERA
#define CAMERA

#include <glm/vec3.hpp>
#include <ray.hpp>

class Camera
{
public:

	Camera(glm::vec3 u, glm::vec3 e , glm::vec3 d,unsigned h,unsigned w):
		up{u},
		eye{e},
		dir{d},
		height{h},
		width{w}{}

	inline Ray calculateRay(unsigned xInp, unsigned yInp)
	{
		int x = xInp - (width/2);
		int y = yInp - (height/2);
//Ray{glm::vec3{x,y,0},glm::vec3{0,0,-1}

		dir = glm::vec3{0,0,-1};
		return (Ray{eye, glm::normalize(eye - glm::vec3{x,y,0}) } );
	}

private:
	glm::vec3 up;
	glm::vec3 eye;
	glm::vec3 dir;
	unsigned height;
	unsigned width;
};

#endif
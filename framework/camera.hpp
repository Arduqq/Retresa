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

		Ray ronny{eye, glm::normalize(glm::vec3{x, y, 0} - eye) };
		return ronny;
	}

private:
	glm::vec3 up;
	glm::vec3 eye;
	glm::vec3 dir;
	unsigned height;
	unsigned width;
};

#endif
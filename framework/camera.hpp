#ifndef CAMERA
#define CAMERA

#include <glm/vec3.hpp>
#include <ray.hpp>

class Camera
{
	Camera(glm::vec3 u, glm::vec3 e , glm::vec3 d):
		up{u},
		eye{e},
		dir{d}{}
public:

	Ray calculateRay();

private:
	glm::vec3 up;
	glm::vec3 eye;
	glm::vec3 dir;
};

#endif
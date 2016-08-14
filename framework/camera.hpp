#ifndef CAMERA
#define CAMERA

#include <glm/vec3.hpp>
#include <ray.hpp>

class Camera
{
public:

	Camera(glm::vec3 const& e, glm::vec3 const& d, float u, unsigned h, unsigned w):
		up{u},
		eye{e},
		dir{glm::normalize(d)},
		height{h},
		width{w}{}

	inline Ray calculateRay(unsigned xInp, unsigned yInp)
	{
		glm::vec3 xyCentre{glm::vec3{dir.x * 1000, dir.y * 1000, dir.z * 1000} + eye };

		glm::vec3 colY{0,1,0};//später wird der mittels Drehmatrix um dir im winkel up gedreht.
		glm::vec3 rowX{glm::normalize(glm::cross(dir,colY))}; 
		//std::cout<<xyCentre.x<<" "<<xyCentre.y<<" "<<xyCentre.z<<" "<<std::endl;
		int x = xInp - (width/2);
		int y = yInp - (height/2);

		Ray ronny{eye, glm::normalize((xyCentre + glm::vec3{x * rowX.x, x * rowX.y, x * rowX.z} + glm::vec3{y * colY.x, y * colY.y, y * colY.z}) - eye)};/* glm::normalize(glm::vec3{x, y, 0} - eye)*/ 
		return ronny;
	}

private:
	float up;
	glm::vec3 eye;
	glm::vec3 dir;
	unsigned height;
	unsigned width;
};

#endif
#ifndef SURFUCK_BUW
#define SURFUCK_BUW

//#include "ray.hpp"
#include "shape.hpp"
//#include <glm/glm.hpp>

class Surface: public Shape
{
public:
	Surface(glm::vec3 const& positionVector, glm::vec3 const& orientation, glm::vec3 const& norm, float length, float width);

	Hit intersect(Ray const& ronny) override;

private:
	glm::vec3 positionVector;
	glm::vec3 orientation;
	float length;
	float width;

	glm::vec3 p1;
	glm::vec3 p2;
	glm::vec3 p3;
	glm::vec3 p4;
	glm::vec3 norm;
};

#endif
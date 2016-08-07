#ifndef SURFUCK_BUW
#define SURFUCK_BUW

//#include "ray.hpp"
#include "shape.hpp"
//#include <glm/glm.hpp>

class Surface: public Shape
{
public:
	Surface(glm::vec3 const& positionVector, glm::vec3 const& orientation, glm::vec3 const& norm, float length, float width);

	Surface(glm::vec3 const& positionVector, glm::vec3 const& orientation, glm::vec3 const& norm, float length, float width, std::string const& name, Material const& mat);

	Hit intersect(Ray const& ronny) override;

	void setEdges(glm::vec3 const& PV, glm::vec3 const& N, glm::vec3 const& O, float W, float L);

	std::ostream & print ( std :: ostream & os ) const override;

private:
	glm::vec3 positionVector;
	glm::vec3 orientation;
	float length;
	float width;

	Material mat;
	std::string name;

	glm::vec3 p1;
	glm::vec3 p2;
	glm::vec3 p3;
	glm::vec3 p4;
	glm::vec3 norm;
};

#endif
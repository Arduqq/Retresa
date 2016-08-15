#ifndef SURFUCK_BUW
#define SURFUCK_BUW

#include "shape.hpp"

class Surface: public Shape
{
public:
	Surface(glm::vec3 const& _p1, glm::vec3 const& _p2, glm::vec3 const& _p3);

	Surface(glm::vec3 const& _p1, glm::vec3 const& _p2, glm::vec3 const& _p3, std::string const& name, Material const& mat);

	Hit intersect(Ray const& ronny) override;

	std::ostream & print ( std :: ostream & os ) const override;

	inline glm::vec3 getp1() const
	{
		return p1;
	}

	inline glm::vec3 getp3() const
	{
		return p3;
	}

private:
	glm::vec3 p1;
	glm::vec3 p2;
	glm::vec3 p3;
	glm::vec3 p4;
	float height;
	float width;
	glm::vec3 norm;

	Material mat;
	std::string name;
};

#endif
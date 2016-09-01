#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "shape.hpp"
#include "vektoroperations.hpp"

class Triangle: public Shape
{
public:
	Triangle(glm::vec3 const& _p1, glm::vec3 const& _p2, glm::vec3 const& _p3);
	Triangle(glm::vec3 const& _p1, glm::vec3 const& _p2, glm::vec3 const& _p3, std::string const& name, Material const& mat);
	
	Hit intersect(Ray const& ronny) override;
	std::ostream & print ( std :: ostream & os ) const override;

private:
	glm::vec3 p1;
	glm::vec3 p2;
	glm::vec3 p3;

	glm::vec3 norm;

	Material mat;
	std::string name;
};

#endif
#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "shape.hpp"
#include "vektoroperations.hpp"

#include <math.h>
#include <string>

class Sphere: public Shape
{
public:
	Sphere();
	Sphere(glm::vec3 const& ctr, float rad);
	Sphere(glm::vec3 const& ctr, float rad, std::string const& name, Material const& mat);
	~Sphere();

	std::ostream & print ( std :: ostream & os ) const override;
	glm::vec3 const& getctr() const;
	float     const& getrad() const;
	void setctr(glm::vec3 ctr);
	void setrad(float     rad);
	Hit intersect(Ray const& inray) override;

private: 
	glm::vec3 ctr_;
	float     rad_;
};

#endif
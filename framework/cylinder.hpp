#ifndef CYLINDER_HPP
#define CYLINDER_HPP

#include "shape.hpp"
#include "surface.hpp"
#include <vector>
#include <memory>
#include <glm/vec3.hpp>

class Cylinder: public Shape
{
public:
	Cylinder();
	Cylinder(glm::vec3 const& ctr, float rad, float height);
	Cylinder(glm::vec3 const& ctr, float rad, float height, std::string const& name, Material const& mat);
	~Cylinder();

	Hit intersect (Ray const& ray) override;

	std::ostream & print ( std :: ostream & os) const override;
	glm::vec3 const& getctr()    const;
	float     const& getrad()    const;
	float const& getheight() const;
	void setctr(glm::vec3 const& ctr);
	void setrad(float rad);
	void setheight(float height);


private:
	glm::vec3 ctr_;
	float     rad_,height_;

};

#endif 
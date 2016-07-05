#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <string>
#include "ray.hpp"
#include "color.hpp"
#include "material.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>

class Shape
{
public:
	Shape();
	Shape(std::string const & name, Material const& mat);
	~Shape();
	std::string const& getname() const;
	Material const& getmat() const;

	virtual float area()   const = 0;
	virtual float volume() const = 0;
	virtual bool  intersect (Ray const & ray, float t) = 0;

	virtual std::ostream & print ( std :: ostream & os ) const ;
	

private:
	std::string name_;
	Material mat_;
};

std::ostream& operator<<(std::ostream& os, Shape const& s);

#endif

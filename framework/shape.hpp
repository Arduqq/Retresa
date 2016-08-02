#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <string>
#include "ray.hpp"
#include "color.hpp"
#include "material.hpp"
#include "hit.hpp"
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

	void  setname(std::string const& s);
	void  setmat(Material  const&    m);

	virtual float area()   const = 0;
	virtual float volume() const = 0;
	virtual Hit intersect(Ray const & ray) = 0;

	virtual std::ostream & print ( std :: ostream & os ) const ;
	

private:
	std::string name_;
	Material mat_;
};

std::ostream& operator<<(std::ostream& os, Shape const& s);

#endif

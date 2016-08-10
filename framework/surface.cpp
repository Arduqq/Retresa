#include "surface.hpp"
#include "vektoroperations.hpp"

Surface::Surface(glm::vec3 const& _p1, glm::vec3 const& _p2, glm::vec3 const& _p3):
	p1{_p1},
	p2{_p2},
	p3{_p3}//eckpunkte mit dem uhrzeigersinn angegeben
	{
		p4 = p3 + (p1 - p2);
		norm = cross(p3 - p1, p2 - p1);
		width = absolute(p1-p2);
		height = absolute(p3-p2);
	}

Surface::Surface(glm::vec3 const& _p1, glm::vec3 const& _p2, glm::vec3 const& _p3, std::string const& _name, Material const& _mat):
	p1{_p1},
	p2{_p2},
	p3{_p3},
	name{_name},
	mat{_mat}
	{
		p4 = p3 + (p1 - p2);
		norm = cross(p3 - p1, p2 - p1);
		width = absolute(p1-p2);
		height = absolute(p3-p2);
	}

std::ostream & Surface::print ( std :: ostream & os ) const
{
	Shape::print(os);
	os <<"e1: ("
	<< p1.x << ", "
	<< p1.y << ", "
	<< p1.z << ") , e2: ("
	<< p2.x << ", "
	<< p2.y << ", "
	<< p2.z << ") , e3: ("
	<< p3.x << ", "
	<< p3.y << ", "
	<< p3.z << ") , e4: ("
	<< p4.x << ", "
	<< p4.y << ", "
	<< p4.z << ") , Width: ("
	<< width<< ") Height: ("
	<< height << std::endl;
}

Hit Surface::intersect(Ray const& ray) 
{
	Hit hit;
	float denominator = skalar(norm , ray.direction);
	if(denominator != 0)
	{
		float distance = (-(norm.x*(ray.origin.x - p1.x))-(norm.y*(ray.origin.y - p1.y))
			-(norm.z*(ray.origin.z - p1.z))) / denominator;
		if(distance > 0)
		{ 
			hit.point  = ray.origin + (distance * ray.direction);
			{
				if( skalar(p2-p1, hit.point-p1) >= 0 and skalar(p3-p2, hit.point-p2) >= 0 and skalar(p4-p3, hit.point-p3) >= 0 and skalar(p1-p4, hit.point-p4) >= 0)
				{
				hit.impact = true;
				hit.normal = norm;
				hit.shape  = this;
				}
			}
		}
	}
	return hit;
}
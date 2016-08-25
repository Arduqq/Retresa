#include "triangle.hpp"
//#include "vektoroperations.hpp"

Triangle::Triangle(glm::vec3 const& _p1, glm::vec3 const& _p2, glm::vec3 const& _p3):
	p1{_p1},
	p2{_p2},
	p3{_p3}//eckpunkte mit dem uhrzeigersinn angegeben
	{norm = cross(p3 - p1, p2 - p1);}

Triangle::Triangle(glm::vec3 const& _p1, glm::vec3 const& _p2, glm::vec3 const& _p3, std::string const& _name, Material const& _mat):
	p1{_p1},
	p2{_p2},
	p3{_p3},
	Shape{_name,_mat}
	{
		norm = cross(p3 - p1, p2 - p1);
		std::cout<<_name<<"  "<<name;
	}

std::ostream & Triangle::print ( std :: ostream & os ) const
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
	<< p3.z <<")"<< std::endl;
}

Hit Triangle::intersect(Ray const& ray) 
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
				if(skalar(p3-p1, p1 - hit.point) <= skalar(p3 - p1, p2 - p1) and skalar(p1-p2, p2 - hit.point) <= skalar(p1 - p2, p3 - p2) and skalar(p2-p3, p3 - hit.point) <= skalar(p2 - p3, p1 - p3) )
				{
				hit.impact = true;
				hit.normal = norm;
				hit.shape  = this;
				hit.distance=glm::length(hit.point - ray.origin);
				}
			}
		}
	}
	return hit;
}
#include "surface.hpp"
#include "vektoroperations.hpp"

Surface::Surface(glm::vec3 const& _positionVector, glm::vec3 const& _orientation, glm::vec3 const& _norm, float _length, float _width):
	positionVector{_positionVector},
	orientation{_orientation},
	norm{_norm},
	length{_length},
	width{_width}{}

Surface::Surface(glm::vec3 const& _positionVector, glm::vec3 const& _orientation, glm::vec3 const& _norm, float _length, float _width, std::string const& _name, Material const& _mat):
	positionVector{_positionVector},
	orientation{_orientation},
	norm{_norm},
	length{_length},
	width{_width},
	name{_name},
	mat{_mat}{}


std::ostream & Surface::print ( std :: ostream & os ) const
{
	Shape::print(os);
	os <<"Location: ("
	<< positionVector.x << ", "
	<< positionVector.y << ", "
	<< positionVector.z << ") , Length: ("
	<< length << ") "<<std::endl;
}

Hit Surface::intersect(Ray const& ray) 
{
	Hit hit;
	float denominator = skalar(norm , ray.direction);
	if(denominator != 0)
	{
		float distance = (-(norm.x*(ray.origin.x - positionVector.x))-(norm.y*(ray.origin.y - positionVector.y))
			-(norm.z*(ray.origin.z - positionVector.z))) / denominator;
		if(distance > 0)
		{ 
			
			hit.impact = true;
			hit.point  = ray.origin + (distance * ray.direction);
			hit.normal = norm;
			hit.shape  = this;
		}
	}
	return hit;
}
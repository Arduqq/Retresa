#include "surface.hpp"
#include "vektoroperations.hpp"

Surface::Surface(glm::vec3 const& _positionVector, glm::vec3 const& _orientation, glm::vec3 const& _norm, float _length, float _width):
	positionVector{_positionVector},
	orientation{_orientation},
	norm{_norm},
	length{_length},
	width{_width}
	
	{
		setEdges(positionVector,norm,orientation,width,length);
	}

Surface::Surface(glm::vec3 const& _positionVector, glm::vec3 const& _orientation, glm::vec3 const& _norm, float _length, float _width, std::string const& _name, Material const& _mat):
	positionVector{_positionVector},
	orientation{_orientation},
	norm{_norm},
	length{_length},
	width{_width},
	name{_name},
	mat{_mat}
	
	{
		setEdges(positionVector,norm,orientation,width,length);
	}

void Surface::setEdges(glm::vec3 const& PV, glm::vec3 const& N, glm::vec3 const& O, float W, float L)
{
	glm::vec3 O2 = cross(O,N);

				p1 = PV + (glm::normalize(O) * (L/2)) + (glm::normalize(O2) * (W/2));
			  p2 = PV - (glm::normalize(O) * (L/2)) + (glm::normalize(O2) * (W/2));
			  p3 = PV + (glm::normalize(O) * (L/2)) - (glm::normalize(O2) * (W/2));
			  p4 = PV - (glm::normalize(O) * (L/2)) - (glm::normalize(O2) * (W/2));
}

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
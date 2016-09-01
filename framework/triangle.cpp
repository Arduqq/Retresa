#include "triangle.hpp"

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

Hit Triangle::intersect(Ray const& raytf) 
{
	Hit hit;
	Ray ray = raytf.transformRay(world_transformation_inv);
	float denominator = skalar(norm , ray.direction);
	if(denominator != 0)
	{
		float distance = (-(norm.x*(ray.origin.x - p1.x))-(norm.y*(ray.origin.y - p1.y))
			-(norm.z*(ray.origin.z - p1.z))) / denominator;
		if(distance > 0)
		{ 
			//hit.point  = ray.origin + (distance * ray.direction);
			glm::vec3 object_position = ray.origin + (distance * ray.direction);

			glm::vec3 world_position{world_transformation * glm::vec4{object_position,1} };
			glm::vec4 world_normal{world_transformation_inv_tp * glm::vec4{norm  ,0} };

			hit.point = object_position;

			{
				if(skalar(p3-p1, p1 - hit.point) <= skalar(p3 - p1, p2 - p1) and skalar(p1-p2, p2 - hit.point) <= skalar(p1 - p2, p3 - p2) and skalar(p2-p3, p3 - hit.point) <= skalar(p2 - p3, p1 - p3) )
				{
				hit.point = world_position;
				hit.impact = true;
				hit.normal = norm;
				hit.shape  = this;
				hit.distance= distance;
				}
			}
		}
	}

	
	return hit;
}
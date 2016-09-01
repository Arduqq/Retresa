#include "sphere.hpp"
//#include "vektoroperations.hpp"
//#include <math.h>
//#include <string>

Sphere::Sphere():
	Shape{"Sphere",{}}, rad_{0.0f}, ctr_{0.0f,0.0f,0.0f}{
	}
Sphere::Sphere(glm::vec3 const& ctr, float rad):
	Shape{"Sphere",{}}, rad_{rad}, ctr_{ctr}{
	}
Sphere::Sphere(glm::vec3 const& ctr, float rad, std::string const& name, Material const& mat):
	Shape{name,mat}, rad_{rad}, ctr_{ctr}{
	}
Sphere::~Sphere(){
	
	std::cout<<"Delete Sphere"<<std::endl;
    }

std::ostream & Sphere::print ( std :: ostream & os ) const
{
	Shape::print(os);
	os <<"Location: ("
	<< ctr_.x << ", "
	<< ctr_.y << ", "
	<< ctr_.z << ") , Radius: ("
	<< rad_ << ") "<<std::endl;
}

glm::vec3 const& Sphere::getctr() const
{
	return ctr_;
}

float const& Sphere::getrad() const 
{
	return rad_;
}

Hit Sphere::intersect(Ray const& inray) 
{	
	Hit sphereHit;
	Ray ray = inray.transformRay(world_transformation_inv);
	ray.direction = glm::normalize(ray.direction);
	//kompatibilität mit der formel aus https://en.wikipedia.org/wiki/Line%E2%80%93sphere_intersection schaffen
	glm::vec3 l = ray.direction;
	glm::vec3 o = ray.origin;
	glm::vec3 c = ctr_;
	float	  r = rad_;
	float underroot = ( skalar(l , (o - c)) * skalar(l , (o - c))) - ((glm::length(o - c) * glm::length(o - c))) + (r*r); //=der bums unter der wurzel
	if( underroot > 0 )
	{
		float root = std::min(sqrt(underroot),-sqrt(underroot));
		float t = (- skalar(l , (o - c))) + root;
		if(t > 0) //strahl schneidet in positiver richtung
		{
			glm::vec3 object_position = o + t * l;
			glm::vec3 normal = glm::normalize(object_position - ctr_);
            
			glm::vec3 world_position{world_transformation  * glm::vec4{object_position,1} };
			glm::vec4 world_normal{world_transformation_inv_tp * glm::vec4{normal  ,0} };

			sphereHit.point = object_position;

            //Hit sphereHit;
			sphereHit.impact = true;
			sphereHit.shape = this;
			sphereHit.point = world_position; //glm::vec3{world_position.x, world_position.y, world_position.z};
			sphereHit.normal =glm::vec3{world_normal.x  , world_normal.y  , world_normal.z  };
			sphereHit.distance=t;
		    
		    //sphereHit.transformHit(world_transformation, world_transformation_inv);
		    return sphereHit;
		}
	}

	return Hit{};
}
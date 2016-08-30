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

Hit Sphere::intersect(Ray const& ray) 
{
	
	//kompatibilität mit der formel aus https://en.wikipedia.org/wiki/Line%E2%80%93sphere_intersection schaffen
	glm::vec3 l = ray.direction;
	glm::vec3 o = ray.origin;
	glm::vec3 c = ctr_;
	float	  r = rad_;
	float underroot = ( skalar(l , (o - c)) * skalar(l , (o - c))) - ((absolute(o - c) * absolute(o - c))) + (r*r); //=der bums unter der wurzel
	if( underroot > 0 )
	{
		float root = std::min(sqrt(underroot),-sqrt(underroot));
		float t = (- skalar(l , (o - c))) + root;
		if(t > 0) //strahl schneidet in positiver richtung
		{
			glm::vec3 position = o + t * l;
			glm::vec3 normal = glm::normalize(position - ctr_);
            
            Hit sphereHit;
			sphereHit.impact = true;
			sphereHit.shape = this;
			sphereHit.point = position;
			sphereHit.normal = normal;
			sphereHit.distance=absolute(sphereHit.point - ray.origin);
		    return sphereHit;
		}
	}

	return Hit{};
}
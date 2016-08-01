#include "sphere.hpp"
#include "vektoroperations.hpp"
#include <math.h>

Sphere::Sphere():
	Shape(),
	ctr_{0.0f,0.0f,0.0f},
	rad_{1}
	{std::cout<<"makin' a lil' Sphere"<<std::endl;}
Sphere::Sphere(glm::vec3 const& ctr, float rad):
	Shape(),
	ctr_{ctr},
	rad_{rad}
	{std::cout<<"makin' a lil' Sphere"<<std::endl;}
Sphere::Sphere(glm::vec3 const& ctr, float rad, std::string const& name, Material const& mat):
	Shape(name, mat),
	ctr_{ctr},
	rad_{rad}
	{std::cout<<"makin' a lil' Sphere"<<std::endl;}
Sphere::~Sphere()
{
	std::cout<<"Killing Sphere"<<std::endl;
}

float Sphere::area() const
{
	return 4*M_PI*rad_*rad_;
}  
float Sphere::volume() const
{
	return (4*M_PI*rad_*rad_*rad_)/3;
}
std::ostream & Sphere::print ( std :: ostream & os ) const
{
	Shape::print(os);
	os <<"CTR: ("
	<< ctr_.x << ", "
	<< ctr_.y << ", "
	<< ctr_.z << ") , RAD: ("
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
	Hit sphereHit;
	//kompatibilität mit der formel aus https://en.wikipedia.org/wiki/Line%E2%80%93sphere_intersection schaffen
	glm::vec3 l = ray.direction;
	glm::vec3 o = ray.origin;
	glm::vec3 c = ctr_;
	float	  r = rad_;
	float underroot = ( skalar(l , (o - c)) * skalar(l , (o - c))) - ((absolute(o - c) * absolute(o - c))) + (r*r); //=der bums unter der wurzel
	if( underroot > 0 )
	{
		float root = std::min(sqrt(underroot),-sqrt(underroot));
		float d = (- skalar(l , (o - c))) + root;
		if(d >= 0) //strahl schneidet in positiver richtung
		{
			sphereHit.impact = true;
			sphereHit.shape = this;
			sphereHit.point = glm::vec3{o + d * l};
			sphereHit.normal = glm::normalize(sphereHit.point - ctr_);
		}
	}

	return sphereHit;
}
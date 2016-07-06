#include "sphere.hpp"
#include <math.h>
#include "vektoroperations.hpp"

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
	os <<"I'm livin in \n ("
	<< ctr_.x << ", "
	<< ctr_.y << ", "
	<< ctr_.z << ") , I'm ("
	<< rad_ << ") tall"<<std::endl;
}

glm::vec3 const& Sphere::getctr() const
{
	return ctr_;
}

float const& Sphere::getrad() const 
{
	return rad_;
}

bool Sphere::intersect(Ray const& ray, float distance) 
{
	bool sphereHit;
	glm::vec3 b = cross(ctr_ - ray.origin,ray.direction)/absolute(ray.direction);

	if(absolute(b) < rad_ )
	{
		sphereHit=true;
		float a = sqrt((rad_*rad_) - (absolute(b)*absolute(b)));
		glm::vec3 p {ctr_+b};
		glm::vec3 intersectPoint{ray.origin + ((1-a) * ray.direction)};
	}
	else sphereHit=false;

	return sphereHit;
}
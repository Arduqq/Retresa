#include "sphere.hpp"
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

/*glm::vec3 cross(glm::vec3 v1, glm::vec3 v2)
{
	glm::vec3 res;
	res.x=(v1.y * v2.z) - (v1.z * v2.y);
	res.y=(v1.z * v2.x) - (v1.x * v2.z);
	res.z=(v1.x * v2.y) - (v1.y * v2.x);
	return res;
}
float betrag(glm::vec3 v)
{
	return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}*/

bool Sphere::intersect(Ray const& ray, float distance) 
{
	bool sphereHit;

	/*float xO = ray.origin.x;
	float yO = ray.origin.y;
	float zO = ray.origin.z;

	float xD = ray.direction.x;
	float yD = ray.direction.y;
	float zD = ray.direction.z;

	float d = 


	sqrt (rad;*/

	return sphereHit;
}
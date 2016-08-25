#include "cylinder.hpp"
//#include "vektoroperations.hpp"
//#include <math.h>
//#include <string>

Cylinder::Cylinder():
	Shape{"Cylinder",{}},ctr_{0.0f,0.0f,0.0f}, rad_{0.0f}, height_{0.0f}{

	}

Cylinder::Cylinder(glm::vec3 const& ctr, float rad, float height):
	Shape{"Cylinder",{}},ctr_{ctr}, rad_{rad}, height_{height}{

	}

Cylinder::Cylinder(glm::vec3 const& ctr, float rad, float height, std::string const& name, Material const& mat):
	Shape{name, mat},ctr_{ctr}, rad_{rad}, height_{height}{

	}

Cylinder::~Cylinder(){

	std::cout << "Delete Cylinder" <<std::endl;
}

std::ostream & Cylinder::print(std :: ostream & os) const{
	os<<"Location: ("
	<<ctr_.x << " , "
	<<ctr_.y << " , "
	<<ctr_.z << " , Radius: ("
	<<rad_ << ") Hoehe: ( "
	<<height_;
}

glm::vec3 const& Cylinder::getctr() const{

	return ctr_;
}

float const& Cylinder::getrad() const{

	return rad_;
}

float const& Cylinder::getheight() const{

	return height_;
}

void Cylinder::setctr(glm::vec3 const& ctr){

	ctr_ = ctr;
}

void Cylinder::setrad(float rad){

	rad_ = rad;
}

void Cylinder::setheight(float height){

	height_ = height;
}

Hit Cylinder::intersect(Ray const& ray){
	Hit a;
	return a;
}
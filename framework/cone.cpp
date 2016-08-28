#include "cone.hpp"
//#include "vektoroperations.hpp"
//#include <math.h>
//#include <string>

Cone::Cone():
	Shape{"Cone",{}},ctr_{0.0f,0.0f,0.0f}, rad_{0.0f}, peak_{0.0f,0.0f,0.0f}{

	}

Cone::Cone(glm::vec3 const& ctr, float rad, glm::vec3 const& peak):
	Shape{"Cone",{}},ctr_{ctr}, rad_{rad}, peak_{peak}{

	}

Cone::Cone(glm::vec3 const& ctr, float rad, glm::vec3 const& peak, std::string const& name, Material const& mat):
	Shape{name, mat},ctr_{ctr}, rad_{rad}, peak_{peak}{

	}

Cone::~Cone(){

	std::cout << "Delete Cone" <<std::endl;
}

std::ostream & Cone::print(std :: ostream & os) const{

	Cone::print(os);
	os<<"Location: ("
	<<ctr_.x << " , "
	<<ctr_.y << " , "
	<<ctr_.z << " , Radius: ("
	<<rad_ << ") Hoehe: ( "
	<<peak_.x<< " , "
	<<peak_.y<< " , "
	<<peak_.z<< " ) "<<std::endl;
}

glm::vec3 const& Cone::getctr() const{

	return ctr_;
}

float const& Cone::getrad() const{

	return rad_;
}

glm::vec3 const& Cone::getpeak() const{

	return peak_;
}

void Cone::setctr(glm::vec3 const& ctr){

	ctr_ = ctr;
}

void Cone::setrad(float rad){

	rad_ = rad;
}

void Cone::setpeak(glm::vec3 const& peak){

	peak_ = peak;
}

Hit Cone::intersect(Ray const& ray){
	Hit hit;
	return hit;

}
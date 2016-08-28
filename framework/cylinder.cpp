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
	Shape::print(os);
	os<<"Location: ("
	<<ctr_.x << " , "
	<<ctr_.y << " , "
	<<ctr_.z << ") , Radius: ("
	<<rad_ << ") Hoehe: ("
	<<height_<<")";
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
	
	Hit hit;
/*
    float a = ray.direction.x*ray.direction.x + ray.direction.z*ray.direction.z;
    float b = 2*(ray.origin.x*ray.direction.x + ray.origin.z*ray.direction.z);
    float c = ray.origin.x*ray.origin.x + ray.origin.z*ray.origin.z - rad_*rad_;

    float discr = b*b - 4*a*c;
    if (discr < 0)
    {
        return intersect({});
    }

    float x1 = (-b+sqrt(discr))/(2*a);
    float x2 = (-b-sqrt(discr))/(2*a);

    float t;
    if (x1 > x2)
    {
        t=x2;
    }

    if (t < 0)
    {
        t=x1;
    }
    if (t<0)
    {
        return intersect({});
    }
    glm::vec3 point = ray.origin + ray.direction*t;
    glm::vec3 normal = glm::vec3(2*point.x, 0.0f, 2*point.z);

    if (point.y < 0 || point.y > height_)
    {
        return intersect({});
    }

    if (ray.direction.y != 0.0f)
    {
        float t3 = (0-ray.origin.y)/ray.direction.y;
        float t4 = (height_-ray.origin.y)/ray.direction.y;
        float t2;

        //choose the smallest and >=0 t
        t2 = std::min(t3,t4);
        if (t2 < 0)
        {
            t2 = std::max(t3,t4);
        }
        if (t2 >= 0)
        {
            glm::vec3 point1 = ray.origin + ray.direction*t2;
            float d=glm::length(point1 - ray.origin);
            if (point1.x*point1.x + point1.z*point1.z <= rad_*rad_+0.9f)
            {
                t = std::min(t,t2);
                if (t == t3)
                {
                    normal = glm::vec3(0.0f,-1.0f,0.0f);
                    return intersect({point1, normal});
                }
                else if (t == t4)
                {
                    normal = glm::vec3(0.0f,1.0f,0.0f);
                    return intersect({point1, normal});
                }
            }
        }
    }

    point = ray.origin + ray.direction*t;
    float d=glm::length(point - ray.origin);

    return intersect({point, normal});
*/
    return hit;
}
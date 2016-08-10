#include "box.hpp"
#include "surface.hpp"
#include "vektoroperations.hpp"

Box::Box():
	Shape(),
	min_{0.0f,0.0f,0.0f},
	max_{0.0f,0.0f,0.0f}
	{std::cout<<"makin' a lil' Box"<<std::endl;}
Box::Box(glm::vec3 const& min, glm::vec3 const& max):
	Shape(),
	min_{min},
	max_{max}
	{std::cout<<"makin' a lil' Box"<<std::endl;}
Box::Box(glm::vec3 const& min, glm::vec3 const& max, std::string const& name, Material const& mat):
	Shape(name, mat),
	min_{min},
	max_{max}
	{std::cout<<"makin' a lil' Box"<<std::endl;}
Box::~Box()
{
	std::cout<<"Killing Box"<<std::endl;
}

std::ostream & Box::print ( std :: ostream & os ) const
{
	Shape::print(os);
	os << "Location Min: ("
	<< min_.x << ", "
	<< min_.y << ", "
	<< min_.z << ") Max :("
	<< max_.x << ", "
	<< max_.y << ", "
	<< max_.z << ")"<<std::endl;
}

glm::vec3 const& Box::getmin() const
{
	return min_;
}

glm::vec3 const& Box::getmax() const 
{
	return max_;
}
Hit inters(glm::vec3 const& positionVector, glm::vec3 const& norm, Ray const& ray, glm::vec3 const& p1, glm::vec3 const& p2, glm::vec3 const& p3, glm::vec3 const& p4)
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
					}
				}
			}
		}
	return hit;
}
Hit Box::intersect(Ray const& ray) 
{
	Hit hit;
	glm::vec3 a {glm::vec3{min_.x,max_.y,min_.z}};
	glm::vec3 b {glm::vec3{min_.x,min_.y,min_.z}};
	glm::vec3 c {glm::vec3{max_.x,max_.y,min_.z}};
	glm::vec3 d {glm::vec3{max_.x,min_.y,min_.z}};
	glm::vec3 e {glm::vec3{min_.x,max_.y,max_.z}};
	glm::vec3 f {glm::vec3{max_.x,max_.y,max_.z}};
	glm::vec3 g {glm::vec3{max_.x,min_.y,max_.z}};
	glm::vec3 h {glm::vec3{min_.x,min_.y,max_.z}};

	glm::vec3 normFront = glm::cross(d-a,c-b);
	glm::vec3 normBack  {-normFront.x, -normFront.y, -normFront.z};
	glm::vec3 normRight = glm::cross(g-c,f-d);
	glm::vec3 normLeft  {-normRight.x, -normRight.y, -normRight.z};
	glm::vec3 normTop   = glm::cross(f-a,c-e);
	glm::vec3 normBotom {-normTop.x, -normTop.y, -normTop.z};

	    hit  = inters(a,normFront,ray,a,c,d,b);
	Hit hit2 = inters(e,normBack ,ray,f,e,h,g);
	Hit hit3 = inters(c,normRight,ray,c,f,g,d);
	Hit hit4 = inters(b,normLeft ,ray,e,a,b,h);
	Hit hit5 = inters(f,normTop  ,ray,e,f,c,a);
	Hit hit6 = inters(d,normBotom,ray,b,d,g,h);

//define shape box Boxleinche3 -600 400 -1000 -200 700 -2000

	if(hit2.impact && glm::length(hit2.point - ray.origin) < glm::length(hit.point - ray.origin)) hit = hit2;
	if(hit3.impact && glm::length(hit3.point - ray.origin) < glm::length(hit.point - ray.origin)) hit = hit3;
	if(hit4.impact && glm::length(hit4.point - ray.origin) < glm::length(hit.point - ray.origin)) hit = hit4;
	if(hit5.impact && glm::length(hit5.point - ray.origin) < glm::length(hit.point - ray.origin)) hit = hit5;
	if(hit6.impact && glm::length(hit6.point - ray.origin) < glm::length(hit.point - ray.origin)) hit = hit6;

	hit.shape  = this;

	return hit2;

}

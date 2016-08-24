#include "box.hpp"
#include "vektoroperations.hpp"

Box::Box():
	Shape(),
	min_{0.0f,0.0f,0.0f},
	max_{0.0f,0.0f,0.0f}
	{

	}
Box::Box(glm::vec3 const& min, glm::vec3 const& max):
	Shape(),
	min_{min},
	max_{max}
	{

	}
Box::Box(glm::vec3 const& min, glm::vec3 const& max, std::string const& name, Material const& mat):
	Shape(name, mat),
	min_{min},
	max_{max}
	{

	}
Box::~Box()
{
	std::cout<<"Delete Box"<<std::endl;
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

void Box::minimum(glm::vec3 const& min)
{
    min_ = min;
}
 
void Box::maximum(glm::vec3 const& max)
{
    max_ = max;
}
 

Hit Box::intersect(Ray const& ray) 
{
	if(min_.x > max_.x)std::swap(min_.x, max_.x);
	if(min_.y > max_.y)std::swap(min_.y, max_.y);
	if(min_.z > max_.z)std::swap(min_.z, max_.z);
	//front:
Hit hit = surfacehit (ray, hit, glm::vec3{max_.x,max_.y,max_.z}, glm::vec3{max_.x,min_.y,max_.z}, glm::vec3{min_.x,min_.y,max_.z}, glm::vec3{min_.x,max_.y,max_.z} );
	//back:
	hit = surfacehit (ray, hit, glm::vec3{min_.x,min_.y,min_.z}, glm::vec3{max_.x,min_.y,min_.z}, glm::vec3{max_.x,max_.y,min_.z}, glm::vec3{min_.x,max_.y,min_.z} );
	//right
	hit = surfacehit (ray, hit, glm::vec3{max_.x,max_.y,max_.z}, glm::vec3{max_.x,max_.y,min_.z}, glm::vec3{max_.x,min_.y,min_.z}, glm::vec3{max_.x,min_.y,max_.z} );
	//left
	hit = surfacehit (ray, hit, glm::vec3{min_.x,min_.y,min_.z}, glm::vec3{min_.x,max_.y,min_.z}, glm::vec3{min_.x,max_.y,max_.z}, glm::vec3{min_.x,min_.y,max_.z} );
	//top
	hit = surfacehit (ray, hit, glm::vec3{max_.x,max_.y,max_.z}, glm::vec3{min_.x,max_.y,max_.z}, glm::vec3{min_.x,max_.y,min_.z}, glm::vec3{max_.x,max_.y,min_.z} );
	//bottom
	hit = surfacehit (ray, hit, glm::vec3{min_.x,min_.y,min_.z}, glm::vec3{min_.x,min_.y,max_.z}, glm::vec3{max_.x,min_.y,max_.z}, glm::vec3{max_.x,min_.y,min_.z} );

	if(hit.impact)hit.shape  = this;
	
	return hit;
}
Hit Box::surfacehit(Ray const& ray, Hit const& iHit, glm::vec3 const& a, glm::vec3 const& b, glm::vec3 const& c, glm::vec3 const& d) const
{
	Hit hit;

	glm::vec3 norm {glm::normalize(cross(d - a,b - a))};

	float denominator = skalar(norm , ray.direction);
	if(denominator != 0)
	{
		float distance = (-(norm.x*(ray.origin.x - a.x))-(norm.y*(ray.origin.y - a.y))
			-(norm.z*(ray.origin.z - a.z))) / denominator;
		if(distance > 0)
		{ 
			hit.point  = ray.origin + (distance * ray.direction);
			{
				if( skalar(b-a, hit.point-a) >= 0 and skalar(c-b, hit.point-b) >= 0 and skalar(d-c, hit.point-c) >= 0 and skalar(a-d, hit.point-d) >= 0)
				{
				hit.impact = true;
				hit.normal = norm;
				hit.distance=glm::length(hit.point - ray.origin);
				}
			}
		}
	}
	if(!iHit.impact or (hit.impact and glm::length(hit.point - ray.origin) < glm::length(iHit.point - ray.origin)))
	{
		return hit; 
	}
	else
	{
		return iHit;
	}
}


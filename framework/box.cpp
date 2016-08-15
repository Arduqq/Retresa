#include "box.hpp"
#include "vektoroperations.hpp"

Box::Box():
	Shape(),
	min_{0.0f,0.0f,0.0f},
	max_{0.0f,0.0f,0.0f}
	{
		setSurfaces(min_, max_);
	}
Box::Box(glm::vec3 const& min, glm::vec3 const& max):
	Shape(),
	min_{min},
	max_{max}
	{
		setSurfaces(min_, max_);
	}
Box::Box(glm::vec3 const& min, glm::vec3 const& max, std::string const& name, Material const& mat):
	Shape(name, mat),
	min_{min},
	max_{max}
	{
		setSurfaces(min_, max_);
	}
Box::~Box()
{
	std::cout<<"Delete Box"<<std::endl;
}
void Box::setSurfaces(glm::vec3 const& min, glm::vec3 const& max)
{
	surfaces_.push_back(std::make_shared<Surface>(glm::vec3 {min_.x,min_.y,min_.z}, glm::vec3 {min_.x,max_.y,min_.z}, glm::vec3 {max_.x,max_.y,min_.z}));//front
	surfaces_.push_back(std::make_shared<Surface>(glm::vec3 {max_.x,max_.y,max_.z}, glm::vec3 {min_.x,max_.y,max_.z}, glm::vec3 {min_.x,min_.y,max_.z}));//back
	surfaces_.push_back(std::make_shared<Surface>(glm::vec3 {max_.x,max_.y,min_.z}, glm::vec3 {max_.x,max_.y,max_.z}, glm::vec3 {max_.x,max_.y,min_.z}));//right
	surfaces_.push_back(std::make_shared<Surface>(glm::vec3 {min_.x,min_.y,max_.z}, glm::vec3 {min_.x,max_.y,max_.z}, glm::vec3 {min_.x,max_.y,min_.z}));//left
	surfaces_.push_back(std::make_shared<Surface>(glm::vec3 {min_.x,max_.y,min_.z}, glm::vec3 {min_.x,max_.y,max_.z}, glm::vec3 {max_.x,max_.y,max_.z}));//top
	surfaces_.push_back(std::make_shared<Surface>(glm::vec3 {max_.x,min_.y,max_.z}, glm::vec3 {max_.x,min_.y,min_.z}, glm::vec3 {min_.x,min_.y,min_.z}));//bottom
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
	Hit hit = surfaces_[0]->intersect(ray);
	for(short i = 1 ; i < 6 ; i++)
	{
		Hit newHit = surfaces_[i]->intersect(ray);

		if(!hit.impact || newHit.impact && glm::length(newHit.point - ray.origin) < glm::length(hit.point - ray.origin))
		{
			hit = newHit;
			hit.normal = ((surfaces_[i]->getp1() + surfaces_[i]->getp3())/2) - ((min_+max_)/2);
		}
	}

	hit.shape  = this;
	
	return hit;
}

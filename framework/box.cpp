#include "box.hpp"

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
float Box::area() const
{
	float a = max_.x - min_.x;
	float b = max_.y - min_.y;
	float c = max_.z - min_.z;
	return 2*((a*b)+(b*c)+(a*c));
}  
float Box::volume() const
{
	float a = max_.x - min_.x;
	float b = max_.y - min_.y;
	float c = max_.z - min_.z;
	return a*b*c;
}
std::ostream & Box::print ( std :: ostream & os ) const
{
	Shape::print(os);
	os << "I'm livin in \n" <<"("
	<< min_.x << ", "
	<< min_.y << ", "
	<< min_.z << ") "<<std::endl<<"("
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

/*bool Box::intersect(Ray const& ray, float t) 
{
glm::vec3 dirfrac{1.0f,1.0f,1.0f};

dirfrac.x = 1.0f / ray.direction.x;
dirfrac.y = 1.0f / ray.direction.y;
dirfrac.z = 1.0f / ray.direction.z;

float t1 = (min_.x - ray.origin.x)*dirfrac.x;
float t2 = (max_.x - ray.origin.x)*dirfrac.x;
float t3 = (min_.y - ray.origin.y)*dirfrac.y;
float t4 = (max_.y - ray.origin.y)*dirfrac.y;
float t5 = (min_.z - ray.origin.z)*dirfrac.z;
float t6 = (max_.z - ray.origin.z)*dirfrac.z;

float tmin = std::max(std::max(std::min(t1, t2), std::min(t3, t4)), std::min(t5, t6));
float tmax = std::min(std::min(std::max(t1, t2), std::max(t3, t4)), std::max(t5, t6));

if (tmax < 0)
{
    t = tmax;
    return false;
}

if (tmin > tmax)
{
    t = tmax;
    return false;
}

t = tmin;
return true;

}*/
#include "box.hpp"
#include "surface.hpp"

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

Hit Box::intersect(Ray const& ray) 
{
	Hit hit;
	/*Surface s1{};
	Surface s2{};
	Surface s3{};
	Surface s4{};
	Surface s5{};
	Surface s6{};*/
	return hit;

}
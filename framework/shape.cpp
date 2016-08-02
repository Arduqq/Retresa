#include "shape.hpp"
#include <iostream>

Shape::Shape(): 
name_{"ELShape"},mat_{}
{
  std::cout<<"makin' a lil' Shape"<<std::endl;
}
Shape::Shape(std::string const& name, Material const& mat):
name_{name},mat_{mat}
{
    std::cout<<"makin' a lil' Shape"<<std::endl;
}

Shape::~Shape()
{
  std::cout<<"Killing Shape"<<std::endl;
}

std::string const& Shape::getname() const
{
  return name_;
}
Material const& Shape::getmat() const
{
  return mat_;
}
void  Shape::setname(std::string const& s)
{
	name_=s;
}
void  Shape::setmat( Material const&    m)
{
	mat_=m;
}

std::ostream& operator<<(std::ostream& os, Shape const& s)
{
  return s.print(os);
}
std::ostream & Shape::print ( std :: ostream & os ) const 
{
  os << "Name: " << name_ << std::endl <<" Material: "<< mat_;
  return os;
}
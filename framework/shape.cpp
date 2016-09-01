#include "shape.hpp"
#include <iostream>

Shape::Shape(): name_{"Shape"}, mat_{} {
}

Shape::Shape(std::string const& name, Material const& mat): 
  name_{name}, mat_{mat} 
  {}
Shape::Shape(std::string const& name, Material const& mat, glm::mat4 const& transe): 
  name_{name}, mat_{mat}, world_transformation{transe} 
  {
  	world_transformation_inv = glm::inverse(world_transformation);
  }

Shape::~Shape() {}

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

void Shape::translate(glm::vec3 const& t)
{
  glm::mat4 translateMat = glm::translate(t);

  world_transformation = translateMat * world_transformation;
  world_transformation_inv = glm::inverse(world_transformation); 
  world_transformation_inv_tp = glm::transpose(world_transformation_inv);
}

void Shape::scale(glm::vec3 const& sca)
{
  glm::mat4 sc{sca.x,0.0f ,0.0f ,0.0f,
               0.0f ,sca.y,0.0f ,0.0f,
               0.0f ,0.0f ,sca.z,0.0f,
               0.0f ,0.0f ,0.0f ,1.0f};
  world_transformation = sc * world_transformation;
  world_transformation_inv = glm::inverse(world_transformation);
  world_transformation_inv_tp = glm::transpose(world_transformation_inv);
}

void Shape::rotate(float phi, glm::vec3 const& axis)
{
  glm::mat4 rot{1.0f,  0.0f  ,  0.0f   ,0.0f,
                0.0f,cos(phi),-sin(phi),0.0f,
                0.0f,sin(phi), cos(phi),0.0f,
                0.0f,  0.0f  ,  0.0f   ,1.0f};
  world_transformation = rot * world_transformation;
  world_transformation_inv = glm::inverse(world_transformation);
  world_transformation_inv_tp = glm::transpose(world_transformation_inv);

}

void Shape::rotatead(float phi, glm::vec3 const& n)
{
  glm::mat4 rotad{n.x * n.x * (1-cos(phi)) + cos(phi)       , n.x * n.y * (1-cos(phi)) - n.z * sin(phi) , n.x * n.z * (1-cos(phi)) + n.y * sin(phi) , 0.0f ,
                  n.y * n.x * (1-cos(phi)) + n.z * sin(phi) , n.y * n.y * (1-cos(phi)) + cos(phi)       , n.y * n.z * (1-cos(phi)) - n.x * sin(phi) , 0.0f ,
                  n.z * n.x * (1-cos(phi)) - n.y * sin(phi) , n.z * n.y * (1-cos(phi)) + n.x * sin(phi) , n.z * n.z * (1-cos(phi)) + cos(phi)       , 0.0f , 
                  0.0f                                      ,             0.0f                          ,                 0.0f                      , 1.0f};
  world_transformation = rotad * world_transformation;
  world_transformation_inv = glm::inverse(world_transformation);
  world_transformation_inv_tp = glm::transpose(world_transformation_inv);

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



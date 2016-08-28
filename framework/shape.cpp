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

Ray translate(glm::mat4 const& trans, Ray const& ray){

  float v_x, v_y;
  float v_z;
  float x;
  float y;
  float z;

  glm::mat4 tran{1.0f,0.0f,0.0f,v_x,
                 0.0f,1.0f,0.0f,v_y,
                 0.0f,0.0f,1.0f,v_z, 
                 0.0f,0.0f,0.0f,1.0f};
  glm::vec4 origin{ray.origin,1.0f};
  glm::vec4 direction{ray.direction,1.0f};
  glm::vec4 transori{x,y,z,1.0f};
  glm::vec4 transdir{x,y,z,1.0f};

  transori = tran * origin;
  transdir = tran * direction;
 
  return Ray{glm::vec3{transori.x,transori.y,transori.z}, glm::vec3{transdir.x,transdir.y,transdir.z}};

}

Ray scale(glm::mat4 const& sca, Ray const& ray){

  float s_x;
  float s_y;
  float s_z;
  float x;
  float y;
  float z;

  glm::mat4 sc{s_x,0.0f,0.0f,0.0f,0.0f,s_y,0.0f,0.0f,0.0f,0.0f,s_z,0.0f,0.0f,0.0f,0.0f,1.0f};
  glm::vec4 origin{ray.origin,1.0f};
  glm::vec4 direction{ray.direction,1.0f};
  glm::vec4 scalori{x,y,z,1.0f};
  glm::vec4 scaldir{x,y,z,1.0f};

  scalori = sc * origin;
  scaldir = sc * direction;

  return Ray {glm::vec3{scalori.x,scalori.y,scalori.z}, glm::vec3{scaldir.x,scaldir.y,scaldir.z}};
}

Ray rotate(glm::mat4 const& rotat, Ray const& ray){

  float phi;
  float x;
  float y;
  float z;

  glm::mat4 rot{1.0f,0.0f,0.0f,0.0f,0.0f,cos(phi),-1*sin(phi),0.0f,0.0f,sin(phi),cos(phi),0.0f,0.0f,0.0f,0.0f,1.0f};
  glm::vec4 origin{ray.origin,1.0f};
  glm::vec4 direction{ray.direction,1.0f};
  glm::vec4 rotatori{x,y,z,1.0f};
  glm::vec4 rotatdir{x,y,z,1.0f};

  rotatori = rot * origin;
  rotatdir = rot * direction;

  return Ray {glm::vec3{rotatori.x,rotatori.y,rotatori.z}, glm::vec3{rotatdir.x,rotatdir.y,rotatdir.z}};
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
Ray transformRay(glm::mat4 const& mat, Ray const& ray)
{
	glm::vec4 origin{ray.origin,1};
	glm::vec4 direction{ray.direction,1};


  float v_x;
  float v_y;
  float v_z;
  float s_x;
  float s_y;
  float s_z;
  float phi;

  glm::mat4 translate{1.0f,0.0f,0.0f,v_x,0.0f,1.0f,0.0f,v_y,0.0f,0.0f,1.0f,v_z,0.0f,0.0f,0.0f,1.0f};
  glm::mat4 scale{s_x,0.0f,0.0f,0.0f,0.0f,s_y,0.0f,0.0f,0.0f,0.0f,s_z,0.0f,0.0f,0.0f,0.0f,1.0f};
	glm::mat4 rotate{1.0f,0.0f,0.0f,0.0f,0.0f,cos(phi),-1*sin(phi),0.0f,0.0f,sin(phi),cos(phi),0.0f,0.0f,0.0f,0.0f,1.0f};

  glm::mat4 world_transformation = translate*scale*rotate ;

  //glm::mat4 world_transformation_inv = glm::inverse world_transformation;
  
  //---

	//mat * ray

	//---
	return Ray{glm::vec3{origin.w, origin.x, origin.y}, glm::vec3{direction.w, direction.x, direction.y}};
}

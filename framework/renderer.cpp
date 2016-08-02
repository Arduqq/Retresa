#include "renderer.hpp"
#include "vektoroperations.hpp"
#include <iostream>
#include "camera.hpp"
#include <math.h>

Renderer::Renderer(Scene const& scene, unsigned w, unsigned h, std::string const& file):
  scene_(scene),
  width_(w),
  height_(h), 
  colorbuffer_(w*h, Color(0.0, 0.0, 0.0)), 
  filename_(file), 
  ppm_(width_, height_)
{}

void Renderer::render()
{
  //for (float i= 0; i<500; i+=10)
  {
  glm::vec3 up{0,1,0};
  glm::vec3 eye{0,0,500};
  glm::vec3 dir{0,0,-1}; 
  Camera cam{up, eye, dir ,height_ ,width_};
  
  //std::cout<<i;
  //std::vector<shared_ptr<Shape>>
  //std::vector<Sphere> s{{glm::vec3{0.0,0.0,-500},100},{glm::vec3{0.0,200,-400},100},{glm::vec3{200,0.0,-400},100},{glm::vec3{0.0,-200,-400},100},{glm::vec3{-200,0.0,-400},100}};
  std::shared_ptr<Sphere> s = std::make_shared <Sphere> (glm::vec3{0.0,0.0,-600},200);
  /*Sphere s[1] = {glm::vec3{0.0,200,-300},200};
  Sphere s[2] = {glm::vec3{200,0.0,-300},200};
  Sphere s[3] = {glm::vec3{0.0,-200,-300},200};
  Sphere s[4] = {glm::vec3{-200,0.0,-300},200};*/
  
  for (unsigned y = 0; y < height_; ++y) 
  {
    for (unsigned x = 0; x < width_; ++x) 
    {

      Pixel p(x,y);
      
      Ray ronny = cam.calculateRay(x,y);

      p.color = raytrace(ronny,s,1);

      write(p);
    }
  }
}
  ppm_.save(filename_);
}

Color Renderer::raytrace(Ray const& ronny, std::shared_ptr<Sphere> const& s,unsigned int depth) const
{
  depth --;
  Color c{0,0,0};
  for (int obj = 0; obj<5 ; obj++)
    {
      Hit hit = s->intersect(ronny);
      if (hit.impact)
      {
        //glm::vec3 light{0,0,-250};

        //Ray ralf{hit.point, light - hit.point}; //beleuchtet?
        //Hit hit2 = s[obj].intersect(ralf);

        glm::vec3 debugNormal = 0.5f * hit.normal + glm::vec3(0.5);
        c = Color(debugNormal.x,debugNormal.y,debugNormal.z);
      } 
      else 
      {
        //p.color = Color(0.0, 0.0, 0.0);
      }
      
    }
  return c;
}
void Renderer::write(Pixel const& p)
{
  // flip pixels, because of opengl glDrawPixels
  size_t buf_pos = (width_*p.y + p.x);
  if (buf_pos >= colorbuffer_.size() || (int)buf_pos < 0) {
    std::cerr << "Fatal Error Renderer::write(Pixel p) : "
      << "pixel out of ppm_ : "
      << (int)p.x << "," << (int)p.y
      << std::endl;
  } else {
    colorbuffer_[buf_pos] = p.color;
  }

  ppm_.write(p);
}
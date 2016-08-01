#include "renderer.hpp"
#include "vektoroperations.hpp"
#include <iostream>
#include "camera.hpp"
#include <math.h>

Renderer::Renderer(unsigned w, unsigned h, std::string const& file):
  width_(w),
  height_(h), 
  colorbuffer_(w*h, Color(0.0, 0.0, 0.0)), 
  filename_(file), 
  ppm_(width_, height_)
{}

void Renderer::render()
{
  glm::vec3 up{0,1,0};
  glm::vec3 eye{0,0,100};
  glm::vec3 dir{0,0,-1}; 
  Camera cam{up, eye, dir ,height_ ,width_};
  
  //for (float i= 0; i<1000; i+=50)
  {
  //std::cout<<i;
  Sphere s{glm::vec3{0.0,0.0,-300},200};
  
  for (unsigned y = 0; y < height_; ++y) 
  {
    for (unsigned x = 0; x < width_; ++x) 
    {

      Pixel p(x,y);
      
      Ray ronny = cam.calculateRay(x,y);
      //std::cout<<ronny.origin.x<<" "<<ronny.origin.y<<" "<<ronny.origin.z<<" - "<<ronny.direction.x<<" "<<ronny.direction.y<<" "<<ronny.direction.z;
      Hit hit = s.intersect(ronny);
      if (hit.impact)
      {
        glm::vec3 light{0,-400,-100};

        Ray ralf{hit.point, light - hit.point}; //beleuchtet?
        Hit hit2 = s.intersect(ralf);

        glm::vec3 debugNormal = 0.5f * hit.normal + glm::vec3(0.5);
        if(!hit2.impact) p.color = Color(debugNormal.x,debugNormal.y,debugNormal.z);
        else p.color = Color(debugNormal.x/5,debugNormal.y/5,debugNormal.z/5);
      } 
      else 
      {
        p.color = Color(0.0, 0.0, 0.0);
      }



      write(p);
    }
  }
}
  ppm_.save(filename_);
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
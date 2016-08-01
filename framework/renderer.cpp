#include "renderer.hpp"
#include "vektoroperations.hpp"
#include <iostream>
#include "camera.hpp"
#include <math.h>
//#define DEBUG false
Renderer::Renderer(unsigned w, unsigned h, std::string const& file):
  width_(w),
  height_(h), 
  colorbuffer_(w*h, Color(0.0, 0.0, 0.0)), 
  filename_(file), 
  ppm_(width_, height_)
{}

void Renderer::render()
{
  Camera cam{glm::vec3{0,1,0},glm::vec3{0,0,200},glm::vec3{0,0,-1},height_,width_};
  
  Sphere s{glm::vec3{0.0,0.0,400},100};
  
  for (unsigned y = 0; y < height_; ++y) 
  {
    for (unsigned x = 0; x < width_; ++x) 
    {

      Pixel p(x,y);
      
      Ray ronny = cam.calculateRay(x,y);

      Hit hit = s.intersect(ronny);//Ray{glm::vec3{x,y,0},glm::vec3{0,0,-1}},1);
      if (hit.impact)
      {
        glm::vec3 light{0,200,300};

        float helle = absolute(hit.point - ronny.origin)/200;

        //Ray ralf{hit.point, light - hit.point};
        //Hit hit2 = s.intersect(ralf);
    
        p.color = Color(1-helle,1-helle,1-helle);
        
      } 
      else 
      {
        p.color = Color(0.0, 0.0, 0.0);
      }



      write(p);
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
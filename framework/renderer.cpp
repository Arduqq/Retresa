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

  glm::vec3 up{0,1,0};
  glm::vec3 eye{0,0,500};
  glm::vec3 dir{0,0,-1}; 
  Camera cam{up, eye, dir ,height_ ,width_};
  
  for (unsigned y = 0; y < height_; ++y) 
  {
    for (unsigned x = 0; x < width_; ++x) 
    {

      Pixel p(x,y);
      
      Ray ronny = cam.calculateRay(x,y);
      
      p.color = raytrace(ronny,1);

      write(p);
    }
  }

  ppm_.save(filename_);
}

Color Renderer::raytrace(Ray const& ronny,unsigned int depth) const
{
depth --;
  
  for(unsigned int i = 0; i < scene_.sizeShape; i++)
  {
    if(scene_.shapes[i] != nullptr)
    {
      Hit hit = scene_.shapes[i]->intersect(ronny);
      if (hit.impact)
      {
        //glm::vec3 light{0,0,-250};

        //Ray ralf{hit.point, light - hit.point}; //beleuchtet?
        //Hit hit2 = s[obj].intersect(ralf);

        glm::vec3 debugNormal = 0.5f * hit.normal + glm::vec3(0.5);
        Color c = Color(debugNormal.x,debugNormal.y,debugNormal.z);
        return c;
      } 
      else 
      {
        //p.color = Color(0.0, 0.0, 0.0);
      }



    }
    else std::cout<< "scene_.shapes["<<i<<"] == nullptr"<<std::endl;
  }


  
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
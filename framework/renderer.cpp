#include "renderer.hpp"
#include "vektoroperations.hpp"
#include <iostream>
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
  const std::size_t checkersize = 20;
  Sphere s{glm::vec3{300.0,300.0,2.0},250.0};
  for (unsigned y = 0; y < height_; ++y) 
  {
    for (unsigned x = 0; x < width_; ++x) 
    {
#if 0
      Ray ray = scene_.camera.calc_eye_ray(x,y);
      p.color = raytrace(ray, 3);
#else
      std::cout<<x<<" "<<y<<std::endl;
      
      Pixel p(x,y);

      Hit hit = s.intersect(Ray{glm::vec3{x,y,0},glm::vec3{0,0,-1}},1);
      if (hit.impact)
      {
        float dunkel = absolute(hit.point-glm::vec3{x,y,0})/100;
        glm::vec3 debugNormal = 0.5f * hit.normal + glm::vec3(0.5);
        p.color = Color(debugNormal.x, debugNormal.y, debugNormal.z);
        //p.color = Color(dunkel,dunkel,dunkel);
      } 
      else 
      {
        p.color = Color(0.0, 0.0, 0.0);
      }
#endif
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
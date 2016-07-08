#include "renderer.hpp"
#include <iostream>

Renderer::Renderer(unsigned w, unsigned h, std::string const& file):
  width_(w),
  height_(h), 
  colorbuffer_(w*h, Color(0.0, 0.0, 0.0)), 
  filename_(file), 
  ppm_(width_, height_)
{}

#if 0
Color Renderer::raytrace(Ray const& ray, unsigned int)
{
  if depth <= 0
    return black
  else
    OptionalHit o = get nearest Object in scene for ray
    if o.hit then
      Color color = shade(o, ray) // + raytrace(reflect(ray, objectnormal), --depth)
      return color

}
#endif
float betrag(glm::vec3 v)
{
  return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}
void Renderer::render()
{
  const std::size_t checkersize = 20;
  Sphere s{glm::vec3{300.0,300.0,2.0},100.0};
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
      Hit hit= s.intersect(Ray{glm::vec3{x,y,0},glm::vec3{0,0,-1}},1);
      if (hit.impact)
      {
        float dunkel = betrag(hit.point-glm::vec3{x,y,0})/100;
        p.color = Color(dunkel,dunkel,dunkel);
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
/*  for (unsigned y = 0; y < height_; ++y) {
    for (unsigned x = 0; x < width_; ++x) {
#if 0
      Ray ray = scene_.camera.calc_eye_ray(x,y);
      p.color = raytrace(ray, 3);
#else

      Pixel p(x,y);
      if ( ((x/checkersize)%2) != ((y/checkersize)%2)) {
        p.color = Color(0.0, 1.0, float(x)/height_);
      } else {
        p.color = Color(1.0, 0.0, float(y)/width_);
      }
#endif
      write(p);
    }
  }
  ppm_.save(filename_);
}*/
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
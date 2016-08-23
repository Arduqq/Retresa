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
  if(scene_.sizeShape > 0)
  {
    for (unsigned y = 0; y < height_; ++y) 
    {
      for (unsigned x = 0; x < width_; ++x) 
      {
        Pixel p(x,y);
        
        Ray ronny = scene_.cam->calculateRay(x,y);
        
        p.color = raytrace(ronny,1);

        write(p);
      }
    }
  }
  else
  {
    std::cout<<"Es wurden keine Objekte geladen."<<std::endl;
  }
  ppm_.save(filename_);
}

Color Renderer::raytrace(Ray const& ronny,unsigned int depth) const
{
  depth --;

  Hit hit = calculateHit(ronny);

  if (hit.impact)
      {
        Color c{0,0,0};
        float ia = 0.10;
        float ip = 0, LN = 0, RV = 0;
        Material mat{hit.shape->getmat()};

        c.r = ia * mat.ka_.r; //die abmienten
        c.g = ia * mat.ka_.g; //terme werden
        c.b = ia * mat.ka_.b; //zugewiesen

        if(1)//illuminate(hit.point, hit.shape))
        { 
          for (unsigned int i = 0 ; i < scene_.sizeLight ; i++)
          {
            ip = scene_.lights[i]->intensity;
            LN = skalar(glm::normalize(scene_.lights[i]->pos - hit.point) , glm::normalize(hit.normal));
            RV = skalar(glm::normalize(mirror(scene_.lights[i]->pos , Ray{hit.point, hit.normal})) , glm::normalize(ronny.origin - hit.point));

            //RV = RV / scene_.sizeLight;
            if(LN < 0) LN = 0;
            if(RV < 0) RV = 0;
            c.r += ip * (LN + mat.ks_.r * pow(RV,mat.m_));
            c.g += ip * (LN + mat.ks_.g * pow(RV,mat.m_));
            c.b += ip * (LN + mat.ks_.b * pow(RV,mat.m_));
          }
        }

        return c;
      } 

}
Hit Renderer::calculateHit(Ray const& rafa) const
{
  Hit hit = scene_.shapes[0]->intersect(rafa);
  
  for(unsigned int i = 1; i < scene_.sizeShape; i++)
  {
    if(scene_.shapes[i] != nullptr)
    {
      Hit newHit = scene_.shapes[i]->intersect(rafa);

        if(!hit.impact || (newHit.impact && glm::length(newHit.point - rafa.origin) < glm::length(hit.point - rafa.origin)))
        {
          hit = newHit;
        }
    }
    else std::cout<< "scene_.shapes["<<i<<"] == nullptr"<<std::endl;
  }
  return hit;
}

bool Renderer::illuminate(glm::vec3 const& point ,Shape* const& shape) const
{
  for(unsigned i =0; i < scene_.sizeLight; i++)
  {
    Ray robert{ point,scene_.lights[i]->pos - point};

    Hit isilluminated = calculateHit(robert);

    if(!isilluminated.impact or glm::length( point - scene_.lights[i]->pos) < glm::length( point - isilluminated. point) or isilluminated.shape == shape)
    { 
      return true;
    }
    else 
    {
      return false;
    }
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
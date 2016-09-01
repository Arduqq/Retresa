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
        
        p.color = antialias(p);
        p.color = tonemap(p.color);

        write(p);
      }
    }//hier ist der colorbuffer geladen
  }
  else
  {
    std::cout<<"Es wurden keine Objekte geladen."<<std::endl;
  }
  ppm_.save(filename_);
}

Color Renderer::raytrace(Ray const& ronny,unsigned int depth) const
{
  Hit hit = calculateHit(ronny);
  Color c{0,0,0};
  if (hit.impact)
      {
        if(depth < 1) 
        {
          Color s = shade(hit, ronny);
          c.r += s.r;
          c.g += s.g;
          c.b += s.b;
        }
        else
        {
          depth --;
          Ray mirrorRay{hit.point, mirror(ronny.origin , Ray{hit.point, hit.normal})};
          Color g = shade(hit, ronny);
          Color s = raytrace(mirrorRay, depth);
          float mirrorFactor = (hit.shape->getmat().m_); 
          c.r = g.r + (s.r * (mirrorFactor*0.2 / (1 + mirrorFactor*0.2)));
          c.g = g.g + (s.g * (mirrorFactor*0.2 / (1 + mirrorFactor*0.2)));
          c.b = g.b + (s.b * (mirrorFactor*0.2 / (1 + mirrorFactor*0.2)));          
        }
      } 
    return c;
}

Color Renderer::shade(Hit const& hit, Ray const& ray) const
{
  Color c{1,0,0};
  float ia = 0.10;
  float ip = 0, LN = 0, RV = 0;
  Material mat{hit.shape->getmat()};
  c.r = ia * mat.ka_.r; //die abmienten
  c.g = ia * mat.ka_.g; //terme werden
  c.b = ia * mat.ka_.b; //zugewiesen
  
    for (unsigned int i = 0 ; i < scene_.sizeLight ; i++)
    {
      if(illuminate(hit, scene_.lights[i]->pos))
      {
        ip = scene_.lights[i]->intensity; //intensität des lichts
        LN = skalar(glm::normalize(scene_.lights[i]->pos - hit.point) , glm::normalize(hit.normal)); //winkel normale / blickwinkel
        RV = skalar(glm::normalize(mirror(scene_.lights[i]->pos , Ray{hit.point, hit.normal})) , glm::normalize(ray.origin - hit.point));

        if(LN < 0) LN = 0;
        if(RV < 0) RV = 0;
        c.r += ip * (LN * mat.kd_.r + mat.ks_.r * pow(RV,mat.m_));
        c.g += ip * (LN * mat.kd_.g + mat.ks_.g * pow(RV,mat.m_));
        c.b += ip * (LN * mat.kd_.b + mat.ks_.b * pow(RV,mat.m_));
      }
    }
    //std::cout<<c.r<<" "<<c.g<<" "<<c.b<<"     ";
  return c;
}

Hit Renderer::calculateHit(Ray const& rafa) const
{
  Hit nearest;
  for(auto const& shape: scene_.shapes)
  {
    if(shape != nullptr)
    {
      Ray ray{rafa.origin,glm::normalize(rafa.direction)};

      Hit newHit = shape->intersect(ray);

        if(newHit.impact && 0.0001 < newHit.distance && newHit.distance < nearest.distance)
        {
          nearest = newHit;
        }
    }
    else std::cout<< "shape == nullptr"<<std::endl;
  }
  return nearest;
}

bool Renderer::illuminate(Hit const& hit, glm::vec3 const& lightPos) const
{
  float epschilom = 0.001f;

  glm::vec3 point = hit.point + (epschilom * glm::normalize(hit.normal));

  Hit shadow = calculateHit(Ray{ point , lightPos - point});

  return (!shadow.impact or glm::length( point - lightPos) < glm::length( point - shadow. point) );
}

Color Renderer::tonemap(Color c){
  float r,g,b;
  float l = 0.2126 * c.r + 0.7512 * c.g + 0.0722 * c.b;
  /*
  //John Hable Method
  r=std::max(0.0f,c.r-0.004f);
  g=std::max(0.0f,c.g-0.004f);
  b=std::max(0.0f,c.b-0.004f);
  r=(r*(6.2*r+0.5))/(r*(6.2*r+1.7)+0.06);
  g=(g*(6.2*g+0.5))/(g*(6.2*g+1.7)+0.06);
  b=(b*(6.2*b+0.5))/(b*(6.2*b+1.7)+0.06);
  return {r,g,b};
  
  */
  //Simple Operator
  return{c.r+0.1f,c.g+0.1f,c.b+0.1f};
  
  
  //Filmic Operator (http://filmicgames.com/archives/75)
  /*float A = 0.15; //shoulder strength
  float B = 0.50; //linear strength
  float C = 0.10; //linear angle
  float D = 0.20; //toe strength
  float E = 0.02; //toe numerator
  float F = 0.30; //toe denominator
  float W = 11.2; //linear hitepoint
  r=((2*c.r * (A * 2*c.r + C * B) + D * E) / (2*c.r * (A * 2*c.r + B) + D * F)) - E / F;
  g=((2*c.g * (A * 2*c.g + C * B) + D * E) / (2*c.g * (A * 2*c.g + B) + D * F)) - E / F;
  b=((2*c.b * (A * 2*c.b + C * B) + D * E) / (2*c.b * (A * 2*c.b + B) + D * F)) - E / F;
  r = r * (1 /  ((W * (A * W + C * B) + D * E) / (W * (A * W + B) + D * F)) - E / F);
  g = g * (1 /  ((W * (A * W + C * B) + D * E) / (W * (A * W + B) + D * F)) - E / F);
  b = b * (1 /  ((W * (A * W + C * B) + D * E) / (W * (A * W + B) + D * F)) - E / F);
  return {r,g,b};*/
  
}

void Renderer::write(Pixel const& p)
{
  // flip pixels, because of opengl glDrawPixels
  size_t buf_pos = (width_*p.y + p.x);

  if (buf_pos >= colorbuffer_.size() or (int)buf_pos < 0) 
  {
    std::cerr << "Fatal Error Renderer::write(Pixel p) : "
      << "pixel out of ppm_ : "
      << (int)p.x << "," << (int)p.y
      << std::endl;
  } 
  else 
  {
    colorbuffer_[buf_pos] = p.color;
  }
  ppm_.write(p);
}

Color Renderer::antialias(Pixel p)
{ 
  std::vector<Ray> rays;
  float x = p.x;
  float y = p.y;
  rays.push_back({scene_.cam->calculateRay(x, y)});
  //Kein AA
  rays.push_back({scene_.cam->calculateRay(x + 0.5, y + 0.5)});
  rays.push_back({scene_.cam->calculateRay(x - 0.5, y - 0.5)});
  rays.push_back({scene_.cam->calculateRay(x - 0.5, y + 0.5)});
  rays.push_back({scene_.cam->calculateRay(x + 0.5, y - 0.5)});
  Color colorAA{0.0f,0.0f,0.0f};
        for (auto ronny : rays) {
            colorAA += raytrace(ronny, 2);
        }
  return 1.0f / rays.size() * colorAA;;
}
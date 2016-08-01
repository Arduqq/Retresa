#ifndef BUW_RENDERER_HPP
#define BUW_RENDERER_HPP

#include "color.hpp"
#include "pixel.hpp"
#include "ppmwriter.hpp"
#include "sphere.hpp"
#include <string>
#include <glm/glm.hpp>
#include <memory>

class Renderer
{
public:
  Renderer(/*Scene const& scene,*/ unsigned w, unsigned h, std::string const& file);

  void render();
  Color raytrace(Ray const& ronny,std::shared_ptr<Sphere> const& s, unsigned int depth) const;
  // Color shade(OptionalHit const&, Ray const&, unsigned depth) const
  void write(Pixel const& p);

  inline std::vector<Color> const& colorbuffer() const
  {
    return colorbuffer_;
  }

private:
  //Scene scene_;
  unsigned width_;
  unsigned height_;
  std::vector<Color> colorbuffer_;
  std::string filename_;
  PpmWriter ppm_;
};

#endif // #ifndef BUW_RENDERER_HPP

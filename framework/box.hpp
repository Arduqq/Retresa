#ifndef BOX_HPP
#define BOX_HPP

#include "shape.hpp"
#include <glm/vec3.hpp>

class Box: public Shape
{
public:
	Box();
	Box(glm::vec3 const& min, glm::vec3 const& max);
	Box(glm::vec3 const& min, glm::vec3 const& max, std::string const& name, Material const& mat);
	~Box();

	Hit intersect (Ray const& ray) override;

	const glm::vec3 &getmin() const;
	const glm::vec3 &getmax() const;

	std::ostream & print ( std :: ostream & os ) const override;


private: 
	glm::vec3 min_;
	glm::vec3 max_;
};

#endif
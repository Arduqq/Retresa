#ifndef CONE_HPP
#define CONE_HPP

#include "shape.hpp"
#include <vector>
#include <memory>
#include <glm/vec3.hpp>

class Cone: public Shape
{
public:
	Cone();
	Cone(glm::vec3 const& ctr, float rad, glm::vec3 const& peak);
	Cone(glm::vec3 const& ctr, float rad, glm::vec3 const& peak, std::string const& name, Material const& mat);
	~Cone();

	//Hit intersect (Ray const& ray) override;

	std::ostream & print ( std :: ostream & os) const override;
	glm::vec3 const& getctr()    const;
	float     const& getrad()    const;
	glm::vec3 const& getpeak() const;
	void setctr(glm::vec3 const& ctr);
	void setrad(float rad);
	void setpeak(glm::vec3 const& peak);


private:
	glm::vec3 ctr_;
	float     rad_;
	glm::vec3 peak_;

};

#endif 
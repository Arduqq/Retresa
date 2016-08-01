#ifndef LIGHTS_HPP
#define LIGHTS_HPP

struct Light
{

	float intensity;
	Color color;
	std::string name;
	glm::vec3 pos;

	Light():
	name{"Default"},
	intensity{100},
	Color{1.0,1.0,1.0},
	pos{0.0,0.0,0.0};

	Light(std::string const& n, float i,Color const& c, glm::vec3 const& v ):
	name{n},
	intensity{i},
	Color{c},
	pos{v};

};

#endif
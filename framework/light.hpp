#ifndef LIGHTS_HPP
#define LIGHTS_HPP

//#include "color.hpp"

struct Light
{

	std::string name;	
	glm::vec3 pos;
	Color color;
	float intensity;

	Light():
	name{"Default"},
	pos{0.0,0.0,0.0},
	color{1.0,1.0,1.0},
	intensity{100}{}

	Light(std::string const& n, float i,Color const& c, glm::vec3 const& v ):
	name{n},
	pos{v},
	color{c},
	intensity{i}{}

	friend std::ostream& operator<<(std::ostream& os, Light const& l)
	{
		os << " Name: " << l.name << " Position: (" << l.pos.x << ", "<< l.pos.y << ","<< l.pos.z << " Color: " << 
		l.color.r <<", "<<l.color.g <<", "<<l.color.b <<") Intensity: "<< l.intensity;

		return os;
	}


};


#endif
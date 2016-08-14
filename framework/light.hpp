#ifndef LIGHTS_HPP
#define LIGHTS_HPP

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
	intensity{1}{}

	Light(std::string const& n, glm::vec3 const& v, Color const& c,float i):
	name{n},
	pos{v},
	color{c},
	intensity{i}{}

	friend std::ostream& operator<<(std::ostream& os, Light const& l)
	{
		os << "Name: " << l.name <<"\n" 
		<< "Position: (" << l.pos.x << ", "<< l.pos.y << ","<< l.pos.z << ")\n" 
		<< "Color: (" << l.color.r <<", "<<l.color.g <<", "<<l.color.b <<")\n"
		<<"Intensity: "<< l.intensity<<"\n";

		return os;
	}


};


#endif
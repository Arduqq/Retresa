#ifndef CAMERA
#define CAMERA

#include <glm/vec3.hpp>
#include <ray.hpp>

class Camera
{
public:

	Camera(glm::vec3 const& e, glm::vec3 const& d, float u, unsigned h, unsigned w):
		up_{u},
		eye_{e},
		dir_{glm::normalize(d)},
		height_{h},
		width_{w}{}

	inline Ray calculateRay(unsigned xInp, unsigned yInp)
	{
		glm::mat4 camMat {rx,vx,-dx,x,
						  ry,vy,-dy,y,
						  rz,vz,-dz,z,
						  0 , 0, 0 ,1};
		
		glm::vec3 xyCentre{glm::vec3{dir_.x * 1000, dir_.y * 1000, dir_.z * 1000} + eye_ };

		glm::vec3 colY{0,1,0};//später wird der mittels Drehmatrix um dir_ im winkel up gedreht.
		glm::vec3 rowX{glm::normalize(glm::cross(dir_,colY))}; 
		//std::cout<<xyCentre.x<<" "<<xyCentre.y<<" "<<xyCentre.z<<" "<<std::endl;
		int x = xInp - (width_/2);
		int y = yInp - (height_/2);

		Ray ronny{eye_, glm::normalize((xyCentre + glm::vec3{x * rowX.x, x * rowX.y, x * rowX.z} + glm::vec3{y * colY.x, y * colY.y, y * colY.z}) - eye_)};/* glm::normalize(glm::vec3{x, y, 0} - eye)*/ 
		return ronny;
	}

private:
	float up_;
	glm::vec3 eye_;
	glm::vec3 dir_;
	unsigned height_;
	unsigned width_;
};

#endif
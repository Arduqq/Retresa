#ifndef CAMERA
#define CAMERA

#include <glm/vec3.hpp>
#include <ray.hpp>

class Camera
{
public:
	//camera <name> <fov-x> <eye> <dir> <up>
	Camera(std::string const& name, float fovX, glm::vec3 const& e, glm::vec3 const& d, glm::vec3 const up, unsigned h, unsigned w):
		name_{name},
		fovX_{fovX},
		up_{up},
		eye_{e},
		dir_{glm::normalize(d)},
		height_{h},
		width_{w}
		{
			u_ = glm::normalize(glm::cross(dir_ , up_));
			v_ = glm::normalize(glm::cross(u_  , dir_));
			dist_ = 1 / (2 * (tan(fovX / 2)));
		}

	inline Ray calculateRay(unsigned xInp, unsigned yInp)
	{
		glm::mat4 camMat{ u_.x, v_.x, -dir_.x, eye_.x,
						  u_.y, v_.y, -dir_.y, eye_.y,
						  u_.z, v_.z, -dir_.z, eye_.z,
						  0   , 0   , 0      ,      1};
		float xF = xInp;
		float yF = yInp;

		float x = (xF / width_) - 0.5;
		float y = (yF / height_) - 0.5;

		Ray ronny{glm::vec3{0, 0, 0}, glm::normalize(glm::vec3{x, y, -dist_})};

		//std::cout<<ronny.direction.x<<" "<<ronny.direction.y<<" "<<ronny.direction.z<<std::endl;

		/*glm::vec3 xyCentre{glm::vec3{dir_.x * 1000, dir_.y * 1000, dir_.z * 1000} + eye_ };

		glm::vec3 colY{0,1,0};
		glm::vec3 rowX{glm::normalize(glm::cross(dir_,colY))}; 
		//std::cout<<xyCentre.x<<" "<<xyCentre.y<<" "<<xyCentre.z<<" "<<std::endl;
		int x = xInp - (width_/2);
		int y = yInp - (height_/2);

		Ray ronny{eye_, glm::normalize((xyCentre + glm::vec3{x * rowX.x, x * rowX.y, x * rowX.z} + glm::vec3{y * colY.x, y * colY.y, y * colY.z}) - eye_)};/* glm::normalize(glm::vec3{x, y, 0} - eye)*/ 
		return ronny;
	}

private:
	
	float fovX_;
	float dist_;
	std::string name_;
	glm::vec3 eye_;
	glm::vec3 dir_;
	glm::vec3 up_;
	glm::vec3 u_;
	glm::vec3 v_;
	unsigned height_;
	unsigned width_;

};

#endif
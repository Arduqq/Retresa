#ifndef CAMERA
#define CAMERA

#include <glm/vec3.hpp>
#include <ray.hpp>

class Camera
{
public:
	Camera(std::string const& name, float fovX, glm::vec3 const& e, glm::vec3 const& d, glm::vec3 const up, unsigned h, unsigned w):
		name_{name},
		fovX_{fovX},
		up_{up},
		eye_{e},
		dir_{glm::normalize(d)},
		height_{h},
		width_{w}
		{
			u_ = glm::normalize(glm::cross(dir_ , up_));//gemäß der Vorlesung
			v_ = glm::normalize(glm::cross(u_  , dir_));
			dist_ = 1 / (2 * (tan(fovX / 2))); //entfernung Bildfläche eye
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
		float y = ((yF / height_)-0.5 ) * (height_/width_) ;

		Ray ronny{glm::vec3{0, 0, 0}, glm::normalize(glm::vec3{x, y, -dist_})};

		glm::vec4 RayTrafOri{ronny.origin,    1};
		glm::vec4 RayTrafDir{ronny.direction, 0};

		RayTrafDir = RayTrafDir * camMat;
		RayTrafOri = RayTrafOri * camMat;

		return Ray{glm::vec3{RayTrafOri.x, RayTrafOri.y, RayTrafOri.z}, glm::vec3{RayTrafDir.x, RayTrafDir.y, RayTrafDir.z} };
	}
	inline std::string name()
	{
		return name_; //getter
	}

private:
	std::string name_;
	float fovX_;
	float dist_;
	glm::vec3 eye_;
	glm::vec3 dir_;
	glm::vec3 up_;
	glm::vec3 u_;
	glm::vec3 v_;
	unsigned height_;
	unsigned width_;

};

#endif
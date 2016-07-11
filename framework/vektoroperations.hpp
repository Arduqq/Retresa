#ifndef Vector_operations
#define Vector_operations

#include <glm/glm.hpp>
#include <cmath>

// equivalent glm::cross
inline glm::vec3 cross(glm::vec3 const& v1, glm::vec3 const& v2)
{
	glm::vec3 res;
	res.x=(v1.y * v2.z) - (v1.z * v2.y);
	res.y=(v1.z * v2.x) - (v1.x * v2.z);
	res.z=(v1.x * v2.y) - (v1.y * v2.x);
	return res;
}

// Das ist equivalent zu glm::length
inline float absolute(glm::vec3 const& v)
{
	return std::sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

#endif
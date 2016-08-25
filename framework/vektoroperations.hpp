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
inline float skalar(glm::vec3 const& a,glm::vec3 const& b)
{
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}
inline float winkel(glm::vec3 const& a,glm::vec3 const& b)
{
	return acos(skalar(a,b)/(absolute(a)*absolute(b)));
}
inline glm::vec3 operator/(glm::vec3 const& v, float a)
{
	return glm::vec3{v.x / a, v.y / a, v.z / a};
}
inline glm::vec3 operator*(glm::vec3 const& v, float a)
{
	return glm::vec3{v.x * a, v.y * a, v.z * a};
}
inline glm::vec3 mirror(glm::vec3 const& point, Ray const& norm)
{
	glm::vec3 N = glm::normalize(norm.direction);
	glm::vec3 L = glm::normalize(point - norm.origin);

	return N * 2 * skalar(N , L) - L;

}

#endif
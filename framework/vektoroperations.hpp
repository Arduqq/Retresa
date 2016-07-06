#ifndef Vector_operations
#define Vector_operations

glm::vec3 cross(glm::vec3 v1, glm::vec3 v2)
{
	glm::vec3 res;
	res.x=(v1.y * v2.z) - (v1.z * v2.y);
	res.y=(v1.z * v2.x) - (v1.x * v2.z);
	res.z=(v1.x * v2.y) - (v1.y * v2.x);
	return res;
}
float absolute(glm::vec3 v)
{
	return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

#endif
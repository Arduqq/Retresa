#include "box.hpp"

Box::Box():
	Shape(),
	min_{0.0f,0.0f,0.0f},
	max_{0.0f,0.0f,0.0f}
	{}
Box::Box(glm::vec3 const& min, glm::vec3 const& max):
	Shape(),
	min_{min},
	max_{max}
	{}
Box::Box(glm::vec3 const& min, glm::vec3 const& max, std::string const& name, Material const& mat):
	Shape(name, mat),
	min_{min},
	max_{max}
	{}
Box::~Box()
{
	std::cout<<"Delete Box"<<std::endl;
}
std::ostream & Box::print ( std :: ostream & os ) const
{
	Shape::print(os);
	os << "Location Min: ("
	<< min_.x << ", "
	<< min_.y << ", "
	<< min_.z << ") Max :("
	<< max_.x << ", "
	<< max_.y << ", "
	<< max_.z << ")"<<std::endl;
}

glm::vec3 const& Box::getmin() const
{
	return min_;
}

glm::vec3 const& Box::getmax() const 
{
	return max_;
}

void Box::minimum(glm::vec3 const& min)
{
    min_ = min;
}
 
void Box::maximum(glm::vec3 const& max)
{
    max_ = max;
}
 

Hit Box::intersect(Ray const& raytf) 
{
	Ray ray = raytf.transformRay(world_transformation_inv);

	if(min_.x > max_.x)std::swap(min_.x, max_.x);
	if(min_.y > max_.y)std::swap(min_.y, max_.y);
	if(min_.z > max_.z)std::swap(min_.z, max_.z);
	//front:
Hit hit[6];
    hit[0] = surfacehit (ray, /*hit,*/ glm::vec3{max_.x,max_.y,max_.z}, glm::vec3{max_.x,min_.y,max_.z}, glm::vec3{min_.x,min_.y,max_.z}, glm::vec3{min_.x,max_.y,max_.z} );	
	//back:
	hit[1] = surfacehit (ray, /*hit,*/ glm::vec3{min_.x,min_.y,min_.z}, glm::vec3{max_.x,min_.y,min_.z}, glm::vec3{max_.x,max_.y,min_.z}, glm::vec3{min_.x,max_.y,min_.z} );
	//right
	hit[2] = surfacehit (ray, /*hit,*/ glm::vec3{max_.x,max_.y,max_.z}, glm::vec3{max_.x,max_.y,min_.z}, glm::vec3{max_.x,min_.y,min_.z}, glm::vec3{max_.x,min_.y,max_.z} );
	//left
	hit[3] = surfacehit (ray, /*hit,*/ glm::vec3{min_.x,min_.y,min_.z}, glm::vec3{min_.x,max_.y,min_.z}, glm::vec3{min_.x,max_.y,max_.z}, glm::vec3{min_.x,min_.y,max_.z} );
	//top
	hit[4] = surfacehit (ray, /*hit,*/ glm::vec3{max_.x,max_.y,max_.z}, glm::vec3{min_.x,max_.y,max_.z}, glm::vec3{min_.x,max_.y,min_.z}, glm::vec3{max_.x,max_.y,min_.z} );
	//bottom
	hit[5] = surfacehit (ray, /*hit,*/ glm::vec3{min_.x,min_.y,min_.z}, glm::vec3{min_.x,min_.y,max_.z}, glm::vec3{max_.x,min_.y,max_.z}, glm::vec3{max_.x,min_.y,min_.z} );

	Hit nearest;

	for (int i = 0; i < 6; i++)
	{
     if(hit[i].impact && 0.0001 < hit[i].distance && hit[i].distance < nearest.distance)
        {
          nearest = hit[i];
        }
	}

	if(nearest.impact)
	{
		nearest.shape  = this;
		return nearest;
	}
	else return Hit{};
}
Hit Box::surfacehit(Ray const& ray, glm::vec3 const& p1, glm::vec3 const& p2, glm::vec3 const& p3, glm::vec3 const& p4) const
{
	Hit hit;
	
	glm::vec3 norm {glm::normalize(cross(p4 - p1,p2 - p1))};

	float denominator = skalar(norm , ray.direction);
	if(denominator != 0)
	{
		float distance = (-(norm.x*(ray.origin.x - p1.x))-(norm.y*(ray.origin.y - p1.y))
			-(norm.z*(ray.origin.z - p1.z))) / denominator;//ebenenintersect

		if(distance > 0.001)
		{ 
			glm::vec3 object_position = ray.origin + (distance * ray.direction);

			glm::vec3 world_position{world_transformation * glm::vec4{object_position,1} };
			glm::vec4 world_normal{world_transformation_inv_tp * glm::vec4{norm  ,0} };

			hit.point  = object_position;
			{
				if(skalar(p4-p1, p1 - hit.point) <= 0 and skalar(p1-p2, p2 - hit.point) <= 0 and skalar(p2-p3, p3 - hit.point) <= 0 and skalar(p3-p4, p4 - hit.point) <= 0)
				{//flächenbegrenzung
					hit.point  = world_position;
					hit.impact = true;
					hit.normal = glm::vec3{world_normal.x,world_normal.y,world_normal.z};
					hit.distance= distance;
				}
			}
		}
	}
	if(hit.impact)
	{
		return hit;
	}
	else return Hit{};
}


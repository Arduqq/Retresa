#include "composite.hpp"

Composite::Composite() {}

Composite::Composite(std::string name): name_{name} {}

Composite::~Composite() {}

void Composite::addChild(std::shared_ptr<Shape>& shape)
{
	shapes_.push_back(shape);
}

void Composite::removeChild(std::shared_ptr<Shape>& shape)
{
	std::vector<std::shared_ptr<Shape>>::iterator it;

	for (it = shapes_.begin(); it!=shapes_.end(); )
	{
		if ((*it)==shape)
		{
			it = shapes_.erase(it);
		}
		else
		{
			++it;
		}
	}

}

void Composite::print(std::ostream os) const{
	for(auto x: shapes_) {
		x->print(os);
	}
}

std::vector<std::shared_ptr<Shape>> Composite::getChild(){
	return shapes_;
}

Hit Composite::intersect(Ray const& ray){
	Hit a;
	
	return a;
}

void Composite::translate(glm::vec3 const& trans){
	for (auto element : shapes_){
    element->translate(trans);
	std::cout<<"Translated "<<element->getname()<<" from "<<this->getname()<<std::endl;
	}	
}
void Composite::scale(glm::vec3 const& sca){
	for (auto element : shapes_){
    element->scale(sca);
	std::cout<<"Scaled "<<element->getname()<<" from "<<this->getname()<<std::endl;
	}
}
void Composite::rotate(float phi , glm::vec3 const& axis){
	for (auto element : shapes_){
    element->rotate(phi,axis);
	std::cout<<"Rotated "<<element->getname()<<" from "<<this->getname()<<std::endl;
	}
}
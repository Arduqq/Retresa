#include "composite.hpp"

Composite::Composite() {}

Composite::Composite(std::string name): name_{name} {}

Composite::~Composite() {}

/*
-> Fügt ein Shape (Box, Sphere, Composite) am Anfang der Map an

~WIP~
*/
void Composite::addChild(std::shared_ptr<Shape>& shape){
	shapes_.push_back(shape);
}

void Composite::removeChild(std::shared_ptr<Shape>& shape){
	std::vector<std::shared_ptr<Shape>>::iterator it;
	for (it=shapes_.begin();it!=shapes_.end();){
		if ((*it)==shape){
			it = shapes_.erase(it);
		}
		else{
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
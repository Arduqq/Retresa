#include "composite.hpp"

Composite::Composite(): shapes_(),name_(){}

Composite::~Composite() {}

/*
-> Fügt ein Shape (Box, Sphere, Composite) am Anfang der Map an

~WIP~
*/
void Composite::addChild(std::shared_ptr<Shape>& shape){
	shapes_.push_back(shape);
}

void Composite::removeChild(std::shared_ptr<Shape>& shape){
	shapes_.erase(std::remove(shapes_.begin(),shapes_.end(), shape),shapes_.end()); 
}

void Composite::print(std::ostream os) const{
	for(auto x: shapes_) {
		x->print(os);
	}
}

std::vector<std::shared_ptr<Shape>> Composite::getChild(){
	return shapes_;
}

Hit intersect(Ray const & ray){
	Hit a;
	return a;
}
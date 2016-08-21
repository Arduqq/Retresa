#include "composite.hpp"

Composite::Composite(){}
Composite::~Composite(){}

/*
-> Fügt ein Shape (Box, Sphere, Composite) am Anfang der Map an

~WIP~
*/
void Composite::addChild(std::shared_ptr<Shape>& shape){
	shapes_.insert(shapes_.begin(),std::pair<std::string, std::shared_ptr<Shape>>(shape->getname(),shape));
}

void Composite::removeChild(std::string const& name){
	shapes_.erase(name);
}

std::ostream& Composite::print(std::ostream os) const{
	for(auto x: shapes_) {
		x.second->print(os); //x.second = zweite Spalte von x
	}
	return os;
}

std::map<std::string, std::shared_ptr<Shape>> Composite::getChild(){
	return shapes_;
}
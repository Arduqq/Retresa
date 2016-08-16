#ifndef COMPOSITE_HPP
#define COMPOSITE_HPP

#include <map>
#include <string>
#include <iostream>
#include <memory>
#include "Shape.hpp"
#include "Box.hpp"
#include "Sphere.hpp"

/*
Composite (7.2)
-------------------------------------------------------------
-> Composite-Pattern entspricht Baumstruktur

          --Composite-Box
Composite-|           -- Sphere
	  --Composite-|
                      -- Box

-> Zusammensetzungen von Objekten können
   können uniform behandelt werden

http://www.bogotobogo.com/DesignPatterns/composite.php
-> Knoten müssen aus Composites bestehen, Blätter sind Shapes
-------------------------------------------------------------
[] Sceneloader muss um ein weiteres if erweitert werden
[] define shape composite [Knoten] [Blatt_1] ... [Blatt_n]
[] Endboss: Composites müssen gerendert werden
[] Könnte vielleicht ein paar Tests vertragen (*)
[] Composites aus Composites aus Composites möglich? (opt.)
*/

class Composite : public Shape{
public:
	Composite();
	~Composite();

	void addChild(std::shared_ptr<Shape>& shape); //*
	void removeChild(std::string const& name); //*

	std::ostream& print(std::ostream os) const;

	std::map<std::string, std::shared_ptr<Shape>> getChild(); //*

private:
	std::map<std::string,std::shared_ptr<Shape>> shapes_;
};

#endif

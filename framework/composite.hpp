#ifndef COMPOSITE_HPP
#define COMPOSITE_HPP

#include "shape.hpp"
#include "box.hpp"
#include "sphere.hpp"

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <memory>


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
[X] Sceneloader muss um ein weiteres if erweitert werden
[X] define shape composite [Knoten] [Blatt_1] ... [Blatt_n]
[] Endboss: Composites müssen gerendert werden
[X] Könnte vielleicht ein paar Tests vertragen (*)
[] Composites aus Composites aus Composites möglich? (opt.)


~WIP~
*/

class Composite : public Shape{
public:
	Composite();
	~Composite();

	void addChild(std::shared_ptr<Shape>& shape) override; //*
	void removeChild(std::shared_ptr<Shape>& shape) override; //*

	void print(std::ostream os) const;

	std::vector<std::shared_ptr<Shape>> getChild() override; //*
	Hit intersect(Ray const& ray) override;

private:
	std::string name_;
	std::vector<std::shared_ptr<Shape>> shapes_;
};

#endif

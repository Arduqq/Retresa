#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <ostream>
#include "color.hpp"
#include <string>

struct Material
{	
	std::string name_;
	Color ka_;
	Color kd_;
	Color ks_;
	float m_;

	Material():

	name_{"Default"},
	ka_  {0.0f,0.0f,0.0f},
	kd_  {0.0f,0.0f,0.0f},
	ks_  {0.0f,0.0f,0.0f},
	m_   {0}{}

	Material(std::string const& name, Color const& ka, Color const& kd, Color const& ks, float m):

	name_{name},
	ka_  {ka},
	kd_  {kd},
	ks_  {ks},
	m_   {m}{}

	friend std::ostream& operator<<(std::ostream& os, Material const& m ) 
	{
		os << "name: " << m.name_ << "\n"
		<<"ka: "<< m.ka_
		<<"kd: "<< m.kd_
		<<"ks: "<< m.ks_
		<<"m: "  << m.m_ << "\n";
		return os;
	}

};
#endif


/*Implementieren Sie ein Struct Material. Es soll die Membervariablen name
vom Typ string, ka, kd, ks vom Typ color und m vom Typ float besitzen.
Die Klasse soll Standard- und User-Konstruktor besitzen. Implementieren Sie
außerdem den Streamoperator (operator<<) zur Ausgabe. Ersetzen Sie den
Color-Member in der Shape durch einen Material-Member und passen Sie die
Getter an. Commiten Sie ihre Änderungen.*/
// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include "material.hpp"
#include <map>
#include <sstream>


int main () {
  using namespace std;
  string line;
  ifstream myfile ("../Material.sdf");

  map<string, Material> materials;

  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      stringstream ss;
      ss<<line;
      Material mat;
      string keyword;
      ss>>keyword;
      ss>>keyword;
      ss>>mat.name_;
      //read ambient term
      ss >> mat.ka_.r;
      ss >> mat.ka_.g;
      ss >> mat.ka_.b;
      //read diffuse term
      ss >> mat.kd_.r;
      ss >> mat.kd_.g;
      ss >> mat.kd_.b;
      //read specular term
      ss >> mat.ks_.r;
      ss >> mat.ks_.g;
      ss >> mat.ks_.b;

      ss >> mat.m_;

      materials[mat.name_] = mat;

      cout<<mat;
    }
    myfile.close();
  }

  else cout << "Unable to open file"; 

  return 0;
}
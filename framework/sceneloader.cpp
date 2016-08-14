#include <iostream>
#include <fstream>
#include <string>
#include "scene.hpp"
#include "sphere.hpp"
#include "surface.hpp"
#include "box.hpp"
#include <map>
#include <memory>
#include <sstream>

void Scene::loadscene(std::string const& input) {
  std::string line;
  std::ifstream myfile (input);//"../Material.sdf");

  std::map<std::string, Material> materials;

  sizeShape = sizeLight = 0;

  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      std::stringstream ss;
      ss<<line;

      std::string keyword;

      ss>>keyword;

      if(keyword == "#")
        {
          continue;
        }

      if(keyword == "define")
      {
        std::string objClass;

        ss>>objClass;

        if(objClass == "shape") //alles was hinter define steht
        {

          std::string shapeType;

          ss>>shapeType;

          if (shapeType == "sphere") //alles was hinter shape steht
          {
            std::string name;
            float x,y,z,r;
            Material mat;

            ss>>name;
            ss>>x;
            ss>>y;
            ss>>z;
            ss>>r;
            //ss>>mat;

            shapes.push_back(std::make_shared<Sphere>(glm::vec3{x,y,z},r,name,mat)); // neues Object in scene schreiben
            sizeShape++;
            std::cout<<"Loaded shape nr " <<sizeShape<<". (Sphere) "<<*shapes[sizeShape-1]<<" - Success"<<std::endl;
          }
          else if (shapeType == "surface")
          {
            std::string name;
            float x1,y1,z1,x2,y2,z2,x3,y3,z3,l,w;
            Material mat;

            ss>>name;
            ss>>x1;
            ss>>y1;
            ss>>z1;
            ss>>x2;
            ss>>y2;
            ss>>z2;
            ss>>x3;
            ss>>y3;
            ss>>z3;

            //ss mat

            shapes.push_back(std::make_shared<Surface>(glm::vec3 {x1,y1,z1}, glm::vec3 {x2,y2,z2}, glm::vec3 {x3,y3,z3}, name, mat));
            sizeShape++;
            std::cout<<"Loaded shape nr " <<sizeShape<<". (Surface) "<<*shapes[sizeShape-1]<<" - Success"<<std::endl;
          }
          else if (shapeType == "box")
          {
            std::string name;
            float x1,y1,z1,x2,y2,z2;
            Material mat;

            ss>>name;
            ss>>x1;
            ss>>y1;
            ss>>z1;
            ss>>x2;
            ss>>y2;
            ss>>z2;
            //ss mat

            shapes.push_back(std::make_shared<Box>(glm::vec3 {x1,y1,z1}, glm::vec3 {x2,y2,z2}, name, mat));
            sizeShape++;
            std::cout<<"Loaded shape nr " <<sizeShape<<". (Box) "<<*shapes[sizeShape-1]<<" - Success"<<std::endl;
          }

        }
        else if (objClass == "material")
          {
            Material mat;
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
            std::cout<<"Loaded Material: "<<mat<<" - Success"<<std::endl;
          }
        else if(objClass == "light")
          {
            std::string name;
            float x,y,z,r,g,b,intensity;

            ss>>name;

            ss>>x;
            ss>>y;
            ss>>z;

            ss>>r;
            ss>>g;
            ss>>b;

            ss>>intensity;
            
            lights.push_back(std::make_shared<Light>(name, glm::vec3{x,y,z}, Color{r,g,b}, intensity));

            sizeLight ++;
            std::cout<< "Loaded Light NR "<<sizeLight<<" "<<*lights[sizeLight-1]<<" - Success"<<std::endl;
          }
        else if(objClass == "camera")
          {
            float ex, ey, ez, dx, dy, dz, u;
            unsigned int h,w;

            ss>>ex;
            ss>>ey;
            ss>>ez;

            ss>>dx;
            ss>>dy;
            ss>>dz;

            ss>>u;
            ss>>h;
            ss>>w;

            cam = std::make_shared<Camera>(glm::vec3{ex, ey, ez}, glm::vec3{dx, dy, dz}, u, h, w);

            std::cout<< "Loaded Camera. Eye: ("<<ex<<", "<<ey<<", "<<ez<<") Direction: ("<<dx<<", "<<dy<<", "<<dz<<") Up: "<<u<<" - Success"<<std::endl;
          }
        else std::cout<< "Dinge hinter 'define' wurden nicht erkannt";
        }
        else if (keyword == "render")
        {
          //tbi
        }
        else
        {
          std::cout<<"Unable to read some Things. Check ur Stuff!"<<std::endl;
        }
      }
      std::cout<<"successfully loaded " << sizeShape << " Objects in Scene."<<std::endl;

    myfile.close();
  }

  else std::cout << "Unable to open file"; 

}

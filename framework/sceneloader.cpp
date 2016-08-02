// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include "scene.hpp"
#include "sphere.hpp"
#include <map>
#include <memory>
#include <sstream>



Scene Scene::loadscene(std::string const& input) {
  std::string line;
  std::ifstream myfile (input);//"../Material.sdf");

  std::map<std::string, Material> materials;

  Scene loadScene;

  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      std::stringstream ss;
      ss<<line;

      std::string keyword;

      ss>>keyword;

      if(keyword == "#"){break;}

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

            Sphere sphere{glm::vec3{x,y,z},r,name,mat};

            std::cout<<"Loaded Sphere: "<<sphere<<" - Success"<<std::endl;
          }
          else if (shapeType == "box")
          {

            //tbi
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
            Light light;

            ss<<light.name;

            ss<<light.pos.x;
            ss<<light.pos.y;
            ss<<light.pos.z;

            ss<<light.color.r;
            ss<<light.color.g;
            ss<<light.color.b;

            ss<<light.intensity;

            std::cout<< "Loaded Light: "<<light<<" - Success"<<std::endl;
          }
        else if(objClass == "camera")
          {
            //tbi
            break;
          }
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

    myfile.close();
  }

  else std::cout << "Unable to open file"; 

  return loadScene;
}

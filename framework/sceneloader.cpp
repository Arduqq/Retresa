#include <iostream>
#include <fstream>
#include <string>
#include "scene.hpp"
#include "sphere.hpp"
#include "box.hpp"
#include "triangle.hpp"
#include "cylinder.hpp"
#include "cone.hpp"
#include <map>
#include <memory>
#include <sstream>

void Scene::loadscene(std::string const& input) {
  std::string line;
  std::ifstream myfile (input);//"../Material.sdf");

  std::map<std::string, Material> materials;
  std::map<std::string, std::shared_ptr<Shape>> compositeBasin;
  Scene scene;

  sizeShape = sizeLight = 0;

  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      std::stringstream ss;
      ss<<line;

      std::string keyword;

      ss>>keyword;

      if(keyword == "#" or keyword == " " or keyword == "")
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
          /*
          define shape sphere [Name] [Zentrum (X,Y,Z)] [Radius] [Material]
          */
          if (shapeType == "sphere") //alles was hinter shape steht
          {
            std::string name,mat_name;
            float x,y,z,r;
            Material mat;
            ss>>name;
            ss>>x;
            ss>>y;
            ss>>z;
            ss>>r;
            ss>>mat_name;
            mat=materials.find(mat_name)->second; 
            std::shared_ptr<Shape> sphere=std::make_shared<Sphere>(glm::vec3{x,y,z},r,name,mat);
            shapes.push_back(sphere); // neues Object in scene schreiben
            sizeShape++;
            std::cout<<"Loaded shape #" <<sizeShape<<". (Sphere) "<<*shapes[sizeShape-1]<<" - Success\n"<<std::endl;
            compositeBasin.insert(std::pair<std::string, std::shared_ptr<Shape>>(sphere->getname(), sphere));
          }
          /*
          define shape triangle [Name] [Punkt A (X,Y,Z)] [Punkt B (X,Y,Z)] [Punkt C (X,Y,Z)] [Material]
          */
          else if(shapeType == "triangle")
          {
            std::string name,mat_name;
            float x1,y1,z1,x2,y2,z2,x3,y3,z3;
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
            ss>>mat_name;
            mat = materials.find(mat_name)->second; 
            std::shared_ptr<Shape> triangle=std::make_shared<Triangle>(glm::vec3 {x1,y1,z1}, glm::vec3 {x2,y2,z2}, glm::vec3 {x3,y3,z3}, name, mat);
            shapes.push_back(triangle);
            sizeShape++;
            std::cout<<"Loaded shape #" <<sizeShape<<". (Triangle) "<<*shapes[sizeShape-1]<<" - Success\n"<<std::endl;
            compositeBasin.insert(std::pair<std::string, std::shared_ptr<Shape>>(triangle->getname(), triangle));
          }
          /*
          define shape box [Name] [Punkt A (X,Y,Z)] [Punkt B (X,Y,Z)] [Punkt C (X,Y,Z)] [Material]
          */
          else if (shapeType == "box")
          {
            std::string name,mat_name;
            float x1,y1,z1,x2,y2,z2;
            Material mat;
            ss>>name;
            ss>>x1;
            ss>>y1;
            ss>>z1;
            ss>>x2;
            ss>>y2;
            ss>>z2;
            ss>>mat_name;
            mat=materials.find(mat_name)->second; 
            std::shared_ptr<Shape> box = std::make_shared<Box>(glm::vec3 {x1,y1,z1}, glm::vec3 {x2,y2,z2}, name, mat);
            shapes.push_back(box);
            sizeShape++;
            std::cout<<"Loaded shape #" <<sizeShape<<". (Box) "<<*shapes[sizeShape-1]<<" - Success\n"<<std::endl;
            compositeBasin.insert(std::pair<std::string, std::shared_ptr<Shape>>(box->getname(), box));
          }
          /*
          define shape cylinder [Name] [Zentrum (X,Y,Z)] [Radius] [Höhe] [Material]
          */
          else if(shapeType == "cylinder")
          {
            std::string name,mat_name;
            float x,y,z,r,h;
            Material mat;
            ss>>name;
            ss>>x;
            ss>>y;
            ss>>z;
            ss>>r;
            ss>>h;
            ss>>mat_name;
            mat = materials.find(mat_name)->second; 
            std::shared_ptr<Shape> cylinder = std::make_shared<Cylinder>(glm::vec3{x,y,z}, r, h, name, mat);
            shapes.push_back(cylinder);
            sizeShape++;
            std::cout<<"Loaded shape #" <<sizeShape<<". (Cylinder) "<<*shapes[sizeShape-1]<<" - Success\n"<<std::endl;
            compositeBasin.insert(std::pair<std::string, std::shared_ptr<Shape>>(cylinder->getname(), cylinder));
          }
          /*
          define shape cone [Name] [Zentrum (X,Y,Z)] [Spitze (X,Y,Z)] [Radius] [Material]
          */
          else if(shapeType == "cone")
          {
            std::string name,mat_name;
            float x1,y1,z1,x2,y2,z2,r;
            Material mat;
            ss>>name;
            ss>>x1;
            ss>>y1;
            ss>>z1;
            ss>>x2;
            ss>>y2;
            ss>>z2;
            ss>>r;
            ss>>mat_name;
            mat = materials.find(mat_name)->second; 
            std::shared_ptr<Shape> cone = std::make_shared<Cone>(glm::vec3{x1,y1,z1}, r, glm::vec3{x2,y2,z2}, name, mat);
            shapes.push_back(cone);
            sizeShape++;
            std::cout<<"Loaded shape #" <<sizeShape<<". (Cone) "<<*shapes[sizeShape-1]<<" - Success\n"<<std::endl;
            compositeBasin.insert(std::pair<std::string, std::shared_ptr<Shape>>(cone->getname(), cone));
          }
          /*
          define shape composite [Name] [Obekt_1] [Objekt_2] ... [Objekt_n]
          */
          else if (shapeType == "composite")
          {
            std::string nameComposite, nameShape;
            ss>>nameComposite;
            scene.composite=std::make_shared<Composite>(nameComposite);
            while (!ss.eof())
            {
              ss>>nameShape;
              auto it = compositeBasin.find(nameShape);
              if(it != compositeBasin.end())
              {
                scene.composite->addChild(it->second);
              }
            }
            std::cout<<"Loaded composite " << nameComposite <<" - Success\n"<<std::endl;
          }

        }
        /*
        define material [Name] [Ambient] [Diffuse] [Specular]
        */
        else if (objClass == "material")
          {
            Material mat;
            ss>>mat.name_;
            ss >> mat.ka_.r;
            ss >> mat.ka_.g;
            ss >> mat.ka_.b;
            ss >> mat.kd_.r;
            ss >> mat.kd_.g;
            ss >> mat.kd_.b;
            ss >> mat.ks_.r;
            ss >> mat.ks_.g;
            ss >> mat.ks_.b;

            ss >> mat.m_;

            materials[mat.name_] = mat;
            std::cout<<"Loaded Material: "<<mat<<" - Success\n"<<std::endl;
          }
        /*
        define light [Name] [Herkunft (X,Y,Z)] [Farbwert (R,G,B)] [Intensität]
        */
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
            std::cout<< "Loaded Light #"<<sizeLight<<" "<<*lights[sizeLight-1]<<" - Success\n"<<std::endl;
          }
        /*
        define camera [Quelle (X,Y,Z)] [Richtung (X,Y,Z)] [Neigung] [Höhe] [Breite]
        */
        else if(objClass == "camera")
          {
            std::string name;
            float fovX, ex, ey, ez, dx, dy, dz, ux, uy, uz;
            unsigned int h,w;

            ss>>name;

            ss>>fovX;

            ss>>ex;
            ss>>ey;
            ss>>ez;

            ss>>dx;
            ss>>dy;
            ss>>dz;

            ss>>ux;
            ss>>uy;
            ss>>uz;

            ss>>h;
            ss>>w;

            cam = std::make_shared<Camera>(name, fovX, glm::vec3{ex, ey, ez}, glm::vec3{dx, dy, dz}, glm::vec3{ux, uy, uz}, h, w);

            std::cout<< "Loaded Camera "<<name<<". FovX: "<<fovX<<". Eye: ("<<ex<<", "<<ey<<", "<<ez
                     <<") Direction: ("<<dx<<", "<<dy<<", "<<dz
                     <<") Up: "<<ux<<", "<<uy<<", "<<uz<<" - Success"<<std::endl;
          }
        else std::cout<< "Dinge hinter 'define' wurden nicht erkannt\n";
        }
        else if (keyword == "render")
        {
          std::string nameCam,nameImg;
          unsigned xRes, yRes;

          ss>>nameCam;
          ss>>OPfileName;

          ss>>width;
          ss>>height;

          if(nameCam != cam->name())
          {
            std::cout<<"Nichtubereinstimmender name der Camera. \nEs wird '"<<cam->name()<<"' verwendet."<<std::endl;
          }

        }
        else if(keyword == "transform")
        {
          std::string name, transformation;
          
          ss>>name;
          ss>>transformation;
          
          if(transformation == "scale")
          {
            float x, y, z;
            ss>>x;
            ss>>y;
            ss>>z;

            auto it = compositeBasin.find(name);
              if(it != compositeBasin.end())
              {
                it->second -> scale(glm::vec3{x,y,z});
              }

          }
          else if(transformation == "translate")
          {
            float x, y, z;
            ss>>x;
            ss>>y;
            ss>>z;

            auto it = compositeBasin.find(name);
              if(it != compositeBasin.end())
              {
                it->second -> translate(glm::vec3{x,y,z});
              }
          }
          else if(transformation == "rotate")
          {
            float x, y, z, k;
            ss>>k;
            ss>>x;
            ss>>y;
            ss>>z;

            auto it = compositeBasin.find(name);
              if(it != compositeBasin.end())
              {
                it->second -> rotate(k, glm::vec3{x,y,z});
              }
          }
          else if(transformation == "rotatead")
          {
            float x , y , z , k;
            ss>>k;
            ss>>x;
            ss>>y;
            ss>>z;

            auto it = compositeBasin.find(name);
              if(it != compositeBasin.end())
              {
                it->second -> rotatead(k, glm::vec3{x,y,z});
              }
          }
          else
          {
            std::cout<<"!! Transformationsbefehl unbekannt !! \n";
          }
        }
        else
        {
          std::cout<<"Unable to read some Things. Check ur Stuff!\n"<<std::endl;
        }
      }
      std::cout<<"successfully loaded " << sizeShape << " Objects in Scene.\n"<<std::endl;

    myfile.close();
  }

  else std::cout << "Unable to open file"; 

}

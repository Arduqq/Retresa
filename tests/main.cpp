//#define CATCH_CONFIG_RUNNER

//#include <catch.hpp>
#include "box.hpp"
#include "sphere.hpp"
#include "shape.hpp"
#include <glm/vec3.hpp>
#include "material.hpp"

#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
/*
TEST_CASE ("intersectRaySphere","[intersect]" )
{
	Ray ronny(glm::vec3{0,0,0},glm::vec3{0,0,1});
	Sphere s(glm::vec3{0,0,3},1);
	REQUIRE(s.intersect(ronny,1));
}

TEST_CASE("1","[one]")
{
	Box bochs  {};
	Box bochs2 {glm::vec3{0,2,4},glm::vec3{1,4,8}};

	glm::vec3 null{0,0,0};
	glm::vec3 a{0,2,4};
	glm::vec3 b{1,4,8};

	REQUIRE(bochs.getmin()==null);
	REQUIRE(bochs.getmax()==null);
	REQUIRE(bochs2.getmin()==a);
	REQUIRE(bochs2.getmax()==b);
	REQUIRE(bochs2.volume()== 8);
	REQUIRE(bochs2.area()==28);

	Sphere kgl {};
	Sphere kgl2 {glm::vec3{3,2,1},4};

	glm::vec3 c{3,2,1};

	REQUIRE(kgl.getctr()==null);
	REQUIRE(kgl.getrad()==1);
	REQUIRE(kgl2.getctr()==c);
	REQUIRE(kgl2.getrad()==4);
	REQUIRE(kgl2.volume()== Approx(268.08258f));
	REQUIRE(kgl2.area()==Approx(201.06194f));

}

TEST_CASE("3","[three]")
{
	Color MatCol{1,1,1};

	Material ma{"a",MatCol,MatCol,MatCol,1};
	Material mb{"b",MatCol,MatCol,MatCol,1};


	Box bochs {glm::vec3 {1,2,3}, glm::vec3 {4,5,6}, "Don Box", ma};
	Sphere kgl {glm::vec3 {-1,-2,-3}, 1,"Soy una Kugel", mb};

	Material m1 = kgl.getmat();
	Material m2 = bochs.getmat();
	REQUIRE(kgl.getname()=="Soy una Kugel");
	REQUIRE(m1.name_== "b");
	REQUIRE(m1.ka_  == MatCol);
	REQUIRE(m1.kd_  == MatCol);
	REQUIRE(m1.ks_  == MatCol);
	REQUIRE(m1.m_   == 1);


	REQUIRE(bochs.getname()=="Don Box");
	REQUIRE(m2.name_== "a");
	REQUIRE(m2.ka_  == MatCol);
	REQUIRE(m2.kd_  == MatCol);
	REQUIRE(m2.ks_  == MatCol);
	REQUIRE(m2.m_   == 1);

}

TEST_CASE("6","[six]")
{
	Color MatCol{1,1,1};

	Material ma{"a",MatCol,MatCol,MatCol,1};
	Sphere kgl {glm::vec3 {3,3,3}, 1,"Soy una Kugel", ma};

	Ray ralf   {glm::vec3 {1,1,1}, glm::vec3 {4,4,4}};
	Ray ronny  {glm::vec3 {4,4,4}, glm::vec3 {2,2,2}};
	Ray roland {glm::vec3 {4,4,4}, glm::vec3 {6,6,6}};

	REQUIRE( kgl.intersect(ralf , 2)); 
	REQUIRE( kgl.intersect(ralf , 0));
	/*REQUIRE(!kgl.intersect(ronny, 2));
	REQUIRE(!kgl.intersect(ronny, 0));
	REQUIRE(!kgl.intersect(roland,2));
	REQUIRE(!kgl.intersect(roland,0));
}
TEST_CASE("boxintersect", "[box]")
{
  Box b{glm::vec3{0.0f}, glm::vec3{1.0f}};

  glm::vec3 origin{-1.0f,-1.0f,-1.0f};
  glm::vec3 direction{1.0f,1.0f,1.0f};

  glm::vec3 origin2{2.0f,2.0f,2.0f};
  glm::vec3 direction2{-1.0f,-1.0f,-1.0f};

  glm::vec3 origin3{-5.5f,-153.5f,98.5f};
  glm::vec3 direction3 = glm::vec3(0.5f,0.5f,0.5f) - origin3;

  glm::vec3 origin4{1.1f,1.1f,1.1f};
  glm::vec3 direction4{2.0f,2.0f,2.0f};


  Ray triffter{origin,direction};
  Ray triffter2{origin2,direction2};
  Ray triffter3{origin3,direction3};
  Ray triffter4{origin4,direction4};
  
  float x = 1.0f;

  REQUIRE(b.intersect(triffter, x));
  REQUIRE(b.intersect(triffter2, x));
  REQUIRE(b.intersect(triffter3, x));
  REQUIRE(!b.intersect(triffter4, x));
}*/

int main(int argc, char *argv[])
{
  /*return Catch::Session().run(argc, argv);*/
	Ray ronny1(glm::vec3{0,0,0},glm::vec3{0,0,1});
	Ray ronny2(glm::vec3{0,0,0},glm::vec3{1,1,1});
	Ray ronny3(glm::vec3{0,0,0},glm::vec3{-1,-1,-1});
	Ray ronny4(glm::vec3{1,1,1},glm::vec3{-1,-1,-1});

	Sphere s1(glm::vec3{0,0,3},1);
	Sphere s2(glm::vec3{4,4,4},1);
	Sphere s3(glm::vec3{-2,-2,-2},1);
	Sphere s4(glm::vec3{-3,-3,-3},1);

	Hit hit1 = s1.intersect(ronny1,1);
	Hit hit2 = s2.intersect(ronny2,1);
	Hit hit3 = s3.intersect(ronny3,1);
	Hit hit4 = s4.intersect(ronny4,1);

	std::cout<<"\n"<<hit1.impact<<std::endl;
	std::cout<<"\n"<<hit2.impact<<std::endl;
	std::cout<<"\n"<<hit3.impact<<std::endl;
	std::cout<<"\n"<<hit4.impact<<std::endl;

	Ray ronny5(glm::vec3{0,0,0},glm::vec3{0,0,1});
	Ray ronny6(glm::vec3{0,0,0},glm::vec3{1,1,1});
	Ray ronny7(glm::vec3{0,0,0},glm::vec3{-1,-1,-1});
	Ray ronny8(glm::vec3{1,1,1},glm::vec3{-1,-1,-1});

	Sphere s5(glm::vec3{4,4,10},6);
	Sphere s6(glm::vec3{4,4,6},3);
	Sphere s7(glm::vec3{-5,-4,-5},2);
	Sphere s8(glm::vec3{-3,-4,-3},2);

	Hit hit5 = s5.intersect(ronny5,1);
	Hit hit6 = s6.intersect(ronny6,1);
	Hit hit7 = s7.intersect(ronny7,1);
	Hit hit8 = s8.intersect(ronny8,1);

	std::cout<<"\n"<<hit5.impact<<std::endl;
	std::cout<<"\n"<<hit6.impact<<std::endl;
	std::cout<<"\n"<<hit7.impact<<std::endl;
	std::cout<<"\n"<<hit8.impact<<std::endl;
	
	return 0;
}

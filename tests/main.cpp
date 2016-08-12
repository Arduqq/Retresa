#define CATCH_CONFIG_RUNNER
 
#include <catch.hpp>
#include "box.hpp"
#include "sphere.hpp"
#include "shape.hpp"
#include <glm/vec3.hpp>
#include "material.hpp"
 
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
 
TEST_CASE("Boxmin","[minimum]"){
    Box b{};
    REQUIRE(Approx(0.0f) == b.getmin().x);
    REQUIRE(Approx(0.0f) == b.getmin().y);
    REQUIRE(Approx(0.0f) == b.getmin().z);
 
   
    glm::vec3 max{1.5f,5.6f,2.3f};
    glm::vec3 min{2.0f,3.3f,4.0f};
   
    Box b1{min, max};
    REQUIRE(Approx(2.0f) == b1.getmin().x);
    REQUIRE(Approx(3.3f) == b1.getmin().y);
    REQUIRE(Approx(4.0f) == b1.getmin().z);
}
 
TEST_CASE("BoxSetsMin","[setminimum]"){
 
    Box b1{};
    b1.minimum({1.0f, 1.0f, 1.0f});
    REQUIRE(Approx(1.0f) == b1.getmin().x);
    REQUIRE(Approx(1.0f) == b1.getmin().y);
    REQUIRE(Approx(1.0f) == b1.getmin().z);
 
    glm::vec3 min2{2.0f, 3.3f, 4.0f};
    glm::vec3 max2{1.5f, 5.6f, 2.3f};
 
    Box b2{min2, max2};
    b2.minimum({2.3f, 1.3f, 4.3f});
    REQUIRE(Approx(2.3f) == b2.getmin().x);
    REQUIRE(Approx(1.3f) == b2.getmin().y);
    REQUIRE(Approx(4.3f) == b2.getmin().z);
 
    glm::vec3 min3{1.0f, 2.3f, 4.1f};
    glm::vec3 max3{0.0f, 2.5f, 1.2f};
 
    Box b3{min3, max3};
    b3.minimum({6.9f, 4.2f, 1.6f});
    REQUIRE(Approx(6.9f) == b3.getmin().x);
    REQUIRE(Approx(4.2f) == b3.getmin().y);
    REQUIRE(Approx(1.6f) == b3.getmin().z);
 
}
 
TEST_CASE("Boxmax","[maximum]"){
 
    Box b{};
    REQUIRE(Approx(0.0f) == b.getmax().x);
    REQUIRE(Approx(0.0f) == b.getmax().y);
    REQUIRE(Approx(0.0f) == b.getmax().z);
 
    glm::vec3 min{2.0f,3.3f,4.0f};
    glm::vec3 max{1.5f,5.6f,2.3f};
 
    Box b1{min, max};
    REQUIRE(Approx(1.5f) == b1.getmax().x);
    REQUIRE(Approx(5.6f) == b1.getmax().y);
    REQUIRE(Approx(2.3f) == b1.getmax().z);
}
 
TEST_CASE("BoxSetsMax","[setsmaximum]"){
 
    Box b1{};
    b1.maximum({1.0f, 1.0f, 1.0f});
    REQUIRE(Approx(1.0f) == b1.getmax().x);
    REQUIRE(Approx(1.0f) == b1.getmax().y);
    REQUIRE(Approx(1.0f) == b1.getmax().z);
 
    glm::vec3 min2{2.0f, 3.3f, 4.0f};
    glm::vec3 max2{1.5f, 5.6f, 2.3f};
 
    Box b2{min2, max2};
    b2.maximum({2.3f, 1.3f, 4.3f});
    REQUIRE(Approx(2.3f) == b2.getmax().x);
    REQUIRE(Approx(1.3f) == b2.getmax().y);
    REQUIRE(Approx(4.3f) == b2.getmax().z);
 
    glm::vec3 min3{1.0f, 2.3f, 4.1f};
    glm::vec3 max3{0.0f, 2.5f, 1.2f};
 
    Box b3{min3, max3};
    b3.maximum({6.9f, 4.2f, 1.6f});
    REQUIRE(Approx(6.9f) == b3.getmax().x);
    REQUIRE(Approx(4.2f) == b3.getmax().y);
    REQUIRE(Approx(1.6f) == b3.getmax().z);
}
 
 
TEST_CASE("Spherecenter","[center]"){
 
    Sphere s1{};
    REQUIRE(Approx(0.0f) == s1.getctr().x);
    REQUIRE(Approx(0.0f) == s1.getctr().y);
    REQUIRE(Approx(0.0f) == s1.getctr().z);
 
    Sphere s2 {{0.6f, 1.9f, 1.1f}, 4.2f};
    REQUIRE(Approx(0.6f) == s2.getctr().x);
    REQUIRE(Approx(1.9f) == s2.getctr().y);
    REQUIRE(Approx(1.1f) == s2.getctr().z);
 
    Sphere s3 {{3.3f, 4.5f, -2.3f}, 4.2f};
    REQUIRE(Approx(3.3f) == s3.getctr().x);
    REQUIRE(Approx(4.5f) == s3.getctr().y);
    REQUIRE(Approx(-2.3f) == s3.getctr().z);
}
 
TEST_CASE("SphereSetCenter","[setcenter]"){
 
    Sphere s1{};
    s1.setctr({1.0f, 1.0f, 1.0f});
    REQUIRE(Approx(1.0f) == s1.getctr().x);
    REQUIRE(Approx(1.0f) == s1.getctr().y);
    REQUIRE(Approx(1.0f) == s1.getctr().z);
 
    Sphere s2{{0.6f, 1.9f, 1.1f}, 4.2f};
    s2.setctr({1.3f, 2.6f, 1.2f});
    REQUIRE(Approx(1.3f) == s2.getctr().x);
    REQUIRE(Approx(2.6f) == s2.getctr().y);
    REQUIRE(Approx(1.2f) == s2.getctr().z);
 
    Sphere s3 {{3.3f, 4.5f, -2.3f}, 4.2f};
    s3.setctr({2.3f, 3.6f, -4.4f});
    REQUIRE(Approx(2.3f) == s3.getctr().x);
    REQUIRE(Approx(3.6f) == s3.getctr().y);
    REQUIRE(Approx(-4.4f) == s3.getctr().z);   
}
 
TEST_CASE("Sphereradius","[radius]"){
 
    Sphere s1{};
    REQUIRE(Approx(1.0f) == s1.getrad());
 
    Sphere s2 {{0.6f, 1.9f, 1.1f}, -4.2f};
    REQUIRE(Approx(-4.2f) == s2.getrad());
   
 
    Sphere s3 {{3.3f, 4.5f, -2.3f}, 5.3f};
    REQUIRE(Approx(5.3f) == s3.getrad());
   
}
 
TEST_CASE("SphereSetRadius","[SetRadius]"){
 
    Sphere s1{};
    s1.setrad(4.2f);
    REQUIRE(Approx(4.2f) == s1.getrad());
 
    Sphere s2{{0.6f, 1.9f, 1.1f}, 4.2f};
    s2.setrad(-1.3f);
    REQUIRE(Approx(-1.3f) == s2.getrad());
 
    Sphere s3 {{3.3f, 4.5f, -2.3f}, 4.2f};
    s3.setrad(3.5f);
    REQUIRE(Approx(3.5f) == s3.getrad());
}
 
TEST_CASE("Material","[three]")
{
    Color MatCol{1,1,1};
 
    Material ma{"a",MatCol,MatCol,MatCol,1};
    Material mb{"b",MatCol,MatCol,MatCol,1};
 
 
    Box bochs {glm::vec3 {1,2,3}, glm::vec3 {4,5,6}, "Box", ma};
    Sphere kgl {glm::vec3 {-1,-2,-3}, 1,"Kugel", mb};
 
    Material m1 = kgl.getmat();
    Material m2 = bochs.getmat();
    REQUIRE(kgl.getname()=="Kugel");
    REQUIRE(m1.name_== "b");
    REQUIRE(m1.ka_  == MatCol);
    REQUIRE(m1.kd_  == MatCol);
    REQUIRE(m1.ks_  == MatCol);
    REQUIRE(m1.m_   == 1);
 
 
    REQUIRE(bochs.getname()=="Box");
    REQUIRE(m2.name_== "a");
    REQUIRE(m2.ka_  == MatCol);
    REQUIRE(m2.kd_  == MatCol);
    REQUIRE(m2.ks_  == MatCol);
    REQUIRE(m2.m_   == 1);
 
}
 
TEST_CASE("SphereIntersect","[intersect1]")
{
    Color MatCol{1,1,1};
 
    Material ma{"a",MatCol,MatCol,MatCol,1};
    Sphere s1{glm::vec3 {3,3,3}, 1,"Kugel", ma};
 
    Ray ralf   {glm::vec3 {1,1,1}, glm::vec3 {4,4,4}};
    Ray ronny  {glm::vec3 {4,4,4}, glm::vec3 {2,2,2}};
    Ray roland {glm::vec3 {4,4,4}, glm::vec3 {6,6,6}};
 
    REQUIRE( s1.intersect(ralf).impact);
    REQUIRE( s1.intersect(ralf).impact);
    REQUIRE(!s1.intersect(ronny).impact);
    REQUIRE(!s1.intersect(ronny).impact);
    REQUIRE(!s1.intersect(roland).impact);
    REQUIRE(!s1.intersect(roland).impact);
}
 
TEST_CASE ("intersectRaySphere","[intersect]" )
{
    Ray ronny(glm::vec3{0,0,0},glm::vec3{0,0,1});
    Sphere s(glm::vec3{0,0,3},1);
    REQUIRE(s.intersect(ronny).impact);
}
 
/*TEST_CASE("boxintersect", "[box]")
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
    Ray ronny1(glm::vec3{0,0,0},glm::vec3{0,0,1});
    Ray ronny2(glm::vec3{0,0,0},glm::vec3{1,1,1});
    Ray ronny3(glm::vec3{0,0,0},glm::vec3{-1,-1,-1});
    Ray ronny4(glm::vec3{1,1,1},glm::vec3{-1,-1,-1});
 
    Sphere s1(glm::vec3{0,0,3},1);
    Sphere s2(glm::vec3{4,4,4},1);
    Sphere s3(glm::vec3{-2,-2,-2},1);
    Sphere s4(glm::vec3{-3,-3,-3},1);
 
    Hit hit1 = s1.intersect(ronny1);
    Hit hit2 = s2.intersect(ronny2);
    Hit hit3 = s3.intersect(ronny3);
    Hit hit4 = s4.intersect(ronny4);
 
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
 
    Hit hit5 = s5.intersect(ronny5);
    Hit hit6 = s6.intersect(ronny6);
    Hit hit7 = s7.intersect(ronny7);
    Hit hit8 = s8.intersect(ronny8);
 
    std::cout<<"\n"<<hit5.impact<<std::endl;
    std::cout<<"\n"<<hit6.impact<<std::endl;
    std::cout<<"\n"<<hit7.impact<<std::endl;
    std::cout<<"\n"<<hit8.impact<<std::endl;
   
    return Catch::Session().run(argc, argv);
}
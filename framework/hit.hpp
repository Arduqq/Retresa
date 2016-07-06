#ifndef MY_HIT
#define MY_HIT

struct Hit
{
Hit():
impact{0},
point{glm::vec3{0,0,0}},
normal{Ray{glm::vec3{0,0,0},glm::vec3{0,0,0}}}
//Shape*{nullptr}
{}

Hit(bool i, glm::vec3 p, Ray n/*, Shape* s*/):
impact{i},
point{p},
normal{n}
//Shape*{s}
{}

bool impact;
glm::vec3 point;
Ray normal;
//Shape* shape;
};

#endif
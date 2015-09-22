#ifndef PLANE_H
#define PLANE_H

#include <iostream>
#include <map>

#include "predef.h"

using namespace std;

//plane categorys
#undef ENUM_TYPE
#undef ENUM_PATH
#define ENUM_TYPE Plane_cate
#define ENUM_PATH "plane_cate.def"
#include "enum_defs/enumer.h"
#include "enum_defs/enum_def.h"

//plane
class Plane{
public:
    string name;
    const Plane_cate category;
    const int antiAir,
              torpeAtk,
              diveAtk,
              accuracy;

    Plane(const char *_name,
          const Plane_cate _category = static_cast<Plane_cate>(0),
          int _antiAir  = 0,
          int _torpeAtk = 0,
          int _diveAtk  = 0,
          int _accuracy = 0)
    :
                name(_name),
            category(_category),
             antiAir(_antiAir),
            torpeAtk(_torpeAtk),
             diveAtk(_diveAtk),
            accuracy(_accuracy)
    {};
};

istream &operator>>(istream &is,Plane &item);
ostream &operator<<(ostream &os,Plane &item);

#endif // PLANE_H

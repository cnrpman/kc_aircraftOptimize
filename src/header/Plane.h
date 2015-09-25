#ifndef PLANE_H
#define PLANE_H

#include <iostream>
#include <map>

//plane categorys
#define ENUM_TYPE Plane_type
#include "../enum_defs/enumer.h"
#undef ENUM_TYPE

//pre declear
namespace acc{
    class Plane;
}
std::istream &operator>>(std::istream &is, acc::Plane &item);
std::ostream &operator<<(std::ostream &os, const acc::Plane &item);

//plane
namespace acc{
    class Plane{
    public:
        Plane(std::string &_name = *new std::string("UnnamedPlane"),
              const Plane_type _type = static_cast<Plane_type>(0),
              int _antiAir  = 0,
              int _torpeAtk = 0,
              int _diveAtk  = 0,
              int _accuracy = 0,
              int _evasion  = 0,
              int _prof     = 0
        ):
                    name(_name),
                    type(_type),
                 antiAir(_antiAir),
                torpeAtk(_torpeAtk),
                 diveAtk(_diveAtk),
                accuracy(_accuracy),
                 evasion(_evasion),
                    prof(_prof)
        {};
        std::string getName(){
            return this->name;
        }
    private:
         std::string name;
         Plane_type type;
         int antiAir,
             torpeAtk,
             diveAtk,
             accuracy,
             evasion,
             prof;


        friend std::istream &::operator>>(std::istream &is, Plane &item);
        friend std::ostream &::operator<<(std::ostream &os, const Plane &item);
    };
}

#endif // PLANE_H

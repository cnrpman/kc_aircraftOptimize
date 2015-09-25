#ifndef CV_H
#define CV_H

#include <iostream>
#include <map>
//CV categorys
#define ENUM_TYPE CV_type
#include "../enum_defs/enumer.h"
#undef ENUM_TYPE

//pre declear
namespace acc{
    class CV;
}
std::istream &operator>>(std::istream &is, acc::CV &item);
std::ostream &operator<<(std::ostream &os, const acc::CV &item);

// CVs
namespace acc{
    class CV{
    public:
        CV(
            std::string &_name = *new std::string("UnnamedCV"),
                 CV_type _type = static_cast<CV_type>(0),
                 int     _gN   = 0,
                 int     _gZ0  = 0,
                 int     _gZ1  = 0,
                 int     _gZ2  = 0,
                 int     _gZ3  = 0,
                 int     _atk  = 0,
                 int     _accu = 0,
                 int     _luck = 0
        ):
            name(_name),
            type(_type),
            gridNum(_gN),
            gridSize{_gZ0,_gZ1,_gZ2,_gZ3},
            atk(_atk),
            accuracy(_accu),
            luck(_luck)
        {};

        std::string getName(){
            return this->name;
        }
    private:
        std::string name;
        CV_type type;
        int gridNum,
            gridSize[4],
            atk,
            accuracy,
            luck;

        friend std::istream &::operator>>(std::istream &is, CV &item);
        friend std::ostream &::operator<<(std::ostream &os, const CV &item);
    };
}

#endif // CV_H

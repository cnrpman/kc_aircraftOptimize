#ifndef CARRIER_H
#define CARRIER_H

#include "predef.h"
#include "enum_defs/enumer.h"

#include <iostream>
#include <map>

using namespace std;

//carrier categorys
#undef ENUM_TYPE
#undef ENUM_PATH
#define ENUM_TYPE CV_cate
#define ENUM_PATH "carrier_cate.def"
#include "enum_defs/enumer.h"
#include "enum_defs/enum_def.h"


// Carriers
class Carrier{
public:
    Carrier(
        string &_name = *new string("UnnamedCarrier"),
        CV_cate _cate = static_cast<CV_cate>(0),
        int     _gN   = 0,
        int     _gZ0  = 0,
        int     _gZ1  = 0,
        int     _gZ2  = 0,
        int     _gZ3  = 0,
        int     _atk  = 0
    ):
        name(_name),
        category(_cate),
        gridNum(_gN),
        gridSize{_gZ0,_gZ1,_gZ2,_gZ3},
        atk(_atk)
    {};

    const string name;
    CV_cate category;
    const int gridNum,
              gridSize[4],
              atk;
};

istream &operator>>(istream &is,Carrier &item);
ostream &operator<<(ostream &os,Carrier &item);

#endif // CARRIER_H

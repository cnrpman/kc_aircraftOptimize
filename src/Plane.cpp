#include "header/Plane.h"

#define ENUM_TYPE Plane_type
#include "enum_defs/enumer.cpp"
#undef ENUM_TYPE

using namespace acc;

std::istream &operator>>(std::istream &is, Plane &item){
    is>>item.name
      >>item.type
      >>item.antiAir
      >>item.torpeAtk
      >>item.diveAtk
      >>item.accuracy
      >>item.evasion;
    return is;
}

std::ostream &operator<<(std::ostream &os, const Plane &item){
    os<<"n:"<<item.name<<' '
      <<"t:"<<item.type<<' '
      <<"A:"<<item.antiAir<<' '
      <<"t:"<<item.torpeAtk<<' '
      <<"d:"<<item.diveAtk<<' '
      <<"a:"<<item.accuracy<<' '
      <<"e:"<<item.evasion;
    return os;
}

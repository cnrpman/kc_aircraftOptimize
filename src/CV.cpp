#include "header/CV.h"

#define ENUM_TYPE CV_type
#include "enum_defs/enumer.cpp"
#undef ENUM_TYPE

using namespace acc;

std::istream& operator>>(std::istream &is, CV &item){
    is>>item.name
      >>item.type
      >>item.gridNum
      >>item.gridSize[0]
      >>item.gridSize[1]
      >>item.gridSize[2]
      >>item.gridSize[3]
      >>item.atk
      >>item.luck;
    return is;
}

std::ostream& operator<<(std::ostream &os, const CV &item){
    os<<"n:"<<item.name<<' '
      <<"t:"<<item.type<<' '
      <<"g:"<<item.gridNum<<' '
      <<item.gridSize[0]<<' '
      <<item.gridSize[1]<<' '
      <<item.gridSize[2]<<' '
      <<item.gridSize[3]<<' '
      <<"a:"<<item.atk<<' '
      <<"l:"<<item.luck;
    return os;
}

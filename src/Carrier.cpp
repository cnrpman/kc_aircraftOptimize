#include "Carrier.h"

istream &operator>>(istream &is,Carrier &item){
    char *cate;
    is>>item.name
      >>cate
      >>item.gridNum
      >>item.gridSize[0]
      >>item.gridSize[1]
      >>item.gridSize[2]
      >>item.gridSize[3]
      >>item.atk;
    item.category = covert_string_to_enum<CV_cate>(cate);
    return is;
}

ostream &operator<<(ostream &os,Carrier &item){
    os<<item.name<<' '
      <<covert_enum_to_string(item.category)<<' '
      <<item.gridNum<<' '
      <<item.gridSize[0]<<' '
      <<item.gridSize[1]<<' '
      <<item.gridSize[2]<<' '
      <<item.gridSize[3]<<' '
      <<item.atk;
    return os;
}

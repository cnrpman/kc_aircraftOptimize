#include "Carrier.h"

istream &operator>>(istream &is,Carrier &item){
    string tmpcate;
    is>>item.name>>tmpcate>>item.gridNum>>item.gridSize[0]>>item.gridSize[1]>>item.gridSize[2]>>item.gridSize[3]>>item.atk;
    item.category=CARRIER_CATE_convert(tmpcate);
    return is;
}

ostream &operator<<(ostream &os,Carrier &item){
    string tmpcate;
    os<<item.name<<" "<<tmpcate<<" "<<item.gridNum<<" "<<item.gridSize[0]<<" "<<item.gridSize[1]<<" "<<item.gridSize[2]<<" "<<item.gridSize[3]<<" "<<item.atk;
    item.category=CARRIER_CATE_convert(tmpcate);
    return os;
}

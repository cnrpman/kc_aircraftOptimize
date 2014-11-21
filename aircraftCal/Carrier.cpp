#include "Carrier.h"

using namespace std;

Carrier::Carrier(string _name,int _cate,int _gridN,int _g0S,int _g1S,int _g2S,int _g3S,int _atk){
    name=_name;
    category=_cate;
    gridNum=_gridN;
    gridSize[0]=_g0S;
    gridSize[1]=_g1S;
    gridSize[2]=_g2S;
    gridSize[3]=_g3S;
    atk=_atk;
}

string Carrier::getName(){
    return name;
}

int Carrier::getCategoryID(){
    return category;
}

string Carrier::getCategoryName(){
    return CARRIER_CATE_convert(category);
}

int Carrier::getGridNum(){
    return gridNum;
}

int Carrier::getGridSize(int order){
    return gridSize[order];
}

int Carrier::getAtk(){
    return atk;
}

int CARRIER_CATE_convert(string name){
    return carrier_cate_m[name];
}

string CARRIER_CATE_convert(int cate){
    return CARRIER_CATE_NAME[cate];
}

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

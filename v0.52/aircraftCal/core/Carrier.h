#ifndef CARRIER_H
#define CARRIER_H

#include "predef.h"

#include <iostream>
#include <map>

using namespace std;


//carrier categorys

extern map<string,int>carrier_cate_m;

const int CARRIER_CATE_NUM =6;
const int CARRIER_UNDEFINE =0;
const int CARRIER_CVL      =1;
const int CARRIER_CV       =2;
const int CARRIER_BBV      =3;
const int CARRIER_CAV      =4;
const int CARRIER_OTHER    =5;

const string CARRIER_CATE_NAME[CARRIER_CATE_NUM]={
    "UNDEFINE",
    "CVL",
    "CV",
    "BBV",
    "CAV",
    "OTHER"
};

inline int CARRIER_CATE_convert(string name){
    return carrier_cate_m[name];
}

inline string CARRIER_CATE_convert(int cate){
    return CARRIER_CATE_NAME[cate];
}


// Carriers

class Carrier{
public:
    Carrier(string _name="default_Carrier",int _cate=0,int _gridN=0,int _g0S=0,int _g1S=0,int _g2S=0,int _g3S=0,int _atk=0)
    :name(_name),category(_cate),gridNum(_gridN),atk(_atk){
        gridSize[0]=_g0S;gridSize[1]=_g1S;gridSize[2]=_g2S;gridSize[3]=_g3S;
    };
    string getCategoryName(){
        return CARRIER_CATE_convert(category);
    }
    string name;
    int category;
    int gridNum;
    int gridSize[4];
    int atk;
};

istream &operator>>(istream &is,Carrier &item);
ostream &operator<<(ostream &os,Carrier &item);

#endif // CARRIER_H

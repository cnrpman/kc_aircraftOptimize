#ifndef CARRIER_H
#define CARRIER_H

#include <iostream>
#include <map>

using namespace std;

const int CARRIER_CATE_NUM=6;

const int CARRIER_UNDEFINE =0;
const int CARRIER_CVL      =1;
const int CARRIER_CV       =2;
const int CARRIER_BBV      =3;
const int CARRIER_CAV      =4;
const int CARRIER_OTHER    =5;

const string CARRIER_CATE_NAME[CARRIER_CATE_NUM]={
    "UNDEFINE",
    "Çá¿ÕÄ¸",
    "Õý¹æ¿ÕÄ¸",
    "º½¿ÕÕ½½¢",
    "º½¿ÕÑ²Ñó½¢",
    "ÆäËû"
};

class Carrier{
public:
    Carrier(string _name="default_Carrier",int _cate=0,int _gridN=0,int _g0S=0,int _g1S=0,int _g2S=0,int _g3S=0,int _atk=0);
    string getName();
    int getCategoryID();
    string getCategoryName();
    int getGridNum();
    int getGridSize(int order);
    int getAtk();
    friend istream &operator>>(istream &is,Carrier &item);
    friend ostream &operator<<(ostream &os,Carrier &item);
private:
    string name;
    int category;
    int gridNum;
    int gridSize[4];
    int atk;
};

string CARRIER_CATE_convert(int cate);
int CARRIER_CATE_convert(string name);

extern map<string,int>carrier_cate_m;

#endif // CARRIER_H

#ifndef PLANE_H
#define PLANE_H

#include <iostream>
#include <map>

#include "predef.h"

using namespace std;

//plane categorys

const int PLANE_CATE_NUM=6;

const int PLANE_UNDEFINE         =0;
const int PLANE_TORPEDO_ATTACKER =1;
const int PLANE_BOMBER           =2;
const int PLANE_FIGHTER          =3;
const int PLANE_WATER_PLANE      =4;
const int PLANE_OTHER            =5;

const string PLANE_CATE_NAME[PLANE_CATE_NUM]={
    "UNDEFINE",
    "TorpedoAttacker",
    "Bomber",
    "Fighter",
    "WaterPlane",
    "Other"
};

extern map<string,int>plane_cate_m;

inline string PLANE_CATE_convert(int cate){
    return PLANE_CATE_NAME[cate];
}

inline int PLANE_CATE_convert(string name){
    return plane_cate_m[name];
}

//plane

class Plane{
public:
    string name;
    int category, airSupremacy, torpedoAtk, bombAtk, accuracy;
    Plane(string _name="default_Plane",int _cate=0,int _airSupr=0,int _torpeAtk=0,int _bombAtk=0,int _accu=0)
    :name(_name),category(_cate),airSupremacy(_airSupr),torpedoAtk(_torpeAtk),bombAtk(_bombAtk),accuracy(_accu)
    {};

    string getCategoryName() const{
        return PLANE_CATE_convert(category);
    }
};

istream &operator>>(istream &is,Plane &item);
ostream &operator<<(ostream &os,Plane &item);

#endif // PLANE_H

#ifndef PLANE_H
#define PLANE_H

#include <iostream>
#include <map>

using namespace std;

const int PLANE_CATE_NUM=6;

const int PLANE_UNDEFINE         =0;
const int PLANE_TORPEDO_ATTACKER =1;
const int PLANE_BOMBER           =2;
const int PLANE_FIGHTER          =3;
const int PLANE_WATER_PLANE      =4;
const int PLANE_OTHER            =5;

const string PLANE_CATE_NAME[PLANE_CATE_NUM]={
    "UNDEFINE",
    "攻击机",
    "爆击机",
    "战斗机",
    "水上飞机",
    "其他"
};

class Plane{
public:
    Plane(string _name="default_Plane",int _cate=0,int _airDomi=0,int _torpeAtk=0,int _bombAtk=0,int _priori=0);
    string getName();
    int getCategoryID();
    string getCategoryName();
    int getAirDominance();
    int getTorpedoAtk();
    int getBombAtk();
    int getPriority();
    string name;
    int category;
    int airDominance;
    int torpedoAtk;
    int bombAtk;
    int priority;
};

string PLANE_CATE_convert(int cate);
int PLANE_CATE_convert(string name);
istream &operator>>(istream &is,Plane &item);
ostream &operator<<(ostream &os,Plane &item);

extern map<string,int>plane_cate_m;

#endif // PLANE_H

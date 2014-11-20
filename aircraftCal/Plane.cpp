#include <iostream>
#include "plane.h"

Plane::Plane(string _name,int _cate,int _airDomi,int _torpeAtk,int _bombAtk,int _priori){
            name = _name;
        category = _cate;
    airDominance = _airDomi;
      torpedoAtk = _torpeAtk;
         bombAtk = _bombAtk;
        priority = _priori;//命中索敌等参数可以算入这里
}
string Plane::getName(){
    return name;
}
int Plane::getCategoryID(){
    return category;
}
string Plane::getCategoryName(){
    return PLANE_CATE_convert(category);
}
int Plane::getAirDominance(){
    return airDominance;
}
int Plane::getTorpedoAtk(){
    return torpedoAtk;
}
int Plane::getBombAtk(){
    return bombAtk;
}
int Plane::getPriority(){
    return priority;
}

string PLANE_CATE_convert(int cate){
    return PLANE_CATE_NAME[cate];
}

int PLANE_CATE_convert(string name){
    return plane_cate_m[name];
}

istream &operator>>(istream &is,Plane &item){
    string tmpcate;
    is>>item.name>>tmpcate>>item.airDominance>>item.torpedoAtk>>item.bombAtk>>item.priority;
    item.category=PLANE_CATE_convert(tmpcate);
    return is;
}

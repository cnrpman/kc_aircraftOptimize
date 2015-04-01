#include <iostream>
#include "Plane.h"

istream &operator>>(istream &is,Plane &item){
    string tmpcate;
    is>>item.name>>tmpcate>>item.airSupremacy>>item.torpedoAtk>>item.bombAtk>>item.accuracy;
    item.category=PLANE_CATE_convert(tmpcate);
    return is;
}

ostream &operator<<(ostream &os,Plane &item){
    os<<"plane name: "<<item.name<<"\ncategory: "<<PLANE_CATE_convert(item.category)<<"\nairSupremacy: "<<item.airSupremacy<<"\ntorpedoAttack: "<<item.torpedoAtk<<"\nbombAttack: "<<item.bombAtk<<"\naccuracy"<<item.accuracy;
    return os;
}

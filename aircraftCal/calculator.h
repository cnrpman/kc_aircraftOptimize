#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <iostream>
#include <sstream>
#include <vector>
#include <map>

#include "Plane.h"
#include "Carrier.h"

class Grid{
public:
    Grid(int _cpos,int _gpos,int _gS,int _atk){
        carrierPos=_cpos;
        gridPos=_gpos;
        gridSize=_gS;
        carrierAtk=_atk;
    }
    friend ostream &operator<<(ostream &os,Grid &item);
private:
    int carrierPos;
    int gridPos;
    int gridSize;
    int carrierAtk;
};

extern int planes_tot;
extern vector<Plane>planes;
extern map<string,int>planes_m;

extern int carriers_tot;
extern vector<Carrier>carriers;
extern map<string,int>carriers_m;

extern map<string,int>plane_cate_m;
extern map<string,int>carrier_cate_m;

extern vector<Grid>gridVec;
extern vector<Plane>planeVec;

void cal_dataReady(string msg);

#endif // CALCULATOR_H

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <cstring>
#include <stack>

#include "Plane.h"
#include "Carrier.h"
#include "math.h"

class Grid{
public:
    Grid(int _cpos,int _gpos,int _gS,int _atk){
        carrierPos=_cpos;
        gridPos=_gpos;
        gridSize=_gS;
        carrierAtk=_atk;
    }
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
extern vector<Plane>planeVecA;
extern vector<Plane>planeVecF;

extern int airDomin;

void cal_dataReady(string msg);
bool cal_run();
string &cal_get_res();

double formulaDamage(Plane &item);
double formulaDamageOP(int gridSize,Plane &item);

#endif // CALCULATOR_H

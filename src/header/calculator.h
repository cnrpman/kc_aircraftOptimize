#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <cstring>
#include <stack>
#include <chrono>

#include "predef.h"

#include "Plane.h"
#include "Carrier.h"
#include "math.h"
#include "formular.h"
#include "atkdp.h"
#include "belongingStructure.h"


extern int planes_tot,carriers_tot;
extern vector<Plane>planes;
extern vector<Carrier>carriers;
extern vector<Grid>gridVec;
extern vector<Plane>planeVec,planeVecA,ResPlaneVecA,planeVecF;
extern map<string,int>planes_m,plane_cate_m,carrier_cate_m,carriers_m;

extern int tarAirSupremacy,armor;
extern int shipAtk[4],carrierNum,usedGrid[4],availGrid[4],belonging[16];;
extern BelongStructure dpRes[5][5][5][5];
extern float op_coef,accu_coef;


void cal_dataReady(stringstream &msg);
bool cal_run();
stringstream &cal_get_res();

#endif // CALCULATOR_H

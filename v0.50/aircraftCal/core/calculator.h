#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <cstring>
#include <stack>

#include "predef.h"

#include "Plane.h"
#include "Carrier.h"
#include "math.h"
#include "formular.h"
#include "atkdp.h"
#include "belongingStructure.h"

#ifdef WINDOWS
#include <windows.h>
#else
#include <sys/time.h>
#endif

extern int planes_tot,carriers_tot;
extern vector<Plane>planes;
extern vector<Carrier>carriers;
extern vector<Grid>gridVec;
extern vector<Plane>planeVec,planeVecA,ResPlaneVecA,planeVecF;
extern map<string,int>planes_m,plane_cate_m,carrier_cate_m,carriers_m;

extern int tarAirSupremacy,shipAtk[4],carrierNum,usedGrid[4],availGrid[4],belonging[16];;
extern BelongStructure dpRes[5][5][5][5];
extern float op_coef,accu_coef;

void cal_dataReady(stringstream &msg);
bool cal_run();
stringstream &cal_get_res();

#ifndef WINDOWS
extern timeval starttime,endtime;
#endif

#endif // CALCULATOR_H

#ifndef CORE_H
#define CORE_H

#include <iostream>
#include <vector>
#include <map>
#include "Plane.h"
#include "Carrier.h"
#include "io.h"

extern int planes_tot;
extern vector<Plane>planes;
extern map<string,int>planes_m;

extern int carriers_tot;
extern vector<Carrier>carriers;
extern map<string,int>carriers_m;

extern map<string,int>plane_cate_m;
extern map<string,int>carrier_cate_m;

void core_initialization();

#endif // CORE_H

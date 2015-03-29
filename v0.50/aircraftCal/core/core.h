#ifndef CORE_H
#define CORE_H

#include <iostream>
#include <vector>
#include <map>
#include <sstream>

#include "predef.h"

#include "Plane.h"
#include "Carrier.h"
#include "io.h"
#include "calculator.h"

extern int planes_tot,carriers_tot;
extern vector<Plane>planes;
extern vector<Carrier>carriers;
extern vector<Grid>gridVec;
extern map<string,int>planes_m,carriers_m,plane_cate_m,carrier_cate_m;

void core_initialization();
stringstream &core_query(stringstream &st);

#endif // CORE_H

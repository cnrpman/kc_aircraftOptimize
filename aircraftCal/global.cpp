#include <vector>
#include <map>
#include "Carrier.h"
#include "Plane.h"
#include "calculator.h"

int planes_tot;
vector<Plane>planes;
map<string,int>planes_m;

int carriers_tot;
vector<Carrier>carriers;
map<string,int>carriers_m;

map<string,int>plane_cate_m;
map<string,int>carrier_cate_m;

vector<Grid>gridVec;
vector<Plane>planeVec;

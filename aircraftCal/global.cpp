#include <vector>
#include <map>
#include "Carrier.h"
#include "Plane.h"
#include "calculator.h"

int planes_tot;
vector<Plane>planes;
map<string,int>planes_m;//飞机名映射

int carriers_tot;
vector<Carrier>carriers;
map<string,int>carriers_m;//船名映射

map<string,int>plane_cate_m;//种类名映射
map<string,int>carrier_cate_m;

//读入查询
vector<Grid>gridVec;//载机格
vector<Plane>planeVec;//飞机
vector<Plane>planeVecA;//attacker/bomber
int airDomin;//制空

#include <vector>
#include <map>
#include "Carrier.h"
#include "Plane.h"
#include "calculator.h"

int planes_tot;
vector<Plane>planes;
map<string,int>planes_m;//�ɻ���ӳ��

int carriers_tot;
vector<Carrier>carriers;
map<string,int>carriers_m;//����ӳ��

map<string,int>plane_cate_m;//������ӳ��
map<string,int>carrier_cate_m;

//�����ѯ
vector<Grid>gridVec;//�ػ���
vector<Carrier>theCarrier;
vector<Plane>planeVec,planeVecA,ResPlaneVecA,planeVecF;
int tarAirSupremacy,armor,shipAtk[4],shipAccu[4],carrierNum;
BelongStructure dpRes[5][5][5][5];
int usedGrid[4],availGrid[4];
float op_coef,accu_coef;
int armor_max,armor_min;
int nearing_coef;

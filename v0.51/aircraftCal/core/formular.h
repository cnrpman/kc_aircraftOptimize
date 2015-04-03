#ifndef FORMULAR_H
#define FORMULAR_H

#include "predef.h"

#include <cmath>
#include <vector>
#include "grid.h"
#include "Plane.h"
#include "Carrier.h"

extern int armor,carrierNum,shipAccu[4];
extern float op_coef,accu_coef;
extern vector<Carrier>theCarrier;

int formulaDamage(const Plane &item);
float formulaDamageOP(int gridSize,const Plane &item);
float sortDamage(Plane &item);
int formulaFighter(int gridSize,int AirSupremacy);
float formularAllShipAtk(int shipAtk[]);
bool cal_cmp_grid(const Grid &a,const Grid &b);
bool cal_cmp_plane_AS(const Plane &a,const Plane &b);
bool cal_cmp_plane_damage(const Plane &a,const Plane &b);
bool cal_cmp_plane_damageOP(const Plane &a,const Plane &b);

void loglist_init();

extern float loglist[LOGLIST_LEN];

#endif // FORMULAR_H

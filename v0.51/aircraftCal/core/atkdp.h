#ifndef ATKDP_H
#define ATKDP_H

#include <cstring>
#include <vector>
#include "predef.h"
#include "belongingStructure.h"
#include "formular.h"
#include "formular_inline.h"

extern int shipAtk[4],carrierNum;
extern vector<Plane>planeVecA;//attacker/bomber
extern BelongStructure dpRes[5][5][5][5];
extern int usedGrid[4],availGrid[4];

void anothersearch(int bomberNum,int bomberID);
void atkdp(int bomberNum);

#endif // ATKDP_H

#ifndef BELONGINGSTRUCTURE_H
#define BELONGINGSTRUCTURE_H

#include <algorithm>
#include <vector>
#include <iostream>
#include "predef.h"

class BelongStructure{
public:
    BelongStructure():biggestAtk(0.0){}
    float biggestAtk;
    std::vector <int *> belongings;
    std::vector<float>as;
};

void checkNew(BelongStructure *bs,float atk,int *belonging);
void pushNew(BelongStructure *bs,float atk,int *belonging);
void clearBelonging(BelongStructure *bs);

#endif // BELONGINGSTRUCTURE_H

#ifndef BELONGINGSTRUCTURE_H
#define BELONGINGSTRUCTURE_H

#include <algorithm>
#include <vector>
#include <iostream>
#include "predef.h"

class BelongStructure{
public:
    BelongStructure():biggestAtk(0){}
    int biggestAtk;
    std::vector <int *> belongings;
};

void checkNew(BelongStructure *bs,int atk,int *belonging);
void pushNew(BelongStructure *bs,int atk,int *belonging);

#endif // BELONGINGSTRUCTURE_H

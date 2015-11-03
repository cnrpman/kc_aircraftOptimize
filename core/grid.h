#ifndef GRID_H
#define GRID_H

#include "predef.h"

#include <iostream>
#include <string>

class Grid{
public:
    Grid(int _cpos,int _gpos,int _gS, int _gSf, int _atk,int _IFO){
        carrierPos=_cpos;
        gridPos=_gpos;
        gridSize=_gS;
        gridSizeFsb=_gSf;
        carrierAtk=_atk;
        isFighterOnly=_IFO;
    }
    int carrierPos;
    int gridPos;
    int gridSize;
    int gridSizeFsb;
    int carrierAtk;
    int isFighterOnly;
};
#endif

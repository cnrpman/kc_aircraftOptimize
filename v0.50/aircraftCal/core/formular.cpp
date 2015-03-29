#include "formular.h"
#include "formular_inline.h"

float formulaDamageOP(int gridSize,const Plane &item){
    if(item.category==PLANE_TORPEDO_ATTACKER)
        return (item.torpedoAtk*sqrt(gridSize))+25*1.15;
    else if(item.category==PLANE_BOMBER)
        return item.bombAtk*sqrt(gridSize)+25;
    else return 0.0;
}

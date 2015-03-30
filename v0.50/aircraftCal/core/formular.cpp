#include "formular.h"
#include "formular_inline.h"

float formulaDamageOP(int gridSize,const Plane &item){
    if(item.category==PLANE_TORPEDO_ATTACKER){
        float atk=item.torpedoAtk*sqrt(gridSize)+25;
        return ((float)armorSimu(atk*1.5)+armorSimu(atk*0.8))/2;
    }
    else if(item.category==PLANE_BOMBER)
        return item.bombAtk*sqrt(gridSize)+25;
    else return 0.0;
}

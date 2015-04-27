#include "formular.h"
#include "formular_inline.h"

float formulaDamageOP(int gridSize,const Plane &item){
    if(item.category==PLANE_TORPEDO_ATTACKER){
        float atk=item.torpedoAtk*sqrt(gridSize)+25;
        return ((float)armorSimu(atk*1.5)+armorSimu(atk*0.8))/2;
    }
    else if(item.category==PLANE_BOMBER)
        return armorSimu(item.bombAtk*sqrt(gridSize)+25);
    else return 0.0;
}

void loglist_init(){
    for(int i=0;i<LOGLIST_LEN;i++)
        loglist[i]=(1+accu_coef*sqrt(i))/2;
}

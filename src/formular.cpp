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

string formula_damageOP_str(int gridSize,const Plane &item){
    char tmp[50];
    if(item.category==PLANE_TORPEDO_ATTACKER){
        float atk = item.torpedoAtk*sqrt(gridSize)+25;
        sprintf(tmp, "%d/%d", (int)(atk*0.8),(int)(atk*1.5));
        return *new string(tmp);
    }
    else if(item.category==PLANE_BOMBER){
        sprintf(tmp, "%d", (int)(item.bombAtk*sqrt(gridSize))+25);
        return *new string(tmp);
    }
    else return "0";
}

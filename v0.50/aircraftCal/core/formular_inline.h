#ifndef FORMULAR_INLINE_H
#define FORMULAR_INLINE_H

#include "formular.h"

inline float formulaSortDamage(const Plane &item){
    return formulaDamage(item)+op_coef*formulaDamageOP(20,item);
}

inline bool sig(float a){
    return a<-EPS?false:a<EPS;
}

inline int damageRegular(int atk){
    if(atk>150){
        atk-=150;
        atk=floor(sqrt(atk))+150;
    }
    return atk;
}

inline int armorSimu(int damage){
    damage-=armor;
    return damage>0?damage:0;
}

//=====

inline bool cal_cmp_grid(const Grid &a,const Grid &b){
    return a.gridSize>b.gridSize;
}

inline bool cal_cmp_plane_AS(const Plane &a,const Plane &b){
    int ASa=a.airSupremacy,ASb=b.airSupremacy;
    return ASa==ASb?a.accuracy>b.accuracy:ASa>ASb;
}

inline bool cal_cmp_plane_damage(const Plane &a,const Plane &b){
    return sig(formulaSortDamage(a)-formulaSortDamage(b))?a.accuracy>b.accuracy:formulaSortDamage(a)>formulaSortDamage(b);
}

inline float formulaDamage(const Plane &item){//yue fen
    return (item.bombAtk<<2)+item.torpedoAtk*3;
}

inline float formularAllShipAtk(int shipAtk[]){
    float res=0;
    for(int i=0;i<carrierNum;i++){
        if(shipAtk[i]==0)continue;
        int ss=((shipAtk[i]+theCarrier[i].atk*3)>>1)+55;
        res+=((float)armorSimu(damageRegular(ss*0.8))+armorSimu(damageRegular(ss)))/2;
    }
    return res;
}

inline bool cal_cmp_plane_damageOP(const Plane &a,const Plane &b){
    return sig(formulaDamageOP(1,a)-formulaDamageOP(1,b))?a.accuracy>b.accuracy:formulaDamageOP(1,a)>formulaDamageOP(1,b);
}

inline int formulaFighter(int gridSize,int AirSupremacy){
    return floor(sqrt(gridSize)*AirSupremacy);
}

#endif // FORMULAR_INLINE_H

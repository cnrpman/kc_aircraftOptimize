#include "atkdp.h"

int times=0;
int belonging[16];

void anothersearch(int bomberNum,int bomberID){
    dpRes[usedGrid[0]][usedGrid[1]][usedGrid[2]][usedGrid[3]].pushNew(formularAllShipAtk(shipAtk),belonging);
    if(bomberNum==0){
//        cout<<usedGrid[0]<<" "<<usedGrid[1]<<" "<<usedGrid[2]<<" "<<usedGrid[3]<<endl;
        return;
    }

    Plane &tplane=planeVecA[bomberID];
    int tdamage=formulaDamage(tplane),taccu=tplane.accuracy;
    for(int i=0;i<carrierNum;i++){
        if(usedGrid[i]<availGrid[i]){
            shipAtk[i]+=tdamage;
            shipAccu[i]+=taccu;
            usedGrid[i]++;
            belonging[bomberID]=i;
            anothersearch(bomberNum-1,bomberID+1);
            usedGrid[i]--;
            shipAccu[i]-=taccu;
            shipAtk[i]-=tdamage;
        }
    }
}

void atkdp(int bomberNum){
    memset(dpRes,0,sizeof(dpRes));
    memset(shipAtk,0,sizeof(shipAtk));
    memset(shipAccu,0,sizeof(shipAccu));
    memset(usedGrid,0,sizeof(usedGrid));
    anothersearch(bomberNum,0);
}

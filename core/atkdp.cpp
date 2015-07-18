#include "atkdp.h"

int times=0;
int belonging[16];

void anothersearch(int bomberNum,int bomberID,void(* func)(BelongStructure *,float ,int *)){
    func(&dpRes[usedGrid[0]][usedGrid[1]][usedGrid[2]][usedGrid[3]],formularAllShipAtk(shipAtk),belonging);
    if(bomberNum == 0){//搜索出口
        return;
    }

    int i=0;
    //背包处理，剪掉重复项
    if(bomberID > 0 && planeVecA[bomberID].name == planeVecA[bomberID - 1].name)
        i = belonging[bomberID - 1];
    Plane &tplane = planeVecA[bomberID];
    int tdamage = formulaDamage(tplane), taccu = tplane.accuracy;
    for(; i < carrierNum; i++){
        if(usedGrid[i]<availGrid[i]){
            shipAtk[i] += tdamage;
            shipAccu[i] += taccu;
            usedGrid[i] ++ ;
            belonging[bomberID] = i;
            anothersearch(bomberNum - 1,bomberID + 1,func);
            usedGrid[i] -- ;
            shipAccu[i] -= taccu;
            shipAtk[i] -= tdamage;
        }
    }
}

void atkdp(int bomberNum){
    //init
    for(int i=0;i<5;i++)
        for(int j=0;j<5;j++)
            for(int k=0;k<5;k++)
                for(int l=0;l<5;l++)
                    clearBelonging(&dpRes[i][j][k][l]);
    memset(dpRes,0,sizeof(dpRes));
    memset(shipAtk,0,sizeof(shipAtk));
    memset(shipAccu,0,sizeof(shipAccu));
    memset(usedGrid,0,sizeof(usedGrid));

    //search
    anothersearch(bomberNum,0,checkNew);
    anothersearch(bomberNum,0,pushNew);
}

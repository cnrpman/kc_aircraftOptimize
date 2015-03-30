#include "belongingStructure.h"

void checkNew(BelongStructure *bs,int atk,int *belonging){
    if(atk<=bs->biggestAtk)return;
    bs->biggestAtk=atk;
}

void pushNew(BelongStructure *bs,int atk,int *belonging){
        if(atk<bs->biggestAtk-NEARING_COEF)return;
        int *ptr = new int[16];
        for(int i=0;i<16;i++)
            ptr[i]=belonging[i];
        bs->belongings.push_back(ptr);
    }

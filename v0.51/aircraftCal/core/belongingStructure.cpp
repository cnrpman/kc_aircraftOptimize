#include "belongingStructure.h"

void checkNew(BelongStructure *bs,float atk,int *belonging){
    if(atk<=bs->biggestAtk)return;
    bs->biggestAtk=atk;
    //std::cout<<atk<<std::endl;
}

void pushNew(BelongStructure *bs,float atk,int *belonging){
        if(atk<bs->biggestAtk-NEARING_COEF)return;
        int *ptr = new int[16];
        for(int i=0;i<16;i++)
            ptr[i]=belonging[i];
        bs->belongings.push_back(ptr);
        bs->as.push_back(atk);
    }

void clearBelonging(BelongStructure *bs){
    std::for_each(bs->belongings.begin(),bs->belongings.end(),
    [](int *ptr){
        delete []ptr;
    });
    bs->belongings.clear();
    bs->as.clear();
    bs->biggestAtk=0;
}

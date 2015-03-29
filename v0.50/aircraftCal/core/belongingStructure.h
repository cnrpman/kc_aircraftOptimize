#ifndef BELONGINGSTRUCTURE_H
#define BELONGINGSTRUCTURE_H

#include <algorithm>
#include <vector>
#include <iostream>

class BelongStructure{
public:
    BelongStructure():biggestAtk(0){}
    int biggestAtk;
    std::vector <int *> belongings;
    void pushNew(int atk,int *belonging){
        if(atk<biggestAtk)return;
        if(atk>biggestAtk){//delete current;
            std::for_each(belongings.begin(),belongings.end(),
            [](int *ptr){
                delete []ptr;
            });
            belongings.clear();
            biggestAtk=atk;
        }
        int *ptr = new int[16];
        for(int i=0;i<16;i++)
            ptr[i]=belonging[i];
        belongings.push_back(ptr);
    }
};

#endif // BELONGINGSTRUCTURE_H

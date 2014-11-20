#include "calculator.h"

#include <iostream>

using namespace std;

void cal_dataReady(string msg){
    stringstream st;
    int carrierNum;
    st.str(msg);
    st>>carrierNum;
    string tmpName;
    for(int i=0;i<carrierNum;i++){
        st>>tmpName;
        int tmpCarrierID=carriers_m[tmpName];
        int tmpGridNum=carriers[tmpCarrierID].getGridNum();
        //insert grid
        for(int j=0;j<tmpGridNum;j++)
            gridVec.push_back(Grid(i,j,carriers[tmpCarrierID].getGridSize(j),carriers[tmpCarrierID].getAtk()));
    }
//    for(int i=0;i<gridVec.size();i++)
//        cout<<gridVec[i]<<endl;

    int planeTypeNum;
    st>>planeTypeNum;
    for(int i=0;i<planeTypeNum;i++){
        st>>tmpName;
        int tmpPlaneID=planes_m[tmpName];
        int tmpNum;
        st>>tmpNum;
        for(int i=0;i<tmpNum;i++)
            planeVec.push_back(planes[tmpPlaneID]);
    }

//    for(int i=0;i<planeVec.size();i++)
//        cout<<planeVec[i]<<endl;
}

ostream &operator<<(ostream &os,Grid &item){
    os<<item.carrierPos<<" "<<item.gridPos<<" "<<item.gridSize<<" "<<item.carrierAtk;
    return os;
}

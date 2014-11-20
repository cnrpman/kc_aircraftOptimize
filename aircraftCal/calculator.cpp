#include "calculator.h"

#include <iostream>

using namespace std;

void cal_dataReady(string msg){
    stringstream st;
    st.str(msg);

    //read the query airDominance
    st>>airDomin;

    //read carrier
    int carrierNum;
    st>>carrierNum;
    string tmpName;
    int tmpAvailGrid;
    for(int i=0;i<carrierNum;i++){
        st>>tmpName>>tmpAvailGrid;
        int tmpCarrierID=carriers_m[tmpName];
        int tmpGridNum=min(carriers[tmpCarrierID].getGridNum(),tmpAvailGrid);
        //insert grid
        for(int j=0;j<tmpGridNum;j++)
            gridVec.push_back(Grid(i,j,carriers[tmpCarrierID].getGridSize(j),carriers[tmpCarrierID].getAtk()));
    }
    for(int i=0;i<gridVec.size();i++)
        cout<<gridVec[i]<<endl;

    //read plane
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
    for(int i=0;i<planeVec.size();i++)
        cout<<planeVec[i]<<endl;
}

bool cal_cmp_grid(const Grid &a,const Grid &b){
    return a.gridSize>b.gridSize;
}

bool cal_cmp_plane(Plane a,Plane b){
    return a.getAirDominance()>b.getAirDominance();
}

double formulaFighter(int gridSize,int airDominance){
    return sqrt(gridSize)*airDominance;
}

bool cal_run(){//if available result
    double curAir=0.0;
    //fighter greedy
    sort(gridVec.begin(),gridVec.end(),cal_cmp_grid);
    sort(planeVec.begin(),planeVec.end(),cal_cmp_plane);

    int gsz=gridVec.size(),tot=0;
    for(int i=0;i<gsz;i++){
        if(curAir>=airDomin)break;
        curAir+=formulaFighter(gridVec[i].gridSize,planeVec[i].getAirDominance());
        tot++;
    }
    if(curAir<airDomin)return false;
//    cout<<curAir<<" "<<tot<<endl;

    //search


    return true;
}

ostream &operator<<(ostream &os,Grid &item){
    os<<item.carrierPos<<" "<<item.gridPos<<" "<<item.gridSize<<" "<<item.carrierAtk;
    return os;
}

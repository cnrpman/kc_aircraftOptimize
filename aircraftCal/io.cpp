#include "io.h"

using namespace std;

void read_planes(int &planes_tot,vector<Plane> &planes,map<string,int> &planes_m){
    fstream in;
    in.open("P_DAT.txt",ios::in);
    if(!in.is_open()) cout<<"P_DAT read failed"<<endl;

    planes_tot=1;
    Plane tmp;
    while(in.good()){
        in>>tmp;
        planes.push_back(tmp);
        planes_m[tmp.getName()]=planes_tot;
        planes_tot++;
    }
    in.close();

//    for(int i=0;i<planes.size();i++)
//        cout<<planes[i].getName()<<" "<<planes[i].getCategoryName()<<endl;
}

void read_carriers(int &carriers_tot,vector<Carrier> &carriers,map<string,int> &carriers_m){
    fstream in;
    in.open("C_DAT.txt",ios::in);
    if(!in.is_open()) cout<<"C_DAT read failed"<<endl;

    carriers_tot=1;
    Carrier tmp;
    while(in.good()){
        in>>tmp;
        carriers.push_back(tmp);
        carriers_m[tmp.getName()]=carriers_tot;
        carriers_tot++;
    }
    in.close();

//    for(int i=0;i<carriers.size();i++)
//        cout<<carriers[i].getName()<<" "<<carriers[i].getCategoryName()<<endl;
}

#include "io.h"

using namespace std;

void read_planes(int &planes_tot,vector<Plane> &planes,map<string,int> &planes_m){
    fstream in;
    in.open("P_DAT.txt",ios::in);
    if(!in.is_open()) cout<<"P_DAT read failed"<<endl;

    planes_tot=1;
    Plane tplane;
    while(in.good()){
        in>>tplane;
        planes.push_back(tplane);
        planes_m[tplane.name]=planes_tot;
        planes_tot++;
    }
    in.close();
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
        carriers_m[tmp.name]=carriers_tot;
        carriers_tot++;
    }
    in.close();
}

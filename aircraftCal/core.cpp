#include "core.h"

using namespace std;

void core_initialization(){
    //initialize category map
    for(int i=0;i<PLANE_CATE_NUM;i++) plane_cate_m[PLANE_CATE_NAME[i]]=i;
    for(int i=0;i<CARRIER_CATE_NUM;i++) carrier_cate_m[CARRIER_CATE_NAME[i]]=i;

    //read preset data
    read_planes(planes_tot,planes,planes_m);
    read_carriers(carriers_tot,carriers,carriers_m);
}

void core_query();

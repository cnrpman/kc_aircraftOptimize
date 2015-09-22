#include "header/ACC.h"

namespace acc{
    ACC::ACC(){
        io_read_csv(this->carriers_pool, "../asset/carrier_data_list.csv");
        io_read_csv(this->planes_pool, "../asset/plane_data_list.csv");
    }

    std::stringstream &ACC::query(const std::stringstream &iss, std::stringstream &oss){
        cal_dataReady(iss);
        if(!cal_run()) cal_get_err(oss);
        else cal_get_res(oss);
        return oss;
    }
}

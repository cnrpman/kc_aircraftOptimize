#include "header/ACC.h"

namespace acc{
    ACC::ACC(){
        io_read_csv(this->cvs_pool,    "asset/CV_ascii.csv");
        io_read_csv(this->planes_pool, "asset/plane_ascii.csv");
    }

    std::stringstream &ACC::query(const std::stringstream &iss, std::stringstream &oss){
        parse_query(this->sortie_cvs,    this->sortie_cvs_N,    this->cvs_pool);
        parse_query(this->sortie_planes, this->sortie_planes_N, this->planes_pool);

        if(!cal_run(cv_queue,plane_queue)) cal_get_err(oss);
        else cal_get_res(oss);
        return oss;
    }
}

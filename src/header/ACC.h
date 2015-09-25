#ifndef TACC_H
#define TACC_H

#include <iostream>
#include <vector>
#include <map>
#include <sstream>

#include "../../def.h"
#include "Plane.h"
#include "CV.h"
#include "io.h"
//#include "calculator.h"

namespace acc{
    class ACC{
    private:
        std::map<std::string,CV>    cvs_pool;
        std::map<std::string,Plane> planes_pool;

        CV    sortie_cvs   [MAX_CV];
        Plane sortie_planes[MAX_PLANE];
        int   sortie_cvs_N,
              sortie_planes_N;
    public:
        ACC();
        std::stringstream &query(const std::stringstream &iss, std::stringstream &oss);
    };
}

#endif // ACC_H

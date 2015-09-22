#ifndef CORE_H
#define CORE_H

#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include "Plane.h"
#include "Carrier.h"
#include "io.h"
#include "calculator.h"

namespace acc{
    class ACC{
    private:
        map<string,Plane> planes_pool;
        map<string,Carrier> carriers_pool;
    public:
        ACC();
        std::stringstream &query(const std::stringstream &iss, std::stringstream &oss);
    };
}

#endif // CORE_H

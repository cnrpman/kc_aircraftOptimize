#ifndef IO_H
#define IO_H

#include "predef.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include "Plane.h"
#include "Carrier.h"

namespace acc{
    template<typename Type>
    bool io_read_csv(std::map<string, Type> &pool, std::string path);
}

#endif // IO_H

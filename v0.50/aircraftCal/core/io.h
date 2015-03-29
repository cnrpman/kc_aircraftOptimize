#ifndef IO_H
#define IO_H

#include "predef.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include "Plane.h"
#include "Carrier.h"
void read_planes(int &planes_tot,vector<Plane> &planes,map<string,int> &planes_m);
void read_carriers(int &carriers_tot,vector<Carrier> &carriers,map<string,int> &carriers_m);
extern char *LOCAL;
#endif // IO_H

#include <iostream>
#include <fstream>
#include <sstream>
#include "core.h"

using namespace std;

int main(void)
{
    core_initialization();

////temporary
    fstream in;
    stringstream ss;
    string tmp;
    in.open("query.txt",ios::in);
    while(in.good()){
        in>>tmp;
        ss<<tmp<<" ";
    }
    tmp=ss.str();
    core_query(tmp);
////

    return 0;
}

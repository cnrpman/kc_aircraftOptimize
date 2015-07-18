#include "core/predef.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include "core/core.h"

using namespace std;

//int main(void)
int main(int argc,char *argv[])
{
    core_initialization();
    fstream in;
    stringstream ss;

    #ifdef DEBUG
        string str;
        in.open("query.txt",ios::in);
        while(in.good()){
            in>>str;
            ss<<str<<" ";
        }
    #else
        for(int i=1;i<argc;i++)
            ss<<argv[i]<<" ";
    #endif

    cout<<core_query(ss).str();

    #ifdef WINDOWS
        system("pause");
    #endif
    return 0;
}

//        main  临时界面
//        |
//        core
//           |-predef
//           |
//           |-io          从P_DAT和C_DAT读入航母&舰载机设定
//           |-calculator      计算逻辑
//           |     |-formulation       用到的公式
//           |     |-grid              航母格子类
//           |-Carrier     航母类
//           |-Plane       舰载机类
//           |-gobal       运算功能的全局变量

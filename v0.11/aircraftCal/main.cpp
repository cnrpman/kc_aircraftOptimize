#include <iostream>
#include <fstream>
#include <sstream>
#include "core/core.h"

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
    cout<<core_query(tmp);

    system("pause");
////
    return 0;
}

//        main  临时界面
//        |
//        core  运算功能本体
//           |-io          从P_DAT和C_DAT读入航母&舰载机设定
//           |-calculator  在这里计算
//           |-Carrier     航母类
//           |-Plane       舰载机类
//           |-gobal       运算功能的全局变量

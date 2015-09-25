#include <cstring>
#include <exception>
#include <iostream>
#include <fstream>
#include <sstream>
#include "def.h"
#include "src/header/ACC.h"

std::stringstream iss, oss;

int main(int argc,char *argv[])
{
    if(argc <= 1){
        std::cout<<"Usage: <query string>  | query"<<std::endl
                 <<"       -d              | debug"<<std::endl;
        //return -1;
    }
    else if(strcmp(argv[1],"-d") == 0){
        std::ifstream fin("query.txt");
        if(!fin.is_open()){
            std::cerr << L"Could not open 'query.txt'" << std::endl;
            return -1;
        }
        else
            iss << fin.rdbuf();
    }
    else{
        iss << argv[1];
    }

    acc::ACC* acc = new acc::ACC();
    //acc->query(iss,oss);
    //cout << oss.rdbuf();

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
//           |-CV     航母类
//           |-Plane       舰载机类
//           |-gobal       运算功能的全局变量

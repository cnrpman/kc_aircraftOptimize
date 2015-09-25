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

//        main  ��ʱ����
//        |
//        core
//           |-predef
//           |
//           |-io          ��P_DAT��C_DAT���뺽ĸ&���ػ��趨
//           |-calculator      �����߼�
//           |     |-formulation       �õ��Ĺ�ʽ
//           |     |-grid              ��ĸ������
//           |-CV     ��ĸ��
//           |-Plane       ���ػ���
//           |-gobal       ���㹦�ܵ�ȫ�ֱ���

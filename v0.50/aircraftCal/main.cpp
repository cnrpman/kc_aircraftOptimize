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
//
//        ├─main  临时界面
//        │
//        └─core
//           ├─predef        预设常量
//           │
//           ├─io            从P_DAT和C_DAT读入航母&舰载机设定
//           │
//           ├─calculator    主体计算逻辑
//           ├─formulation   公式，内联的公式定义在formular_inline.h中
//           ├─atkdp         对炮击伤害的搜索
//           ├─belongingStructure  存放炮击伤害搜索结果的数据结构
//           │
//           ├─grid          航母格子类
//           ├─Carrier
//           ├─Plane
//           │
//           └─gobal

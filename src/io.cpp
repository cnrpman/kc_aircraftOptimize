#include "io.h"

namespace acc{
    template<typename Type>
    bool io_read_csv(std::map<string, Type> &pool, std::string path){
        std::fstream in;
        in.open(path, ios::in);
        if(!in.is_open()){
            std::cerr << path + " read failed" << std::endl;
            return false;
        }

        std::string head;
        Type content;
        in >> head;
        while(in.good()){
            in >> content;
            pool[content.name] = content;
        }
        in.close();
        return true;
    }
}

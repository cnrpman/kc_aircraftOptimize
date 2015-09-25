#ifndef TIO_H
#define TIO_H

#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <string>
#include "Plane.h"
#include "CV.h"
#include "CustomDelimiter.h"

namespace acc{
    template<typename Type>
    bool io_read_csv(std::map<std::string, Type> &pool, const std::string path){
        std::fstream in;
        in.open(path, std::ios::in);
        if(!in.is_open()){
            std::cerr << path + " read failed" << std::endl;
            return false;
        }
        in.imbue(std::locale(std::locale(), new custom_delim<char>(',')));

        std::string head;
        std::getline(in, head);
        Type content;
        while(in>>content){
            pool[content.getName()] = content;
            std::cout<<content<<std::endl;
        }
        in.close();
        return true;
    }
}

#endif // IO_H

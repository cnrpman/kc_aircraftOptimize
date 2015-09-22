#ifndef ENUMER_H
#define ENUMER_H

#include <map>
#include <string>
#include <iostream>
#include <stdexcept>

#define ENUM_STR(a) ENUM_STR_(a)
#define ENUM_STR_(a) #a

template<typename Enum_type>
struct Enumer{
    static const char * const Array[];
    static std::map<std::string, Enum_type> Map;
};
#endif // ENUMER_H
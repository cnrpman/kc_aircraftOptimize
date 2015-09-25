#ifndef ENUMER
#define ENUMER

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>

#define ENUM_PATH(a) ENUM_STR(a.def)
#define ENUM_STR(a) ENUM_STR_(a)
#define ENUM_STR_(a) #a

template<typename Enum_type>
struct Enumer{
    static const char * const Array[];
    static std::map<std::string, Enum_type> Map;
};
#endif // ENUMER

enum class ENUM_TYPE{
#   define _(a) a,
#   include ENUM_PATH(ENUM_TYPE)
#   undef _
    Num
};
std::ostream &operator << (std::ostream &os, const ENUM_TYPE &obj);
std::istream &operator >> (std::istream &is, ENUM_TYPE &obj);

#ifdef ENUM_TYPE

#define ENUM_PATH(a) ENUM_STR(a.def)
#define ENUM_STR(a) ENUM_STR_(a)
#define ENUM_STR_(a) #a

#define DIRTY_STR_TYPE(str,type) type(str.begin(),str.end())

template<>
const char * const Enumer<ENUM_TYPE>::Array[] = {
#   define _(a) #a,
#   include ENUM_PATH(ENUM_TYPE)
#   undef _
    0
};
template<>
std::map<std::string, ENUM_TYPE> Enumer<ENUM_TYPE>::Map = {
#   define _(a) {#a,ENUM_TYPE::a},
#   include ENUM_PATH(ENUM_TYPE)
#   undef _
    {"", static_cast<ENUM_TYPE>(0)}
};

std::ostream &operator << (std::ostream &os, const ENUM_TYPE &obj){
    os << Enumer<ENUM_TYPE>::Array[static_cast<int>(obj)];
    return os;
}

std::istream &operator >> (std::istream &is, ENUM_TYPE &obj){
    std::string tmp;
    is >> tmp;
    try{
        obj = Enumer<ENUM_TYPE>::Map.at(tmp);
    } catch (std::out_of_range &err){
        std::cerr << "Illegal Enum input, Enum Class:" << ENUM_STR(ENUM_TYPE) << " , input: " << tmp << std::endl
				  << err.what() << std::endl;
		obj = static_cast<ENUM_TYPE>(0);
    }

    return is;
}

#endif

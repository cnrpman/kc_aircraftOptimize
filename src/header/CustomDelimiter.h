/*
ref:
http://ftivk.blogspot.jp/2007/03/input-stream-delimiter.html
*/

#ifndef CUSTOM_DELIMITER_H
#define CUSTOM_DELIMITER_H

#include <locale>
#include <iostream>
#include <algorithm>

template <typename CharType>
class custom_delim : public std::ctype<CharType> {};

template <>
class custom_delim<char> : public std::ctype<char>{
    std::ctype<char>::mask my_table[table_size];
public:
    custom_delim(char delim) : std::ctype<char>(my_table,false,0){
        std::copy_n(classic_table(), table_size, my_table);
        my_table[delim] = (std::ctype<char>::mask)space;
    }
};

template <>
class custom_delim<wchar_t> : public std::ctype<wchar_t>{
    wchar_t delim;
public:
    custom_delim(wchar_t delim) : delim(delim) {}
    bool do_is(mask m, wchar_t c) const{
        if(m == space){
            if(c == delim) return true;
        }
        return std::ctype<wchar_t>::do_is(m, c);
    }
};
#endif // CUSTOM_DELIMITER_H

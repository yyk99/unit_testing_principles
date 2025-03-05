#ifndef STRING_SPLIT_H
#define STRING_SPLIT_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

inline std::vector<std::string> 
split_string(std::string const & str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

#endif
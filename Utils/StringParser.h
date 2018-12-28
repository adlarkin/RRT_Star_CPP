//
// Created by adlarkin on 12/28/18.
//

#ifndef RRT_STAR_CPP_STRINGPARSER_H
#define RRT_STAR_CPP_STRINGPARSER_H


#include <string>

class StringParser {
public:
    int parseInt(std::string inputStr);
    double parseDouble(std::string inputStr);
    std::string toLowerCase(std::string inputStr);
};


#endif //RRT_STAR_CPP_STRINGPARSER_H

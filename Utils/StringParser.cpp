//
// Created by adlarkin on 12/28/18.
//

#include <sstream>
#include <algorithm>
#include "StringParser.h"

int StringParser::parseInt(std::string inputStr) {
    std::stringstream userInput(inputStr);
    int outputInt = -1;
    userInput >> outputInt;
    return outputInt;
}

size_t StringParser::parseSizeT(std::string inputStr) {
    std::stringstream userInput(inputStr);
    size_t outputSizeT = 0;
    userInput >> outputSizeT;
    return outputSizeT;
}

double StringParser::parseDouble(std::string inputStr) {
    return std::atof(inputStr.c_str());
}

std::string StringParser::toLowerCase(std::string inputStr) {
    std::transform(inputStr.begin(), inputStr.end(), inputStr.begin(), ::tolower);
    return inputStr;
}

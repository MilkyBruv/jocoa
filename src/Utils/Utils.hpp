#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

class Utils
{
public:
    static vector<string> split(string str, string delimiter);
};

#endif
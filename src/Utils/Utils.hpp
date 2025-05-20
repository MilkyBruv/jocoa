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
    static bool stringCompare(string str1, string str2);
};

#endif
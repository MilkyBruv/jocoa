#include "./Utils.hpp"
#include "Utils.hpp"

vector<string> Utils::split(string str, string delimiter)
{
    vector<string> tokens;
    string token;
    size_t pos = 0;

    // Loop through each appearance of delimiter and split the string into tokens
    while ((pos = str.find(delimiter)) != string::npos)
    {
        token = str.substr(0, pos);
        tokens.push_back(token);
        str.erase(0, pos + delimiter.length());
    }

    tokens.push_back(str);

    return tokens;
}

bool Utils::stringCompare(string str1, string str2)
{
    // Compare strings for equality
    return strcmp(str1.c_str(), str2.c_str()) == 0 ? true : false;
}
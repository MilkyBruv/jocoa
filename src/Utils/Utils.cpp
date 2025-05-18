#include "./Utils.hpp"

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
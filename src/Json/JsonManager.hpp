#ifndef JSON_MANAGER_HPP
#define JSON_MANAGER_HPP

#include <iostream>
#include <string>
#include <vector>
#include "./../../lib/include/json.hpp"
#include "./../File/FileManager.hpp"

using std::string;
using std::vector;
using namespace nlohmann;

typedef struct JsonData
{
    string name;
    string type;
    string package;
    string packagePath;
    vector<string> sourceFiles;
    vector<string> dependencies;
    string natives;
} JsonData;

class JsonManager
{
public:
    static void loadJsonData();
    static JsonData jsonData;
};


#endif
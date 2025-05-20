#ifndef JSON_MANAGER_HPP
#define JSON_MANAGER_HPP

#include "./../Macros/Macros.hpp"
#include "./../../lib/include/json.hpp"
#include "./../File/FileManager.hpp"

using namespace nlohmann;

typedef struct JsonData
{
    string name;
    string type;
    string package;
    string packagePath;
    vector<string> sourceFiles;
    vector<string> dependencies;
} JsonData;

class JsonManager
{
public:
    static string packageToPackagePath(string package);
    static void loadJsonData();
    static JsonData jsonData;
    static string buildJsonFileRaw(string name, string type, string package, vector<string> sourceFiles, vector<string> dependencies);
    static string buildJsonFileJson(JsonData data);
};


#endif
#ifndef JSONREADER_HPP
#define JSONREADER_HPP

#include <string>
#include <vector>
#include "../../lib/include/json.hpp"

using std::string;
using std::vector;
using json = nlohmann::json;

/*
Java Commands:
 - javac -d <classfiles dir> -cp .;1.jar;2,jar dir1/*.java dir2/*.java
 - java -cp .;<classfiles>;1.jar;2.jar -Djava.library.path=<dll dir> main/Main
*/

typedef struct JsonData
{
    string projectName;
    string projectType;
    vector<string> sourceFiles;
    vector<string> dependencies;
    string natives;
    string classpath;
} JsonData;

class JSONReader
{
public:
    static JsonData getJsonData();
    static string getStringValue(string key, json jsonData);
    static vector<string> getVectorValue(string key, json jsonData);
};


#endif
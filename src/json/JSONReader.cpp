#include <iostream>
#include <fstream>
#include <string>
#include "JSONReader.hpp"

using std::string;
using std::cerr;
using std::cout;
using std::endl;

JsonData JSONReader::getJsonData()
{
    JsonData jsonDataOut;
    std::ifstream inFile(std::filesystem::current_path().u8string() + "/jocoa.json");
    
    json jsonDataIn;

    try
    {
        inFile >> jsonDataIn;
    }
    catch(const json::parse_error &e)
    {
        cerr << "Failed to parse jocoa.json file. >>" << e.what() << endl;
    }

    jsonDataOut.projectName = getStringValue("projectName", jsonDataIn);
    jsonDataOut.projectType = getStringValue("projectType", jsonDataIn);
    jsonDataOut.sourceFiles = getVectorValue("sourceFiles", jsonDataIn);
    jsonDataOut.dependencies = getVectorValue("dependencies", jsonDataIn);
    jsonDataOut.classpath = getStringValue("classpath", jsonDataIn);
    jsonDataOut.natives = getStringValue("natives", jsonDataIn);

    return jsonDataOut;
}

string JSONReader::getStringValue(string key, json jsonData)
{
    try
    {
        return jsonData[key];
    }
    catch(const json::type_error &e)
    {
        cerr << "Failed to parse {" << key << "} in jocoa.json file. >>" << e.what() << endl;
        return nullptr;
    }
}

vector<string> JSONReader::getVectorValue(string key, json jsonData)
{
    vector<string> output;

    try
    {
        for (const auto &item : jsonData[key])
        {
            output.push_back(item);
        }
    }
    catch(const json::type_error &e)
    {
        cerr << "Failed to parse {" << key << "} in jocoa.json file. >>" << e.what() << endl;
    }

    return output;
}

#include "./JsonManager.hpp"
#include "JsonManager.hpp"

JsonData JsonManager::jsonData;

string JsonManager::packageToPackagePath(string package)
{
    string packagePath = package;

    // Replace all "." with "/"
    for (int i = 0; i < package.length(); i++)
    {
        if (packagePath[i] == '.') { packagePath[i] = '/'; }
    }

    return packagePath;
}

void JsonManager::loadJsonData()
{
    // Check if file exists
    if (FileManager::fileExists("jocoa.json"))
    {
        // Load json data from jocoa.json file
        std::fstream jsonFile(FileManager::currentPath + "/jocoa.json");
        json json;
        jsonFile >> json;
        
        // Assign all attributes
        jsonData.name = json["name"];
        jsonData.type = json["type"];
        jsonData.package = json["package"];
        jsonData.packagePath = packageToPackagePath(jsonData.package); // Create path from package
        jsonData.sourceFiles = json["sourceFiles"];
        jsonData.dependencies = json["dependencies"];
    }
}

string JsonManager::buildJsonFileRaw(string name, string type, string package, vector<string> sourceFiles, vector<string> dependencies)
{
    string jsonFile = "{\n"
    "\t\"name\": " + name + ",\n"
    "\t\"type\": " + type + ",\n"
    "\t\"package\": " + package + ",\n"
    "\t\"sourceFiles\": [";

    // Only add if there's any source files
    if (sourceFiles.size() != 0)
    {
        for (size_t i = 0; i < sourceFiles.size(); i++)
        {
            jsonFile += "\n\t\t\"" + sourceFiles[i] + "\"";

            // If not at the end then add ",", else move onto dependencies
            if (i != sourceFiles.size() - 1) { jsonFile += ","; }
        }
    }
    else { jsonFile += "\n"; } // Add new line between [] if no sourceFiles for cleaner json

    jsonFile += "\n\t],\n\t\"dependencies\": [";
    
    // Only add if there's any dependencies
    if (dependencies.size() != 0)
    {
        for (size_t i = 0; i < dependencies.size(); i++)
        {
            jsonFile += "\n\t\t\"" + dependencies[i] + "\"";

            // If not at the end then add ",", else add rest of json data
            if (i != dependencies.size() - 1) { jsonFile += ","; }
        }
    }
    else { jsonFile += "\n"; } // Add new line between [] if no sourceFiles for cleaner json

    jsonFile += "\n\t]\n}";

    return jsonFile;
}

string JsonManager::buildJsonFileJson(JsonData data)
{
    string jsonFile = "{\n"
    "\t\"name\": " + data.name + ",\n"
    "\t\"type\": " + data.type + ",\n"
    "\t\"package\": " + data.package + ",\n"
    "\t\"sourceFiles\": [";

    // Only add if there's any source files
    if (data.sourceFiles.size() != 0)
    {
        for (size_t i = 0; i < data.sourceFiles.size(); i++)
        {
            jsonFile += "\n\t\t\"" + data.sourceFiles[i] + "\"";

            // If not at the end then add ",", else move onto dependencies
            if (i != data.sourceFiles.size() - 1) { jsonFile += ","; }
        }
    }
    else { jsonFile += "\n"; } // Add new line between [] if no sourceFiles for cleaner json

    jsonFile += "\n\t],\n\t\"dependencies\": [";
    
    // Only add if there's any dependencies
    if (data.dependencies.size() != 0)
    {
        for (size_t i = 0; i < data.dependencies.size(); i++)
        {
            jsonFile += "\n\t\t\"" + data.dependencies[i] + "\"";

            // If not at the end then add ",", else add rest of json data
            if (i != data.dependencies.size() - 1) { jsonFile += ","; }
        }
    }
    else { jsonFile += "\n"; } // Add new line between [] if no sourceFiles for cleaner json

    jsonFile += "\n\t]\n}";

    return jsonFile;
}
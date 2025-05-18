#include "./JsonManager.hpp"

JsonData JsonManager::jsonData;

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

        // Create path from package
        jsonData.packagePath = jsonData.package;
        for (int i = 0; i < jsonData.packagePath.length(); i++)
        {
            if (jsonData.packagePath[i] == '.') { jsonData.packagePath[i] = '/'; }
        }
        
        jsonData.sourceFiles = json["sourceFiles"];
        jsonData.dependencies = json["dependencies"];
        jsonData.natives = json["natives"];
    }
}
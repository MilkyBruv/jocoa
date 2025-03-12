#include "./Jocoa.hpp"
#include "./../Macros.hpp"
#include "./../Log/Logger.hpp"
#include <filesystem>
#include <fstream>

string Jocoa::currentPath = "";

void Jocoa::createDirectory(string path)
{
    if (std::filesystem::create_directory(currentPath + "/" + path))
    {
        Logger::info("Created \t ./" + path);
    }
    else
    {
        Logger::error("Failed to create \t ./" + path);
    }
}

void Jocoa::createFile(string path)
{
    std::ofstream file(currentPath + "/" + path);
    file.close();
    Logger::info("Created \t ./" + path);
}

void Jocoa::writeFile(string path, string contents)
{
    std::ofstream file(currentPath + "/" + path);
    file << contents;
    file.close();
    Logger::info("Wrote to \t ./" + path);
}

void Jocoa::init()
{
    currentPath = std::filesystem::current_path();
    std::cout << currentPath << "\n";
}

void Jocoa::_new(string args[])
{
    // arg1 = name
    string name;
    if (args->size() >= 3) { name = args[2]; }
    else
    {
        Logger::error("Usage:\n\tjocoa new <name>\n\tOR jocoa new <name> <type>");
        return;
    }

    // arg2 = type (r, run, runnable, l, lib, library) OPTIONAL
    // arg2 default = runnable
    char type;
    string typeStr;
    if (args->size() == 4 && (args[3].c_str()[0] == 'r' || args[3].c_str()[0] == 'l'))
    {
        type = args[3][0];
    }
    else { type = 'r'; }

    if (type == 'r') { typeStr = "runnable"; } 
    else if (type == 'l') { typeStr = "library"; }

    // Create Folders
    createDirectory(name);
    createDirectory(name + "/src");
    createDirectory(name + "/src/main");
    createDirectory(name + "/lib");
    createDirectory(name + "/lib/natives");
    createDirectory(name + "/res");
    createFile(name + "/jocoa.json");
    writeFile(name + "/jocoa.json", "{\n\t\"tasks\": [\n\t\t{\n\t\t\t\"projectName\": \"" + name + "\",\n\t\t\t\"projectType\": \"" + typeStr + "\",\n\t\t\t\"sourceFiles\": [\n\t\t\t\t\"src/main/Main.java\"\n\t\t\t],\n\t\t\t\"dependencies\": [\n\t\t\t\t\n\t\t\t],\n\t\t\t\"natives\": \"lib/natives\"\n\t\t}\n\t]\n}");
    createFile(name + "/src/main/Main.java");
    writeFile(name + "/src/main/Main.java", "package main;\n\npublic class Main {\n\n\tpublic static void main(String[] args) {\n\n\t\tSystem.out.println(\"Hello World!\");\n\n\t}\n\n}");
}

void Jocoa::_search(string args[])
{
    // 
}

void Jocoa::_run(string args[])
{
    // 
}

void Jocoa::_clean(string args[])
{
    // 
}

void Jocoa::_package(string args[])
{
    // 
}

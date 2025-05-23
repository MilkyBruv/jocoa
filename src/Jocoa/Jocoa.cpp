#include "./Jocoa.hpp"
#include "Jocoa.hpp"

namespace fs = std::filesystem;
using std::cout;
using std::cin;
using std::endl;

string Jocoa::version = "v0.1.1";

void Jocoa::init(string args[])
{
    FileManager::setCurrentPath();

    // Check if json file exists
    if (!FileManager::exists("jocoa.json"))
    {
        Logger::warn("Invalid Project, no jocoa.json file found");
        return;
    }

    JsonManager::loadJsonData();
}

void Jocoa::_help(string args[])
{
    cout << 
    "\033[31m"
    "     _\n"
    "    | | ___   ___ ___   __ _ \t\033[36m" + version + "\033[31m\n"
    " _  | |/ _ \\ / __/ _ \\ / _` |\n"
    "| |_| | (_) | (_| (_) | (_| |\n"
    " \\___/ \\___/ \\___\\___/ \\__,_|\t\033[36mgithub.com/MilkyBruv 2025\n\n"
    "\033[39mCommands:\n"

    "\thelp - Displays this command\n"

    "\tnew - Creates new Jocoa project\n"

    "\tinfo - Displays current project information\n"

    "\trun - Compiles and executes current project\n"
    "\t\t\033[36m-no-search\033[39m - Compiles and executes without searching for new source files or dependencies\n"

    "\tbuild - Compiles and exectures current project as .jar\n"
    "\t\t\033[36m-no-search\033[39m - Compiles and executes without searching for new source files or dependencies\n"
    "\t\t\033[36m-fat\033[39m - Compiles project and all dependencies into one .jar\n"

    "\tpackage - Compiles project to .jar\n"
    "\t\t\033[36m-no-search\033[39m - Compiles project without searching for new source files or dependencies\n"
    "\t\t\033[36m-fat\033[39m - Compiles project and all dependencies into one .jar\n"

    "\tsearch - Searches for new source files or dependencies, and appends them to jocoa.json\n"

    "\tclean - Cleans current project of compilation files" << endl;
}

void Jocoa::_info(string args[])
{
    cout << "Java Version: \033[36m";
    system("java -version");
    cout << "\n\033[39mJocoa Version: \033[36m" + version + "\033[39m\n";

    if (FileManager::exists("jocoa.json"))
    {
        cout << "Project Name: \033[36m" + JsonManager::jsonData.name + "\033[39m\n"
        "Project Type: \033[36m" + JsonManager::jsonData.type + "\033[39m\n"
        "Project Package: \033[36m" + JsonManager::jsonData.package + "\033[39m\n"
        "Project Source Files:\033[36m";
        
        for (const string& file : JsonManager::jsonData.sourceFiles)
        {
            cout << "\n \t" + file + ",";
        }

        cout << "\033[39m\nProject Dependencies:\033[36m\n";
        
        for (const string& dependency : JsonManager::jsonData.dependencies)
        {
            cout << "\n \t" + dependency + ",";
        }
    }

    cout << "\033[39m" << endl;
}

void Jocoa::_new(string args[])
{
    string name, package, defaultPackage, packagePath, typeStr;

    cout << "Enter options for new project (options marked with * are required)\n" << endl;

    // Project name

    cout << "*Project name: ";
    std::getline(cin, name);
    cout << endl;

    if (name.empty())
    {
        Logger::error("Project name must be specified");
        return;
    }

    // Type

    cout << "Project type (runnable,r/library,l), leave blank for default (runnable, r): ";
    std::getline(cin, typeStr);
    cout << endl;
    if (typeStr.empty())
    {
        typeStr = "runnable";
    }
    if (typeStr[0] == 'r') { typeStr = "runnable"; }
    else if (typeStr[0] == 'l') { typeStr = "library"; }
    else { typeStr = "runnable"; }

    // Package

    // Get system username
    string user = FileManager::getSystemUser();
    defaultPackage = "net." + user + "." + name;

    cout << "Package, leave blank for default (" + defaultPackage + "): ";
    std::getline(cin, package);
    cout << endl;
    if (package.empty())
    {
        package = defaultPackage;
    }

    packagePath = package;
    for (int i = 0; i < packagePath.length(); i++)
    {
        if (packagePath[i] == '.') { packagePath[i] = '/'; }
    }

    // Create file and folders
    FileManager::createDirectory(name + "/src/" + packagePath);
    FileManager::createDirectory(name + "/lib/natives");
    FileManager::createDirectory(name + "/res");
    FileManager::createDirectory(name + "/bin");
    FileManager::createFile(name + "/jocoa.json");

    if (Utils::stringCompare(typeStr, "runnable"))
    {
        cout << "runnable" << endl;
        FileManager::createDirectory(name + "/src/" + packagePath + "/main");
        FileManager::writeFile(name + "/jocoa.json", "{\n\t\"name\": \"" + name + "\",\n\t\"type\": \"" + typeStr + "\",\n\t\"package\": \"" + package + "\",\n\t\"sourceFiles\": [\n\t\t\"./src/" + packagePath + "/main/Main.java\"\n\t],\n\t\"dependencies\": [\n\t\t\n\t]\n}");
        FileManager::createFile(name + "/src/" + packagePath + "/main/Main.java");
        FileManager::writeFile(name + "/src/" + packagePath + "/main/Main.java", "package " + package + ".main;\n\npublic class Main {\n\n\tpublic static void main(String[] args) {\n\n\t\tSystem.out.println(\"Hello World!\");\n\n\t}\n\n}");
    }
    else if (Utils::stringCompare(typeStr, "library"))
    {
        // Create and package main library
        FileManager::writeFile(name + "/jocoa.json", "{\n\t\"name\": \"" + name + "\",\n\t\"type\": \"" + typeStr + "\",\n\t\"package\": \"" + package + "\",\n\t\"sourceFiles\": [\n\t\t\"./src/" + packagePath + "/library/Library.java\"\n\t],\n\t\"dependencies\": [\n\t\t\n\t],\n}");
        FileManager::createDirectory(name + "/src/" + packagePath + "/library");
        FileManager::createFile(name + "/src/" + packagePath + "/library/Library.java");
        FileManager::writeFile(name + "/src/" + packagePath + "/library/Library.java", "package " + package + ".library;\n\npublic class Library {\n\n\tpublic static void test() {\n\n\t\tSystem.out.println(\"Hello World from Library!\");\n\n\t}\n\n}");

        // Create test stuff for library project type
        FileManager::createDirectory(name + "/test/" + packagePath + "Test/main");
        FileManager::createFile(name + "/test/" + packagePath + "Test/main/Main.java");
        FileManager::writeFile(name + "/test/" + packagePath + "Test/main/Main.java", "package " + package + ".main;\n\nimport " + package + ".library.Library;\n\npublic class Main {\n\n\tpublic static void main(String[] args) {\n\n\t\tSystem.out.println(\"Hello World!\");\n\n\t}\n\n}");

        // Package in new project mode
        args[0] = "internal_new";
        JsonManager::loadJsonData();
        _package(args, 1);
    }
}

void Jocoa::_search(string args[])
{
    // Check if current dir is a project
    if (!FileManager::exists("jocoa.json"))
    {
        Logger::warn("Invalid Project, no jocoa.json file found");
        return;
    }

    // Clear current source files and dependencies
    JsonManager::jsonData.sourceFiles.clear();
    JsonManager::jsonData.dependencies.clear();

    // Search for source files and libraries
    FileManager::searchForFiles("src", ".java", JsonManager::jsonData.sourceFiles);
    FileManager::searchForFiles("lib", ".jar", JsonManager::jsonData.dependencies);

    // Build new json file
    string newJson = JsonManager::buildJsonFileJson(JsonManager::jsonData);

    // Write new json data to json file
    FileManager::writeFile("jocoa.json", newJson);

    // Update new json data
    JsonManager::loadJsonData();
}

void Jocoa::_run(string args[], size_t argc)
{
    if (!FileManager::exists("jocoa.json"))
    {
        Logger::error("jocoa.json file does not exist");
        return;
    }

    // Check if should search
    if (argc >= 3)
    {
        if (!Utils::stringCompare(args[2], "-no-search")) { Jocoa::_search(args); } // Check if should search before running
    }
    else { Jocoa::_search(args); }

    string javac, java;

    // Clear ./bin
    _clean(args);

    // If runnable then just compile to class then run
    if (Utils::stringCompare(JsonManager::jsonData.type, "runnable"))
    {   
        // Create commands from default source files and dependencies
        javac = CommandBuiler::buildClassJson(JsonManager::jsonData);
        java = CommandBuiler::runClassJson(JsonManager::jsonData);
    }
    if (Utils::stringCompare(JsonManager::jsonData.type, "library")) // If library then package src/main then run src/test
    {
        // Create commands from default source files and dependencies
        javac = CommandBuiler::buildClassJson(JsonManager::jsonData);

        // Get all source files from ./test
        vector<string> testSourceFiles;
        FileManager::searchForFiles("test", ".java", testSourceFiles);

        // Get all dependencies from ./lib and add the ./<name>.jar
        FileManager::searchForFiles("lib", ".jar", JsonManager::jsonData.dependencies);
        vector<string> testDependencies = JsonManager::jsonData.dependencies;
        testDependencies.push_back("./" + JsonManager::jsonData.name + ".jar");

        // Create commands from test source files and dependencies
        javac = CommandBuiler::buildClassRaw(testSourceFiles, testDependencies);
        java = CommandBuiler::runClassRaw(testSourceFiles, testDependencies, JsonManager::jsonData.packagePath);
    }

    // Run and print commands
    cout << javac << endl;
    system(javac.c_str());
    cout << java << endl;
    system(java.c_str());
}

void Jocoa::_clean(string args[])
{
    // Clear bin folder
    FileManager::clearDirectory("bin");
    Logger::info("Cleaned project");
}

void Jocoa::_package(string args[], size_t argc)
{
    string jar = "jar cf";
    string java;

    // Check if not in internal_new (new project) mode
    if (Utils::stringCompare(args[0], "internal_new")) { _search(args); }

    // If runnable compile to jar with main method
    if (Utils::stringCompare(JsonManager::jsonData.type, "runnable"))
    {
        jar += "e " + JsonManager::jsonData.name + ".jar " + JsonManager::jsonData.package + ".main.Main -C ./bin .";

        // Run command
        cout << jar << endl;
        system(jar.c_str());

        // Run jar file if specified to
        if (strcmp(args[2].c_str(), "run") == 0)
        {
            java = "java -jar ./" + JsonManager::jsonData.name + ".jar";

            // Run command
            cout << java << endl;
            system(java.c_str());
        }
    }
    if (Utils::stringCompare(JsonManager::jsonData.type, "library")) // If library then compile to jar without main method
    {
        // Compile to ./<name>.jar
        jar += " ./" + JsonManager::jsonData.name + ".jar -C ./bin .";

        // Run commands
        cout << jar << endl;
        system(jar.c_str());

        // Run jar file if specified to
        if (strcmp(args[2].c_str(), "run") == 0)
        {
            // Run test files with packaged .jar as a library
            _run(args, argc);
        }
    }
}

void Jocoa::_build(string args[], size_t argc)
{
    if (!FileManager::exists("jocoa.json"))
    {
        Logger::error("jocoa.json file does not exist");
        return;
    }

    // Check if should search
    if (argc >= 3)
    {
        if (!Utils::stringCompare(args[2], "-no-search")) {  } // Check if should search before running
    }
    else { Jocoa::_search(args); }

    bool fat, noSearch = false;

    for (size_t i = 0; i < argc; i++)
    {
        if (Utils::stringCompare(args[i], "-fat"))
        {
            fat = true;
        }
        else if (Utils::stringCompare(args[i], "-no-search"))
        {
            noSearch = true;
        }
    }

    if (!noSearch) { Jocoa::_search(args); }

    string java, jar;

    // If runnable compile to jar with main method
    if (Utils::stringCompare(JsonManager::jsonData.type, "runnable"))
    {
        if (!fat)
        {
            jar = CommandBuiler::buildRunnableJarJson(JsonManager::jsonData);
        }
        else if (fat)
        {
            jar = CommandBuiler::buildFATRunnableJarJson(JsonManager::jsonData);
        }

        java = "java -jar ./" + JsonManager::jsonData.name + ".jar";

        // Run command
        cout << jar << endl;
        system(jar.c_str());

        // Remove ./binf after creating the fat jar
        FileManager::remove("binf");
    }
    if (Utils::stringCompare(JsonManager::jsonData.type, "library")) // If library then compile to jar without main method
    {
        // Compile to ./<name>.jar
        jar += " ./" + JsonManager::jsonData.name + ".jar -C ./bin .";

        // Run commands
        cout << jar << endl;
        system(jar.c_str());

        // Run jar file if specified to
        if (strcmp(args[2].c_str(), "run") == 0)
        {
            // Run test files with packaged .jar as a library
            _run(args, argc);
        }
    }
}

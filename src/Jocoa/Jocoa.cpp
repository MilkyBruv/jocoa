#include "./Jocoa.hpp"
#include "Jocoa.hpp"

namespace fs = std::filesystem;
using std::cout;
using std::cin;
using std::endl;

string Jocoa::version = "v0.2.0";

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

    "\tbuild - Compiles current project as .jar\n"
    "\t\t\033[36m-no-search\033[39m - Compiles without searching for new source files or dependencies\n"
    "\t\t\033[36m-run\033[39m - Compiles project to .jar and executes it\n"
    "\t\t\033[36m-fat\033[39m - Compiles project and all dependencies into one .jar\n"

    "\tsearch - Searches for new source files or dependencies, and appends them to jocoa.json\n"

    "\tclean - Cleans current project of compilation files" << endl;
}

void Jocoa::_info(string args[])
{
    cout << "Java Version: \033[36m";
    system("java -version");
    cout << "\033[39mJocoa Version: \033[36m" + version + "\033[39m\n";

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

    cout << "\033[39m";
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
        FileManager::createDirectory(name + "/src/" + packagePath + "/main");
        FileManager::writeFile(name + "/jocoa.json", "{\n\t\"name\": \"" + name + "\",\n\t\"type\": \"" + typeStr + "\",\n\t\"package\": \"" + package + "\",\n\t\"sourceFiles\": [\n\t\t\"./src/" + packagePath + "/main/Main.java\"\n\t],\n\t\"dependencies\": [\n\t\t\n\t]\n}");
        FileManager::createFile(name + "/src/" + packagePath + "/main/Main.java");
        FileManager::writeFile(name + "/src/" + packagePath + "/main/Main.java", "package " + package + ".main;\n\npublic class Main {\n\n\tpublic static void main(String[] args) {\n\n\t\tSystem.out.println(\"Hello World!\");\n\n\t}\n\n}");
    }
    else if (Utils::stringCompare(typeStr, "library"))
    {
        // Create and package main library
        FileManager::writeFile(name + "/jocoa.json", "{\n\t\"name\": \"" + name + "\",\n\t\"type\": \"" + typeStr + "\",\n\t\"package\": \"" + package + "\",\n\t\"sourceFiles\": [\n\t\t\"./src/" + packagePath + "/library/Library.java\"\n\t],\n\t\"dependencies\": [\n\t\t\n\t]\n}");
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

    // Check for -jar and -no-search arguments
    bool jar = false, noSearch = false;

    for (size_t i = 0; i < argc; i++)
    {
        if (Utils::stringCompare(args[i], "-jar"))
        {
            jar = true;
        }
        else if (Utils::stringCompare(args[i], "-no-search"))
        {
            noSearch = true;
        }
    }

    if (!noSearch) { Jocoa::_search(args); }

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
    system(javac.c_str()); // Compile to .class
    cout << java << endl;
    system(java.c_str()); // Run .class files
}

void Jocoa::_clean(string args[])
{
    // Clear bin folder
    FileManager::clearDirectory("bin");
    Logger::info("Cleaned project");
}

void Jocoa::_build(string args[], size_t argc)
{
    if (!FileManager::exists("jocoa.json"))
    {
        Logger::error("jocoa.json file does not exist");
        return;
    }

    // Check for -fat and -no-search arguments
    bool fat = false, run = false, noSearch = false;

    for (size_t i = 0; i < argc; i++)
    {
        if (Utils::stringCompare(args[i], "-fat"))
        {
            fat = true;
        }
        else if (Utils::stringCompare(args[i], "-run"))
        {
            run = true;
        }
        else if (Utils::stringCompare(args[i], "-no-search"))
        {
            noSearch = true;
        }
    }

    if (!noSearch) { Jocoa::_search(args); }

    string javac, java, jar;

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

        // Create commands from standard json data
        javac = CommandBuiler::buildClassJson(JsonManager::jsonData);

        // Run commands
        cout << javac << endl;
        system(javac.c_str()); // Compile to .class
        cout << jar << endl;
        system(jar.c_str()); // Compile to .jar

        // If should run .jar
        if (run)
        {
            java = CommandBuiler::buildRunJarJson(JsonManager::jsonData);
            cout << java << endl;
            system(java.c_str()); // Run .jar
        }

        // Remove ./binf after creating the fat jar
        FileManager::remove("binf");

        // Clear ./bin
        FileManager::clearDirectory("bin");
    }
    else if (Utils::stringCompare(JsonManager::jsonData.type, "library")) // If library then compile to jar without main method
    {
        // Compile to ./<name>.jar
        if (fat)
        {
            jar = CommandBuiler::buildFATLibraryJarJson(JsonManager::jsonData);
        }
        else if (!fat)
        {
            jar = CommandBuiler::buildLibraryJarJson(JsonManager::jsonData);
        }

        javac = CommandBuiler::buildClassJson(JsonManager::jsonData);

        // Run commands
        cout << javac << endl;
        system(javac.c_str()); // Compile to .class
        cout << jar << endl;
        system(jar.c_str()); // Compile to .jar

        // Clear ./bin
        FileManager::clearDirectory("bin");

        // Compile and run ./test
        if (run)
        {
            cout << "run" << endl;
            vector<string> testSourceFiles, testDependencies;
            FileManager::searchForFiles("test", ".java", testSourceFiles);

            // Only copy standard dependencies if not using FAT jar
            if (!fat)
            {
                testDependencies = JsonManager::jsonData.dependencies;
            }
            
            // Add ./<name>.jar
            testDependencies.push_back("./" + JsonManager::jsonData.name + ".jar");
            
            // Build javac and java command from ./test source files and ./lib dependencies with ./<name>.jar
            javac = CommandBuiler::buildClassRaw(testSourceFiles, testDependencies);
            string java = CommandBuiler::runClassRaw(testSourceFiles, testDependencies, 
                JsonManager::jsonData.packagePath);

            cout << javac << endl;
            system(javac.c_str()); // Compile to .class
            cout << java << endl;
            system(java.c_str()); // Run .class files

            // Clear ./bin
            FileManager::clearDirectory("bin");
        }
    }
}

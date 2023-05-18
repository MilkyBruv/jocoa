#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <nlohmann/json.hpp>


using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::cerr;

using json = nlohmann::json;


string getCWD()
{

    std::filesystem::path path = std::filesystem::current_path();
    string path_str{path.u8string()};

    return path_str;

}


int main(int argc, char const *argv[])
{

    // Read json file

    std::ifstream in_file(getCWD() + "/jocoa.json");

    if (!in_file) 
    {
        
        cerr << "Failed to open the <jocoa.json> file." << endl;

        return 1;

    }

    // Get files and dependencies

    json data;

    try
    {

        in_file >> data;

    } catch (const json::parse_error& e)
    {

        cerr << "Failed to parse the JSON data: " << e.what() << endl;

        return 1;

    }

    vector<string> files;
    vector<string> dependencies;

    string final_javac = "javac -d ";
    string final_java = "java ";

    string d_args = "classfiles";
    string cp_args = "-cp \".";
    string sourcepath_args = "-sourcepath ";

    #pragma region try_catch_arrs_vars

    try
    {
        
        const auto &classfilesJson = data["classfiles"];
        d_args = classfilesJson;

    } catch (const json::type_error &e)
    {

        cerr << "Failed to access the 'classfiles' variable: " << e.what() << endl;

        return 1;

    }

    try
    {
        
        const auto &filesJson = data["files"];

        for (const auto &file : filesJson)
        {

            files.push_back(file);

        }

    } catch (const json::type_error &e)
    {

        cerr << "Failed to access the 'files' array: " << e.what() << endl;

        return 1;

    }

    try
    {

        const auto &dependenciesJson = data["dependencies"];

        for (const auto &dependency : dependenciesJson)
        {

            dependencies.push_back(dependency);

        }

    } catch (const json::type_error &e)
    {

        cerr << "Failed to access the 'dependencies' array: " << e.what() << endl;

        return 1;

    }

    #pragma endregion 

    for (const auto &dependency : dependencies)
    {

        cp_args += ";" + dependency;

    }

    cp_args += "\"";

    for (const auto &file : files)
    {

        sourcepath_args += file + ";";

    }

    sourcepath_args.at(sourcepath_args.length() - 1) = 0;

    final_javac += d_args + " " + cp_args + " " + sourcepath_args;

    cout << final_javac + "\n";

    return 0;
}

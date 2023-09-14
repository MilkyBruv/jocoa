#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <nlohmann/json.hpp>
#include <stdio.h>
#include <direct.h>

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::cerr;
using json = nlohmann::json;

const void create_directory(const string name);

int main(int argc, char const *argv[]) {

    string mode = argv[1];
    string path = std::filesystem::current_path().u8string();

    if (strcmp(mode.c_str(), "run") == 0) {

        // Read json file

        std::ifstream in_file(path + "/jocoa.json");

        if (!in_file) {
            
            cerr << "Failed to open the <jocoa.json> file." << endl;
            return 1;

        }

        // Get files and dependencies

        json data;

        try {

            in_file >> data;

        } catch (const json::parse_error &e) {

            cerr << "Failed to parse the JSON data: " << e.what() << endl;
            return 1;

        }

        vector<string> files;
        vector<string> dependencies;

        string final_javac = "javac -d ";
        string final_java = "java -cp ";
        string final_cmd = "";

        string d_args = "bin";
        string cp_args = "";
        string files_args = "";
        string natives_args = "";
        string D_args = "";

        #pragma region parseJson

        try {
            
            const auto &classfilesJson = data["classfiles"];
            d_args = classfilesJson;

        } catch (const json::type_error &e) {

            cerr << "Failed to access the 'classfiles' variable: " << e.what() << endl;
            return 1;

        }

        try {
            
            const auto &nativesJson = data["natives"];
            natives_args = nativesJson;

        } catch (const json::type_error &e) {

            cerr << "Failed to access the 'natives' variable: " << e.what() << endl;
            return 1;

        }

        try {
            
            const auto &filesJson = data["files"];

            for (const auto &file : filesJson) {

                files.push_back(file);

            }

        } catch (const json::type_error &e) {

            cerr << "Failed to access the 'files' array: " << e.what() << endl;
            return 1;

        }

        try {

            const auto &dependenciesJson = data["dependencies"];

            for (const auto &dependency : dependenciesJson) {

                dependencies.push_back(dependency);

            }

        } catch (const json::type_error &e) {

            cerr << "Failed to access the 'dependencies' array: " << e.what() << endl;
            return 1;

        }

        #pragma endregion

        // Create javac and java commands

        for (const auto &dependency : dependencies) {

            cp_args += ";" + dependency;

        }

        for (const auto &file : files) {

            files_args += file + " ";

        }

        D_args = " -Djava.library.path=./" + natives_args;

        files_args.at(files_args.length() - 1) = 0;

        final_javac += d_args + " -cp ." + cp_args + " " + files_args;
        final_java += ".;" + d_args + cp_args + D_args + " main/Main";

        cout << final_javac << "\n";
        cout << final_java << "\n";

        system("cmd /c");
        system(final_javac.c_str());
        system(final_java.c_str());

        // javac   -d <classfiles>   -cp .;1.jar;2,jar   dir1/*.java dir2/*.java
        // java   -cp .;<classfiles>;1.jar;2.jar   -Djava.library.path=<dll dir>   main/Main

        return 0;

    } else if (strcmp(mode.c_str(), "jar") == 0) {

        

    } else if (strcmp(mode.c_str(), "new") == 0) {

        string name = argv[2];

        create_directory(path + "\\" + name);
        create_directory(path + "\\" + name + "\\src\\main");
        create_directory(path + "\\" + name + "\\lib\\natives");
        create_directory(path + "\\" + name + "\\bin");

        std::ofstream jocoa_json_file(path + "\\" + name + "\\jocoa.json");
        jocoa_json_file << "{\n\n\t\"files\": [\"src/main/Main.java\"],\n\n\t\"dependencies\": [],\n\n\t\"natives\": \"lib/natives\",\n\n\t\"classfiles\": \"bin\"\n\n}";
        jocoa_json_file.close();
        
        std::ofstream main_java_file(path + "\\" + name + "\\src\\main\\Main.java");
        main_java_file << "package main;\n\npublic class Main {\n\n\tpublic static void main(String[] args) {\n\n\t\t//\n\n\t\t}\n\n}";
        main_java_file.close();

    }
    
}



const void create_directory(const string dir) {

    if (!std::filesystem::create_directories(dir)) {

        cerr << "Directory could not be created!" << endl;

    } else {

        cout << "Created \"" + dir + "\"" << endl;

    }

}

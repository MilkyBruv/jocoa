#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
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

typedef struct task_t
{

    string task;
    vector<string> files;
    vector<string> dependencies;
    string natives;
    string classfiles;

    string final_javac = "javac -d ";
    string final_java = "java -cp ";
    string final_cmd = "";

    string d_args = "bin";
    string cp_args = "";
    string files_args = "";
    string natives_args = "";
    string D_args = "";

} task_t;

int main(int argc, char const *argv[]) {

    string mode = argv[1];
    string path = std::filesystem::current_path().u8string();

    if (strcmp(mode.c_str(), "run") == 0) {

        string task_arg = argv[2];

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

        vector<task_t> tasks;
        vector<string> task_names;
        task_t current_task;

        #pragma region parseJson

        try {

            int current_task_index = 0;
            const auto &tasks_json = data["tasks"];

            for (const auto &tasks : tasks_json) {

                task_t new_task;

                try {
            
                    const auto &classfiles_json = data["tasks"][current_task_index];

                    try {
            
                        const auto &task_json = data["tasks"][current_task_index]["task"];
                        new_task.task = task_json;
                        task_names.push_back(task_json);

                    } catch (const json::type_error &e) {

                        cerr << "Failed to access the 'task' variable: " << e.what() << endl;
                        return 1;

                    }

                    try {
            
                        const auto &classfiles_json = data["tasks"][current_task_index]["classfiles"];
                        new_task.d_args = classfiles_json;

                    } catch (const json::type_error &e) {

                        cerr << "Failed to access the 'classfiles' variable: " << e.what() << endl;
                        return 1;

                    }

                    try {
            
                        const auto &natives_json = data["tasks"][current_task_index]["natives"];
                        new_task.natives_args = natives_json;

                    } catch (const json::type_error &e) {

                        cerr << "Failed to access the 'natives' variable: " << e.what() << endl;
                        return 1;

                    }

                    try {
            
                        const auto &files_json = data["files"];

                        for (const auto &file : files_json) {

                            new_task.files.push_back(file);

                        }

                    } catch (const json::type_error &e) {

                        cerr << "Failed to access the 'files' array: " << e.what() << endl;
                        return 1;

                    }

                    try {

                        const auto &dependencies_json = data["dependencies"];

                        for (const auto &dependency : dependencies_json) {

                            new_task.dependencies.push_back(dependency);

                        }

                    } catch (const json::type_error &e) {

                        cerr << "Failed to access the 'dependencies' array: " << e.what() << endl;
                        return 1;

                    }

                    current_task_index++;

                } catch (const json::other_error &e) {

                    cerr << "Failed to access index [" << current_task_index << "] of 'tasks' array: " << e.what() << endl;
                    return 1;

                }

            }

        } catch (const json::type_error &e) {

            cerr << "Failed to access the 'files' array: " << e.what() << endl;
            return 1;

        }

        #pragma endregion

        cout << "HERE 1" << endl;

        // Find specified task and create respective javac and java commands

        if (std::find(task_names.begin(), task_names.end(), task_arg) != task_names.end())
        {

            cout << "HERE 2" << endl;

            cout << tasks.size() << endl; // returns 0 idk why cuh

            for (task_t task : tasks)
            {

                cout << "HERE 3" << endl;

                if (strcmp(task.task.c_str(), task_arg.c_str()) == 0)
                {

                    current_task = task;
                    cout << "HERE 4 " << task_arg << endl;

                }

            }

            for (const auto &dependency : current_task.dependencies) {

                current_task.cp_args += ";" + dependency;

            }

            for (const auto &file : current_task.files) {

                current_task.files_args += file + " ";

            }

            current_task.D_args = " -Djava.library.path=./" + current_task.natives_args;

            current_task.files_args.at(current_task.files_args.length() - 1) = 0;

            current_task.final_javac += current_task.d_args + " -cp ." + current_task.cp_args + " " + current_task.files_args;
            current_task.final_java += ".;" + current_task.d_args + current_task.cp_args + current_task.D_args + " main/Main";

            cout << current_task.final_javac << "\n";
            cout << current_task.final_java << "\n";

            system("cmd /c");
            system(current_task.final_javac.c_str());
            system(current_task.final_java.c_str());

            // javac   -d <classfiles>   -cp .;1.jar;2,jar   dir1/*.java dir2/*.java
            // java   -cp .;<classfiles>;1.jar;2.jar   -Djava.library.path=<dll dir>   main/Main

            return 0;

        } else
        {

            cerr << "There are no tasks in the <jocoa.json> file: " << endl;
            return 1;

        }

    } else if (strcmp(mode.c_str(), "jar") == 0) {

        

    } else if (strcmp(mode.c_str(), "new") == 0) {

        string name = argv[2];

        create_directory(path + "\\" + name);
        create_directory(path + "\\" + name + "\\src\\main");
        create_directory(path + "\\" + name + "\\lib\\natives");
        create_directory(path + "\\" + name + "\\bin");

        std::ofstream jocoa_json_file(path + "\\" + name + "\\jocoa.json");
        jocoa_json_file << "{\n\n\t\"tasks\": [\n\n\t\t{\n\n\t\t\t\"files\": [\n\n\t\t\t\t\"src/main/Main.java\"\n\n\t\t\t],\n\n\t\t\t\"dependencies\": [],\n\n\t\t\t\"natives\": \"lib/natives\",\n\n\t\t\t\"classfiles\": \"bin\"\n\n}]}";
        jocoa_json_file.close();
        
        std::ofstream main_java_file(path + "\\" + name + "\\src\\main\\Main.java");
        main_java_file << "package main;\n\npublic class Main {\n\n\tpublic static void main(String[] args) {\n\n\t\tSystem.out.println(\"Hello world!\");\n\n\t}\n\n}";
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

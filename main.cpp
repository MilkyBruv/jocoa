#include <iostream>
#include <Windows.h>
#include <string>
#include <filesystem>
#include <sstream>
#include <fstream>
#include <cctype>
#include <algorithm>
#include <functional>

using std::string;
using std::cout;
using std::endl;
using std::ifstream;
using std::ios;
using std::vector;

string getCWD()
{

    std::filesystem::path path = std::filesystem::current_path();
    string path_str{path.u8string()};

    return path_str;

}

string getExePath()
{
    
    char buffer[MAX_PATH];

    GetModuleFileNameA(NULL, buffer, MAX_PATH);

    return buffer;

}

string replace(string str, char c1, char c2)
{

    int l = str.length();
 
    for (int i = 0; i < l; i++)
    {
        
        if (str[i] == c1)
        {

            str[i] = c2;

        }
 
        else if (str[i] == c2)
        {
        
            str[i] = c1;

        }

    }

    return str;

}

vector<string> split(string str, char delimiter)
{

    vector<string> splits;

    char arr[100];
    
    std::cin.getline(arr, 100);
    int i = 0;
    
    // Temporary string used to split the string.
    string s; 
    while (arr[i] != '\0')
    {
    
        if (arr[i] != delimiter)
        {
        
            s += arr[i]; 

        } else
        {
        
            splits.push_back(s);
            s.clear();

        }

        i++;

    }

    return splits;

}

int main(int argc, char const *argv[])
{

    // Test path stuff

    string path = getExePath();
    cout << path << endl;

    string cwd = getCWD();
    cout << cwd << endl;

    // Get lines from file

    ifstream in_file;
    in_file.open(cwd + "/jocoa_lists.txt", ios::in);
    vector<string> lines;
    string l;

    while (std::getline(in_file, l))
    {

        lines.push_back(l);

    }

    in_file.close();

    vector<string> files;
    vector<string> libs;

    bool add_files = false;
    bool add_libs = false;

    string st_line;
    string sp_line;

    // Strip line of trailing / pre whitespace

    for (string &line : lines)
    {

        cout << line + "\n";
        
        auto st_line_start_strip = line.begin();
        auto st_line_end_strip = line.rbegin();

        while (std::isspace(*st_line_start_strip))
        {

            ++st_line_start_strip;

        }

        while (std::isspace(*st_line_end_strip))
        {

            ++st_line_end_strip;

        }

        st_line = string(st_line_start_strip, st_line_end_strip.base());

        // Check for empty lines

        if (st_line != "\n" && st_line != "" && st_line != "\0")
        {

            cout << st_line << endl;

            // Remove all spaces

            sp_line.erase(std::remove(sp_line.begin(), sp_line.end(), ' '), sp_line.end());

            // Split line at '{' and check if line is for files or dependencies

            if (split(sp_line, '{').at(0) == "files" && sp_line.at(sp_line.length() - 1) == '{')
            {

                add_files = true;
                add_libs = false;

            } if (split(sp_line, '{').at(0) == "dependencies" && sp_line.at(sp_line.length() - 1) == '{')
            {

                add_files = false;
                add_libs = true;

            }

            // Check if line doesn't contain anything that isn't a file path / dependency path

            if (add_files && !(st_line.find("files") != string::npos) && !(st_line.find("{") == string::npos) && !(st_line.find("}") == string::npos))
            {

                files.push_back(st_line);

            } if (add_libs && !(st_line.find("dependencies") == string::npos) && !(st_line.find("{") == string::npos) && !(st_line.find("}") == string::npos))
            {

                libs.push_back(st_line);

            }

            if (add_files && st_line.find("}") != string::npos)
            {

                add_files = false;
                add_libs = false;

            } if (add_libs && st_line.find("}") != string::npos)
            {

                add_files = false;
                add_libs = false;

            }

        }

    }

    for (string &file1 : files)
    {
        
        cout << file1 << endl;

    }

    for (string &lib1 : libs)
    {
        
        cout << lib1 << endl;

    }

    return 0;

}
#include <iostream>
#include <Windows.h>
#include <string>
#include <filesystem>
#include <fstream>
#include <boost/algorithm/string.hpp>


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

    }

    return str;

}

vector<string> split(const string &str, const string &delimiter)
{

    vector<string> splits;

    boost::split(splits, str, boost::is_any_of(delimiter));

    return splits;

}

string strip(const string &str)
{

    string result = str;

    boost::algorithm::trim(result);

    return result;

}

bool contains(const string &str, char c)
{

    int l = str.length();
 
    for (int i = 0; i < l; i++)
    {
        
        if (str[i] == c)
        {

            return true;

        }

    }

    return false;

}

bool contains(const string &str1, const string &str2)
{

    if (str1.find(str2) != std::string::npos)
    {

        return true;
    
    }

    return false;

}

bool compare(const string &str1, const string &str2)
{

    return boost::algorithm::equals(str1, str2);

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
    in_file.open(cwd + "/jocoa_lists.txt");
    vector<string> lines;
    string l;

    if (!in_file)
    {

        //

    }

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

    string line;

    for (size_t i = 0; i < lines.size(); i++)
    {

        line = lines.at(i);

        st_line = strip(line);

        // Check for empty lines

        if (!compare(st_line, "\n") && !compare(st_line, "") && !compare(st_line, "\0"))
        {

            // Remove all spaces

            sp_line = replace(st_line, ' ', 0);

            cout << sp_line << "\n";

            // Split line at '{' and check if line is for files or dependencies

            if (compare(split(sp_line, "{").at(0), "files") && sp_line.at(sp_line.length() - 1) == '{')
            {

                add_files = true;
                add_libs = false;

                cout << "FILE\n";

            }
            
            if (compare(split(sp_line, "{").at(0), "dependencies") && sp_line.at(sp_line.length() - 1) == '{')
            {

                add_files = false;
                add_libs = true;

                cout << "DEP\n";

            }
            
            if (!contains(st_line, '{') && !contains(st_line, '}'))
            {
            
                if (add_files)
                {

                    files.push_back(st_line);

                }

                if (add_libs)
                {

                    libs.push_back(st_line);

                }

            }
            
            if (add_files && contains(st_line, '}'))
            {

                add_files = false;
                add_libs = false;

            }
            
            if (add_libs && contains(st_line, '}'))
            {

                add_files = false;
                add_libs = false;

            }

            cout << "END\n";

        }

    }

    for (string &file1 : files)
    {
        
        cout << file1 + "\n";

    }

    cout << "\n";

    for (string &lib1 : libs)
    {
        
        cout << lib1 + "\n";

    }

    return 0;

}
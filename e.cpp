#include <iostream>
#include <Windows.h>
#include <string>
#include <filesystem>

using std::string;
using std::cout;
using std::endl;

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

int main(int argc, char const *argv[])
{

    // Test path stuff

    string path = getExePath();
    cout << path << endl;

    string cwd = getCWD();
    cout << cwd << endl; 

    return 0;

}
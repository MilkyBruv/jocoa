#include <iostream>
#include <Windows.h>
#include <string>
#include <filesystem>

std::string getCWD()
{

    std::filesystem::path path = std::filesystem::current_path();
    std::string path_str{path.u8string()};

    return path_str;

}

std::string getExePath()
{
    
    char buffer[MAX_PATH];

    GetModuleFileNameA(NULL, buffer, MAX_PATH);

    return buffer;

}

int main(int argc, char const *argv[])
{

    std::string path = getExePath();

    std::cout << path << std::endl;

    std::string cwd = getCWD();

    std::cout << cwd << std::endl;

    return 0;

}

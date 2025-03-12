#include <iostream>
#include <fstream>
#include <string>
#include "./../../lib/include/json.hpp"
#include "./../Jocoa/Jocoa.hpp"

using std::string;
using namespace nlohmann;

int main(int argc, char const *argv[])
{
    std::cout << "test" << std::endl;
    // Take arguments from argv and put them in a string array
    string args[argc];
    for (size_t i = 0; i < argc; i++)
    {
        args[i] = string(argv[i]);
        std::cout << args[i] << ", ";
    }

    // std::fstream jsonFile("./src/test.json");
    // json jsonData;
    // jsonFile >> jsonData;
    // string thing = jsonData["things"][0]["name"];
    // std::cout << thing << std::endl;

    Jocoa::init();

    if (strcmp(args[1].c_str(), "new") == 0)
    {
        Jocoa::_new(args);
    }

    return 0;
}

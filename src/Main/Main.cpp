#include <iostream>
#include <fstream>
#include <string>
#include "./../../lib/include/json.hpp"
#include "./../Jocoa/Jocoa.hpp"

using std::string;
using namespace nlohmann;

int main(int argc, char const *argv[])
{
    // Take arguments from argv and put them in a string array
    string args[argc];
    for (size_t i = 0; i < argc; i++)
    {
        args[i] = string(argv[i]);
    }

    std::fstream jsonFile("./src/test.json");
    json jsonData;
    jsonFile >> jsonData;
    string thing = jsonData["things"][0]["name"];
    std::cout << thing << std::endl;

    if (strcmp(args[1].c_str(), "new") == 1)
    {
        Jocoa::_new(args);
    }

    return 0;
}

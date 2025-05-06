#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include "./../Jocoa/Jocoa.hpp"

using std::string;

int main(int argc, char const *argv[])
{
    // Set logger to verbose
    Logger::setVerbose(true);

    // Take arguments from argv and put them in a string array
    string* args = new string[argc];
    for (size_t i = 0; i < argc; i++)
    {
        args[i] = string(argv[i]);
    }

    // Initialize Jocoa
    Jocoa::init();

    // Detect command
    if (argc >= 2)
    {
        if (strcmp(args[1].c_str(), "new") == 0)
        {
            Jocoa::_new(args);
        }
        else if (strcmp(args[1].c_str(), "run") == 0)
        {
            Jocoa::_run(args);
        }
        else if (strcmp(args[1].c_str(), "search") == 0)
        {
            Jocoa::_search(args);
        }
        else
        {
            Jocoa::_help(args);
        } 
    }
    else { Jocoa::_help(args); }

    // Free args
    delete[] args;

    return 0;
}

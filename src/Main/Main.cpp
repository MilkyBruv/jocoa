#include "./../Jocoa/Jocoa.hpp"

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
    Jocoa::init(args);

    // Detect command
    if (argc >= 2)
    {
        if (Utils::stringCompare(args[1], "new"))
        {
            Jocoa::_new(args);
        }
        else if (Utils::stringCompare(args[1], "run"))
        {
            Jocoa::_run(args, argc);
        }
        else if (Utils::stringCompare(args[1], "search"))
        {
            Jocoa::_search(args);
        }
        else if (Utils::stringCompare(args[1], "package"))
        {
            Jocoa::_package(args, argc);
        }
        else if (Utils::stringCompare(args[1], "build"))
        {
            Jocoa::_build(args, argc);
        }
        else if (Utils::stringCompare(args[1], "clean"))
        {
            Jocoa::_clean(args);
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

#include "./Jocoa.hpp"
#include "./../Macros.hpp"
#include "./../Log/Logger.hpp"
#include <filesystem>

bool Jocoa::createDirectory(string path)
{
    if (std::filesystem::create_directory(path))
    {
        Logger::info("Created ./" + path);
    }
    else
    {
        Logger::error("Failed to create ./" + path);
    }
}

void Jocoa::_new(string args[])
{
    // arg1 = name
    string name;
    if (len(args) >= 2) { name = args[1]; }
    else
    {
        Logger::error("Usage:\n\tjocoa new <name>\n\tOR jocoa new <name> <path>\n\tOR jocoa new <name> <path> <type>");
        return;
    }

    // arg2 = path (blank = new, create if doesn't exist) OPTIONAL
    // arg2 default = ./projectName
    string path;
    if (len(args) >= 3) { path = "./" + args[2]; }
    else
    {
        path = "./" + name;
        Logger::info("No path specified, defaulting to " + path);
    }

    // arg3 = type (r, run, runnable, l, lib, library) OPTIONAL
    // arg3 default = runnable
    char type;
    if (len(args) == 4 && (args[3][0] == 'r' || args[3][0] == 'l'))
    {
        type = args[3][0];
    }
    else { type = 'r'; }



}

void Jocoa::_search(string args[])
{
    //
}

void Jocoa::_run(string args[])
{
}

void Jocoa::_clean(string args[])
{
}

void Jocoa::_package(string args[])
{
}

#include <string.h>
#include "../jocoa/Jocoa.hpp"
#include "../command/Commands.hpp"

void Jocoa::runCommandFromArguments(char const *argv[])
{
    if (argv[1] == nullptr) { Commands::help(argv); }
    else // Only run commands with arguments if there are any supplied
    {
        if (strcmp(argv[1], "run") == 0) { Commands::run(argv); }
        else if (strcmp(argv[1], "to-jar") == 0) { Commands::toJar(argv); }
        else if (strcmp(argv[1], "new") == 0) { Commands::_new(argv); }
        else if (strcmp(argv[1], "search") == 0) { Commands::search(argv); }
        else { Commands::help(argv); }
    }
}
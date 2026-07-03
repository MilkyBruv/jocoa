#include "jocoa.h"

void init(JOCOA_COMMAND_ARGS)
{
    printf("this is a test!!\n");
}

void help(JOCOA_COMMAND_ARGS)
{
    printf( 
    "\033[39m"
    "\033[39m       ++ \033[31m #######  \033[39m +++++++   +++++++     +++   \n"
    "\033[39m       ++ \033[31m##     ## \033[39m++     ++ ++     ++   ++ ++  \n"
    "\033[39m++     ++ \033[31m## ### ## \033[39m++        ++     ++  ++   ++ \n"
    "\033[39m++     ++ \033[31m##     ## \033[39m++     ++ ++     ++ +++++++++\n"
    "\033[39m +++++++  \033[31m #######  \033[39m +++++++   +++++++  ++     ++\n"
    "\033[36m%s\033[31m\n"
    "\033[36mgithub.com/MilkyBruv 2026\033[39m\n"
    "\033[39mCommands:\n"

    "\thelp - Displays this command\n"

    "\tnew - Creates new Jocoa project\n"

    "\tinfo - Displays current project information\n"

    "\trun - Compiles and executes current project\n"
    "\t\t\033[36m-no-search\033[39m - Compiles and executes without searching for new source files or dependencies\n"

    "\tbuild - Compiles current project as .jar\n"
    "\t\t\033[36m-no-search\033[39m - Compiles without searching for new source files or dependencies\n"
    "\t\t\033[36m-fat\033[39m - Compiles project and all dependencies into one .jar\n"

    "\tsearch - Searches for new source files or dependencies, and appends them to jocoa.json\n"

    "\tclean - Cleans current project of compilation files", JOCOA_VERSION);
}

void info(JOCOA_COMMAND_ARGS)
{
    
}

void _new(JOCOA_COMMAND_ARGS)
{
    for (size_t i = 0; i < argc; i++)
    {
        printf("%s,\n", argv[i]);
    }
    

    // create_directory(dir);
    printf("done?\n");
}

void search(JOCOA_COMMAND_ARGS)
{
    // 
}

void run(JOCOA_COMMAND_ARGS)
{
    // 
}

void clean(JOCOA_COMMAND_ARGS)
{
    // 
}

void build(JOCOA_COMMAND_ARGS)
{
    // 
}

void version(JOCOA_COMMAND_ARGS)
{
    printf("Jocoa \033[36m%s\033[39m\n", JOCOA_VERSION);
}
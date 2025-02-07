#ifndef JOCOA_HPP
#define JOCOA_HPP

class Jocoa
{
public:
    // Match the argument to the correspending command.
    static void runCommandFromArguments(char const *argv[]);
};

#endif
#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>

using std::string;

class Logger
{
public:
    static void info(string message);
    static void warn(string message);
    static void error(string message);
};

#endif
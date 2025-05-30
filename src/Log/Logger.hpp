#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "./../Macros/Macros.hpp"

class Logger
{
public:
    static bool verbose;
    static void setVerbose(bool state);
    static void info(string message);
    static void warn(string message);
    static void error(string message);
};

#endif
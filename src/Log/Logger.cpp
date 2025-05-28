#include "./Logger.hpp"
#include <iostream>

using std::cout;
using std::cerr;
using std::endl;

bool Logger::verbose = true;

void Logger::setVerbose(bool state)
{
    verbose = state;
}

void Logger::info(string message)
{
    if (verbose)
    {
        cout << "\033[32mINFO: " << message << "\033[39m" << endl;
    }
}

void Logger::warn(string message)
{
    if (verbose)
    {
        cout << "\033[31mWARN: " << message << "\033[39m" << endl;
    }
}

void Logger::error(string message)
{
    if (verbose)
    {
        cerr << "ERROR: " << message << endl;
    }
}

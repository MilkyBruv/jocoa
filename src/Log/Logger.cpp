#include "Logger.hpp"
#include <iostream>

using std::cout;
using std::cerr;
using std::endl;

void Logger::info(string message)
{
    cout << "INFO: " << message << endl;
}

void Logger::warn(string message)
{
    cout << "WARN: " << message << endl;
}

void Logger::error(string message)
{
    cerr << "ERROR: " << message << endl;
}

#include <iostream>
#include <Windows.h>
#include <string>
#include <filesystem>
#include <sstream>
#include <fstream>
#include <cctype>
#include <algorithm>
#include <functional>
#include <locale>

#include <boost/algorithm/string.hpp>


using std::string;
using std::cout;
using std::endl;
using std::ifstream;
using std::ios;
using std::vector;


const string WHITESPACE = " \t";
const bool FALSE_TRUE[2] = {false, true};


string replace(string str, char c1, char c2)
{

    int l = str.length();
 
    for (int i = 0; i < l; i++)
    {
        
        if (str[i] == c1)
        {

            str[i] = c2;

        }

    }

    return str;

}

vector<string> split(const string &str, const string &delimiter)
{

    vector<string> splits;

    boost::split(splits, str, boost::is_any_of(delimiter));

    return splits;

}

string strip(const string &str)
{

    string result = str;

    boost::algorithm::trim(result);

    return result;

}

bool contains(const string &str, char c)
{

    int l = str.length();
 
    for (int i = 0; i < l; i++)
    {
        
        if (str[i] == c)
        {

            return true;

        }

    }

    return false;

}

bool contains(const string &str1, const string &str2)
{

    if (str1.find(str2) != std::string::npos)
    {

        return true;
    
    }

    return false;

}

bool compare(const string &str1, const string &str2)
{

    return boost::algorithm::equals(str1, str2);

}

int main(int argc, char const *argv[])
{

    string str1 = "te_st";
    string str2 = "te_st";
    string str3 = "   test     ";
    string str4 = "tepppst";
    string str5 = "test";

    string str1_out = replace(str1, '_', '0'); //   te0st
    cout << str1_out + "\n";

    boost::algorithm::trim(str2); //    te
    cout << str2 + "\n";

    string str3_out = strip(str3); //               test
    cout << str3_out + "\n";

    string out = split("test", "e").at(1);

    cout << out + "\n";

    if (!contains("test", 'o'))
    {

        cout << "matches mayte\n";

    }

    cout << str5.at(str5.length() - 1);

    return 0;

}
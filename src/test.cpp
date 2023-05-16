#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::wstring;
using std::fstream;
using std::ios;

wstring ExePath() {

    TCHAR buffer[MAX_PATH] = {0};
    GetModuleFileName(NULL, buffer, MAX_PATH);

    wstring::size_type pos = wstring(buffer).find_last_of(L"\\/");

    return wstring(buffer).substr(0, pos);

}

int main(int argc, char const *argv[])
{

    vector<string> lines;
    wstring file = "/japm_lists.txt";
    wstring path = ExePath();

    fstream fs;
    fs.open("", ios::out);
    
    return 0;

}

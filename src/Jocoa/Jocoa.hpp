#ifndef JOCOA_HPP
#define JOCOA_HPP

#include "./../Log/Logger.hpp"
#include "./../File/FileManager.hpp"
#include "./../Json/JsonManager.hpp"
#include "./../Command/CommandBuilder.hpp"

class Jocoa
{
public:
    static string version;
    static void init(string args[]);
    static void _help(string args[]);
    static void _new(string args[]);
    static void _search(string args[]);
    static void _run(string args[], size_t argc);
    static void _clean(string args[]);
    static void _package(string args[], size_t argc);
    static void _build(string args[], size_t argc);
};

#endif
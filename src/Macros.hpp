#ifndef MACROS_HPP
#define MACROS_HPP

#include <iostream>

#define len(a) ({size_t b; b = (sizeof(a) / sizeof(a[0])); b;})

#endif
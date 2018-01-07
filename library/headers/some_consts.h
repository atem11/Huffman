#ifndef SOME_CONSTS
#define SOME_CONSTS

#include <stdexcept>
#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <cstring>

typedef unsigned char symbol;
typedef unsigned long long ull;
typedef uint16_t two_byte;

const size_t BLOCK_SIZE = static_cast<size_t>(1e4);
const size_t MAX_NUM = 255;
const uint16_t NONE = 555;

template <typename T>
symbol cast(T s) {
    return *reinterpret_cast<symbol*>(&s);
}

#endif //SOME_CONSTS

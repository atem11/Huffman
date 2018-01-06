#ifndef CODE
#define CODE

#include <vector>
#include "some_consts.h"

using std::vector;

struct code {
    code() = delete;

    code(vector<symbol> const &_data, size_t x) : data(_data), cnt(x) {}

    vector<symbol> data;
    size_t cnt;
};

#endif //CODE
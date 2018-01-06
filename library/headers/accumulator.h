#ifndef ACCUMULATOR
#define ACCUMULATOR

#include <vector>
#include <fstream>
#include "some_consts.h"

using std::vector;

struct accumulator {
    accumulator();

    void add_data(vector<symbol> const &a);

    ull get_cnt(size_t ind) const;

    void read_accumulator(std::ifstream &reader);

    void del_cnt(vector<symbol> const &a);

    bool check();

private:
    ull cnt[MAX_NUM + 1];
};

#endif //ACCUMULATOR

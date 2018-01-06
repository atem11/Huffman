#include "headers\accumulator.h"

accumulator::accumulator() {
    memset(cnt, 0, (MAX_NUM + 1) * sizeof(ull));
}

void accumulator::add_data(vector<symbol> const &a) {
    for (auto x : a) {
        cnt[x]++;
    }
}

ull accumulator::get_cnt(size_t ind) const {
    return cnt[ind];
}

void accumulator::read_accumulator(std::ifstream &reader) {
    for (size_t i = 0; i <= MAX_NUM; ++i) {
        char k;
        for (size_t j = 0; j < 8; ++j) {
            reader.read(&k, 1);
            symbol s = static_cast<symbol>(k);
            cnt[i] = (cnt[i] << 8) + static_cast<ull>(s);
        }
    }
}

void accumulator::del_cnt(const vector<symbol> &a) {
    for (auto x : a) {
        cnt[x]--;
    }
}

bool accumulator::check() {
    for (size_t i = 0; i <= MAX_NUM; ++i) {
        if (cnt[i]++) {
            return false;
        }
    }
    return true;
}

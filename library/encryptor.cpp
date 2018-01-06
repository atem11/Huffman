#include "headers\encryptor.h"
#include <algorithm>

encryptor::encryptor(accumulator const &acc) : tree(acc) {}

code encryptor::encrypt(vector<symbol> const &data) const {
    vector<ull> tres(data.size(), 0);
    size_t cur_ind = 0, size = 0;
    for (auto x : data) {
        code_word t = codes[x];
        size += t.len;
        tres[cur_ind >> 6] |= t.code << (64 - (cur_ind & 63) - t.len);
        size_t written = std::min(64 - (cur_ind & 63), t.len);
        cur_ind += written;

        tres[cur_ind >> 6] |= (t.code) << (64 - t.len + written);
        cur_ind += t.len - written;
    }

    vector<symbol> res(size / 8 + static_cast<size_t>((size % 8) != 0));
    for (size_t i = 0; i < res.size(); ++i) {
        res[i] = static_cast<symbol>(tres[i / 8] >> (8 * (7 - (i % 8))));
    }
    return code(res, data.size());
}

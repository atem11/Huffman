#include "encryptor.h"
#include <algorithm>

encryptor::encryptor(accumulator const &acc) : tree(acc) {}

code encryptor::encrypt(vector<symbol> const &data) const {
    vector<ull> tres(data.size(), 0);
    size_t cur_ind = 0;
    for (auto x : data) {
        code_word t = codes[x];
        if (t.len > (64 - (cur_ind &63))) {
            tres[(cur_ind >> 6)] |= (t.code >> (t.len - (64 - (cur_ind & 63))));
        }
        else {
            tres[(cur_ind >> 6)] |= (t.code << (64 - (cur_ind & 63) - t.len));
        }
        size_t written = std::min(64 - (cur_ind & 63), t.len);
        cur_ind += written;

        if (t.len != written) {
            tres[(cur_ind >> 6)] |= (t.code << (64 - t.len + written));
        }
        cur_ind += t.len - written;
    }

    vector<symbol> res((cur_ind / 8) + static_cast<size_t>((cur_ind % 8) != 0));
    for (size_t i = 0; i < res.size(); ++i) {
        res[i] = cast(tres[size_t(i / 8)] >> (8 * (7 - (i % 8))));
    }
    return code(res, data.size());
}

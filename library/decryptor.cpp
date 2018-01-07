#include "decryptor.h"

decryptor::decryptor(accumulator acc) : tree(acc) {}

vector<symbol> decryptor::decrypt(code const &block) const {
    two_byte cur = static_cast<two_byte>(root);

    vector<symbol> res;
    int ind = 0;
    res.reserve(block.cnt);
    for (size_t i = 0; i < block.data.size(); i++) {
        symbol t = block.data[i];
        for (size_t j = 0; j < 8; j++) {
            if (t & (1 << (7 - j))) {
                cur = g[cur].son_2;
            } else {
                cur = g[cur].son_1;
            }
            if (g[cur].sym != NONE) {
                ind++;
                res.push_back(cast(g[cur].sym));
                cur = static_cast<two_byte>(root);
                if (ind == block.cnt) {
                    break;
                }
            }
        }
    }
    return res;
}
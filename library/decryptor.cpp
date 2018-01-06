#include "headers\decryptor.h"

decryptor::decryptor(accumulator acc) : tree(acc), ready(true) {}

vector<symbol> decryptor::decrypt(code const &block) const {
    if (!ready) {
        throw std::runtime_error("No decryption tree");
    }
    two_byte cur = static_cast<two_byte>(g.size() - 1);

    vector<symbol> res;
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
                res.push_back(static_cast<symbol>(g[cur].sym));
                cur = static_cast<uint16_t>(g.size() - 1);
            }
        }
    }
    res.erase(res.begin() + block.cnt, res.end());
    return res;
}
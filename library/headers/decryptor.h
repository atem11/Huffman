#ifndef DECRYPTOR
#define DECRYPTOR

#include "tree.h"
#include "code.h"

struct decryptor : private tree {
    decryptor() = delete;

    decryptor(accumulator acc);

    vector<symbol> decrypt(code const &block) const;
};

#endif //DECRYPTOR
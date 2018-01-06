#ifndef ENCRYPTOR
#define ENCRYPTOR

#include "tree.h"
#include "code.h"

struct encryptor : private tree {
    encryptor() = delete;

    encryptor(accumulator const &acc);

    code encrypt(vector<symbol> const &data) const;

private:

};

#endif //ENCRYPTOR
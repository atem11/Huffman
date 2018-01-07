#ifndef TREE
#define TREE

#include <utility>
#include "some_consts.h"
#include "accumulator.h"
#include "code_word.h"

using std::pair;

struct tree {
protected:
    struct node {
        two_byte son_1, son_2;
        two_byte sym;

        node() : son_1(), son_2(), sym(NONE) {}

        node(two_byte s) : son_1(), son_2(), sym(s) {}

        node(two_byte x, two_byte y) : son_1(x), son_2(y), sym(NONE) {}
    };

    tree();

public:
    tree(const accumulator &a);

    size_t root;
    vector<node> g;
    code_word codes[MAX_NUM + 1];

private:
    void code_dfs(size_t v, code_word code);

};

#endif //TREE
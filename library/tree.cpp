#include "tree.h"
#include <set>

using std::set;

tree::tree() {}

tree::tree(const accumulator &a) {
    set<pair<ull, two_byte> > lists;
    size_t ind = 0;
    for (two_byte i = 0; i <= MAX_NUM; ++i) {
        ull cnt = a.get_cnt(i);
        if (cnt > 0) {
            lists.insert({cnt, ind++});
            g.push_back(node(i));
        }
    }
    if (lists.size() == 1) {
        code_word code(0,1);
        codes[g[0].sym] = code;
        root = 0;
    } else if (ind) {
        while (lists.size() > 1) {
            ull sum = lists.begin()->first;
            two_byte v1 = lists.begin()->second;
            lists.erase(lists.begin());

            sum += lists.begin()->first;
            two_byte v2 = lists.begin()->second;
            lists.erase(lists.begin());

            g.push_back(node(v1, v2));
            lists.insert({sum, ind++});
        }
        root = ind - 1;
        code_dfs(root, code_word());
    }
}

void tree::code_dfs(size_t v, code_word code) {
    if (g[v].sym != NONE) {
        codes[g[v].sym] = code;
    } else {
        code.add_bit(false);
        code_dfs(g[v].son_1, code);
        code.erase_bit();

        code.add_bit(true);
        code_dfs(g[v].son_2, code);
        code.erase_bit();
    }
}



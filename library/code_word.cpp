#include "headers\code_word.h"

code_word::code_word() : code(0), len(0) {}

code_word::code_word(size_t a, size_t b) : code(a), len(b) {}

void code_word::add_bit(bool f) {
    code <<= 1;
    code |= static_cast<ull>(f);
    len++;
}

void code_word::erase_bit() {
    code >>= 1;
    len--;
}

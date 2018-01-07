#include <iostream>
#include "file_decompressor.h"

void write_decompressed_block(vector<symbol> const &block, ofstream &writer) {
    char s;
    for (auto x : block) {
        s = static_cast<char>(x);
        writer.write(&s, 1);
    }
}

two_byte read_two_byte(ifstream &reader) {
    two_byte ans = 0;
    char k = 0;
    symbol s;
    if (reader.fail()) {
        throw std::runtime_error("");
    }
    reader.read(&k, 1);
    s = static_cast<symbol>(k);
    ans = (static_cast<two_byte>(s) << 8);
    if (reader.fail()) {
        throw std::runtime_error("");
    }
    reader.read(&k, 1);
    s = static_cast<symbol>(k);
    ans += static_cast<two_byte>(s);
    return ans;
}

void decompress(string const &src, string const &dst) {
    ifstream check(src);
    if (!check) {
        throw std::runtime_error("Try another file for decompression, this one is unavailable or doesn't exist\n");
    }
    check.close();
    ifstream reader(src, ifstream::binary);
    ofstream writer(dst, ofstream::binary);
    accumulator acc;

    try {
        acc.read_accumulator(reader);
    }
    catch (std::runtime_error) {
        throw std::runtime_error("Incorrect decompressed file: no data for tree\n");
    }

    decryptor decompressor(acc);

    vector<symbol> cur_block;
    while (reader.peek() != EOF) {
        two_byte x, y;
        try {
            x = read_two_byte(reader);
            y = read_two_byte(reader);
        } catch (std::runtime_error) {
            throw std::runtime_error("Incorrect decompressed file: cut block found");
        }
        cur_block.resize(x);
        for (two_byte i = 0; i < x; i++) {
            char s;
            if (reader.eof()) {
                throw std::runtime_error("Incorrect decompressed file: cut block found");
            }
            reader.read(&s, 1);
            cur_block[i] = static_cast<symbol>(s);
        }
        vector<symbol> res = decompressor.decrypt(code(cur_block, y));
        acc.del_cnt(res);
        write_decompressed_block(res, writer);
    }
    if (!acc.check()) {
        throw std::runtime_error("Incorrect decompressed file: data isn't empty");
    }
    writer.close();
    reader.close();
}
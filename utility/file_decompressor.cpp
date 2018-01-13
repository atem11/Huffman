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
    char buf[2];
    reader.read(buf, sizeof buf);
    if (reader.fail())
        throw std::runtime_error("cut block found");

    return static_cast<two_byte>(static_cast<symbol>(buf[0])) << 8 | static_cast<symbol>(buf[1]);
}

void decompress(string const &src, string const &dst) {
    ifstream check(src);
    if (!check) {
        throw std::runtime_error("Try another file for adecompression, this one is unavailable or doesn't exist\n");
    }
    check.close();
    ifstream reader(src, ifstream::binary);
    ofstream writer(dst, ofstream::binary);
    accumulator acc;
    acc.read_accumulator(reader);

    decryptor decompressor(acc);

    try {
        vector<symbol> cur_block;
        while (reader.peek() != EOF) {
            two_byte x = read_two_byte(reader);
            two_byte y = read_two_byte(reader);
            cur_block.resize(x);
            for (two_byte i = 0; i < x; i++) {
                char s;
                if (reader.eof()) {
                    throw std::runtime_error("cut block found");
                }
                reader.read(&s, 1);
                cur_block[i] = static_cast<symbol>(s);
            }
            vector<symbol> res = decompressor.decrypt(code(cur_block, y));
            acc.del_cnt(res);
            write_decompressed_block(res, writer);
        }
        if (!acc.check()) {
            throw std::runtime_error("data isn't empty");
        }
    }
    catch (std::runtime_error const& e) {
        throw std::runtime_error(std::string("incorrect decompressed file: ") + e.what());
    }
}

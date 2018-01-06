#include <iostream>
#include <fstream>
#include "headers/file_compressor.h"

accumulator get_count(string const &filename) noexcept {
    accumulator res;
    ifstream reader(filename, ifstream::binary);
    vector<symbol> block;
    char s;
    while (!reader.eof()) {
        reader.read(&s, 1);
        if (block.size() == BLOCK_SIZE) {
            res.add_data(block);
            block.clear();
        }
        block.push_back(static_cast<symbol>(s));
    }
    res.add_data(block);
    reader.close();
    return res;
}

void write_two_byte(two_byte x, ofstream &writer) {
    char first = static_cast<char>(x >> 8);
    char second = static_cast<char>((x << 8) >> 8);
    writer.write(&first, 1);
    writer.write(&second, 1);
}

void write_compressed_block(code const &block, ofstream &writer) {
    write_two_byte(static_cast<two_byte>(block.data.size()), writer);
    write_two_byte(static_cast<two_byte>(block.cnt), writer);
    for (auto t : block.data) {
        char s = static_cast<char>(t);
        writer.write(&s, 1);
    }
}

void compress(string const &src, string const &dst) {
    ifstream check(src);
    if (!check) {
        throw std::runtime_error("Try another file for compression, this one is unavailable or doesn't exist\n");
    }
    check.close();

    accumulator cnt = get_count(src);
    encryptor compressor(cnt);
    ifstream reader(src, ifstream::binary);
    ofstream writer(dst, ofstream::binary);

    for (size_t i = 0; i <= MAX_NUM; ++i) {
        for (size_t j = 0; j < 8; ++j) {
            char s = static_cast<char>((cnt.get_cnt(i) << (j * 8)) >> 56);
            writer.write(&s, 1);
        }
    }

    vector<symbol> block;
    block.reserve(BLOCK_SIZE);
    char s;
    while (!reader.eof()) {
        reader.read(&s, 1);
        if (block.size() == BLOCK_SIZE) {
            write_compressed_block(compressor.encrypt(block), writer);
            block.clear();
            block.reserve(BLOCK_SIZE);
        }
        block.push_back(static_cast<symbol>(s));
    }
    if (!block.empty()) {
        write_compressed_block(compressor.encrypt(block), writer);
    }
    writer.close();
    reader.close();
}//*/
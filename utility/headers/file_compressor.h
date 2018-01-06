#ifndef FILE_COMPRESSOR
#define FILE_COMPRESSOR

#include "../../library/headers/encryptor.h"

using std::string;
using std::ofstream;
using std::ifstream;

accumulator get_count(std::string const &filename) noexcept;

void write_compressed_block(code const &block, ofstream &writer);

void compress(string const &src, string const &dst);

#endif //FILE_COMPRESSOR
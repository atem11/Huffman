#ifndef FILE_DECOMPRESSOR
#define FILE_DECOMPRESSOR

#include <string>
#include <fstream>
#include "../../library/headers/decryptor.h"
#include "../../library/headers/some_consts.h"

using std::string;
using std::ofstream;
using std::ifstream;

void write_decompressed_block(vector <symbol> const &block, ofstream &writer);

void decompress(string const &src, string const &dst);


#endif //FILE_DECOMPRESSOR
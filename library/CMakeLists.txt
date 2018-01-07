cmake_minimum_required(VERSION 2.8)

project(HUFFMAN_LIBRARY)

include_directories(${HUFFMAN_LIBRARY_SOURCE_DIR}/headers)

set(LIB_HEADERS headers/accumulator.h
		headers/code.h
		headers/code_word.h
		headers/decryptor.h
		headers/encryptor.h
		headers/some_consts.h
		headers/tree.h)

set(LIB_SOURCES accumulator.cpp
		code_word.cpp
		decryptor.cpp
		encryptor.cpp
		tree.cpp)

add_library(huf_lib ${LIB_HEADERS} ${LIB_SOURCES})

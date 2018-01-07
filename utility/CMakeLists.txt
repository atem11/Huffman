cmake_minimum_required(VERSION 2.8)

project(HUFFMAN_UTILITY)

include_directories(${HUFFMAN_LIBRARY_SOURCE_DIR}/headers)
include_directories(${HUFFMAN_UTILITY_SOURCE_DIR}/headers)


set(HEADERS headers/file_compressor.h
	    headers/file_decompressor.h)

set(SOURCES file_compressor.cpp
	    file_decompressor.cpp
	    main.cpp)

add_executable(huffman ${HEADERS} ${SOURCES})

target_link_libraries(huffman huf_lib)

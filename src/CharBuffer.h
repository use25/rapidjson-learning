#pragma once

struct CharBuffer {
    char* data;
    unsigned int size;

    CharBuffer(unsigned int i_size)
        : data(new char[i_size] {0}),
        size (i_size)
    {
    }

    ~CharBuffer()
    {
        delete[] data;
    }
};
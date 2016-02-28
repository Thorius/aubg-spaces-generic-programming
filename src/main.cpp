/// GENERIC PROGRAMMING LECTURE SERIES

// It is usually smart to keep main as small as possible.

#include <iostream>

#include "buffer.hpp"
#include "revision.hpp"


int main(int argc, char* argv[])
{
    // Tests for color_rgba class;
    color_rgba red { 255, 0, 0, 255 };
    color_rgba green { 0, 255, 0, 255 };
    color_rgba blue { 0, 0, 255, 255 };
    std::cout << red << green << blue << std::endl;

    color_rgba white = make_color_rgba(255, 255, 255);
    std::cout << white << std::endl;
    white.a = 125;
    std::cout << white << std::endl;

    red *= 0.5f;
    green *= 0.5f;
    blue *= 0.5f;
    color_rgba light_grey = (red * 1.5f) + (1.5f * green) + ( 1.5f * blue);
    std::cout << red << green << blue << light_grey << std::endl;

    // Tests for the buffer class
    buffer b1;
    b1[0] = 100;
    buffer b2 {1};
    buffer b3 = b2;
    b3 += b2;
    b2[2] = 42;
    buffer b4 = b2 + b3;
    print_buffer(std::cout, b1);
    print_buffer(std::cout, b2);
    print_buffer(std::cout, b3);
    print_buffer(std::cout, b4);

    return 0;	 
}

/// Topics left to cover.
// Function objects
// Function templates
// Class templates
// Type aliases
// Traits
// Tag dispatch
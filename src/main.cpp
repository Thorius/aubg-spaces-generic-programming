/// GENERIC PROGRAMMING LECTURE SERIES

// It is usually smart to keep main as small as possible.

#include <iostream>

#include "buffer.hpp"
#include "singleton.hpp"
#include "revision.hpp"
#include "revision_2.hpp"

void test_singleton();
void test_buffer();
void revision_test_2();
void revision_test();

int main(int argc, char* argv[])
{
    revision_test_2();
    test_singleton();
    return 0;	 
}

void test_singleton()
{
    // Test singleton
    singleton<int> a(10);
    singleton<int> b(22);
    singleton<int> c(-2);
    bool cmp1 = a < b;
    bool cmp2 = a >= b;
    bool cmp3 = a != c;

    cout << boolalpha << cmp1 << " " << cmp2 << " " << " " << cmp3
        << " " << a + b << " " << a - c << " " << b * c << "\n\n";
}


void test_buffer()
{
    // Tests for the buffer class
    buffer<int, 10> b1;
    b1[0] = 100;
    buffer<int, 10> b2 { 1 };
    buffer<int, 10> b3 = b2;
    b3 += b2;
    b2[2] = 42;
    buffer<int, 10> b4 = b2 + b3;
    print_buffer(std::cout, b1);
    print_buffer(std::cout, b2);
    cout << b1 << b2;
}


void revision_test_2()
{
    test_function_objects();
    test_compare();
    test_pair();

    buffer<int, 4> b(1);
    buffer<string, 25> c("asdfasfd");
    b[2] = 10;
    // The explicit string  constructor is not necessary in this case.
    c[3] = string("ggg");

    // We need to explicitly qualify the first non-type template argument
    // since it is impossible for the compiler to deduce it.
    get<1>(b) = 400;
    // We need to convert int to string before we assign.
    get<10>(c) = to_string(get<1>(b));

    print_buffer(cout, b);
    print_buffer(cout, c);

    cout << "\n\n";
}

void revision_test()
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
    color_rgba light_grey = (red * 1.5f) + (1.5f * green) + (1.5f * blue);
    std::cout << red << green << blue << light_grey << std::endl;
}


// Topics to discuss if they happen to come up.

// Safe array  (??)

// Cross pairs  (??)

// Template specialization (??)

// Type traits  (??)

// Tag dispatch (??)
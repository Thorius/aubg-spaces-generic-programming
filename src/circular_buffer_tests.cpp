#include "circular_buffer_tests.hpp"

#include <iostream>
#include <chrono>
#include "circular_buffer.hpp"

using std::cout;

bool test_circular_buffer_simple_usage()
{
    bool test1 = test_circular_buffer_push_back();
    bool test2 = test_circular_buffer_pop_front();
    bool test3 = test_circular_buffer_modification();
    bool test4 = test_circular_buffer_random_access();
    bool test5 = test_circular_buffer_reserve();
    bool test6 = test_circular_buffer_resize();

    return test1 && test2 && test3 && test4 && test5 && test6;
}

bool test_circular_buffer_full_usage()
{
    bool simple = test_circular_buffer_simple_usage();
    bool test1 = test_circular_buffer_push_back_n();
    bool test2 = test_circular_buffer_pop_front_n();

    return simple && test1 && test2;
}

bool test_circular_buffer_push_back()
{
    circular_buffer<int> cbuf(10);
    bool result = true;

    cbuf.push_back(1);
    cbuf.push_back(2);
    cbuf.push_back(3);
    result = result && cbuf[0] == 1 && cbuf[1] == 2 && cbuf[2] == 3 && cbuf.size() == 3;
    
    for (int i = 0; i < 8; ++i) {
        cbuf.push_back(100);
    }
    result = result && cbuf.front() == 2 && cbuf.size() == 10;

    return result;
}

bool test_circular_buffer_pop_front()
{
    circular_buffer<int> cbuf(10);
    bool result = true;

    cbuf.push_back(1);
    cbuf.push_back(2);
    cbuf.push_back(3);
    result = result && (cbuf.size() == 3) && cbuf.front() == 1;
    
    cbuf.pop_front();
    result = result && (cbuf.size() == 2) && cbuf.front() == 2;
    
    for (int i = 0; i < 15; ++i) {
        cbuf.push_back(99);
    }
    result = result && (cbuf.size() == 10);
    
    for (int i = 0; i < 10; ++i) {
        cbuf.pop_front();
    }
    result = result && cbuf.empty();

    return result;
}

bool test_circular_buffer_modification()
{
    circular_buffer<int> cbuf(10);
    bool result = true;

    cbuf.push_back(1);
    cbuf.push_back(2);
    cbuf.push_back(3);

    cbuf.front() = 99;
    cbuf.back() = 88;
    result = result && cbuf.front() == 99 && cbuf.back() == 88 && cbuf[1] == 2;

    return result;
}

bool test_circular_buffer_random_access()
{
    circular_buffer<int> cbuf(10);
    bool result = true;
    
    for (int i = 0; i < 10; ++i) {
        cbuf.push_back(i);
    }
    for (int i = 0; i < 10; ++i) {
        result = result && cbuf[i] == i;
    }
    
    for (int i = 30; i < 45; ++i) {
        cbuf.push_back(i);
    }
    for (int i = 35; i < 45; ++i) {
        result = result && cbuf[i - 35] ==  i;
    }

    return result;
}

bool test_circular_buffer_reserve()
{
    circular_buffer<int> cbuf(10);
    bool result = true;

    for (int i = 0; i < 10; ++i) {
        cbuf.push_back(i);
    }
    cbuf.reserve(20);
    for (int i = 0; i < 10; ++i) {
        result = result && cbuf[i] == i;
    }
    result = result && cbuf.capacity() == 20 && cbuf.size() == 10;
    
    for (int i = 0; i < 10; ++i) {
        cbuf.push_back(i);
    }
    for (int i = 0; i < 20; ++i) {
        result = result && cbuf[i] == (i % 10);
    }
    result = result && cbuf.capacity() == 20 && cbuf.size() == 20;

    return result;

}

bool test_circular_buffer_resize()
{
    circular_buffer<int> cbuf(10);
    bool result = true;

    for (int i = 0; i < 10; ++i) {
        cbuf.push_back(i);
    }
    cbuf.resize(5);
    for (int i = 0; i < 5; ++i) {
        result = result && cbuf[i] == 5 + i;
    }
    result = result && cbuf.capacity() == 10 && cbuf.size() == 5;

    cbuf.resize(15);
    for (int i = 0; i < 5; ++i) {
        result = result && cbuf[i] == 5 + i;
    }
    for (int i = 5; i < 15; ++i) {
        result = result && cbuf[i] == 0;
    }
    result = result && cbuf.capacity() == 15 && cbuf.size() == 15;

    return result;
}

bool test_circular_buffer_push_back_n()
{
    circular_buffer<int> cbuf(10);
    bool result = true;

    cbuf.push_back_n(8, 100);
    for (int i = 0; i < 8; ++i) {
        result = result && cbuf[i] == 100;
    }
    result = result && cbuf.size() == 8;

    cbuf.push_back_n(5, 99);
    for (int i = 0; i < 5; ++i) {
        result = result && cbuf[i] == 100;
    }
    for (int i = 5; i < 10; ++i) {
        result = result && cbuf[i] == 99;
    }
    result = result && cbuf.size() == 10;

    return result;
}

bool test_circular_buffer_pop_front_n()
{
    circular_buffer<int> cbuf(10);
    bool result = true;

    cbuf.push_back_n(8, 100);
    for (int i = 0; i < 8; ++i) {
        result = result && cbuf[i] == 100;
    }
    result = result && cbuf.size() == 8;

    cbuf.pop_front_n(7);
    result = result && cbuf.size() == 1;

    cbuf.push_back_n(8, 100);
    result = result && cbuf.size() == 9;

    cbuf.pop_front_n(9);
    result = result && cbuf.empty();

    return result;
}

bool test_circular_buffer_copy_and_assignment()
{
    bool result = true;

    circular_buffer<int> cbuf1(10);
    for (int i = 0; i < 8; ++i) {
        cbuf1.push_back(100);
    }
    for (int i = 0; i < 8; ++i) {
        result = result && cbuf1[i] == 100;
    }
    result = result && cbuf1.size() == 8;

    circular_buffer<int> cbuf2(cbuf1);
    for (int i = 0; i < 8; ++i) {
        result = result && cbuf2[i] == 100;
    }
    result = result && cbuf2.size() == 8;
    
    for (int i = 0; i < 8; ++i) {
        cbuf2.push_back(90);
    }
    for (int i = 0; i < 2; ++i) {
        result = result && cbuf2[i] == 100;
    }
    for (int i = 2; i < 10; ++i) {
        result = result && cbuf2[i] == 90;
    }
    result = result && cbuf2.size() == 10;

    cbuf1 = cbuf2;

    for (int i = 0; i < 2; ++i) {
        result = result && cbuf1[i] == 100;
    }
    for (int i = 2; i < 10; ++i) {
        result = result && cbuf1[i] == 90;
    }
    result = result && cbuf1.size() == 10;

    return result;
}

void test_circular_buffer_push_back_performance()
{
    using namespace std::chrono;

    circular_buffer<int> cbuf1(100);
    circular_buffer<int> cbuf2(100);

    high_resolution_clock clock {};
    auto t1 = clock.now();

    for (int i = 0; i < 100'000'000; ++i) {
        cbuf1.push_back(10);
    }

    auto t2 = clock.now();
    auto delta_1 = t2 - t1;
    cout << "Time for normal push_back: " << duration_cast<milliseconds>(delta_1).count() << "\n\n";

    auto t3 = clock.now();

    for (int i = 0; i < 2'000'000; ++i) {
        cbuf2.push_back_n(50, 10);
    }

    auto t4 = clock.now();
    auto delta_2 = t4 - t3;
    cout << "Time for bulk push_back: " << duration_cast<milliseconds>(delta_2).count() << "\n\n";
}

void test_circular_buffer_output()
{

    circular_buffer<int> cbuf(10);
    cbuf.push_back(1);
    cbuf.push_back(2);
    cbuf.push_back(3);

    cout << "Expected: 1, 2, 3\n";
    cout << "Actual: " << cbuf;
    cbuf.pop_front();
    cbuf.push_back(10);
    cout << "Size: " << cbuf.size() << "\nCapacity: " << cbuf.capacity() << '\n';

    cout << "Expected: 2, 3, 10\n";
    cout << "Actual: " << cbuf;
    cout << "Size: " << cbuf.size() << "\nCapacity: " << cbuf.capacity() << '\n';

    for (int i = 0; i < 9; ++i) {
        cbuf.push_back(i * 20);
    }
    cout << "Expected: 10, 0, 20, 40, 60, 80, 100, 120, 140, 160\n";
    cout << "Actual: " << cbuf;
    cout << "Size: " << cbuf.size() << "\nCapacity: " << cbuf.capacity() << '\n';

    for (int i = 0; i < 5; ++i) {
        cbuf.pop_front();
    }
    cout << "Expected: 80, 100, 120, 140, 160\n";
    cout << "Actual: " << cbuf;
    cout << "Size: " << cbuf.size() << "\nCapacity: " << cbuf.capacity() << '\n';

    cbuf.push_back_n(3, 99);
    cout << "Expected: 80, 100, 120, 140, 160, 99, 99, 99\n";
    cout << "Actual: " << cbuf;
    cout << "Size: " << cbuf.size() << "\nCapacity: " << cbuf.capacity() << '\n';


    cbuf.push_back_n(5, 88);
    cout << "Expected: 140, 160, 99, 99, 99, 88, 88, 88, 88, 88\n";
    cout << "Actual: " << cbuf;
    cout << "Size: " << cbuf.size() << "\nCapacity: " << cbuf.capacity() << '\n';

    cbuf.pop_front_n(3);
    cout << "Expected: 99, 99, 88, 88, 88, 88, 88\n";
    cout << "Actual: " << cbuf;
    cout << "Size: " << cbuf.size() << "\nCapacity: " << cbuf.capacity() << '\n';

    cbuf.reserve(20);
    cout << "Expected: 99, 99, 88, 88, 88, 88, 88\n";
    cout << "Actual: " << cbuf;
    cout << "Size: " << cbuf.size() << "\nCapacity: " << cbuf.capacity() << '\n';
}

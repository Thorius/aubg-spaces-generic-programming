/// GENERIC PROGRAMMING LECTURE SERIES

// It is usually smart to keep main as small as possible.

#include <iostream>
#include "circular_buffer.hpp"
#include "circular_buffer_tests.hpp"

using namespace std;

int main(int argc, char* argv[])
{

    cout << boolalpha
        //<< "Result for push_back test: " << test_circular_buffer_push_back() << "\n"
        //<< "Result for pop_front test: " << test_circular_buffer_pop_front() << "\n"
        //<< "Result for modifications test: " << test_circular_buffer_modification() << "\n"
        //<< "Result for random access test: " << test_circular_buffer_random_access() << "\n"
        //<< "Result for reserve test: " << test_circular_buffer_reserve() << "\n"
        //<< "Result for resize test: " << test_circular_buffer_resize() << "\n"
        //<< "Result for simple usage: " << test_circular_buffer_simple_usage() << "\n"
        //<< "Result for resize test: " << test_circular_buffer_push_back_n() << "\n"
        //<< "Result for resize test: " << test_circular_buffer_pop_front_n() << "\n"
        //<< "Result for copy construction and assignment test:" << test_circular_buffer_copy_and_assignment() << "\n"
        //<< "Result for full usage: " << test_circular_buffer_full_usage() << "\n"
        
        //<< "Result for iterator regularity: " << test_circular_buffer_iterator_regularity() << "\n"
        //<< "Result for iterator element access: " << test_circular_buffer_iterator_element_access() << "\n"
        //<< "Result for iterator movement: " << test_circular_buffer_iterator_movement() << "\n"
        ;

    //test_circular_buffer_push_back_performance();

    //test_circular_buffer_output();

    return 0;
}



// Topics to discuss if they happen to come up.

// Safe array  (??)

// Cross pairs  (??)

// Template specialization (??)

// Type traits  (??)

// Tag dispatch (??)
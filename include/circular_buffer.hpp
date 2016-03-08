#ifndef CIRCULAR_BUFFER_GENERIC_PROGRAMMING
#define CIRCULAR_BUFFER_GENERIC_PROGRAMMING

#include <cstddef>
#include <limits>
#include <iostream>
#include <utility>

/// Steps for creating an STL compliant circular buffer.
//  1) Create constructor and destructor.
//  2) Define associated types.
//  3) Add read/write functions.
//  4) Add size and capacity function.
//  5) Add random access. 
//  6) Add a method to change the buffers capacity.
//  6) Add methods for resizing the circular buffer and reserving memory.
//  7) Implement correct copy construction and assignment.

// For now this is just the skeleton of the class we will create.
// We must design it in such a way as to pass all of the test in "circular_buffer_test.hpp/.cpp".

template<typename T>
class circular_buffer {
public:

public:

private:
   
};


template<typename T>
std::ostream& operator<<(std::ostream& out, const circular_buffer<T>& buf)
{

}



#endif //!CIRCULAR_BUFFER_GENERIC_PROGRAMMING
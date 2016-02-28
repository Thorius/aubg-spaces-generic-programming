#ifndef BUFFER_GENERIC_PROGRAMMING
#define BUFFER_GENERIC_PROGRAMMING

#include <iostream>

// We will improve out buffer class with each topic covered.

class buffer {
public:
    // Default constructor - Initialize all array elements to zero
    buffer()
    {
        for (int i = 0; i != 10; ++i) {
            buf[i] = 0;
        }
    }

    // Normal Constructor - initialize array elements to the integer passed
    buffer(int a)
    {
        for (int i = 0; i != 10; ++i) {
            buf[i] = a;
        }
    }

    // Copy Constructor
    buffer(const buffer& other)
    {
        for (int i = 0; i != 10; ++i) {
            buf[i] = other.buf[i];
        }
    }

    // Move constructor
    buffer(buffer&& other) = default; // Instructs the compiler to use the default move constructor

    // Copy Assignment
    buffer& operator=(const buffer& other)
    {
        for (int i = 0; i != 10; ++i) {
            buf[i] = other.buf[i];
        }
        return *this;
    }

    // Move Assignment
    buffer& operator=(buffer&& other) = default;

    int size() const
    {
        return 10;
    }
    
    // Allow for access to the internals of the buffer.
    int& operator[](int n)
    {
        return buf[n];
    }
    // We need to overload on const to allow for this method to work on const buffers as well.
    const int& operator[](int n) const
    {
        return buf[n];
    }
    
    //We will define "buffer addition" in terms of element wise addition.
    buffer& operator+=(const buffer& other)
    {
        for (int i = 0; i != 10; ++i) {
            buf[i] += other[i];
        }
        return *this;
    }

    buffer& operator-=(const buffer& other)
    {
        for (int i = 0; i != 10; ++i) {
            buf[i] -= other[i];
        }
        return *this;
    }

private:
    int buf[10];
};

// The inline keyword "kindly" asks the compiler to remove the function call overhead and just insert the function
// body whenever the function is called. 
// Note all functions defined inside the class body have the inline specifier by default so that is why 
// we do not need to add inline there.
inline
buffer operator+(const buffer& x, const buffer& y)
{
    buffer ret = x;
    ret += y;
    return ret;
}

inline
buffer operator-(const buffer& x, const buffer& y)
{
    buffer ret = x;
    ret -= y;
    return ret;
}

// We pass a ostream object (cout has a type inheriting from it) so that we do not depend on a particular output.
inline
void print_buffer(std::ostream& out, const buffer& b)
{
    for (int i = 0; i != b.size(); ++i) {
        out << b[i] << " ";
    }
    out << std::endl;
}

#endif // !BUFFER_GENERIC_PROGRAMMING
#ifndef BUFFER_GENERIC_PROGRAMMING
#define BUFFER_GENERIC_PROGRAMMING

#include <iostream>

/// Type aliases
// This is an example of a type function implemented using a template type alias.
// Given a type C, it gives back its associated value_type. Type aliases like this
// are helpful because they remove the need for using typename in outside of code.
// In addition to this it is also easier to  reason about them.
// For the typename thing just know that whenever we want to access an associated
// type of a type we have to tell the compiler that it is a type (using the typename keyword).
template<typename C>
using Value_type = typename C::value_type;

// We will improve out buffer class with each topic covered.

// We have parametrized the buffer class both on the type and on the size. 
template<typename T, int N>
class buffer {
public:
    // Associated type
    using value_type = T;

    // Default constructor - Initialize all array elements to zero
    buffer()
    {
        for (int i = 0; i != N; ++i) {
            buf[i] = 0;
        }
    }

    // Normal Constructor - initialize array elements to the integer passed
    buffer(const T& a)
    {
        for (int i = 0; i != N; ++i) {
            buf[i] = a;
        }
    }

    // Copy Constructor
    buffer(const buffer& other)
    {
        for (int i = 0; i != N; ++i) {
            buf[i] = other.buf[i];
        }
    }

    // Move constructor
    buffer(buffer&& other) = default; // Instructs the compiler to use the default move constructor

    // Copy Assignment
    buffer& operator=(const buffer& other)
    {
        for (int i = 0; i != N; ++i) {
            buf[i] = other.buf[i];
        }
        return *this;
    }

    // Move Assignment
    buffer& operator=(buffer&& other) = default;

    // We  now just return the non-type template argument for the size.
    int size() const
    {
        return N;
    }
    
    // Allow for access to the internals of the buffer.
    T& operator[](int n)
    {
        return buf[n];
    }
    // We need to overload on const to allow for this method to work on const buffers as well.
    const T& operator[](int n) const
    {
        return buf[n];
    }
    
    //We will define "buffer addition" in terms of element wise addition.
    buffer& operator+=(const buffer& other)
    {
        for (int i = 0; i != N; ++i) {
            buf[i] += other[i];
        }
        return *this;
    }

    buffer& operator-=(const buffer& other)
    {
        for (int i = 0; i != N; ++i) {
            buf[i] -= other[i];
        }
        return *this;
    }

private:
    // We just need to modify make all elements in the class to refer to T and to N.
    T buf[N];
};

// The inline keyword "kindly" asks the compiler to remove the function call overhead and just insert the function
// body whenever the function is called. 
// Note all functions defined inside the class body have the inline specifier by default so that is why 
// we do not need to add inline there.
template<typename T, int N>
inline
buffer<T,N> operator+(const buffer<T,N>& x, const buffer<T,N>& y)
{
    buffer<T,N> ret = x;
    ret += y;
    return ret;
}

// Note: Outside of the class definition, we must use redeclare the template parameters.
// Also, all occurences of buffer must be to buffer<T, N> and  not to just buffer as in the class definition 
template<typename T, int N>
inline
buffer<T, N> operator-(const buffer<T,N>& x, const buffer<T,N>& y)
{
    buffer<T, N> ret = x;
    ret -= y;
    return ret;
}

/*  // Get n-th element of a buffer. More specific but it does not offer any benefit.
    // we can just use the more general version bellow.
template<int M, typename T, int N>
T& get(buffer<T, N>& b)
{
    return b[M];
} */

// Get n-th element from a container.
template<int M, typename C>
// requires Container<C>{}  // Next time we will see what the container concept actually is.
inline                      // For now, we just consider it intuitively as something that holds stuff.
Value_type<C>& get(C& c)    // Also, a nice example of using the type function from above.
{                           
    return c[M];
}

// Get n-th element from a const container.
template<int M, typename C>
// requires Container<C>{} 
inline
const Value_type<C>& get(const C& c)    
{                           
    return c[M];
}

// We pass a ostream object (cout has a type inheriting from it) so that we do not depend on a particular output.
template<typename T, int N>
// requires Streamable<T>{}
std::ostream& print_buffer(std::ostream& out, const buffer<T, N>& b)
{
    for (int i = 0; i != b.size(); ++i) {
        out << b[i] << ' ';
    }
    out << '\n';
    return out;
}

// Put to stream operator
template<typename T, int N>
// requires Streamable<T>{}
std::ostream& operator<<(std::ostream& out, const buffer<T, N>& b)
{
    return print_buffer(out, b);
} 

#endif // !BUFFER_GENERIC_PROGRAMMING
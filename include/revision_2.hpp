#ifndef REVISION_2_GENERIC_PROGRAMMING
#define REVISION_2_GENERIC_PROGRAMMING

#include <string>
#include <cctype>
#include <iostream>

using namespace std;

// Test functions

void test_function_objects();

void test_compare();

/// Function templates

// Function template generalize algorithms based on types (actually, they are generic algorithms).
// Inside the function body T names some type. We can use it like any other type. We can  create
// objects of that type or apply operations on values of type T (if any of them are supported).
// This is a simple comparison function. See test_compare function in revision.cpp for usage. 
template<typename T>
// requires Comparable<T>{}             // This will be how we "say" that a type must model a concept 
int compare(const T& x, const T& y)     // (see presentation for definition of concept and model).
{                                       // The reason we will do this is that concepts might become a core language 
    if (x < y) {                        // feature in C++ 17 so it would be nice to do what might be in the future
        return 1;
    }
    else if (x > y) {
        return -1;
    }
    else {
        return 0;
    }
}


/// Class templates
// The same way we can parametrize functions based on type, we can parametrize classes or structs.
// Once again, the types we use in the template clause are valid for the entire class/struct body.
// Note that we can have as many parameterized types as we want. 
// This is an example of an object holding two objects of arbitrary types
template<typename T, typename U>
struct simple_pair {
    // This is a called type alias or an associated type. We can use the scope resolution operator (::) to access this
    // type alias for any simple_pair object. See the test_simple_pair function in revision_2.cpp for an example
    // if how to use it. Type aliases are essentially type functions - they take in some type T and give you
    // some other type U that is in effect connected to U. See the introductory presentation for some intuition.
    // In the following lectures we will see a lot more of these type aliases.
    // In per C++ 11, programmers used the keyword typedef which has similar usage, though it is not as flexible, and
    // it has different syntax.
    using first_type = T;
    using second_type = U;

    T first;
    U second;
};

void test_pair();

#endif // !REVISION_2_GENERIC_PROGRAMMING
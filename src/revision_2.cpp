#include "revision_2.hpp"

#include <iostream>

using namespace std;

/// Callable objects in C++
// 1) Free Functions
// 2) Member functions
// 3) Classes/structs overloading the () operator

// Defining a function object is very simple. We just need to overload the function call
// operator, also known as (). Here are several examples:
// A simple function object imitating a function.
struct abs_int {
    int operator()(int a) const
    {
        return a < 0 ? -a : a;
    }
};

// A function object can be useful when you need to store some state. 
// Store a number at construction and then use that number to compare
// integers passed to it later.
struct less_than_n {
    int n;
    less_than_n(int m) : n{n} {}
    bool operator()(int a) const
    {
        return a < n;
    }
};

// Unlike the other ordinary operators, the function call operator can take in an arbitrary
// number of operators.
// Square three numbers and add them together.
struct square_add_3 {
    int operator()(int a, int b, int c) const
    {
        return (a*a + b*b + c*c);
    }
};

// Test function objects
void test_function_objects()
{
    // We need to create instances of the function objects (like normal objects) to use them.
    abs_int f;
    int a = -10;
    int b = 20;
    cout << f(a) << " " << f(b) << "\n\n";

    less_than_n g { 1 };
    cout << g(a) << " " << g(b) << "\n\n";

    square_add_3 h {};
    cout << h(a, b, a) << "\n\n";
}

// See the revision_2.hpp file for the compare file.
void test_compare()
{
    int a = 1;
    int b = 2;
    string s1 = "Foo";
    string s2 = "Genreric";
    // We need not explicitly specify the types used for the function. However, we can do so if we want to.
    // Still, it usually better to let the compiler deduce them for us unless it possibly cannot or there is some ambiguity.
    cout << compare(a, b) << " " << compare<string>(s2, s1) << "\n\n";
}

// See the revision_2.hpp file for the compare file.
void test_pair()
{
    int a = 0;
    double b = 10.5;
    simple_pair<int, double> p1 { a, b };
    // const char* are implicitly converted to strings because of the pair's member types.
    simple_pair<string, string> p2 { "asdf", "sadfasdf" };
    cout << p1.first << " " << p1.second << " " << p2.first << " " << p2.second << "\n\n";

    // Usage of type aliases
    // This essentially creates an int.
    // Same as: int c = 1;
    simple_pair<int, double>::first_type c = 1;
    // This might not seem helpful at all here but consider if we are given a some type C which we know
    // nothing about (could be a pair, a triple or something else) except that it has an associated type called first_type
    // Then this associate type becomes really useful because there is no other way to create an object of the first type.
    // Example. Note the using keyword can be used to simply name some type so that it has a shorter name.
    using pair_type = simple_pair<int, double>;
    pair_type::first_type d = 2;
    pair_type::second_type e = 3.4;
    pair_type p3 { d, e };
    cout << p3.first << " " << p3.second << "\n\n";
}


/// Value types

// These are the first "official" concepts that we will discuss. We actually use them all over the place
// whenever we code. The problem is that usually, the algorithms or procedures we write usually need
// value types to work properly but we forget to make sure our own types behave as such. Actually, value types
// are really intuitive but just need to keep them at the back of our head and not forget about them.

// Bellow, are the descriptions for three important concepts of what we think of value types.

///  Definition of the concept SemiRegular
// T models the concept SemiRegular if it has the following operations defined on it.
/*
    Default constructor T a;
    Copy constructor T a = b;
    Destructor ~T(a);
    Assignment a = b;
*/

///  Definition of the concept Regular
// T models the concept Regular if it has the following operations defined on it.
/*
    T is SemiRegular
    Equality a == b
    Inequality a != b
*/

///  Definition of the concept TotallyOrdered
// T models the concept TotallyOrdered if it has the following operations defined on it.
/*
    T is Regular
    Ordering: a < b, a > b, a <= b, a >= b
*/

/// Axioms for regular types
/*
    (1) T a = b; assert(a==b);
    // Whenever we copy construct a from b, a and b have to be equal.

    (2) T a; a = b <==> T a = b;
    // Default constructing a and then assigning b to it is equivalent to copy constructing a from b.

    (3) T a = c; T b = c; a = d; assert(b==c);
    // If we copy constructing a from c and copy constructing b from c and then we assign some d to a,
    // then b is still equal to c no matter what d is (i.e. a and b are separate).

    (4) T a = c; T b = c; zap(a); assert(b==c && a!=b);
    // If we copy constructing a from c and copy constructing b from c and then we apply some function zap
    // which always changes the value of its argument, then b is still equal to c and a is not anymore equal to b.
    // (because zap has certainly modified the value of a in some way)
*/
 
/// Wise Guidelines
// Working with value types (be they semi-regular, regular or totally ordered) is actually quite pleasant.
// You always know what to expect for certain operations. These concepts also immensely simplify writing
// generic containers and algorithms. You need not worry about modifying other arguments when creating local copies,
// you can default construct objects and then assign values based on conditions and other control flow.
// Also without the notion of equality and/or ordering many useful algorithms and even data structures become
// unusable. As a general rule (pun intended), try to develop your objects to be at the very least semi regular.
// If equality makes sense or is not computationally too expensive, make it a regular type. If ordering is also
// meaningful (be it lexicographical or some other), implement it as well to make your type model the TotallyOrdered
// concept. Of course, all of these operations should make sense.

// What follow are some examples where the type T better be semi-regular for the first example and 
// be totally ordered for the second one for the algorithm to be well defined. The reasons go deeper than mere
// definition of the operators. The regular type axioms are really important as well.

template<typename T>
T sum(T* a, int n)
{
    // We need default construction.
    T s {};
    while (n != 0) {
        // T should model a more complicated type but we will not deal with this for now.
        s += *a;
        ++a;
    }
    // In order to return from the function, we need to copy the type T.
    // It better be at least a regular type or summing over T-s would not make much sense,
    return s;
}

template<typename T>
void zap(T& a)
{
    // Something which modifies a in some  way.
}

template<typename T>
T take_larger_and_modify(const T& x, const T& y)
{
    // We need to default construct in order to simplify our code.
    // Otherwise it is unwieldy and awkward. We would have to repeat the end of the
    // function inside each scope of the if-else statement.
    T z {};
    if (x < y) {
        // We need copy assignment. This better be equal to simply copy construction.
        z = y;
    }
    else {
        // Same as above
        z = x;
    }
    // For sure, zap(x) must not modify x or y in some strange, indirect way because
    // the caller would not like having his values modified when he passed them by const reference.
    zap(z);
    // We need to copy to return the change value.
    return z;
}














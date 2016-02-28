// This is an include guard. It is the most widely used method to protect against including
// the same files (more importantly declarations) several time. You can also use #pragma once in VS
// but that is not portable to other compilers. (Still it is worthwhile to also add that add the top of each
// file in VS project since it might decrease compilation time).
#ifndef REVISION_GENERIC_PROGRAMMING
#define REVISION_GENERIC_PROGRAMMING

#include <iostream>

// In header files we place (what follows is an almost exhaustive list):
// type definitions, function declarations, named namespaces, 
// template declarations and definitions, inline function definitions,
// enumerations, data declarations, type aliases, named declarations and include directives
// (plus some other not that important things for us)
// On the other side, we should never place ordinary function definitions (they go in .cpp files),
// data definitions (like global variable), aggregate definitions (same as before but think of global arrays),
// unnamed namespaces and using-directives.


/// Default Constructor, Copy Constructor, Copy Assignment Operator, 
/// Move Constructor, Move Assignment Operator, Destructor
class int_element {
public:
    int_element();
    int_element(int el);
    int_element(const int_element& e);
    int_element(int_element&& e);
    int_element& operator=(const int_element& e);
    int_element& operator=(int_element&& e);
    int& acquire();
    const int& acquire() const;
private:
    int el;
};

/// Operator Overloading
// In C++ we can overload almost all of the operators for use by our types.
// We can do so either inside or outside a class.
struct color_rgba {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;

    // It is better to define operators if the type $= (where is +,-,*, etc.) as members since
    // the left hand of the operator is bound to the current object
    // and by convention these operators modify the state of the object.
    color_rgba& operator+=(const color_rgba& c);
    color_rgba& operator-=(const color_rgba& c);
    color_rgba& operator*= (float s);
};

// Free functions involving color_rgba.

color_rgba make_color_rgba(unsigned char red, unsigned char green,
                           unsigned char blue, unsigned char alpha = 255);   // This is an example of default function arguments

std::ostream& print(std::ostream& out, const color_rgba& c);

// Overloaded operator declarations.

color_rgba operator+(const color_rgba& c1, const color_rgba& c2);

color_rgba operator-(const color_rgba& c1, const color_rgba& c2);

color_rgba operator*(float s, const color_rgba& c);

color_rgba operator*(const color_rgba& c, float s);

std::ostream& operator<<(std::ostream& out, const color_rgba& c);

#endif // !REVISION_GENERIC_PROGRAMMING
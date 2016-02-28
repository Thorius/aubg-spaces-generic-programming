/// Generic Programming Act 2
/// Overview or C++ Techniques for Generic Programming

// Always add your includes at the top (don't be like me on Wednesday)
// Also, by convention, always begin with the *.h/*.hpp twin for this *.cpp file 
// then add standard headers (<string>, <iostream>, etc.),
// and then add other headers like library ones or your own.
#include "revision.hpp"														 
#include <iostream>

// Better to not use using directives but in *.cpp files it is not all that bad.
// However, in *.h/*.hpp never do so!
using namespace std;
// Using declarations are better since they bring only specific names into scope
// For example this bring in just std::cout into scope. (in this case it is redundant
// because of the above directive).
using std::cout;

/// So, why use C++ for generic programming?
// C++ was one of the first languages to support generic programming and it is still one of the few
// languages to do so without an abstraction penalty. It is still far from being the "ultimate" 
// generic programming language (though it is mostly better than others) mainly because it offers
// very little safety when instantiating templates.

/// Types
/// Classes and structs
// The mechanism for defining user defined types is with the keywords struct or class.
// struct -> all members implicitly public
// class  -> all members implicitly private

// The simplest type
struct empty_element { };

/// Function declarations and definitions
// Function declaration,
void some_function();
// Function definition
void some_other_function()
{
    std::cout << "some_other_function\n";
    some_function();
}
// All declared functions must be eventually defined.
void some_function()
{
    std::cout << "some_function\n";
}

/// Passing function arguments
// When passing small objects (say around the size of several floats) pass by value (i.e. copy them).
int function_by_value(int a, int b)
{
    return a + b;
}

struct my_insanely_big_struct {
    static constexpr int array_size = 100000;
    int that_array[array_size];
};

// When passing medium sized or large objects, pass by const reference if you are not going to modify them.
my_insanely_big_struct function_by_const_reference(const my_insanely_big_struct& a, const my_insanely_big_struct& b)
{
    my_insanely_big_struct ret{};
    for (int i = 0; i < my_insanely_big_struct::array_size; ++i) {
        ret.that_array[i] = a.that_array[i] + b.that_array[i];
    }
    return ret;
}

// If you are going to be modifying the arguments to a function and want to see that effect outside of the function
// you should pass by reference
void function_by_reference(my_insanely_big_struct& a)
{
    for (int i = 0; i < my_insanely_big_struct::array_size; ++i) {
        a.that_array[i] = i;
    }
}

// Still, by default, pass by const reference.

/// Values and references
// Remember, C++ is a value centered language. Copying an objects means copying all of its internals.
// References and pointers to objects must be explicitly provided
void values_and_references()
{
    // Value (created on the stack)
    empty_element e1;
    // Reference to e1 (cannot be null or not referring to something)
    empty_element& e2_r = e1;
    // Pointer to e1 (can be null).
    empty_element* e3_p = &e1;
}
// Tip: prefer always use references unless null is valid state, the pointer needs to pointed somewhere else or
// you need default construction.

/// The const keyword
// This keyword is essentially a promise to the compiler that you will not change 
// a certain value (or call non const methods). The compiler will get angry at you and 
// insult you using all kinds of errors (ok, maybe just two or three kinds of errors) 
// if you do not keep your word.
void const_keyword()
{
    // Modifiable
    int a = 10;
    // Constant int
    const int b = 10;
    // Fine
    a = 20;
    // Error
    // b = 20;
    
    // Same holds for references to const
    const int& cr = a;
    // Cannot modify a through cr.
    // Error
    // cr = 200; 
    
    // Example of a local class
    struct some_struct {
        int a;
        some_struct(): a{} {}
        // This function can be used only on non-const objects.
        void func_1() {}
        // This function can be used on both const and non-const objects
        void func_2() const {}
    };
    some_struct ss;
    const some_struct css;
    // Fine
    ss.func_1();
    // Error
    //css.func_1();
    // Fine
    ss.func_2();
    // Fine
    ss.func_2();
}

/// Default Constructor, Copy Constructor, Copy Assignment Operator,
///  Move Constructor, Move Assignment Operator, Destructor

// Default constructor
int_element::int_element()
    : el {}		// If a normal constructor is provided you must declare a default constructor
{}

// Normal constructor
int_element::int_element(int el)	// Outside the curly braces there is no name clash with member variables
    : el { el }		// This is an initializer list. It initializes member elements before entering the constructor body
{}

// Copy constructor
int_element::int_element(const int_element& e)
    : el { e.el }
{}
    
// Move constructor
int_element::int_element(int_element&& e) // "Steal" the internal representation of the moved from element. In this case it is not
    : el { e.el }			 // useful at all but you can read more about it or ask me about it.
{}

// Copy Assignment Operator
int_element& int_element::operator=(const int_element& e) // Similar in idea to the copy constructor but called on created objects.
{
    el = e.el;
    return *this;
}

// Move Assignment Operator
int_element& int_element::operator=(int_element&& e) // Similar in idea to the move constructor but called on created objects.
{
    el = e.el;
    return *this;
}

// Both a "getter" and "setter"
int& int_element::acquire()
{
    return el;
}

// We need to overload on const to allow for this member function to be called on const int_element objects. 
const int& int_element::acquire() const
{
    return el;
}


/// Operator Overloading
// In C++ we can overload almost all of the operators for use by our types.
// We can do so either inside or outside a class.

// NOTE: Let us make the design decision to not change alpha in the operators.
// Alpha will only be set manually

// It is better to define operators if the type $= (where is +,-,*, etc.) as members since
// the left hand of the operator is bound to the current object
// and by convention these operators modify the state of the object.
color_rgba& color_rgba::operator+=(const color_rgba& c)
{
    // We need to convert to an integer in order to check and prevent overflow.
    int red = r + c.r;
    int green = g + c.g;
    int blue = b + c.b;
    if (red > 255)
        red = 255;
    if (blue > 255)
        blue = 255;
    if (green > 255)
        green = 255;
    r = red; g = green; b = blue;
    // 'this' is a pointer to the enclosing object. We need to dereference it in order to return a reference.
    return *this;
}
color_rgba& color_rgba::operator-=(const color_rgba& c)
{
    // Same as the += operator but this time we need to check the lower bound for char.
    int red = r - c.r;
    int green = g - c.g;
    int blue = b - c.b;
    if (red < 0)
        red = 0;
    if (blue < 0)
        blue = 0;
    if (green < 0)
        green = 0;
    r = red; g = green; b = blue;
    return *this;
}
color_rgba& color_rgba::operator*=(float s)
{
    // Check if the value provided is negative and convert it to positive (one possible handling)
    if (s < 0.0f)
        s = -s;
    // We need an int (a bigger type) to check for possible overflow.
    int c_vals[3];
    // Ignore possible loss of float data.
    c_vals[0] = r * s;
    c_vals[1] = g * s;
    c_vals[2] = b * s;
    // An example of a for each loop in C++ 11. (I just wanted to show it off here.
    for (int& val : c_vals) {
        // Bound the maximal growth and/or decay of the color
        if (val > 255) {
            val = 255;
        }
        else if (val < 0) {
            val = 0;
        }
    }
    r = c_vals[0];
    g = c_vals[1];
    b = c_vals[2];

    return *this;
}

// It is usually better to define symmetric operators outside of structs or classes in order to allow for conversion.
// In addition, it makes more sense and it looks better. Can't argue with that!
color_rgba operator+(const color_rgba& c1, const color_rgba& c2)
{
    // Try to define operators in terms of other operators if possible
    color_rgba ret = c1;
    ret += c2;
    return ret;
}
color_rgba operator-(const color_rgba& c1, const color_rgba& c2)
{
    // Try to define operators in terms of other operators if possible
    color_rgba ret = c1;
    ret -= c2;
    return ret;
}
color_rgba operator*(float s, const color_rgba& c)
{
    // Try to define operators in terms of other operators if possible
    color_rgba ret = c;
    ret *= s;
    return ret;
}
color_rgba operator*(const color_rgba& c, float s)
{
    // Use the operator above to make this definition even easier.
    return (s * c);
}

// A simple factory function for the color class. We will use functions like this a lot when writing containers
// and generic wrappers.
color_rgba make_color_rgba(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha){
    // This uses C++ 11 initializes syntax. Essentially, what it does it assigns the corresponding
    // values to the values inside the struct (note: names are not important, the way the data members are ordered is).
    return {red, green, blue, alpha};
}

// A regular free function definition for printing colors. (We can use it later for overloading the << operator).
std::ostream& print(std::ostream& out, const color_rgba& c)
{
    // We need to convert the unsigned chars to integers in order to display them.
    // In order to do this we use the operation static_cast. We could use a simpler cast but it is
    // a good idea to get into the habit of not using C-style or function style casts.
    return out  << "Red: " << static_cast<int>(c.r)
                << " Green: " << static_cast<int>(c.g)
                << " Blue: " << static_cast<int>(c.b)
                << " Alpha: " << static_cast<int>(c.a) << '\n';
}


// This is a typical implementation for overloading an output operator for a user type.
// You should take two arguments: one reference to an ostream object and an user defined type (usually by const reference)
// You should also return the passed ostream object by reference  in order to allow for operator chaining.
std::ostream& operator<<(std::ostream& out, const color_rgba& c)
{
    // Use the free function above.
    return print(out, c);
}
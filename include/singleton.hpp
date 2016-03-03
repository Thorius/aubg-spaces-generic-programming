#ifndef SINGLETON_GENERIC_PROGRAMMING
#define SINGLETON_GENERIC_PROGRAMMING

template <typename T>
// requires SemiRegular<T> || Regular<T> || TotallyOrdered<T>
struct singleton {
    using value_type = T;
    T value;
    // Conversions from T and to T.
    // We have not considered conversion operators but these are essentially it.
    // The conversion: T -> singleton<T> is done through a constructor.
    // Explicit means that we have to explicitly call the constructor (by name) to invoke it.
    // We will remove it to allow to implicit conversions between type. See mai.cpp for and example.
    // explicit
    singleton(const T& x) : value(x) {}
    // The conversion singleton<T> -> T is done through a conversion operator.
    // What you do is just write operator and the name of the type you want to convert to.
    // explicit
    operator T() const
    { 
        return value; 
    }
    // This is a template function inside a template class. It is well defined for all types U
    // such that U is convertible to T
    template <typename U>
    singleton(const singleton<U>& x) : value(x.value) {}

    // What follow are requirement for singleton<T> being semi-regular.
    // Default constructor, copy constructor, move constructor, 
    // copy assignment operator, move assignment operator and  destructor.
    // All of them can be implicitly defined so we just use the = default keyword.
    singleton() = default;
    singleton(const singleton& x) = default;
    singleton(singleton&& x) = default;
    singleton& operator=(const singleton& x) = default;
    singleton& operator=(singleton&& x) = default;
    ~singleton() = default;
    
    // What follow are requirement for singleton<T> being regular.
    // We define the functions as friends so as not to define them outside the class and
    // to still be free functions.
    friend
    bool operator==(const singleton& x, const singleton& y)
    {
        return x.value == y.value;
    }
    friend
    bool operator!=(const singleton& x, const singleton& y)
    {
        // Remember, define functions in terms of others if possible.
        return !(x == y);
    }
    // What follow are requirement for singleton<T> being totally-ordered.
    // Same as before.
    friend
    bool operator<(const singleton& x, const singleton& y)
    {
        return x.value < y.value;
    }
    friend
        bool operator>(const singleton& x, const singleton& y)
    {
        return y < x;
    }
    friend
        bool operator<=(const singleton& x, const singleton& y)
    {
        return !(y < x);
    }
    friend
        bool operator>=(const singleton& x, const singleton& y)
    {
        return !(x < y);
    }
};

#endif // !SINGLETON_GENERIC_PROGRAMMING


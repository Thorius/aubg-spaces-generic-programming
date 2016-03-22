#ifndef CIRCULAR_BUFFER_GENERIC_PROGRAMMING
#define CIRCULAR_BUFFER_GENERIC_PROGRAMMING

#include <cstddef>
#include <limits>
#include <iostream>
#include <utility>

/// STL Complaint Circular Buffer.
/// The idea is to have an array that mimics an array that loops around on itself, thus leaving the impression
/// that we can indefinitely add elements to it. See https://en.wikipedia.org/wiki/Circular_buffer for more info.
/// Of course we will eventually override old elements as there is no
/// such thing as indefinite storage. We will see uses of this later on.
/// For now our goal is to create a type that models the container concept. In short, a container is something that 
/// "contains" other things. One important thing is that the container owns its elements so when it is destroyed, all
/// of the elements contained in it should also be destroyed. For more info on the container concept see the this
/// link: https://www.sgi.com/tech/stl/Container.html. (This cite is also a good reference for generic programming 
/// since it has the original justification and concept definitions for the initial version of the STL.)

/// For now, the bellow implementation lacks some important parts in order top be qualified to be a container
/// (namely iterators) but we will fix this later on.

template<typename T>
// requires SemiRegular<T>{}
class circular_buffer {
public:
    // Associated types for the circular buffer. For now only value_type is really important but the
    // others are convenient. Later on, the iterator type will also be important. 
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
public:
    // We define several constructors bellow.
    circular_buffer()
        : array_(nullptr), array_size_(0),
        head_(0), tail_(0), contents_size_(0)
    {}

    explicit circular_buffer(std::size_t capacity)
        : array_(new T[capacity]), array_size_(capacity),
        head_(0), tail_(capacity), contents_size_(0)
    {}

    // The copy constructor and assignment operator are necessary for keeping the invariant of container.
    circular_buffer(const circular_buffer& other)
        : array_(new T[other.array_size_]), array_size_(other.array_size_),
        head_(other.head_), tail_(other.tail_), contents_size_(other.contents_size_)
    {
        // We need to perform a deep copy. In order to do this we have to copy each element in the underlying buffer
        for (size_type i = 0; i != other.size(); ++i) {
            this->operator[](i) = other[i];
        }
        // Once we implement iterators this will simplify immensely.
    }
    circular_buffer& operator=(const circular_buffer& other)
    {
        // We will use an interesting C++ idiom for the copy assignment operator - Copy and Swap
        // First create a temporary circular buffer with the contents of other.
        circular_buffer temp(other);
        // Then swap the contents of the temporary with those of the buffer that we are assigning to,
        this->swap(temp);
        // Lastly return the newly assigned object.
        return *this;
    }

    // This function essentially swaps the internal state of the two buffers.
    void swap(circular_buffer& other)
    {
        // We want to use the standard swap (no need to define out own for this).
        using std::swap;
        swap(this->array_, other.array_);
        swap(this->array_size_, other.array_size_);
        swap(this->head_, other.head_);
        swap(this->tail_, other.tail_);
        swap(this->contents_size_, other.contents_size_);
    }

    // Obviously, we must free all of the resources we are in control of.
    // In C++, a destructor is essential for the invariant of the class if the class contains resources.
    // See the idiom RAII on-line for more information on this.
    ~circular_buffer()
    {
        delete[] array_;
    }
    
    // Bellow are methods for accessing or modifying the container.
    // We will use a new syntax for expressing preconditions and postconditions:
    // [[expects: (boolean expression)]] for preconditions and
    // [[assures: (boolean expression)]] for postconditions.

    reference front() // [[expects: !empty()]]
    {
        return array_[head_];
    }
    reference back() // [[expects: !empty()]]
    {
        return array_[tail_ - 1];
    }
    const_reference front() const // [[expects: !empty()]]
    {
        return array_[head_];
    }
    const_reference back() const // [[expects: !empty()]]
    {
        return array_[tail_ - 1];
    }
    // A method that simply resets the buffer state
    void clear() // [[assures: empty()]]
    {
        head_ = contents_size_ = 0;
        tail_ = capacity();
    }
    // A method to get the underlying array pointer if needed.
    const_pointer data()
    {
        return array_;
    }
    // This method allocates a new array if needed (through reserve) and then makes the container have the specified number of elements.
    void resize(size_type n, const_reference val) // [[assures: size() == n]]
    {
        // We need to first check if the capacity of the circular buffer is large enough
        // to hold the requested number of elements.
        if (n > capacity()) {
            reserve(n);
        }
        // We now check if we need to add  or remove elements.
        if (size() < n) {
            size_type k = n - size();
            push_back_n(k, val);
        }
        else {
            size_type k = size() - n;
            pop_front_n(k);
        }
    }
    // Same but uses a default constructed element for the resizing
    void resize(size_type n) // [[assures: size() == n]]
    {
        resize(n, value_type {});
    }

    // This method allocates a new array with the specified storage size
    void reserve(size_type n) // [[assures: capacity() == n]]
    {
        // Only take actions when there is less capacity.
        if (n > capacity()) {
            // Allocate the memory first;
            pointer temp_buffer = new value_type[n];
            // Copy the valid elements of the circular buffer to the new memory.
            // We do not care for elements that are outside the range [head, tail)
            for (size_type i = 0; i < size(); ++i) {
                // Of course, we will use the functions we have already defined.
                temp_buffer[i] = this->operator[](i);
            }
            // We need to swap the old buffer with the new one and then free the old memory.
            std::swap(temp_buffer, array_);
            // We need to change the head_ and the tail_ indexes since we have copied the
            // all elements to the beginning of a new allocated array.
            head_ = 0;
            tail_ = size();
            array_size_ = n;
            delete[] temp_buffer;
        }
    }
    
    // The main method to add new elements to the circular_buffer.
    void push_back(const_reference val) // [[assures: !empty()]]
    {
        // We increment the tail to point to one past the end element.
        increment_tail();
        // Then we assign the element to the one before where tail points to.
        array_[tail_ - 1] = val;
        // We will override the first element in case we "overflow".
        if (size() > capacity()) {
            increment_head();
        }
        // Assign the next item to the incremented tail.
    }
    // The main method to remove elements from the circular_buffer.
    void pop_front() // [[expects: !empty()]]
    {
        increment_head();
    }
    // Helper method to insert at the back of the circular_buffer.
    // Semantically equivalent to calling push_back k times, but it is more efficient.
    void push_back_n(size_type n, const_reference val) // [[assures: !empty()]]
    {
        size_type old_size = size();
        increment_tail(n);
        for (size_type i = old_size; i < size(); ++i) {
            this->operator[](i) = val;
        }
        int diff = size() - capacity();
        //if (size() > capacity()) {
        if (diff > 0) {
            increment_head(diff);
        }
    }
    void pop_front_n(size_type n) // [[expects: size() - n >= 0]]
    {
        increment_head(n);
    }

    // Simple methods that all containers should have. All of them are self explanatory
    size_type size() const
    {
        return contents_size_;
    }
    size_type capacity() const
    {
        return array_size_;
    }
    bool empty() const
    {
        return contents_size_ == 0;
    }
    size_type max_size() const
    {
        return std::numeric_limits<size_type>::max();
    }

    // Random access operators. Not the main purpose of the class (as they are not as efficient as those on arrays)
    // but they are useful for the containers own methods (example: copy constructor) and may be sometimes useful for client code.
    reference operator[](size_type i) // [[expects: i < size()]]
    {
        // To index into the circular buffer we essentially add the head_value
        // and the passed index to the function and we loop around if necessary
        size_type index = (head_ + i);
        while (index >= array_size_) {
            index = index - array_size_;
        }
        return array_[index];
    }
    const_reference operator[](size_type i) const // [[expects: i < size()]]
    {
        size_type index = head_ + i;
        while (index >= array_size_) {
            index = index - array_size_;
        }
        return array_[index];
    }

private:
    // Helper methods for keeping the containers invariants

    void increment_tail() // [[expects: size() != capacity()]]
    {
        ++tail_;
        ++contents_size_;
        // Loop back only if the tail_ has an index bigger that the size
        if (tail_ > capacity()) {
            tail_ = 1;
        }
    }
    void increment_head() // [[expects: !empty()]]
    {
        ++head_;
        --contents_size_;
        // Head loops differently since it points to the first element of the sequence.
        if (head_ == capacity()) {
            head_ = 0;
        }
    }

    // Helper methods for the multi insert/delete methods.

    void increment_tail(size_type k) // [[expects: size() + k <= capacity()]]
    {
        tail_ += k;
        contents_size_ += k;
        // The semantics of the test are similar to the increment_tail with no arguments. 
        if (tail_ > capacity()) {
            tail_ -= capacity();
        }
    }
    void increment_head(size_type k) // [[expects: size() - k  >= 0]]
    {
        head_ += k;
        contents_size_ -= k;
        // The semantics of the test are similar to the increment_tail with no arguments. 
        if (head_ >= capacity()) {
            head_ -= capacity();
        }
    }
    
    // Internal data for the circular_buffer

    // A pointer to the underlying elements.
    value_type* array_;
    // The size of the underlying array.
    size_type  array_size_;
    // The index of the first element.
    size_type  head_;
    // One past the last element.
    size_type  tail_;
    // Number of (valid) elements stored in the buffer. 
    size_type  contents_size_;
};


// Output operator for the circular_buffer class
template<typename T>
std::ostream& operator<<(std::ostream& out, const circular_buffer<T>& buf)
{
    typename circular_buffer<T>::size_type curr {};
    typename circular_buffer<T>::size_type size = buf.size();
    while (curr < size) {
        out << buf[curr] << ", ";
        ++curr;
    }
    out << '\n';
    return out;
}


/// Steps for creating an STL complaint iterator
//  1) Setup associated types.
//  2) Provide appropriate constructors.
//  3) Refine to regular type.
//  4) Refine to trivial iterator.
//     Provide element access: dereference, member access.
//  5) Refine to input iterator.
//     Provide post and pre increment.
//  6) Refine to bidirectional iterator.
//     Provide post and pre decrement.
//  7) Refine to random access iterator.
//     Provide arithmetic operators with the difference type
//     along with some other utility functions.
//  8) Return to the circular buffer class and provide factory functions
//     for the begin and end of the container.



class circular_buffer_iterator {
public:
    
public:
    

};


#endif //!CIRCULAR_BUFFER_GENERIC_PROGRAMMING